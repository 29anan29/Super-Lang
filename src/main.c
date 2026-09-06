/*
 * main.c — SUPER compiler entry point.
 */
/* SPDX-License-Identifier: MIT */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_banner(void) {
    printf("SUPER Compiler v0.1 — Safe Unified Programming Easy Reliable\n");
}

extern int compile_file(const char *source_path, const char *output_prefix);

int main(int argc, char *argv[]) {
    print_banner();

    if (argc < 2) {
        fprintf(stderr, "Usage: superc <file.super>\n");
        return 1;
    }

    const char *source_file = argv[1];
    printf("Compiling: %s\n", source_file);

    const char *filename = strrchr(source_file, '/');
    filename = filename ? filename + 1 : source_file;

    char prefix[1024];
    strncpy(prefix, filename, sizeof(prefix) - 1);
    prefix[sizeof(prefix) - 1] = '\0';
    char *dot = strrchr(prefix, '.');
    if (dot) *dot = '\0';

    if (!compile_file(source_file, prefix)) {
        fprintf(stderr, "Compilation failed.\n");
        return 1;
    }

    printf("Done.\n");
    return 0;
}
