#ifndef BUILD_H
#define BUILD_H

int build_project(const char *project_dir);
int compile_to_object(const char *source, const char *output);
int link_objects(const char **objects, int count, const char *output);

#endif
