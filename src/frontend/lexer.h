#ifndef LEXER_H
#define LEXER_H

typedef enum {
    TOKEN_EOF = 0,
    TOKEN_IDENT,
    TOKEN_INT,
    TOKEN_FLOAT,
    TOKEN_STRING,
    TOKEN_BOOL,
    TOKEN_KEYWORD_FN,
    TOKEN_KEYWORD_PUB,
    TOKEN_KEYWORD_STRUCT,
    TOKEN_KEYWORD_ENUM,
    TOKEN_KEYWORD_MATCH,
    TOKEN_KEYWORD_IF,
    TOKEN_KEYWORD_ELSE,
    TOKEN_KEYWORD_FOR,
    TOKEN_KEYWORD_UNSAFE,
    TOKEN_KEYWORD_IMPORT,
    TOKEN_KEYWORD_EXTERN,
    TOKEN_KEYWORD_LET,
    TOKEN_KEYWORD_RETURN,
    TOKEN_KEYWORD_OUT,
    TOKEN_KEYWORD_IN,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_STAR,
    TOKEN_SLASH,
    TOKEN_PERCENT,
    TOKEN_EQ,
    TOKEN_NEQ,
    TOKEN_LT,
    TOKEN_GT,
    TOKEN_LTE,
    TOKEN_GTE,
    TOKEN_AND,
    TOKEN_OR,
    TOKEN_NOT,
    TOKEN_PLUS_EQ,
    TOKEN_MINUS_EQ,
    TOKEN_STAR_EQ,
    TOKEN_SLASH_EQ,
    TOKEN_PERCENT_EQ,
    TOKEN_INC,
    TOKEN_DEC,
    TOKEN_COLON,
    TOKEN_COMMA,
    TOKEN_DOT,
    TOKEN_ARROW,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_LBRACE,
    TOKEN_RBRACE,
    TOKEN_LBRACKET,
    TOKEN_RBRACKET,
    TOKEN_HASH,
    TOKEN_EXCLAM,
    TOKEN_AMP,
    TOKEN_AMP_MUT,
    TOKEN_SEMICOLON,
    TOKEN_ERROR
} TokenType;

typedef struct {
    TokenType type;
    const char *value;
    int line;
    int column;
} Token;

Token *lexer_tokenize(const char *source, int *token_count);
void lexer_free_tokens(Token *tokens, int count);
const char *token_type_name(TokenType type);

#endif
