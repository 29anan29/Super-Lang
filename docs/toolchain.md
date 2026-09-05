# 工具链设计

## 概述

SUPER 工具链包含构建命令、错误诊断、包管理和包管理器。

## 构建命令

### `super build`

```
super build              # 构建当前目录项目
super build --lib        # 生成库文件（.a / .so）
super build --bin        # 生成可执行文件
super build --release    # 启用优化
super build -j N         # 并行编译 N 个任务
```

### 构建流程

```
super build
  │
  ├── 扫描目录，找到所有 .super 源文件
  ├── 调用编译器编译每个源文件
  │     └── superc src/main.super → build/main.o
  ├── 链接目标文件
  │     └── gcc build/*.o -o build/main
  └── 输出产物
        ├── build/main（可执行文件）
        ├── build/libsuper.a（静态库）
        └── build/libsuper.so（动态库）
```

### 项目结构

```
project/
├── main.super         # 主源文件
├── lib/               # 库文件目录
│   └── utils.super
├── super.toml         # 项目配置
└── build/             # 构建输出目录
    ├── main.o
    ├── main
    └── ...
```

## 配置文件

### super.toml

```toml
[project]
name = "my_project"
version = "0.1.0"

[dependencies]
stdio = "1.0"
sqlite3 = "3.40"

[build]
optimize = true
target = "x86_64-linux"
```

## 错误诊断

- 所有编译器错误输出到 stderr
- 格式：位置 + 原因 + 修复建议
- 彩色输出（终端支持时）
- 支持 `--verbose` 显示详细推导过程

## 包管理

### `super pkg`

```
super pkg install <package>    # 安装依赖
super pkg list                 # 列出已安装包
super pkg update               # 更新依赖
super pkg remove <package>     # 移除依赖
```

### 依赖解析

- 解析 `super.toml` 中的依赖声明
- 版本约束匹配
- 依赖树构建
- 下载源码包并缓存

### 依赖声明

```toml
[dependencies]
# 标准库
stdio = "1.0"
# C 库绑定
sqlite3 = "3.40"
zlib = "1.2"
```

### 构建集成

- 自动编译依赖的 .super 源码
- 链接 C 系统库（通过 pkg-config）
- vendored C 源码编译集成

## C 项目集成

SUPER 产物可直接嵌入现有 C 项目：

```bash
# 1. 编译 SUPER 代码为 .o
super build --lib -j4

# 2. 链接到现有 C 项目
gcc main.c -L. -lsuper -o program

# 3. 或直接链接 .o
gcc main.c build/libsuper.a -o program
```

## 性能指标

- 中型项目（5 万行）全量编译 ≤ 30s
- hello world 静态二进制 ≤ 1MB
- 支持增量编译（后续版本）
