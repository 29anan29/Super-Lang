#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "ast.h"

typedef struct {
    Token *tokens;
    int count;
    int pos;
    int line;
    int column;
    char error_msg[256];
} Parser;

Parser *parser_create(Token *tokens, int count);
ASTNode *parser_parse(Parser *parser);
void parser_free(Parser *parser);
const char *parser_error(Parser *parser);

#endif
