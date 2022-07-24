#ifndef STACK_H
#define STACK_H
#include "singleLinkedList.h"
#include "GenericFunctions.h"

typedef struct Stack{
	struct SLL* list;
	int size;
} Stack;

Stack* stackCreate(GenericTypes types){
	Stack* temp = calloc(1,sizeof(Stack));
	assert(temp != NULL);
	temp->size = 0;
	temp->list = SLLCreate(0,types);
	return temp;
}

void stackPush(Stack* list,void* value){
	if(list->size == 0){
		list->list->root = malloc(sizeof(SLLNode));
		list->list->root->value = value;
		list->list->root->next = NULL;
		list->size+=1;
		return;
	}
	assert(list != NULL);
	SLLAddStart(list->list,value);
	list->size+=1;
}

void stackPop(Stack* list){
	assert(list != NULL);
	SLLRemoveStart(list->list);
	list->size-=1;
}

void* stackPeek(Stack* list){
	assert(list != NULL);
	return list->list->root->value;
}

int stackSize(Stack* list){
	assert(list != NULL);
	return list->size;
}

void stackPrint(Stack* list){
	assert(list != NULL);
	SLLPrint(list->list);
}

void stackFree(Stack* list){
	assert(list != NULL);
	SLLFree(list->list);
	free(list);
}
#endif
