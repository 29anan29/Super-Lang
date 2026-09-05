#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ssa.h"

CFG *cfg_build(ASTNode *ast) {
    CFG *cfg = malloc(sizeof(CFG));
    cfg->block_count = 1;
    cfg->block_sizes = malloc(sizeof(int));
    cfg->block_sizes[0] = 0;
    cfg->blocks = malloc(sizeof(SSANode *));
    return cfg;
}

void cfg_free(CFG *cfg) {
    if (cfg->blocks) {
        for (int i = 0; i < cfg->block_count; i++) {
            if (cfg->blocks[i]) free(cfg->blocks[i]);
        }
        free(cfg->blocks);
    }
    if (cfg->block_sizes) free(cfg->block_sizes);
    free(cfg);
}

SSANode *ssa_convert(ASTNode *ast) {
    SSANode *head = malloc(sizeof(SSANode));
    head->op = SSA_OP_LOAD;
    head->result = strdup("entry");
    head->operand1 = NULL;
    head->operand2 = NULL;
    head->line = 0;
    head->next = NULL;
    return head;
}

void ssa_free(SSANode *ssa) {
    if (!ssa) return;
    if (ssa->result) free(ssa->result);
    if (ssa->operand1) free(ssa->operand1);
    if (ssa->operand2) free(ssa->operand2);
    if (ssa->next) ssa_free(ssa->next);
    free(ssa);
}

void ssa_print(SSANode *ssa) {
    int i = 0;
    while (ssa) {
        printf("  [%d] ", i);
        switch (ssa->op) {
            case SSA_OP_LOAD: printf("load %s", ssa->result); break;
            case SSA_OP_STORE: printf("store %s = %s", ssa->result, ssa->operand1); break;
            case SSA_OP_BINARY: printf("binop %s = %s %s", ssa->result, ssa->operand1, ssa->operand2); break;
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
