#include <stdio.h>

// SUPER 标准库：基础类型

// 整数运算
int super_add(int a, int b) {
    return a + b;
}

int super_sub(int a, int b) {
    return a - b;
}

int super_mul(int a, int b) {
    return a * b;
}

int super_div(int a, int b) {
    if (b == 0) return 0;
    return a / b;
}

// 字符串操作
int super_strlen(const char *s) {
    int len = 0;
    while (s[len]) len++;
    return len;
}

// 输出
void super_print(const char *s) {
    printf("%s", s);
}

void super_println(const char *s) {
    printf("%s\n", s);
}

// 布尔
int super_true() { return 1; }
int super_false() { return 0; }
int super_not(int b) { return !b; }
