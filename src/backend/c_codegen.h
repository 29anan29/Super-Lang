#ifndef C_CODEGEN_H
#define C_CODEGEN_H

#include "ssa.h"

int c_codegen_generate(ASTNode *ast, const char *output_file);
int c_codegen_generate_header(ASTNode *ast, const char *header_file);
int c_codegen_map_type(const char *super_type, char *c_type, int size);

#endif
