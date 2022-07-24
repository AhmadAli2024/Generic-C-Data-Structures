#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H
#include "GenericFunctions.h"

//The struct
typedef struct AL{
	int size;
	int initalSize;
	void** array;
	GenericOperations* type;
} AL;

void ALFree(AL* obj){
	free(obj->array);
	free(obj->type);
	free(obj);
}

AL* ALCreate(int size,GenericTypes types){
	assert(size >= 0);
	AL* temp = malloc(sizeof(AL));
	assert(temp != NULL);
	temp->size = 0;
	temp->initalSize = size;
	temp->array = malloc(sizeof(void*)*temp->initalSize);
	assert(temp->array != NULL);
	for(int i=0;i<temp->initalSize;i++){
		temp->array[i] = NULL;
	}
	temp->type = getOperations(types);
	assert(temp->array != NULL);
	return temp;
}

void ALAddEnd(AL* obj,void* value){
	assert(value != NULL);
	assert(obj != NULL);
	obj->size+=1;
	if(obj->size < obj->initalSize && obj->array[obj->size-1]  == NULL){
		obj->array[obj->size-1] = value;
		return;
	}
	obj->array = realloc(obj->array,sizeof(void*[obj->size]));
	assert(obj->array != NULL);
	obj->array[obj->size-1] = value;
}

void ALAdd(AL* obj,int index,void* value){
	assert(obj != NULL);
	assert(value != NULL);
	assert(index < 0 || (index > obj->initalSize && obj->initalSize != 0) || (obj->initalSize == 0 && index > obj->size));
	if(index == obj->size || (index == obj->initalSize && obj->initalSize != 0)){
		ALAddEnd(obj,value);
		return;
	}
	if(obj->array[index] == NULL){
		obj->array[index] = value;
		return;
	}	
	obj->size+=1;
	obj->array = realloc(obj->array,sizeof(void*)*obj->size);
	assert(obj->array != NULL);
	for(int i=obj->size-1;i>index;i--){
		obj->array[i] = obj->array[i-1];
	}
	obj->array[index] = value;
	return;
}

void ALRemove(AL* obj,int index){
	assert(obj != NULL);
	assert(index >= 0 && index < obj->size);
	obj->size-=1;
	for(int i=index;i<obj->size;i++){
		obj->array[i] = obj->array[i+1];
	}
}

void* ALSet(AL* obj,int index,void* value){
	assert(obj != NULL);
	if(obj->initalSize > obj->size){
		assert(index >= 0 && index < obj->initalSize);
	}
	else{
		assert(index >= 0 && index < obj->size);
	}
	void* temp = obj->array[index];
	obj->array[index] = value;
	return temp;
}

void* ALGetIndex(AL* obj,int index){
	assert(obj != NULL);
	if(index < 0 || (index >= obj->size && index >= obj->initalSize)){
		return NULL;
	}
	return obj->array[index];
}

int ALGetValue(AL* obj,void* value){
	assert(obj != NULL);
	assert(value != NULL);
	for(int i=0;i<obj->size;i++){
		if(obj->array[i] == value){
			return i;
		}
	}
	return -1;
}

void ALPrint(AL* list){
	assert(list != NULL);
	if(list->size == 0 && list->initalSize == 0){
		printf("Array List is Empty");
		return;
	}
	if(list->size < list->initalSize){
		for(int i=0;i<list->initalSize-1;i++){
			list->type->printFn(list->array[i]);
		printf(", ");
		}
		list->type->printFn(list->array[list->initalSize-1]);
		return;
	}
	for(int i=0;i<list->size-1;i++){
		list->type->printFn(list->array[i]);
		printf(", ");
	}
	list->type->printFn(list->array[list->size-1]);
}
#endif
