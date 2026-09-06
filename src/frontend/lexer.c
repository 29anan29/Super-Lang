/*
 * lexer.c — SUPER lexical analyzer: tokenizes source code into a token stream.
 */
/* SPDX-License-Identifier: MIT */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"

static int is_keyword(const char *s) {
    const char *kw[] = {
        "fn", "pub", "struct", "enum", "match", "if", "else",
        "for", "unsafe", "import", "extern", "let", "return", "out", "in"
    };
    for (int i = 0; i < 15; i++) if (strcmp(kw[i], s) == 0) return 1;
    return 0;
}

static TokenType keyword_to_type(const char *kw) {
    switch (*kw) {
        case 'f':
            if (strcmp(kw, "fn") == 0) return TOKEN_KEYWORD_FN;
            if (strcmp(kw, "for") == 0) return TOKEN_KEYWORD_FOR;
            return TOKEN_IDENT;
        case 'p': return strcmp(kw, "pub") == 0 ? TOKEN_KEYWORD_PUB : TOKEN_IDENT;
        case 's': return strcmp(kw, "struct") == 0 ? TOKEN_KEYWORD_STRUCT : TOKEN_IDENT;
        case 'e': return strcmp(kw, "enum") == 0 ? TOKEN_KEYWORD_ENUM : TOKEN_IDENT;
        case 'm': return strcmp(kw, "match") == 0 ? TOKEN_KEYWORD_MATCH : TOKEN_IDENT;
        case 'i':
            if (strcmp(kw, "if") == 0) return TOKEN_KEYWORD_IF;
            if (strcmp(kw, "import") == 0) return TOKEN_KEYWORD_IMPORT;
            if (strcmp(kw, "in") == 0) return TOKEN_KEYWORD_IN;
            return TOKEN_IDENT;
        case 'u': return strcmp(kw, "unsafe") == 0 ? TOKEN_KEYWORD_UNSAFE : TOKEN_IDENT;
        case 'l': return strcmp(kw, "let") == 0 ? TOKEN_KEYWORD_LET : TOKEN_IDENT;
        case 'r': return strcmp(kw, "return") == 0 ? TOKEN_KEYWORD_RETURN : TOKEN_IDENT;
        case 'o': return strcmp(kw, "out") == 0 ? TOKEN_KEYWORD_OUT : TOKEN_IDENT;
        default: return TOKEN_IDENT;
    }
}

static int skip_comment(const char *source, int pos, int *line, int *col) {
    if (source[pos] == '/' && source[pos + 1] == '/') {
        while (source[pos] != '\n' && source[pos] != '\0') pos++;
        *line += 1;
        *col = 1;
        return pos;
    }
    if (source[pos] == '/' && source[pos + 1] == '*') {
        pos += 2;
        while (source[pos] != '\0') {
            if (source[pos] == '\n') { (*line)++; *col = 1; }
            else (*col)++;
            pos++;
        }
        return pos;
    }
    return pos;
}

Token *lexer_tokenize(const char *source, int *token_count) {
    int capacity = 256;
    Token *tokens = malloc(capacity * sizeof(Token));
    int count = 0;
    int i = 0;
    int line = 1, col = 1;

    while (source[i] != '\0') {
        if (source[i] == ' ' || source[i] == '\t' || source[i] == '\r') { i++; col++; continue; }
        if (source[i] == '\n') { i++; line++; col = 1; continue; }

        if (source[i] == '/' && (source[i + 1] == '/' || source[i + 1] == '*')) {
            i = skip_comment(source, i, &line, &col);
            continue;
        }

        if (isalpha(source[i]) || source[i] == '_') {
            int start = i;
            while (isalnum(source[i]) || source[i] == '_') i++;
            int len = i - start;
            char *word = malloc(len + 1);
            memcpy(word, source + start, len);
            word[len] = '\0';
            Token *t = &tokens[count++];
            t->type = keyword_to_type(word);
            t->value = word;
            t->line = line;
            t->column = col;
            col += len;
            continue;
        }

        if (isdigit(source[i])) {
            int start = i;
            while (isdigit(source[i])) i++;
            if (source[i] == '.' && isdigit(source[i + 1])) { i++; while (isdigit(source[i])) i++; }
            int len = i - start;
            char *num = malloc(len + 1);
            memcpy(num, source + start, len);
            num[len] = '\0';
            Token *t = &tokens[count++];
            t->type = TOKEN_FLOAT;
            t->value = num;
            t->line = line;
            t->column = col;
            col += len;
            continue;
        }

        if (source[i] == '"') {
            i++;
            int start = i;
            while (source[i] != '"') { if (source[i] == '\\') i++; i++; }
            int len = i - start;
            char *str = malloc(len + 1);
            memcpy(str, source + start, len);
            str[len] = '\0';
            Token *t = &tokens[count++];
            t->type = TOKEN_STRING;
            t->value = str;
            t->line = line;
            t->column = col;
            i++; col += len + 2;
            continue;
        }

        Token *t = &tokens[count++];
        t->line = line;
        t->column = col;
        t->value = NULL;

        switch (source[i]) {
            case '+': t->type = TOKEN_PLUS; break;
            case '-': t->type = TOKEN_MINUS; break;
            case '*': t->type = TOKEN_STAR; break;
            case '/': t->type = TOKEN_SLASH; break;
            case '%': t->type = TOKEN_PERCENT; break;
            case '=':
                if (source[i + 1] == '=') { t->type = TOKEN_EQ; i++; col += 2; }
                else { t->type = TOKEN_NEQ; i++; col++; }
                break;
            case '!': t->type = TOKEN_EXCLAM; break;
            case '<':
                if (source[i + 1] == '=') { t->type = TOKEN_LTE; i++; col += 2; }
                else { t->type = TOKEN_LT; i++; col++; }
                break;
            case '>':
                if (source[i + 1] == '=') { t->type = TOKEN_GTE; i++; col += 2; }
                else { t->type = TOKEN_GT; i++; col++; }
                break;
            case '&':
                if (source[i + 1] == '&') { t->type = TOKEN_AND; i++; col += 2; }
                else { t->type = TOKEN_AMP; i++; col++; }
                break;
            case ':': t->type = TOKEN_COLON; break;
            case ',': t->type = TOKEN_COMMA; break;
            case '.': t->type = TOKEN_DOT; break;
            case '(': t->type = TOKEN_LPAREN; break;
            case ')': t->type = TOKEN_RPAREN; break;
            case '{': t->type = TOKEN_LBRACE; break;
            case '}': t->type = TOKEN_RBRACE; break;
            case '[': t->type = TOKEN_LBRACKET; break;
            case ']': t->type = TOKEN_RBRACKET; break;
            case '#': t->type = TOKEN_HASH; break;
            case ';': t->type = TOKEN_SEMICOLON; break;
            default: t->type = TOKEN_ERROR; break;
        }
        i++; col++;
    }

    Token *eof = &tokens[count++];
    eof->type = TOKEN_EOF;
    eof->value = NULL;
    eof->line = line;
    eof->column = col;

    *token_count = count;
    return tokens;
}

void lexer_free_tokens(Token *tokens, int count) {
    for (int i = 0; i < count; i++) {
        if (tokens[i].value) free((void *)tokens[i].value);
    }
    free(tokens);
}

const char *token_type_name(TokenType type) {
    switch (type) {
        case TOKEN_EOF: return "EOF";
        case TOKEN_IDENT: return "IDENT";
        case TOKEN_INT: return "INT";
        case TOKEN_FLOAT: return "FLOAT";
        case TOKEN_STRING: return "STRING";
        default: return "UNKNOWN";
    }
}
