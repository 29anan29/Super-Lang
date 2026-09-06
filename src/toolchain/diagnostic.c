/*
 * diagnostic.c — Error diagnostic system for SUPER compiler.
 */
/* SPDX-License-Identifier: MIT */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "diagnostic.h"

typedef struct {
    char *message;
    int line;
    int column;
    int severity;
} DiagnosticEntry;

static DiagnosticEntry *diags;
static int diag_count;
static int diag_capacity;

static DiagnosticEntry *get_ctx(void) {
    if (!diags) {
        diag_capacity = 64;
        diag_count = 0;
        diags = calloc(diag_capacity, sizeof(DiagnosticEntry));
    }
    return diags;
}

void diagnostic_init(void) {
    get_ctx();
}

void diagnostic_emit(const char *file, int line, int col, const char *message) {
    DiagnosticEntry *ctx = get_ctx();
    if (diag_count >= diag_capacity) {
        diag_capacity *= 2;
        diags = realloc(diags, diag_capacity * sizeof(DiagnosticEntry));
    }
    diags[diag_count].line = line;
    diags[diag_count].column = col;
    diags[diag_count].message = strdup(message);
    diags[diag_count].severity = 1;
    diag_count++;
}

void diagnostic_print(const char *source_file) {
    for (int i = 0; i < diag_count; i++) {
        fprintf(stderr, "Error: %s:%d:%d: %s\n",
            source_file, diags[i].line, diags[i].column, diags[i].message);
    }
}

void diagnostic_free(void) {
    if (diags) {
        for (int i = 0; i < diag_count; i++) {
            if (diags[i].message) free(diags[i].message);
        }
        free(diags);
        diags = NULL;
        diag_count = 0;
    }
}

int diagnostic_count(void) {
    return diag_count;
}
