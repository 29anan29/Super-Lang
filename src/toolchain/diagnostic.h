/*
 * diagnostic.h — diagnostic for SUPER compiler.
 */
/* SPDX-License-Identifier: MIT */

#ifndef DIAGNOSTIC_H
#define DIAGNOSTIC_H

void diagnostic_init(void);
void diagnostic_emit(const char *file, int line, int col, const char *message);
void diagnostic_print(const char *source_file);
void diagnostic_free(void);
int diagnostic_count(void);

#endif
