#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int lexer_run(const char *source);
extern int parser_run(const char *source);
extern int type_inference_run(const char *source);
extern int codegen_run(const char *source);

void print_banner(void) {
    printf("SUPER Compiler v0.1\n");
    printf("Safe Unified Programming Easy Reliable\n");
}

int main(int argc, char *argv[]) {
    print_banner();

    if (argc < 2) {
        fprintf(stderr, "Usage: superc <file.super>\n");
        return 1;
    }

    const char *source_file = argv[1];
    printf("Compiling: %s\n", source_file);

    return 0;
}
