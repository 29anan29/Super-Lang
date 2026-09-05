# SUPER

> 编译期内存安全、无 GC、C 生态原生兼容、对 Python 使用者零门槛入门的系统编程语言。

## 这个名字什么意思

**S**afe — 编译期内存安全，无悬垂指针、use-after-free、数据竞争

**U**nified — 统一 Rust 级安全与 Python 级易学，一次学习两种体验

**P**rogramming — 系统级编程，C 后端生成 C 源码，性能对标 Rust

**E**asy — 自动借用推导，零显式标注负担，Python 用户 1 天上手

**R**eliable — RAII 确定性析构，编译期保证，零运行时开销

## 特性

- 自动借用推导：编译器自动为参数推导 `borrowed`/`inout`/`owned`，用户无需写 `&`/`&mut`/生命周期
- 无 GC：RAII 语义，编译期确定性释放，零运行时开销
- C ABI 第一公民：直接调用未修改的 C 库，导出函数可被 C 代码直接链接
- Python 式语法：冒号定义块，`if condition:`、`fn name():`，零学习成本
- C 后端：生成 C 源码，由 gcc/clang 编译，产物为标准 `.o`/`.a`/`.so`

## 快速上手

```super
fn add(a int, b int) int:
    return a + b

pub fn PrintHello() void:
    out("Hello, SUPER!")

struct Point:
    x int
    y int

enum Direction:
    up, down, left, right

extern "C":
    import "stdio.h"
    fn printf(format string, ...) int

export "C" fn main() int:
    let p Point
    p.x = 10
    p.y = 20
    print(p.x + p.y)
    return 0
```

## 路线图

| 阶段 | 周期 | 目标 |
|------|------|------|
| M0 垂直切片 | 3 个月 | 显式标注版编译器 + C 后端 + C 导出 |
| M1 MVP | +4 个月 | 自动借用推导 + drop 插入 + bindgen |
| M2 自举候选 | +6 个月 | 跨过程推导 + 30+ C 库绑定 + 性能基准 |
| M3 公测 | +6 个月 | 包管理 + 教程 + 10 外部用户验证 |

详见 [ROADMAP.md](docs/ROADMAP.md)

## 文档

- [PRD — 产品需求文档](docs/PRD.md)
- [语言规范](docs/lang.md)
- [实现路线图](docs/ROADMAP.md)

## 许可证

MIT — 详见 [LICENSE](LICENSE)
