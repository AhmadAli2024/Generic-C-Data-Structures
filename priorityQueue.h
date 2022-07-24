#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H
#include "GenericFunctions.h"
#include "binaryHeap.h"

typedef struct PQ{
	int size;
	BH* list;
} PQ;

PQ* PQCreate(GenericTypes types){
	PQ* temp = calloc(1,sizeof(PQ));
	assert(temp != NULL);
	temp->size = 0;
	temp->list = BHCreate(types);
	return temp;
}

void PQAdd(PQ* list,void* value){
	assert(list != NULL);
	assert(value != NULL);
	BHAdd(list->list,value);
	list->size+=1;
}

void PQPoll(PQ* list){
	assert(list != NULL);
	assert(list->size != 0);
	BHPoll(list->list);
	list->size-=1;
}

void PQRemove(PQ* list,void* value){
	assert(list != NULL);
	assert(list != NULL);
	BHRemove(list->list,value);
	list->size-=1;
}

void PQPrint(PQ* list){
	assert(list != NULL);
	BHPrint(list->list);
}

void PQFree(PQ* list){
	assert(list != NULL);
	BHFree(list->list);
	free(list);
}
#endif
