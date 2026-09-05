#ifndef SSA_H
#define SSA_H

#include "ast.h"

typedef enum {
    SSA_OP_LOAD,
    SSA_OP_STORE,
    SSA_OP_BINARY,
    SSA_OP_CALL,
    SSA_OP_RETURN,
    SSA_OP_PHI,
    SSA_OP_ALLOC
} SSAOpType;

typedef struct SSANode {
    SSAOpType op;
    char *result;
    char *operand1;
    char *operand2;
    int line;
    struct SSANode *next;
} SSANode;

typedef struct {
    SSANode **blocks;
    int block_count;
    int *block_sizes;
} CFG;

CFG *cfg_build(ASTNode *ast);
void cfg_free(CFG *cfg);
SSANode *ssa_convert(ASTNode *ast);
void ssa_free(SSANode *ssa);
void ssa_print(SSANode *ssa);

#endif
