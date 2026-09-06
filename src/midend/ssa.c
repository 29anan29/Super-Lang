/*
 * ssa.c — SSA construction and CFG for SUPER.
 */
/* SPDX-License-Identifier: MIT */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ssa.h"

static SSANode *new_ssa_node(SSAOpType op, const char *result, const char *op1, const char *op2) {
    SSANode *node = malloc(sizeof(SSANode));
    node->op = op;
    node->result = result ? strdup(result) : NULL;
    node->operand1 = op1 ? strdup(op1) : NULL;
    node->operand2 = op2 ? strdup(op2) : NULL;
    node->line = 0;
    node->next = NULL;
    return node;
}

CFG *cfg_build(ASTNode *ast) {
    CFG *cfg = malloc(sizeof(CFG));
    cfg->block_count = 1;
    cfg->block_sizes = malloc(sizeof(int));
    cfg->block_sizes[0] = 0;
    cfg->blocks = malloc(sizeof(SSANode *));
    cfg->blocks[0] = NULL;
    return cfg;
}

void cfg_free(CFG *cfg) {
    if (cfg->blocks) {
        for (int i = 0; i < cfg->block_count; i++) {
            if (cfg->blocks[i]) {
                SSANode *n = cfg->blocks[i];
                while (n) {
                    SSANode *next = n->next;
                    if (n->result) free(n->result);
                    if (n->operand1) free(n->operand1);
                    if (n->operand2) free(n->operand2);
                    free(n);
                    n = next;
                }
            }
        }
        free(cfg->blocks);
    }
    if (cfg->block_sizes) free(cfg->block_sizes);
    free(cfg);
}

SSANode *ssa_convert(ASTNode *ast) {
    SSANode *head = new_ssa_node(SSA_OP_ALLOC, "entry", NULL, NULL);
    SSANode *tail = head;

    if (ast && ast->children) {
        for (int i = 0; i < ast->child_count; i++) {
            ASTNode *child = ast->children[i];
            if (child->type == AST_FN_DEF || child->type == AST_PUB_FN_DEF) {
                tail->next = new_ssa_node(SSA_OP_LOAD, child->value, NULL, NULL);
                tail = tail->next;
            }
        }
    }
    return head;
}

void ssa_free(SSANode *ssa) {
    while (ssa) {
        SSANode *next = ssa->next;
        if (ssa->result) free(ssa->result);
        if (ssa->operand1) free(ssa->operand1);
        if (ssa->operand2) free(ssa->operand2);
        free(ssa);
        ssa = next;
    }
}

void ssa_print(SSANode *ssa) {
    int i = 0;
    while (ssa) {
        printf("  [%d] ", i);
        switch (ssa->op) {
            case SSA_OP_LOAD: printf("load %s", ssa->result); break;
            case SSA_OP_STORE: printf("store %s = %s", ssa->result, ssa->operand1); break;
            case SSA_OP_BINARY: printf("binop %s = %s %s",
                ssa->result, ssa->operand1, ssa->operand2); break;
            case SSA_OP_CALL: printf("call %s(%s)", ssa->result, ssa->operand1); break;
            case SSA_OP_RETURN: printf("return %s", ssa->operand1); break;
            case SSA_OP_PHI: printf("phi %s", ssa->result); break;
            case SSA_OP_ALLOC: printf("alloc %s", ssa->result); break;
        }
        printf("\n");
        ssa = ssa->next;
        i++;
    }
}
