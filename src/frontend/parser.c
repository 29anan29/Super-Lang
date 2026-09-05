#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

static int peek(Parser *p) {
    if (p->pos >= p->count) return TOKEN_EOF;
    return p->tokens[p->pos].type;
}

static Token current(Parser *p) {
    if (p->pos >= p->count) {
        Token t = {TOKEN_EOF, "", 0, 0};
        return t;
    }
    return p->tokens[p->pos];
}

static Token advance(Parser *p) {
    Token t = current(p);
    if (p->pos < p->count) p->pos++;
    return t;
}

static int match(Parser *p, TokenType type) {
    return peek(p) == type;
}

static void set_error(Parser *p, const char *msg) {
    snprintf(p->error_msg, sizeof(p->error_msg), "%s at line %d col %d", msg, current(p).line, current(p).column);
}

static ASTNode *parse_statement(Parser *p);
static ASTNode *parse_expression(Parser *p);

ASTNode *parser_create_node(Parser *p, ASTNodeType type) {
    return ast_create(type, current(p).line, current(p).column);
}

ASTNode *parser_parse(Parser *parser) {
    ASTNode *program = ast_create(AST_PROGRAM, 0, 0);
    while (peek(parser) != TOKEN_EOF) {
        ASTNode *stmt = parse_statement(parser);
        if (stmt) ast_add_child(program, stmt);
        if (strlen(parser->error_msg) > 0) {
            fprintf(stderr, "Parse error: %s\n", parser->error_msg);
            break;
        }
    }
    return program;
}

static ASTNode *parse_statement(Parser *p) {
    TokenType tt = peek(p);

    if (tt == TOKEN_KEYWORD_FN || tt == TOKEN_KEYWORD_PUB) {
        ASTNode *fn = parser_create_node(p, tt == TOKEN_KEYWORD_PUB ? AST_PUB_FN_DEF : AST_FN_DEF);
        advance(p);
        if (match(p, TOKEN_IDENT)) {
            char *name_val = malloc(strlen(current(p).value) + 1); strcpy(name_val, current(p).value);
            ASTNode *name = ast_create(AST_IDENT, current(p).line, current(p).column);
            name->value = name_val;
            advance(p);
            ast_add_child(fn, name);
        }
        if (match(p, TOKEN_LPAREN)) {
            advance(p);
            while (!match(p, TOKEN_RPAREN) && peek(p) != TOKEN_EOF) {
                advance(p);
                if (match(p, TOKEN_RPAREN)) break;
            }
            advance(p);
        }
        if (match(p, TOKEN_COLON)) {
            advance(p);
            if (match(p, TOKEN_IDENT)) {
                char *ret_val = malloc(strlen(current(p).value) + 1); strcpy(ret_val, current(p).value);
                ASTNode *ret = ast_create(AST_IDENT, current(p).line, current(p).column);
                ret->value = ret_val;
                ast_add_child(fn, ret);
                advance(p);
            }
        }
        if (match(p, TOKEN_COLON)) {
            advance(p);
            while (!match(p, TOKEN_RBRACE) && peek(p) != TOKEN_EOF) {
                ASTNode *body = parse_statement(p);
                if (body) ast_add_child(fn, body);
            }
        }
        return fn;
    }

    if (tt == TOKEN_KEYWORD_STRUCT) {
        ASTNode *st = parser_create_node(p, AST_STRUCT_DEF);
        advance(p);
        if (match(p, TOKEN_IDENT)) {
            char *name_val = malloc(strlen(current(p).value) + 1); strcpy(name_val, current(p).value);
            ASTNode *name = ast_create(AST_IDENT, current(p).line, current(p).column);
            name->value = name_val;
            ast_add_child(st, name);
            advance(p);
        }
        return st;
    }

    if (tt == TOKEN_KEYWORD_ENUM) {
        ASTNode *en = parser_create_node(p, AST_ENUM_DEF);
        advance(p);
        if (match(p, TOKEN_IDENT)) {
            char *name_val = malloc(strlen(current(p).value) + 1); strcpy(name_val, current(p).value);
            ASTNode *name = ast_create(AST_IDENT, current(p).line, current(p).column);
            name->value = name_val;
            ast_add_child(en, name);
            advance(p);
        }
        return en;
    }

    if (tt == TOKEN_KEYWORD_IF) {
        ASTNode *iff = parser_create_node(p, AST_IF_STMT);
        advance(p);
        ASTNode *cond = parse_expression(p);
        if (cond) ast_add_child(iff, cond);
        return iff;
    }

    if (tt == TOKEN_KEYWORD_FOR) {
        ASTNode *for_ = parser_create_node(p, AST_FOR_STMT);
        advance(p);
        ASTNode *cond = parse_expression(p);
        if (cond) ast_add_child(for_, cond);
        return for_;
    }

    if (tt == TOKEN_KEYWORD_MATCH) {
        ASTNode *match_ = parser_create_node(p, AST_MATCH_STMT);
        advance(p);
        ASTNode *expr = parse_expression(p);
        if (expr) ast_add_child(match_, expr);
        return match_;
    }

    if (tt == TOKEN_KEYWORD_UNSAFE) {
        ASTNode *unsafe_ = parser_create_node(p, AST_UNSAFE_STMT);
        advance(p);
        return unsafe_;
    }

    if (tt == TOKEN_KEYWORD_LET) {
        ASTNode *vardecl = parser_create_node(p, AST_VAR_DECL);
        advance(p);
        if (match(p, TOKEN_IDENT)) {
            char *name_val = malloc(strlen(current(p).value) + 1); strcpy(name_val, current(p).value);
            ASTNode *name = ast_create(AST_IDENT, current(p).line, current(p).column);
            name->value = name_val;
            ast_add_child(vardecl, name);
            advance(p);
        }
        return vardecl;
    }

    if (tt == TOKEN_KEYWORD_RETURN) {
        ASTNode *ret = parser_create_node(p, AST_RETURN_STMT);
        advance(p);
        ASTNode *val = parse_expression(p);
        if (val) ast_add_child(ret, val);
        return ret;
    }

    advance(p);
    return NULL;
}

static ASTNode *parse_expression(Parser *p) {
    ASTNode *node = ast_create(AST_IDENT, current(p).line, current(p).column);
    if (match(p, TOKEN_IDENT)) {
        char *val = malloc(strlen(current(p).value) + 1); strcpy(val, current(p).value);
        node->value = val;
        advance(p);
    } else if (match(p, TOKEN_INT) || match(p, TOKEN_FLOAT)) {
        node->type = AST_LITERAL;
        char *val = malloc(strlen(current(p).value) + 1); strcpy(val, current(p).value);
        node->value = val;
        advance(p);
    } else {
        advance(p);
    }
    return node;
}

Parser *parser_create(Token *tokens, int count) {
    Parser *p = malloc(sizeof(Parser));
    p->tokens = tokens;
    p->count = count;
    p->pos = 0;
    p->line = 1;
    p->column = 1;
    p->error_msg[0] = '\0';
    return p;
}

void parser_free(Parser *parser) {
    free(parser);
}

const char *parser_error(Parser *parser) {
    return parser->error_msg[0] ? parser->error_msg : NULL;
}
