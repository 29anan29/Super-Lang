#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "type_inference.h"

TypeEnv *type_env_create(void) {
    TypeEnv *env = malloc(sizeof(TypeEnv));
    env->capacity = 64;
    env->count = 0;
    env->bindings = malloc(env->capacity * sizeof(TypeBinding));
    return env;
}

void type_env_free(TypeEnv *env) {
    for (int i = 0; i < env->count; i++) {
        if (env->bindings[i].name) free(env->bindings[i].name);
        if (env->bindings[i].type) free(env->bindings[i].type);
    }
    free(env->bindings);
    free(env);
}

int type_env_lookup(TypeEnv *env, const char *name, char **type) {
    for (int i = 0; i < env->count; i++) {
        if (strcmp(env->bindings[i].name, name) == 0) {
            *type = env->bindings[i].type;
            return 1;
        }
    }
    return 0;
}

int type_env_insert(TypeEnv *env, const char *name, const char *type) {
    if (env->count >= env->capacity) {
        env->capacity *= 2;
        env->bindings = realloc(env->bindings, env->capacity * sizeof(TypeBinding));
    }
    env->bindings[env->count].name = strdup(name);
    env->bindings[env->count].type = strdup(type);
    env->count++;
    return 1;
}

static const char *infer_expr_type(ASTNode *expr, TypeEnv *env) {
    if (!expr) return "unknown";
    switch (expr->type) {
        case AST_LITERAL:
            if (expr->value && strchr(expr->value, '.')) return "float";
            return "int";
        case AST_IDENT: {
            char *t;
            if (type_env_lookup(env, expr->value, &t)) return t;
            return "unknown";
        }
        default:
            return "unknown";
    }
}

static void infer_node(ASTNode *node, TypeEnv *env) {
    if (!node) return;
    if (node->type == AST_IDENT && node->value) {
        char *t;
        if (!type_env_lookup(env, node->value, &t)) {
            type_env_insert(env, node->value, "int");
        }
    }
    if (node->children) {
        for (int i = 0; i < node->child_count; i++) {
            infer_node(node->children[i], env);
        }
    }
}

int infer_types(ASTNode *ast) {
    TypeEnv *env = type_env_create();
    infer_node(ast, env);
    type_env_free(env);
    return 1;
}

void infer_free_bindings(TypeBinding *bindings, int count) {
    for (int i = 0; i < count; i++) {
        if (bindings[i].name) free(bindings[i].name);
        if (bindings[i].type) free(bindings[i].type);
    }
}
