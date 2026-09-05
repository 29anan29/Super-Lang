#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "c_codegen.h"

static const char *type_map[][2] = {
    {"int", "int"},
    {"float", "double"},
    {"bool", "int"},
    {"string", "char*"},
    {"void", "void"},
    {NULL, NULL}
};

int c_codegen_map_type(const char *super_type, char *c_type, int size) {
    for (int i = 0; type_map[i][0]; i++) {
        if (strcmp(type_map[i][0], super_type) == 0) {
            strncpy(c_type, type_map[i][1], size);
            c_type[size - 1] = '\0';
            return 1;
        }
    }
    strncpy(c_type, super_type, size);
    c_type[size - 1] = '\0';
    return 0;
}

static void emit_c_code(FILE *f, ASTNode *node, int indent) {
    if (!node) return;
    for (int i = 0; i < indent; i++) fprintf(f, "    ");

    switch (node->type) {
        case AST_FN_DEF:
        case AST_PUB_FN_DEF: {
            if (node->type == AST_PUB_FN_DEF) fprintf(f, "extern \"C\" ");
            fprintf(f, "int %s(", node->value ? node->value : "unknown");
            // TODO: emit parameters
            fprintf(f, ") {\n");
            if (node->children) {
                for (int i = 0; i < node->child_count; i++) {
                    emit_c_code(f, node->children[i], indent + 1);
                }
            }
            for (int i = 0; i < indent; i++) fprintf(f, "    ");
            fprintf(f, "}\n\n");
            break;
        }
        case AST_RETURN_STMT:
            fprintf(f, "    return 0;\n");
            break;
        case AST_VAR_DECL:
            fprintf(f, "    int %s = 0;\n", node->value ? node->value : "unknown");
            break;
        case AST_STRUCT_DEF:
            fprintf(f, "typedef struct {\n");
            if (node->children) {
                for (int i = 0; i < node->child_count; i++) {
                    emit_c_code(f, node->children[i], indent + 1);
                }
            }
            for (int i = 0; i < indent; i++) fprintf(f, "    ");
            fprintf(f, "} %s;\n\n", node->value ? node->value : "unknown");
            break;
        default:
            break;
    }
}

int c_codegen_generate(ASTNode *ast, const char *output_file) {
    FILE *f = fopen(output_file, "w");
    if (!f) {
        fprintf(stderr, "Error: cannot open output file %s\n", output_file);
        return 0;
    }

    fprintf(f, "#include <stdio.h>\n");
    fprintf(f, "#include <stdlib.h>\n\n");

    if (ast && ast->children) {
        for (int i = 0; i < ast->child_count; i++) {
            emit_c_code(f, ast->children[i], 0);
        }
    }

    fclose(f);
    return 1;
}

int c_codegen_generate_header(ASTNode *ast, const char *header_file) {
    FILE *f = fopen(header_file, "w");
    if (!f) {
        fprintf(stderr, "Error: cannot open header file %s\n", header_file);
        return 0;
    }

    fprintf(f, "#ifndef SUPER_GENERATED_H\n");
    fprintf(f, "#define SUPER_GENERATED_H\n\n");

    if (ast && ast->children) {
        for (int i = 0; i < ast->child_count; i++) {
            ASTNode *child = ast->children[i];
            if (child->type == AST_FN_DEF || child->type == AST_PUB_FN_DEF) {
                fprintf(f, "int %s();\n", child->value ? child->value : "unknown");
            }
        }
    }

    fprintf(f, "\n#endif\n");
    fclose(f);
    return 1;
}
