#ifndef IN_OUTPUTS_H
#define IN_OUTPUTS_H

#include <stdbool.h>

typedef struct{
	char* chave;
	int prr;
}ChavePrimaria;

int HowManyLines(char* name);
ChavePrimaria* BuildPrimaryKey(char* name_withoutext, int size);
void AddStudent(char* name_withoutext, int size);
void RemoveRegisterFromFile(char* name_withoutext, int prr);
void FindInTheRegister(char* name_withoutext, int prr);
int DetermineOrder(char* name_withoutext);

#endif //IN_OUTPUTS_H