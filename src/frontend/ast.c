/*
 * ast.c — AST node implementation for SUPER compiler.
 */
/* SPDX-License-Identifier: MIT */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

ASTNode *ast_create(ASTNodeType type, int line, int column) {
    ASTNode *node = calloc(1, sizeof(ASTNode));
    node->type = type;
    node->line = line;
    node->column = column;
    node->value = NULL;
    node->children = NULL;
    node->child_count = 0;
    node->left = NULL;
    node->right = NULL;
    node->type_name = NULL;
    return node;
}

void ast_add_child(ASTNode *parent, ASTNode *child) {
    parent->child_count++;
    parent->children = realloc(parent->children, parent->child_count * sizeof(ASTNode *));
    parent->children[parent->child_count - 1] = child;
}

void ast_free(ASTNode *node) {
    if (!node) return;
    if (node->value) free(node->value);
    if (node->children) {
        for (int i = 0; i < node->child_count; i++) {
            ast_free(node->children[i]);
        }
        free(node->children);
    }
    if (node->left) ast_free(node->left);
    if (node->right) ast_free(node->right);
    if (node->type_name) free(node->type_name);
    free(node);
}

static const char *node_type_name(ASTNodeType type) {
    switch (type) {
        case AST_PROGRAM: return "Program";
        case AST_FN_DEF: return "FnDef";
        case AST_PUB_FN_DEF: return "PubFnDef";
        case AST_STRUCT_DEF: return "StructDef";
        case AST_ENUM_DEF: return "EnumDef";
        case AST_VAR_DECL: return "VarDecl";
        case AST_IF_STMT: return "IfStmt";
        case AST_FOR_STMT: return "ForStmt";
        case AST_MATCH_STMT: return "MatchStmt";
        case AST_UNSAFE_STMT: return "UnsafeStmt";
        case AST_IMPORT_STMT: return "ImportStmt";
        case AST_EXTERN_BLOCK: return "ExternBlock";
        case AST_RETURN_STMT: return "ReturnStmt";
        case AST_EXPR_STMT: return "ExprStmt";
        default: return "Unknown";
    }
}

void ast_print(ASTNode *node, int indent) {
    if (!node) return;
    for (int i = 0; i < indent; i++) printf("  ");
    printf("%s", node_type_name(node->type));
    if (node->value) printf("(%s)", node->value);
    if (node->type_name) printf(" : %s", node->type_name);
    printf(" [line:%d col:%d]\n", node->line, node->column);
    if (node->children) {
        for (int i = 0; i < node->child_count; i++) {
            ast_print(node->children[i], indent + 1);
        }
    }
}
