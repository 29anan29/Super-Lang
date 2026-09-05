# 前端设计：词法分析与语法分析

## 整体流程

```
源码 → Lexer → Token 流 → Parser → AST
```

## 词法分析器（Lexer）

### Token 类型

| 类别 | Token |
|------|-------|
| 关键字 | `fn`, `pub`, `struct`, `enum`, `match`, `if`, `else`, `for`, `unsafe`, `import`, `extern`, `let`, `return`, `out`, `in` |
| 标识符 | 字母开头，含字母、数字、下划线 |
| 字面量 | 整数、浮点、字符串、布尔 |
| 运算符 | `+`, `-`, `*`, `/`, `%`, `==`, `!=`, `<`, `>`, `<=`, `>=`, `++`, `--` |
| 复合运算符 | `+=`, `-=`, `*=`, `/=`, `%=` |
| 逻辑运算符 | `and`, `or`, `not` |
| 分隔符 | `:`, `,`, `.`, `->`, `(`, `)`, `{`, `}`, `[`, `]`, `#`, `!`, `*`, `&`, `;` |
| 借用符号 | `&`, `&mut`, `*` |
| 注释 | `//` 单行，`/* */` 多行 |

### 实现要点

- 无状态机：逐字符扫描，按规则匹配
- 关键字优先：标识符匹配时先查关键字表
- 字符串支持转义：`\n`, `\t`, `\\`, `\"`, `\u{XXXX}`

## 语法分析器（Parser）

### AST 节点类型

```
Program
  └── Statement
       ├── FnDef          // 函数定义
       ├── PubFnDef       // 公开函数定义
       ├── StructDef      // 结构体定义
       ├── EnumDef        // 枚举定义
       ├── VarDecl        // 变量声明
       ├── ExprStmt       // 表达式语句
       ├── IfStmt         // if/else
       ├── ForStmt        // for 循环
       ├── MatchStmt      // match 表达式
       ├── UnsafeStmt     // unsafe 块
       ├── ImportStmt     // import 语句
       ├── ExternBlock    // extern "C" 块
       └── ReturnStmt     // return
  └── Expr
       ├── BinOp          // 二元运算
       ├── UnOp           // 一元运算
       ├── Call           // 函数调用
       ├── FieldAccess    // 字段访问
       ├── Index          // 索引
       ├── Lit            // 字面量
       └── Ident          // 标识符
```

### 语法规则（选）

**函数定义：**
```
fn name(params): return_type: body
pub fn name(params): return_type: body
```

**参数（带借用标注）：**
```
param: type           // 自动推导
&param: type          // borrowed
&mut param: type      // inout
*param: type          // owned
```

**结构体：**
```
struct Name:
    field_name field_type
```

**枚举：**
```
enum Name:
    variant1, variant2, ...
enum Name:
    variant1 type1
    variant2 type2
    ...
```

**Match：**
```
match expr:
    case pattern: body
    case pattern..range: body
    case _: body
```

**Unsafe 块：**
```
unsafe:
    statements
```

**Extern "C"：**
```
extern "C":
    import "header.h"
    fn name(params): return_type
```

### 错误处理

- 语法错误：报告位置、期望内容、实际内容
- 提供可能的修复建议
- 错误恢复：跳过当前语句继续解析后续内容

## 前端测试

- 词法分析测试：各种边界情况（空文件、极端长度行、特殊字符）
- 语法分析测试：合法程序解析 + 非法程序报错
- 错误诊断测试：错误位置准确、修复建议合理
