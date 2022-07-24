#ifndef SINGLELINKEDLIST_H
#define SINGLELINKEDLIST_H
#include "GenericFunctions.h"

typedef struct SLLNode{
	void* value;
	struct SLLNode* next;
} SLLNode;

typedef struct SLL{
	struct SLLNode* root;
	struct SLLNode* tail;
	GenericOperations* type;
	int size;
} SLL;

SLLNode* SLLNodeGetTail(SLLNode* root,int* index){
	assert(root != NULL);
	SLLNode* temp = root;
	while(temp != NULL){
		temp = temp->next;
		*index+=1;
	}
	return temp;
}

void SLLAddEnd(SLL* list,void* value){
	assert(list != NULL);
	SLLNode* temp = malloc(sizeof(SLLNode));
	assert(temp != NULL);
	list->size+=1;
	temp->value = value;
	temp->next = NULL;
	if(list->size == 1){
		list->root = temp;
		list->tail = temp;
		return;
	}
	list->tail->next = temp;
	list->tail = temp;
}

void SLLAddStart(SLL* list,void* value){
	list->size+=1;
	assert(list != NULL);
	SLLNode* temp = malloc(sizeof(SLLNode));
	assert(temp != NULL);
	temp->value = value;
	temp->next = list->root;
	list->root = temp;
}

SLL* SLLCreate(int size,GenericTypes types){
	assert(size >= 0);
	SLL* list = malloc(sizeof(SLL));
	assert(list != NULL);
	list->size = 0;
	list->type = getOperations(types);
	if(size == 0){
		list->root = NULL;
		list->tail = NULL;
		return list;
	}
	SLLNode* root = malloc(sizeof(SLLNode));
	assert(root != NULL);
	list->root = root;
	list->tail = root;
	SLLNode* temp = root;
	for(int i=0;i<size;i++){
		SLLAddEnd(list,NULL);
	}
	return list;
}

SLLNode* SLLGetAdressIndex(SLL* list,int index){
	assert(list != NULL);
	assert(index >= 0 && list->size > index);
	SLLNode* temp = list->root;
	for(int i=0;i<index;i++){
		temp = temp->next;
		if(temp == NULL){
			return NULL;
		}
	}
	return temp;
}

SLLNode* SLLGetAdressValue(SLL* list,void* value){
	assert(list != NULL);
	assert(value != NULL);
	SLLNode* temp = list->root;
	while(temp->value != value){
		temp = temp->next;
		if(temp == NULL){
			return NULL;
		}
	}
	return temp;
}

void SLLAdd(SLL* list,int index,void* value){
	assert(list != NULL);
	assert(index >= 0 && list->size >= index);
	if(index == list->size){
		SLLAddEnd(list,value);
		return;
	}
	if(index == 0){
		SLLAddStart(list,value);
		return;
	}
	list->size+=1;
	SLLNode* newValue = malloc(sizeof(SLLNode));
	assert(newValue != NULL);
	newValue->value = value;
	SLLNode* temp = SLLGetAdressIndex(list,index-1);
	SLLNode* temp1 = temp->next;
	temp->next = newValue;
	newValue->next = temp1;
	return;
}

void SLLRemoveEnd(SLL* list){
	assert(list != NULL);
	list->size-=1;
	SLLNode* temp = list->root;
	while(temp->next != list->tail){
		temp = temp->next;
	}
	temp->next = NULL;
	free(list->tail);
	list->tail = temp;
}

void SLLRemoveStart(SLL* list){
	assert(list != NULL);
	assert(list->root != NULL);
	list->size-=1;
	SLLNode* temp = list->root->next;
	free(list->root);
	list->root = temp;
}

void SLLRemove(SLL* list,int index){
	assert(list != NULL);
	assert(index >= 0 && list->size > index);
	if(index == 0){
		SLLRemoveStart(list);
		return;
	}
	if(index == list->size-1){
		SLLRemoveEnd(list);
		return;
	}
	SLLNode* temp = SLLGetAdressIndex(list,index-1);
	if(temp->next == list->tail){
		SLLRemoveEnd(list);
		return;
	}
	list->size-=1;
	SLLNode* temp1 = temp->next->next;
	free(temp->next);
	temp->next = temp1;
	return;
}

void SLLSet(SLL* list,int index,void* value){
	assert(list != NULL);
	assert(index >= 0 && list->size > index);
	SLLGetAdressIndex(list,index)->value = value;
	return;
}

void SLLPrint(SLL* list){
	assert(list->root != NULL);
	SLLNode* temp = list->root;
	while(temp->next != NULL){
		list->type->printFn(temp->value);
		printf(", ");
		temp = temp->next;
	}
	list->type->printFn(temp->value);
	printf("\n");
}

int SLLGetSize(SLL* list){
	assert(list != NULL);
	return list->size;
}

void SLLFree(SLL* list){
	assert(list != NULL);
	if(list->root == NULL){
		free(list);
		return;
	}
	while(list->root->next != NULL){
		SLLRemoveEnd(list);
	}
	free(list->type);
	free(list->root);
	free(list);
}
#endif
