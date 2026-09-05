# SUPER — Safe Unified Programming Easy Reliable

> 编译期内存安全、无 GC、C 生态原生兼容、对 Python 使用者零门槛入门的系统编程语言。

[![Language](https://img.shields.io/badge/language-SUPER-blue)]()
[![Status](https://img.shields.io/badge/status-development-orange)]()
[![License](https://img.shields.io/badge/license-MIT-green)]()

---

## 为什么是 SUPER？

| 字母 | 全称 | 含义 |
|------|------|------|
| **S** | **Safe** | 编译期内存安全，无悬垂指针、use-after-free、数据竞争 |
| **U** | **Unified** | 统一 Rust 安全与 Python 易学，一次学习两种体验 |
| **P** | **Programming** | 系统级编程，LLVM 后端，性能对标 Rust |垂直切片→M0→M1→M2→M3 |
| **E** | **Easy** | 自动借用推导，零显式标注负担，Python 用户 1 天上手 |
| **R** | **Reliable** | RAII 确定性析构，编译期保证，零运行时开销 |

---

## 核心特性

- **自动借用推导** — 编译器自动为每个参数推导 `borrowed`/`inout`/`owned`，用户无需写 `&`/`&mut`/生命周期
- **无 GC** — RAII 语义，编译期确定性释放，零运行时开销
- **C ABI 第一公民** — 直接调用未修改的 C 库，导出函数可被 C 代码直接链接
- **Python 式语法** — 冒号定义块，`if condition:`，`fn name():`，零学习成本
- **LLVM 后端** — 性能对标 Rust，产物为标准 `.o`/`.a`/`.so`

---

## 快速示例

```super
// 函数定义：参数类型自动推断借用约定
fn add(a int, b int) int:
    return a + b

// 公开函数，可导出给 C
pub fn PrintHello() void:
    out("Hello, SUPER!")

// 结构体
struct Point:
    x int
    y int

// 枚举
enum Direction:
    up, down, left, right

// C 互操作
extern "C":
    import "stdio.h"
    fn printf(format string, ...) int

// 主函数
export "C" fn main() int:
    let p Point
    p.x = 10
    p.y = 20
    print(p.x + p.y)
    return 0
```

---

## 路线图

| 阶段 | 周期 | 目标 |
|------|------|------|
| **M0** 垂直切片 | 3 个月 | 显式标注版编译器 + LLVM 后端 + C 导出 |
| **M1** MVP | +4 个月 | 自动借用推导 + drop 插入 + bindgen |
| **M2** 自举候选 | +6 个月 | 跨过程推导 + 30+ C 库绑定 + 性能基准 |
| **M3** 公测 | +6 个月 | 包管理 + 教程 + 10 外部用户验证 |

详见 [ROADMAP.md](docs/ROADMAP.md)

---

## 文档

- [PRD — 产品需求文档](docs/PRD.md)
- [语言规范](docs/lang.md)
- [实现路线图](docs/ROADMAP.md)

---

## 许可证

MIT
