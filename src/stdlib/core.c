/*
 * core.c — SUPER standard library: basic types and utilities.
 */
/* SPDX-License-Identifier: MIT */

#include <stdio.h>
#include <stdarg.h>

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
    if (b == 0) {
        fprintf(stderr, "Error: division by zero\n");
        return 0;
    }
    return a / b;
}

int super_strlen(const char *s) {
    int len = 0;
    while (s[len]) len++;
    return len;
}

void super_print(const char *s) {
    printf("%s", s);
}

void super_println(const char *s) {
    printf("%s\n", s);
}

int super_true() { return 1; }
int super_false() { return 0; }
int super_not(int b) { return !b; }
