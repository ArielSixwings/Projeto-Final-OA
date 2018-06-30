#ifndef IN_OUTPUTS_H
#define IN_OUTPUTS_H

#include <stdbool.h>

int HowManyLines(char* name);
char** BuildPrimaryKey(char* name, int size);
void AddStudent(char* name_withoutext, int size);

#endif //IN_OUTPUTS_H