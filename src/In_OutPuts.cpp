#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "In_OutPuts.hpp"
#include "ArvoreB.hpp"


int HowManyLines(char* name){
	int howmany = 0;
	FILE * fpoint;
	fpoint = fopen(name, "r");
	if(!fpoint){
		printf("Arquivo não Encontrado\n");
		return 0;
	}
	while(!feof(fpoint)){
		if(fgetc(fpoint) == '\n'){
			howmany++;
		}
	}
	fclose(fpoint);
	return howmany;
}

char** BuildPrimaryKey(char* name_withoutext, int size){
	int i, j, k;
	FILE * read;
	char auxname[3];
	char auxmat[5];
	char* name = (char*) malloc(sizeof(name_withoutext)+4);
	sprintf(name, "%s.txt", name_withoutext);
	read = fopen(name, "r");
	char** KeyArray = (char**) malloc(size*sizeof(char*));
	for(k = 0; k < size; k++){
		KeyArray[k] = (char*) malloc(9*sizeof(char));
	}
	for(j = 0; j < size; j++){
		fseek(read, 55*j, 0);
		fread(auxname, sizeof(char), 3, read);
		if (auxname[0] == '*');{
			continue;
		}
		for(i = 0; i < 3; i++){
			auxname[i] = toupper(auxname[i]);
			KeyArray[j][i] = auxname[i];
		}
		fseek(read, 38, 1);
		fread(auxmat, sizeof(char), 5, read);
		KeyArray[j][3] = auxmat[0];
		KeyArray[j][4] = auxmat[1];
		KeyArray[j][5] = auxmat[2];
		KeyArray[j][6] = auxmat[3];
		KeyArray[j][7] = auxmat[4];
		KeyArray[j][8] = '\0';
	}
	fclose(read);
	free(name);
	return KeyArray;
}

void AddStudent(char* name_withoutext, int size){
	FILE * read;
	char name[42];
	char mat[5];
	char curse[2];
	char clas[1];
	char* filename = (char*) malloc(sizeof(name_withoutext)+4);
	sprintf(filename, "%s.txt", name_withoutext);
	read = fopen(filename, "r+");
	fseek(read, 55*size, 0);
	printf("Escreva o nome do aluno que será adicionado em até 42 espaços: \n");
	scanf(" %[^\n]", name);
	fprintf(read, "%s", name);
	int sizename = strlen(name);
	for(int i = sizename; i <= 40; i++){
		fprintf(read, " ");
	}
	printf("Escreva a matrícula do aluno que será adicionado em até 5 espaços: \n");
	scanf(" %[^\n]", mat);
	fprintf(read, "%s  ", mat);
	printf("Escreva o curso do aluno que será adicionado em até 2 espaços (letras maiúsculas): \n");
	scanf(" %[^\n]", curse);
	fprintf(read, "%s  ", curse);
	printf("Escreva a turma do aluno que será adicionado em até 1 espaço (letra maiúscula): \n");
	scanf(" %[^\n]", clas);
	fprintf(read, "%s\n", clas);
	free(filename);
	fclose(read);
}