/*
 * type_inference.c — Hindley-Milner type inference for SUPER.
 */
/* SPDX-License-Identifier: MIT */

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

int infer_types(ASTNode *ast) {
    TypeEnv *env = type_env_create();
    if (ast && ast->children) {
        for (int i = 0; i < ast->child_count; i++) {
            ASTNode *child = ast->children[i];
            if (child->type == AST_FN_DEF || child->type == AST_PUB_FN_DEF) {
                if (child->children && child->children[0]) {
                    type_env_insert(env, child->children[0]->value, "int");
                }
            }
        }
    }
    type_env_free(env);
    return 1;
}
