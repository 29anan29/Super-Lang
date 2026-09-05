#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "c_codegen.h"
#include "type_inference.h"
#include "parser.h"

extern Token *lexer_tokenize(const char *source, int *token_count);
extern void lexer_free_tokens(Token *tokens, int count);
extern Parser *parser_create(Token *tokens, int count);
extern ASTNode *parser_parse(Parser *parser);
extern void parser_free(Parser *parser);
extern int infer_types(ASTNode *ast);
extern int c_codegen_generate(ASTNode *ast, const char *output_file);
extern int c_codegen_generate_header(ASTNode *ast, const char *header_file);

int compile_file(const char *source_path, const char *output_prefix) {
    char source[4096];
    FILE *f = fopen(source_path, "r");
    if (!f) {
        fprintf(stderr, "Error: cannot open %s\n", source_path);
        return 0;
    }
    size_t len = fread(source, 1, sizeof(source) - 1, f);
    source[len] = '\0';
    fclose(f);

    int token_count;
    Token *tokens = lexer_tokenize(source, &token_count);
    if (token_count == 0) {
        fprintf(stderr, "Error: no tokens found\n");
        return 0;
    }

    Parser *parser = parser_create(tokens, token_count);
    ASTNode *ast = parser_parse(parser);
    parser_free(parser);
    lexer_free_tokens(tokens, token_count);

    if (!ast) {
        fprintf(stderr, "Error: parse failed\n");
        return 0;
    }

    infer_types(ast);

    char c_file[4096];
    snprintf(c_file, sizeof(c_file), "%s.c", output_prefix);
    if (!c_codegen_generate(ast, c_file)) {
        fprintf(stderr, "Error: C code generation failed\n");
        return 0;
    }

    char header[4096];
    snprintf(header, sizeof(header), "%s.h", output_prefix);
    c_codegen_generate_header(ast, header);

    printf("Generated: %s, %s\n", c_file, header);
    return 1;
}
