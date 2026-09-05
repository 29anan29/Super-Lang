# 编程语言规范

输入输出:
```
out("hello")
a = in("input:")
b = in()
```

表达式
```
a++
a--
a += 2
a -= 2
a / b
a % b
a * b
```

注释
```
// aaa
```

/* 多行注释 */

函数
```
fn print() int:
    print("1111")
    return 0

//公开函数
pub fn Print() void:
    print(a)
```

变量
```
a int = 10
b bool = true
c string = "hello"
a int // nil
b bool //nil
c string // ""
d float //nil
*f = 111 //没有 f *int这种
```

控制流
```
if condition:
    // statements
else:
    // statements

for condition:
    // statements

break
continue
```

结构体
```
struct Point:
    x int
    y int

p Point
p.x = 10
```

导入
```
import "module_name"
import "fmt"
import "math"