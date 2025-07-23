`sigprocmask()` 是 Unix/Linux 系统中用于 **控制进程信号掩码（signal mask）** 的核心函数，它允许你 **阻塞（block）或解除阻塞（unblock）某些信号**，从而控制这些信号是否可以被递送给当前进程。

---

## 📌 一、函数原型

```c
#include <signal.h>

int sigprocmask(int how, const sigset_t *set, sigset_t *oldset);
```

### 🔹 返回值：
- 成功：返回 `0`
- 失败：返回 `-1`，并设置 `errno`

> ⚠️ 注意：只能在**单线程进程**中使用 `sigprocmask()`。多线程程序应使用 `pthread_sigmask()`。

---

## 🧩 二、参数详解

### 1. `how`：操作类型（必选）
决定如何修改当前的信号掩码（即哪些信号被阻塞）。

| 值 | 说明 |
|-----|------|
| `SIG_BLOCK`  | 将 `set` 中的信号**添加到**当前阻塞集合中（**并集**） |
| `SIG_UNBLOCK`| 将 `set` 中的信号**从**当前阻塞集合中移除（**取消阻塞**） |
| `SIG_SETMASK`| 将当前阻塞集合**完全替换为** `set` 指定的集合 |

> 🔄 类比集合操作：
> - `SIG_BLOCK`: `mask = mask ∪ set`
> - `SIG_UNBLOCK`: `mask = mask \ set`
> - `SIG_SETMASK`: `mask = set`

---

### 2. `set`：要操作的信号集合（可选）
- 指向一个 `sigset_t` 类型的信号集。
- 如果为 `NULL`，则不修改信号掩码，仅查询当前掩码（通过 `oldset` 获取）。

---

### 3. `oldset`：保存旧的信号掩码（可选）
- 如果非空，`sigprocmask()` 会将**调用前的信号掩码**保存到 `oldset` 中。
- 常用于：临时阻塞一些信号 → 执行关键代码 → 恢复原掩码。

---

## 🛠 三、`sigset_t` 与信号集操作

`sigset_t` 是一个数据类型，用于表示一组信号。必须先初始化再使用。

### 常用函数：

| 函数 | 作用 |
|------|------|
| `sigemptyset(sigset_t *set)` | 清空集合，不包含任何信号 |
| `sigfillset(sigset_t *set)`  | 添加所有信号到集合 |
| `sigaddset(sigset_t *set, int sig)` | 添加单个信号（如 `SIGINT`） |
| `sigdelset(sigset_t *set, int sig)` | 从集合中删除某个信号 |
| `sigismember(const sigset_t *set, int sig)` | 判断信号是否在集合中 |

---

## 🧪 四、使用示例

### 示例 1：阻塞 `SIGINT`（Ctrl+C）

```c
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    sigset_t set, oldset;

    // 初始化信号集
    sigemptyset(&set);
    sigaddset(&set, SIGINT);  // 想要阻塞 SIGINT

    // 阻塞 SIGINT，保存旧掩码
    sigprocmask(SIG_BLOCK, &set, &oldset);
    printf("SIGINT 已阻塞。按 Ctrl+C 无效...\n");
    sleep(5);

    // 恢复原来的信号掩码（解除阻塞）
    sigprocmask(SIG_SETMASK, &oldset, NULL);
    printf("SIGINT 已恢复。现在可以按 Ctrl+C 了。\n");
    sleep(5);

    return 0;
}
```

📌 运行效果：
- 前 5 秒：按 `Ctrl+C` 无反应（信号被阻塞，处于 pending 状态）
- 后 5 秒：按 `Ctrl+C` 会终止程序或触发 handler

---

### 示例 2：临时阻塞多个信号

```c
sigset_t set;
sigemptyset(&set);
sigaddset(&set, SIGINT);
sigaddset(&set, SIGTERM);

sigprocmask(SIG_BLOCK, &set, NULL);  // 阻塞 SIGINT 和 SIGTERM

// 执行关键操作（如修改全局数据结构）
// ...

sigprocmask(SIG_UNBLOCK, &set, NULL); // 恢复
```

---

### 示例 3：查询当前信号掩码

```c
sigset_t current_mask;
sigprocmask(0, NULL, &current_mask);  // how=0 表示不修改，只获取

if (sigismember(&current_mask, SIGINT)) {
    printf("SIGINT 当前被阻塞\n");
} else {
    printf("SIGINT 未被阻塞\n");
}
```

> ✅ 这是获取当前信号掩码的标准方法（`how=0` 表示无操作）。

---

## ⚠️ 五、重要注意事项

| 项目 | 说明 |
|------|------|
| **`SIGKILL` 和 `SIGSTOP` 无法被阻塞** | 即使你尝试阻塞它们，系统也会忽略 |
| **信号阻塞是进程级别的** | 所有线程共享信号掩码（但在多线程中应使用 `pthread_sigmask`） |
| **普通信号不排队** | 如果在阻塞期间多次发送 `SIGINT`，解除阻塞后只会递送一次 |
| **实时信号会排队** | `SIGRTMIN` 到 `SIGRTMAX` 支持排队，每个信号可多次递送 |
| **信号处理函数执行期间自动阻塞该信号** | 防止重入（除非设置了 `SA_NODEFER`） |

---

## 🔄 六、典型使用模式

### 模式：保护临界区（避免信号中断）

```c
sigset_t set, oldset;

sigemptyset(&set);
sigaddset(&set, SIGALRM);

// 阻塞 SIGALRM
sigprocmask(SIG_BLOCK, &set, &oldset);

// === 临界区开始 ===
// 修改全局变量、数据结构等
// 不希望被 SIGALRM 中断
// === 临界区结束 ===

// 恢复信号掩码
sigprocmask(SIG_SETMASK, &oldset, NULL);
```

> ✅ 这是防止竞态条件的重要手段。

---

## 📚 七、与相关函数对比

| 函数 | 用途 |
|------|------|
| `sigprocmask()` | 单线程中修改信号掩码 |
| `pthread_sigmask()` | 多线程中修改线程的信号掩码 |
| `sigpending()` | 查看当前 pending 的信号集合 |
| `sigaction()` | 设置信号处理函数（比 `signal()` 更强大） |
| `kill()` / `raise()` | 发送信号 |

---

## ✅ 八、总结

| 问题 | 回答 |
|------|------|
| **`sigprocmask()` 是干什么的？** | 控制哪些信号被阻塞，不能递送给进程 |
| **三个 `how` 参数的区别？** | `BLOCK`: 添加；`UNBLOCK`: 移除；`SETMASK`: 替换 |
| **为什么需要阻塞信号？** | 保护临界区、避免竞态、实现同步 |
| **如何临时阻塞再恢复？** | 用 `oldset` 保存原掩码，操作完后 `SIG_SETMASK` 恢复 |
| **能否阻塞 `SIGKILL`？** | ❌ 不能，它是强制的 |

---

🔚 **一句话总结**：  
> `sigprocmask()` 是进程的“信号防火墙”，让你决定哪些信号可以进来，哪些要暂时拦在外面。