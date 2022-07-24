#ifndef UNION_H
#define UNION_H
#include "GenericFunctions.h"
#include "DynamicArray.h"
#include "Dictionary.h"

typedef struct Union{
	Dic* list;
	Dic* sizes;
	int size;
	int groupNum;
	GenericOperations* type;
} Union;

Union* unionCreate(GenericTypes types){
	Union* temp = malloc(sizeof(Union));
	assert(temp != NULL);
	temp->size = 0;
	temp->groupNum = 0;
	temp->list = DicCreate(types);
	temp->sizes = DicCreate(types);
	temp->type = getOperations(types);
	return temp;
}

void unionAdd(Union* list,void* value){
	assert(list != NULL);
	assert(value != NULL);
	DicAdd(list->list,value,value);
	int* size = calloc(1,sizeof(int));
	DicAdd(list->sizes,value,(void*)size);
	list->size+=1;
	list->groupNum+=1;
}

void* unionFind(Union* list,void* obj){
	assert(list != NULL);
	assert(obj != NULL);
	void* parent = DicGet(list->list,obj);
	while(DicGet(list->list,parent) != parent){
		parent = DicGet(list->list,parent);
	}
	void* temp = obj;
	while(list->type->compFn(temp,parent) != 1){
		DicChange(list->list,temp,parent);
	}
	return parent;
}

void unionElements(Union* list,void* obj1,void* obj2){
	assert(list != NULL);
	assert(obj1 != NULL);
	assert(obj2 != NULL);
	void* parent1 = unionFind(list,obj1);
	int size1 = *(int*)DicGet(list->sizes,parent1);
	void* parent2 = unionFind(list,obj2);
	int size2 = *(int*)DicGet(list->sizes,parent2);
	free(DicGet(list->sizes,parent1));
	free(DicGet(list->sizes,parent2));
	int* newSize = malloc(sizeof(int));
	*newSize = size1+size2;
	if(size1 >= size2){
		DicChange(list->sizes,parent1,newSize);
		DicChange(list->list,parent2,parent1);
		DicRemove(list->sizes,parent2);
	}
	else{
		DicChange(list->sizes,parent2,newSize);
		DicChange(list->list,parent1,parent2);
		DicRemove(list->sizes,parent1);
	}
	list->groupNum-=1;
}

void unionFree(Union* list){
	DicFree(list->list,0);
	DicFree(list->sizes,1);
	free(list->type);
	free(list);
}
#endif
