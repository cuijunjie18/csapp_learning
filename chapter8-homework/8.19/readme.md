### 8.19

我的答案

$$ helllo = 2 ^ n 次$$

推导如下

假设$f[k]$为循环k次最后的输出次数  
已知$f[0] = 1,f[1] = 2$

数学归纳法有
$$
\begin{align}
    f[3] &= f[2] + f[1] + 1 = 2 + 1 + 1 = 4 \nonumber \\
    f[n] &= f[n - 1] + f[n - 2] + ... + f[1] + 1\nonumber \\
         &= 2 ^ {n - 1} + 2 ^ {n - 2} + ... + 2 + 1 + 1 \nonumber \\
         &= 2 ^ {n} - 1 + 1 \nonumber \\
         &= 2 ^ n \nonumber
\end{align}
$$