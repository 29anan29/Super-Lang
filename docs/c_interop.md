# C 互操作设计

## 概述

C ABI 是 SUPER 的第一公民。SUPER 可以直接调用未修改的 C 库，也可以将自身函数导出为 C 符号供其他语言调用。

## 导出

### 基本导出

```super
export "C" fn function_name(params): return_type:
    body
```

- 生成未 mangle 符号
- 自动生成 C 头文件（`.h`）
- 函数签名映射为 C 调用约定

### 符号名称规则

- SUPER 函数名 → 同名 C 符号
- 无额外前缀或后缀
- 编译后符号可被 gcc 直接链接

### 头文件生成

自动生成对应的 `.h` 文件：
```c
// function_name.h
#ifndef SUPER_FUNCTION_NAME_H
#define SUPER_FUNCTION_NAME_H

int function_name(int param1, int param2);

#endif
```

## 导入

### C 头文件导入

```super
extern "C":
    import "stdio.h"
    fn printf(format string, ...) int
```

- 基于 libclang 解析 C 头文件
- 提取函数签名、struct、enum 定义
- 生成 SUPER 绑定代码

### C 类型映射

| C 类型 | SUPER 类型 |
|--------|-----------|
| `int` | `int` |
| `double` | `float` |
| `char*` | `string` |
| `void*` | `*`（不透明指针） |
| `size_t` | `int` |
| `int32_t` | `int` |
| `int64_t` | `int` |

### `#[repr(C)]` 结构体

```super
#[repr(C)]
struct CPoint:
    x int
    y int
```

- 布局与 C 结构体一致
- 字段顺序、对齐方式与 C 相同

## 不透明指针

封装 C 句柄，禁止直接解引用：

```super
struct DbHandle:
    ptr void     // 不透明指针

fn sqlite_open(path string) DbHandle:
    // 调用 C 函数创建句柄

fn sqlite_close(handle DbHandle):
    // 调用 C 函数释放句柄
```

## 跨界所有权规则

非 POD 类型跨界需显式转换：

```super
fn to_raw(handle DbHandle) *void:
    return handle.ptr    // into_raw

fn from_raw(ptr *void) DbHandle:
    return DbHandle{ptr}  // from_raw
```

- 配对释放：每个 `into_raw` 必须对应一个 `from_raw`
- 禁止悬空：`from_raw` 后原句柄失效

## unsafe 边界

```super
unsafe:
    let p: *int = &x
    *p = 100
```

- 裸指针操作、直接解引用仅限 unsafe 块
- 纯计算型 C 库可通过 `#[safe_c]` 标注在安全代码直接调用

### 安全标注审查

- 白名单从严起步：只放行无指针参数、无堆返回的纯函数
- 建立标注审查清单
- `#[safe_c]` 函数禁止内部 unsafe 操作

## 生命周期检查（FR-4.7）

- 禁止 C 调用持有 SUPER 引用逃逸
- 编译器检查：若 C 函数存储了 SUPER 引用，后续使用报错
- 实现：生命周期分析 + 逃逸分析
