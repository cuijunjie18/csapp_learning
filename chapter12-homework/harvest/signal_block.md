“**信号阻塞**”（Signal Blocking）是 Unix/Linux 信号机制中的一个重要概念，它指的是 **暂时阻止某个信号被递送给进程**，即使该信号已经被发送或产生。

---

## 🌟 一、基本概念

### ✅ 什么是信号递送（Delivery）？
当一个信号被发送给进程（如 `kill()`、硬件异常、`SIGCHLD` 等），它不会立即被处理。操作系统会先将信号**挂起（pending）**，等到合适的时机再“递送”给进程。

信号递送的时机通常是：
- 进程从内核态返回用户态时
- 当前没有被阻塞

---

### ✅ 什么是信号阻塞？
- **信号阻塞 = 暂时不接收某个信号**
- 被阻塞的信号不会被递送，但可以处于“**挂起（pending）**”状态
- 一旦解除阻塞，如果信号仍处于挂起状态，就会立即被递送

> 🔔 类比：你手机开了“勿扰模式”，别人给你打电话 → 电话不会响（被阻塞），但未接来电会保留（pending），等你关闭勿扰后，可能会收到通知。

---

## 🧱 二、信号的三种状态

| 状态 | 说明 |
|------|------|
| **Generated** | 信号产生（如调用 `kill()`、除零错误） |
| **Pending**   | 信号已生成但尚未递送（可能因为被阻塞） |
| **Delivered** | 信号被递送给进程并处理（执行 handler 或默认动作） |

📌 只有当信号**未被阻塞**时，才能从 “pending” 变成 “delivered”。

---

## 🛠 三、如何阻塞信号？

使用 `sigprocmask()` 系统调用可以修改进程的**信号掩码（signal mask）**，即当前被阻塞的信号集合。

### 函数原型：
```c
#include <signal.h>

int sigprocmask(int how, const sigset_t *set, sigset_t *oldset);
```

### 参数说明：

| 参数 | 作用 |
|------|------|
| `how` | 操作方式：`SIG_BLOCK`, `SIG_UNBLOCK`, `SIG_SETMASK` |
| `set` | 要操作的信号集合 |
| `oldset` | 保存原来的信号掩码（可选） |

### 常见操作：

```c
sigset_t set, oldset;

// 1. 添加某些信号到阻塞集合
sigemptyset(&set);
sigaddset(&set, SIGINT);
sigprocmask(SIG_BLOCK, &set, &oldset);

// ... 此时 SIGINT 被阻塞 ...

// 2. 解除阻塞
sigprocmask(SIG_UNBLOCK, &set, NULL);
```

---

## 🧪 四、举个例子

```c
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void handler(int sig) {
    printf("收到 SIGINT！\n");
}

int main() {
    signal(SIGINT, handler);

    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGINT);

    // 阻塞 SIGINT
    sigprocmask(SIG_BLOCK, &set, NULL);
    printf("SIGINT 已阻塞。尝试按 Ctrl+C...\n");
    sleep(5);  // 在这期间按 Ctrl+C 不会触发 handler

    // 解除阻塞
    sigprocmask(SIG_UNBLOCK, &set, NULL);
    printf("SIGINT 已解除阻塞。现在可以按 Ctrl+C 触发了。\n");
    sleep(5);

    return 0;
}
```

📌 运行时：
- 前 5 秒按 `Ctrl+C`：无反应（信号被阻塞，处于 pending 状态）
- 后 5 秒按 `Ctrl+C`：立即打印“收到 SIGINT！”

> ⚠️ 注意：如果在阻塞期间多次发送信号，**对于大多数普通信号（如 SIGINT），只会记录一次 pending**（不排队）。实时信号例外。

---

## 📌 五、信号阻塞 vs 忽略 vs 捕获

| 操作 | 行为 |
|------|------|
| **阻塞（Block）** | 信号暂时不递送，可挂起，后续可处理 |
| **忽略（Ignore）** | 信号被丢弃，永远不处理（除非是 `SIGKILL`/`SIGSTOP`） |
| **捕获（Catch）** | 设置 handler，信号递送时执行自定义函数 |

> ❗ 阻塞 ≠ 忽略。阻塞的信号可以 later 被处理；忽略的信号直接丢弃。

---

## 🛡 六、为什么需要信号阻塞？

### 常见用途：

1. ### 防止竞态条件（Race Condition）
   - 在修改全局数据结构时，临时阻塞信号，避免 handler 中断导致数据不一致。

2. ### 原子性操作
   - 保证一段代码“原子”执行（不被信号中断）。

3. ### 与 `sigwait()` 配合使用
   - 主动阻塞信号，然后在特定线程中用 `sigwait()` 同步等待。

4. ### 多线程程序中控制信号处理线程
   - 阻塞某些线程的信号，只允许特定线程处理。

---

## 🧩 七、信号集（sigset_t）基本操作

```c
sigset_t set;

sigemptyset(&set);     // 清空集合
sigfillset(&set);      // 添加所有信号
sigaddset(&set, SIGINT);  // 添加 SIGINT
sigdelset(&set, SIGINT);  // 删除 SIGINT
sigismember(&set, SIGINT); // 判断是否包含
```

---

## 🧠 八、注意事项

- `SIGKILL` 和 `SIGSTOP` **不能被阻塞、忽略或捕获**。
- 阻塞信号是**进程级别**的（所有线程共享信号掩码，但线程可单独设置）。
- 在信号处理函数执行期间，**该信号默认自动阻塞**（防止重入），除非设置了 `SA_NODEFER`。
- 使用 `sigaction` 更安全、可移植。

---

## ✅ 总结

| 问题 | 回答 |
|------|------|
| **什么是信号阻塞？** | 暂时不让某个信号递送给进程 |
| **阻塞后信号去哪了？** | 处于“挂起（pending）”状态，等待解除阻塞 |
| **如何阻塞？** | 使用 `sigprocmask()` 修改信号掩码 |
| **有什么用？** | 避免竞态、保证原子性、控制信号处理时机 |
| **和忽略的区别？** | 阻塞可恢复处理；忽略是永久丢弃 |

---

🔚 **一句话总结**：  
> **信号阻塞就像“延迟处理”——不是不要，只是现在不方便，等会儿再处理。**