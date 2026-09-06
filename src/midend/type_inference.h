/*
 * type_inference.h — type_inference for SUPER compiler.
 */
/* SPDX-License-Identifier: MIT */

#ifndef TYPE_INFERENCE_H
#define TYPE_INFERENCE_H

#include "ast.h"

typedef struct {
    char *name;
    char *type;
} TypeBinding;

typedef struct {
    TypeBinding *bindings;
    int count;
    int capacity;
} TypeEnv;

TypeEnv *type_env_create(void);
void type_env_free(TypeEnv *env);
int type_env_lookup(TypeEnv *env, const char *name, char **type);
int type_env_insert(TypeEnv *env, const char *name, const char *type);

int infer_types(ASTNode *ast);
void infer_free_bindings(TypeBinding *bindings, int count);

#endif
