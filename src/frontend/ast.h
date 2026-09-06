/*
 * ast.h — ast for SUPER compiler.
 */
/* SPDX-License-Identifier: MIT */

#ifndef AST_H
#define AST_H

typedef enum {
    AST_PROGRAM,
    AST_FN_DEF,
    AST_PUB_FN_DEF,
    AST_STRUCT_DEF,
    AST_ENUM_DEF,
    AST_VAR_DECL,
    AST_IF_STMT,
    AST_FOR_STMT,
    AST_MATCH_STMT,
    AST_UNSAFE_STMT,
    AST_IMPORT_STMT,
    AST_EXTERN_BLOCK,
    AST_RETURN_STMT,
    AST_EXPR_STMT
} ASTNodeType;

typedef enum {
    AST_BINOP,
    AST_UNOP,
    AST_CALL,
    AST_FIELD_ACCESS,
    AST_INDEX,
    AST_LITERAL,
    AST_IDENT,
    AST_CAST
} ASTExprType;

typedef struct ASTNode ASTNode;

struct ASTNode {
    ASTNodeType type;
    int line;
    int column;
    char *value;
    ASTNode **children;
    int child_count;
    ASTNode *left;
    ASTNode *right;
    char *type_name;
};

ASTNode *ast_create(ASTNodeType type, int line, int column);
void ast_add_child(ASTNode *parent, ASTNode *child);
void ast_free(ASTNode *node);
void ast_print(ASTNode *node, int indent);

#endif
