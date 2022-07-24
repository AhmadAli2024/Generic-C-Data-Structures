#ifndef DOUBLELINKEDLIST_H
#define DOUBLELINKEDLIST_H
#include "GenericFunctions.h"

typedef struct DLLNode{
	void* value;
	struct DLLNode* next;
	struct DLLNode* back;
} DLLNode;

typedef struct DLL{
	struct DLLNode* root;
	struct DLLNode* tail;
	GenericOperations* type;
	int size;
} DLL;

DLLNode* DLLNodeGetTail(DLLNode* root,int* index){
	DLLNode* temp = root;
	while(temp != NULL){
		temp = temp->next;
		*index+=1;
	}
	return temp;
}

void DLLAddEnd(DLL* list,void* next){
	assert(list != NULL);
	list->size+=1;
	DLLNode* temp = calloc(1,sizeof(DLLNode));
	temp->value = next;
	temp->next = NULL;
	temp->back = list->tail;
	list->tail->next = temp;
	list->tail = temp;
}

void DLLAddStart(DLL* list,void* next){
	assert(list != NULL);
	list->size+=1;
	DLLNode* temp = calloc(1,sizeof(DLLNode));
	temp->value = next;
	temp->next = list->root;
	temp->back = NULL;
	list->root->back = temp;
	list->root = temp;
}

DLL* DLLCreate(int size,GenericTypes types){
	assert(size >= 0);
	DLL* list = calloc(1,sizeof(DLL));
	assert(list != NULL);
	DLLNode* root = calloc(1,sizeof(DLLNode));
	assert(root != NULL);
	list->root = root;
	list->tail = root;
	list->type = getOperations(types);
	DLLNode* temp = root;
	list->size = 1;
	for(int i=0;i<size-1;i++){
		DLLAddEnd(list,NULL);
	}
	return list;
}

DLLNode* DLLGetAdressIndex(DLL* list,int index){
	assert(list != NULL);
	assert(index >= 0 && list->size > index);
	DLLNode* temp = list->root;
	for(int i=0;i<index;i++){
		temp = temp->next;
		if(temp == NULL) { return NULL; }
	}
	return temp;
}

DLLNode* DLLGetAdressValue(DLL* list,void* value){
	assert(list != NULL);
	DLLNode* temp = list->root;
	while(temp->value != value){
		temp = temp->next;
		if(temp == NULL){
			return NULL;
		}
	}
	return temp;
}

void DLLAdd(DLL* list,int index,void* value){
	assert(index >= 0 && list->size >= index);
	assert(list != NULL);
	if(index == 0){ DLLAddStart(list,value); return; }
	if(index == list->size){ DLLAddEnd(list,value); return; }
	list->size+=1;
	DLLNode* newValue = calloc(1,sizeof(DLLNode));
	assert(newValue != NULL);
	newValue->value = value;
	DLLNode* temp = DLLGetAdressIndex(list,index-1);
	DLLNode* temp1 = temp->next;
	temp->next = newValue;
	newValue->back = temp;
	newValue->next = temp1;
	temp1->back = newValue;
	return;
}

void DLLRemoveEnd(DLL* list){
	assert(list != NULL);
	DLLNode* temp = list->tail->back;
	temp->next = NULL;
	free(list->tail);
	list->tail = temp;
}

void DLLRemoveStart(DLL* list){
	assert(list != NULL);
	DLLNode* temp = list->root->next;
	free(list->root);
	list->root = temp;
}

void DLLRemove(DLL* list,int index){
	assert(list != NULL);
	assert(index >= 0 && list->size >= index);
	if(index == 0){
		DLLRemoveStart(list);
		return;
	}
	DLLNode* temp = DLLGetAdressIndex(list,index-1);
	if(temp->next == list->tail){
		DLLRemoveEnd(list);
		return;
	}
	list->size-=1;
	DLLNode* temp1 = temp->next->next;
	free(temp->next);
	temp->next = temp1;
	temp1->back = temp;
	return;
}

void DLLSet(DLL* list,int index,void* value){
	assert(list != NULL);
	assert(index >= 0 && list->size > index);
	DLLGetAdressIndex(list,index)->value = value;
	return;
}

void DLLPrint(DLL* list){
	assert(list != NULL);
	DLLNode* temp = list->root;
	while(temp->next != NULL){
		list->type->printFn(temp->value);
		printf(", ");
		temp = temp->next;
	}
	list->type->printFn(temp->value);
	printf("\n");
}

void DLLFree(DLL* list){
	assert(list != NULL);
	while(list->root->next != NULL){
		DLLRemoveEnd(list);
	}
	free(list->root);
	free(list);
}
#endif
