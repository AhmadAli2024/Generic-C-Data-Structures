#ifndef QUEUE_H
#define QUEUE_H
#include "GenericFunctions.h"
#include "singleLinkedList.h"

typedef struct Queue{
	SLL* list;
	int size;
	GenericOperations* types;
} Queue;

Queue* queueCreate(GenericTypes types){
	Queue* temp = malloc(sizeof(Queue));
	assert(temp != NULL);
	temp->list = SLLCreate(0,types);
	temp->size = 0;
	temp->types = getOperations(types);
	return temp;
}

void queueAdd(Queue* list,void* value){
	assert(list != NULL);
	assert(value != NULL);
	SLLAddEnd(list->list,value);
	list->size+=1;
}

void* queuePop(Queue* list){
	assert(list != NULL);
	void* temp = SLLGetAdressIndex(list->list,0)->value;
	SLLRemoveStart(list->list);
	list->size-=1;
	return temp;
}

void queueRemove(Queue* list,void* value){
	assert(list != NULL);
	assert(value != NULL);
	int index = 0;
	while(list->types->equalFn(SLLGetAdressIndex(list->list,index),value) != 0){
		index+=1;
	}
	SLLRemove(list->list,index);
	list->size-=1;
}

int queueSize(Queue* list){
	assert(list != NULL);
	return list->size;
}

void queuePrint(Queue* list){
	assert(list != NULL);
	SLLPrint(list->list);
}

void queueFree(Queue* list){
	assert(list != NULL);
	free(list->list->type);
	SLLFree(list->list);
	free(list->types);
	free(list);
}
#endif
