**说中文**

## 项目：SUPER 编程语言

SUPER 是一门编译期内存安全、无 GC、C 生态原生兼容的系统编程语言。核心差异化：自动借用推导，用户无需写 `&`/`&mut`/生命周期。技术栈：纯 C 实现，C 后端生成 C 源码，由 gcc/clang 编译。

## 项目结构

- `docs/` — 技术文档
  - `PRD.md` — 产品需求文档
  - `lang.md` — 语言规范
  - `ROADMAP.md` — 实现路线图
  - `architecture.md` — 架构设计
  - `frontend.md` — 前端设计（词法/语法）
  - `type_inference.md` — 类型推断设计
  - `borrow_inference.md` — 借用推导设计（核心）
  - `c_interop.md` — C 互操作设计
  - `error_diagnostic.md` — 错误诊断设计
  - `toolchain.md` — 工具链设计
  - `m0_plan.md` — M0 实施计划
- `src/` — 编译器源代码（C 语言）
  - `frontend/` — 词法分析、语法分析、AST
  - `midend/` — 类型推断、SSA 构造、借用推导
  - `backend/` — C 代码生成、后端集成
  - `toolchain/` — 构建命令、错误诊断、包管理
  - `stdlib/` — 标准库源码
- `examples/` — 示例代码（.super 文件）
- `test/` — 测试代码
- `build/` — 构建输出

## 关键技术决策

- 类型推断：Hindley-Milner
- 借用检查层级：MIR/SSA 层
- 后端：C 代码生成器 + gcc/clang
- 内存管理：编译器插入 drop + RAII，无 GC
- C 互操作：`extern "C"` + bindgen
- 错误诊断：位置 + 推导过程 + 修复建议
- 借用覆盖符号：`*`/`&`/`&mut`
- unsafe 语法：`unsafe:`
- 枚举写法：`enum Name: val1, val2`
- Option/Result：边界显式声明

## 命名

语言名：SUPER — Safe Unified Programming Easy Reliable

## 许可证

MIT
