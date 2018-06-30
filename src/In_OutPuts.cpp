#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "In_OutPuts.hpp"


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
