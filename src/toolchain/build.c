/*
 * build.c — Build system integration for SUPER compiler.
 */
/* SPDX-License-Identifier: MIT */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "build.h"

int build_project(const char *project_dir) {
    char cmd[1024];
    snprintf(cmd, sizeof(cmd), "make -C %s", project_dir);
    int result = system(cmd);
    return result == 0;
}

int compile_to_object(const char *source, const char *output) {
    char cmd[1024];
    snprintf(cmd, sizeof(cmd), "gcc -c %s -o %s", source, output);
    int result = system(cmd);
    return result == 0;
}

int link_objects(const char **objects, int count, const char *output) {
    char cmd[2048];
    cmd[0] = '\0';
    strcat(cmd, "gcc");
    for (int i = 0; i < count; i++) {
        strcat(cmd, " ");
        strcat(cmd, objects[i]);
    }
    strcat(cmd, " -o ");
    strcat(cmd, output);
    int result = system(cmd);
    return result == 0;
}
