### A

```shell
gcc p.o libx.a
```

### B

```shell
gcc p.o libx.a liby.a
```

### C

错误的
```shell
gcc p.o libx.a liby.a libx.a p.o
```

正确的
```shell
gcc p.o libx.a liby.a libx.a
```