# 编程语言规范

## 1. 输入输出
```
out("hello")
a = in("input:")
b = in()
```

## 2. 表达式

### 2.1 算术与位运算
```
a++
a--
a += 2
a -= 2
a / b      // 整数除法，向零取整
a % b      // 取模
a * b
```

### 2.2 比较运算符
```
a == b
a != b
a < b
a > b
a <= b
a >= b
```

### 2.3 逻辑运算符
```
a and b
a or b
not a
```

### 2.4 复合赋值
```
a += 2   // 等价于 a = a + 2
a -= 2
a *= 3
a /= 3
a %= 3
```

## 3. 注释
### 3.1 单行注释
```
// 这是单行注释
```

### 3.2 多行注释
```
/* 这是多行注释
   可以多行 */
```

## 4. 函数

### 4.1 基本定义
```
fn print() int:
    print("1111")
    return 0
```

### 4.2 公开函数
```
// 公开函数，对 C 可导出
pub fn Print() void:
    print(a)
```

### 4.3 带参数函数
```
// 借用自动推导，无需 &
fn add(a int, b int) int:
    return a + b

// 显式 borrowed
fn print_ptr(&x int) int:
    return *x

// 显式 owned（移动）
fn take_owner(*x int) int:
    return *x

// 显式 inout（可变借用）
fn modify(&mut x int) int:
    x = x + 1
    return *x
```

### 4.4 Option/Result（边界显式声明）
```
// 内部自动推导，无需包装类型
fn get_index(v int, i int) int:
    return v[i]  // 若越界编译错误

// 公共 API 边界显式声明
fn safe_divide(a int, b int) Result<int, string>:
    if b == 0:
        return err("division by zero")
    return ok(a / b)

fn maybe_value() Option<int>:
    return some(42)  // 或 None
```

## 5. 变量

### 5.1 基本声明
```
a int = 10
b bool = true
c string = "hello"
d float = 3.14

// 无初始值（nil）
a int       // nil
b bool      // nil  
c string    // ""
d float     // nil
```

### 5.2 类型推断
```
x = 10        // 自动推断为 int
y = "hello"   // 自动推断为 string
z = true      // 自动推断为 bool
```

### 5.3 Copy 语义
```
// 自动派生 Copy（编译期大小 ≤ 2 机器字，所有字段可复制）
a int = 10
b = a         // 合法，b 是 a 的副本

// Non-Copy：移动语义
let s = String::new()
let t = s     // 合法，s 移动到 t
// 此处 s 不可用，已被移动
```

## 6. 控制流

### 6.1 if/else
```
if condition:
    // statements
else:
    // statements
```

### 6.2 match (分支选择)
```
match x:
    case 1:
        // 处理 1
    case 2..10:
        // 处理 2 到 10
    case _:
        // 默认分支
```

### 6.3 for 循环
```
// 条件循环
for condition:
    // statements
    if break_condition:
        break

// 遍历（待后续扩展）
for item in collection:
    // statements
```

### 6.4 break / continue
```
for i in range(10):
    if i == 5:
        break  // 跳出循环
    if i % 2 == 0:
        continue  // 跳过本次迭代
```

## 7. 结构体

### 7.1 基本定义
```
struct Point:
    x int
    y int

p Point
p.x = 10
p.y = 20
```

### 7.2 repr(C) 结构体
```
// C 互操作：布局与 C 一致
#[repr(C)]
struct CPoint:
    x int
    y int
```

### 7.3 方法绑定
```
// 关联函数
impl Point:
    fn new(x int, y int) Point:
        return Point{x, y}
    
    fn area(self) int:
        return self.x * self.y
```

## 8. 枚举

### 8.1 标准枚举
```
enum Direction:
    up, down, left, right
```

### 8.2 带值的枚举
```
enum Result:
    ok int
    err string

// 使用
r Result = ok 42
match r:
    case ok val:
        // 使用 val
    case err msg:
        // 使用 msg
```

## 9. 导入

### 9.1 单包导入
```
import "module_name"
import "fmt"
import "math"
```

### 9.2 C 互操作导入
```
// 导入 C 库函数
extern "C":
    import "stdio.h"
    fn printf(format string, ...) int
```

## 10. unsafe 块

```
// 裸指针操作仅限 unsafe 语境
unsafe:
    let p: *int = &x
    *p = 100
    // 其他 C FFI 调用...
```

## 11. 借用覆盖（FR-2.5）

### 11.1 函数参数约定
```
// owned（移动语义）
fn consume(*x int):
    // 使用后 x 失效

// borrowed（只读借用）
fn inspect(&x int):
    // 仅读，x 保持有效

// inout（可变借用）
fn update(&mut x int):
    x = x + 1
```

### 11.2 自动推导默认
```
// 无特殊标注时，编译器按如下规则推导：
// - 仅读参数 → borrowed
// - 有写路径 → inout  
// - 被存储/返回 → owned
```