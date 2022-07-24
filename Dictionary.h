#ifndef DICTIONARY_H
#define DICTIONARY_H
#include "GenericFunctions.h"
#include "HashTable.h"

typedef struct Dic{
	HT* list;
} Dic;

Dic* DicCreate(GenericTypes types){
	Dic* temp = malloc(sizeof(Dic));
	assert(temp != NULL);
	temp->list = HTCreate(10,types);
	assert(temp->list != NULL);
	return temp;
}

void DicAdd(Dic* list,void* name,void* data){
	assert(list != NULL);
	assert(name != NULL);
	assert(data != NULL);
	HTAdd(&list->list,HTCreateEntry(list->list,name,data));
}

void DicRemove(Dic* list,void* name){
	assert(list != NULL);
	assert(name != NULL);
	HTRemove(list->list,name);
}

void* DicGet(Dic* list,void* name){
	assert(list != NULL);
	assert(name != NULL);
	return HTGet(list->list,name)->data;
}

void DicChange(Dic* list,void* name,void* value){
	assert(list != NULL);
	assert(name != NULL);
	HTChangeData(list->list,name,value);
}

void DicFree(Dic* list,int dataFree){
	assert(list != NULL);
	HTFree(list->list,dataFree);
	free(list);
}
#endif
