#### 4.30

```py
word f_stat = [
    imem_error : SADR;
    !instr_valid : SINS;
    f_icode == IHALT : SHLT;
    1 : SAOK; 
]
```

#### 4.31

```py
word d_dstE = [
    icode in {IRRMOVQ} : rB;
    icode in {IIRMOVQ, IOPQ} : rB;
    icode in {IPUSHQ, IPOPQ, ICALL, IRET} : RRSP;
    1 : RNONE;
]

# standard ans
word d_dstE = [
    D_icode in {IRRMOVQ, IIRMOVQ, IOPQ} : D_rB;
    D_icode in {IPUSHQ, IPOPQ, ICALL, IRET} : RRSP;
    1 : RNONE;
]
```

#### 4.32

```py
导致popq %rsp指令不是预期的movq (%rsp),%rsp的效果，而是 %rsp = %rsp + 8
```

#### 4.33

```py
popq %rsp
nop
nop
rrmovq %rsp,%rax

结果：同4.32一样，达不到预期的效果
```

#### 4.34

```py
word d_valB = [
    d_srcB == e_dstE : e_valE;  # Forward from execute
    d_srcB == M_dstM : m_valM;  # Forward from memory
    d_srcB == M_dstE : M_valE;
    d_srcB == W_dstM : W_valM;  # Forward from write back
    d_srcB == W_dstE : W_valE;
    1 : d_rvalB;     # default situation
]

# 终于一遍过了
```

#### 4.35

```py
# 直接不会，看了答案
想明白了，什么时候写入的寄存器id会变呢？不就是条件传送指令吗，原来\
预测默认的是会传送，后面根据计算结果set CC后，可能 id = RNONE，所\
以还是要用e_dstE而不是E_dstE.
```

#### 4.36

```py
word m_stat = [
    dmem_error : SADR;
    1 : M_stat;
]
```