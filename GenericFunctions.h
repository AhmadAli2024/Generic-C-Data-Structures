#ifndef GENERIC_FUNCTIONS_H
#define GENERIC_FUNCTIONS_H
#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
#include<float.h>
#include<string.h>
#include<math.h>

typedef enum{
	DOUBLE = 1,
	INT = 2,
	STRING = 3,
	CHAR = 4,
	VOID = 5
} GenericTypes;

typedef struct{
	void (*printFn)(void*);
	int (*compFn)(void*,void*);
	int (*toInt)(void*);
	int (*equalFn)(void*,void*);
	size_t (*getSize)(void*);
	void* (*add)(void*,void*);
	GenericTypes type;
} GenericOperations;	

//DOUBLE
void printDouble(void* x){
	if(x == NULL){
		printf("%f",0.0);
		return;
	} 
	printf("%f",*(double*)x);
}

int compDouble(void* x,void * y){
	if(y == NULL){
		return 1;
	}
	if(x == NULL){
		return 0;
	}	
	return *(double*)x >= *(double*)y ? 1 : 0;
}

double getDouble(void* x){
	return *(double*)x;
}

int doubleToInt(void* x){
	return (int)*(double*)x;
}

int equalDouble(void* x,void* y){
	return *(double*)x == *(double*)y ? 1 : 0;
}

size_t getSizeDouble(void* x){
	return sizeof(double);
}

void* addDouble(void* x,void* y){
	double* sum = malloc(sizeof(double));
	*sum = *(double*)x + *(double*)y;
	return (void*)sum;
}

//INT
void printInt(void* x){
	if(x == NULL){printf("%i",0);
		return;
	}
	printf("%i",*(int*)x);
}

int compInt(void* x,void * y){
	if(y == NULL){
		return 1;
	}
	if(x == NULL){
		return 0;
	}	
	return *(int*)x >= *(int*)y ? 1 : 0;
}

int getInt(void* x){
	return *(int*)x;
}

int intToInt(void* x){
	return *(int*)x;
}

int equalInt(void* x,void* y){
	return *(int*)x == *(int*)y ? 1 : 0;
}

size_t getSizeInt(void* x){
	return sizeof(int);
}

void* addInt(void* x,void* y){
	int* sum = malloc(sizeof(int));
	*sum = *(int*)x + *(int*)y;
	return (void*)sum;
}

//CHAR
void printChar(void* x){
	if(x == NULL){printf("NULL");
		return;
	}
	printf("%c",*(char*)x);
}

char getChar(void* x){
	return *(char*)x;
}

int charToInt(void* x){
	return (int)*(char*)x;
}

int equalChar(void* x,void* y){
	return *(char*)x == *(char*)y ? 1 : 0;
}

size_t getSizeChar(void* x){
	return sizeof(char);
}

void* addChar(void* x,void* y){
	char* sum = malloc(sizeof(char));
	*sum = (char)(*(int*)x + *(int*)y);
	return (void*)sum;
}

//STRING
void printString(void* x){
	if(x == NULL){
		printf("NULL");
		return;
	}
	printf("%s",*(char**)x);
}

char* getString(void** x){
	return *(char**)x;
}

int stringToInt(void* x){
	char* index = (char*)x;
	int counter = 0;
	int temp = 0;
	while(index[counter] != '\0'){
		temp+= (int)index[counter];
	}
	return temp;
}

int equalString(void* x,void* y){
	return strcmp((char*)x,(char*)y) == 0 ? 1 : 0;
}

size_t getSizeString(void* x){
	return sizeof(char)*strlen((char*)x);
}

GenericOperations* getOperations(GenericTypes types){
	GenericOperations* temp = calloc(1,sizeof(GenericOperations));
	switch(types){
		case DOUBLE:{
			temp->printFn = printDouble;
			temp->compFn = compDouble;
			temp->toInt = doubleToInt;
			temp->equalFn = equalDouble;
			temp->type = DOUBLE;
			temp->getSize = getSizeDouble;
			temp->add = addDouble;
			return temp;
		}
		case INT:{
			temp->printFn = printInt;
			temp->compFn = compInt;
			temp->toInt = intToInt;
			temp->equalFn = equalInt;
			temp->type = INT;
			temp->getSize = getSizeInt;
			temp->add = addInt;
			return temp;
		}
		case CHAR:{
			temp->printFn = printChar;
			temp->toInt = charToInt;
			temp->equalFn = equalChar;
			temp->type = CHAR;
			temp->getSize = getSizeChar;
			temp->add = addChar;
			return temp;
		}
		case STRING:{
			temp->printFn = printString;
			temp->toInt = stringToInt;
			temp->equalFn = equalString;
			temp->type = STRING;
			temp->getSize = getSizeString;
			return temp;
		}
		case VOID:{
			temp->type = VOID;
			return temp;
		}
		default:{
			assert(types == DOUBLE || types == INT || types == CHAR || types == STRING);
		}
	}
}
#endif
