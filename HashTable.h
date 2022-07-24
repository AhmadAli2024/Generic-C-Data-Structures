#ifndef HASHTABLE_H
#define HASHTABLE_H
#include "GenericFunctions.h"
#include "singleLinkedList.h"
#include "DynamicArray.h"
#include "HashTable.h"
#include "SHA-512.h"

typedef struct HTEntry{
	void* name;
	void* data;
	uint64_t* key;
} HTEntry;

typedef struct HT{
	AL* list;
	int* indexType;
	int size;
	int count;
	GenericOperations* type;
} HT;

HT* HTReSize(HT* list);

HT* HTCreate(int size,GenericTypes types){
	assert(size > 0);
	HT* temp = malloc(sizeof(HT));
	assert(temp != NULL);
	temp->list = ALCreate(size,types);
	assert(temp->list != NULL);
	temp->indexType = calloc(size,sizeof(int));
	assert(temp->indexType != NULL);
	temp->size = size;
	temp->count = 0;
	temp->type = getOperations(types);
	return temp;
}

uint64_t* HTFunction(HT* list,void* value){
	return SHA512(value,list->type->getSize(value));
}

void HTAdd(HT** list,HTEntry* item){
	assert((*list)->count < (*list)->size);
	assert((*list) != NULL);
	assert(item != NULL);
	int index = (int)(item->key[0]%(*list)->size);
	int indexType = (*list)->indexType[index];
	(*list)->count+=1;
	SLL* tempList;
	if(indexType == 0){
		ALSet((*list)->list,index,item);
		(*list)->indexType[index] = 1;
	}
	else if(indexType == 1){
		void* tempEntry = ALGetIndex((*list)->list,index);
		ALSet((*list)->list,index,(void*)SLLCreate(0,VOID));
		tempList = ALGetIndex((*list)->list,index);
		SLLAddEnd(tempList,tempEntry);
		SLLAddEnd(tempList,(void*)item);
		(*list)->indexType[index] = 2;
	}
	else if(indexType == 2){
		tempList = (SLL*)ALGetIndex((*list)->list,index);
		SLLAddEnd(tempList,(void*)item);
		(*list)->indexType[index] = 2;
	}
	if((double)(*list)->count/(*list)->size >= 0.6){
		*list = HTReSize(*list);
	}
}

HTEntry* HTGet(HT* list,void* name){
	assert(list != NULL);
	assert(name != NULL);
	uint64_t* hash = HTFunction(list,name);
	int index = hash[0]%list->size;
	free(hash);
	if(list->indexType[index] == 0){
		return NULL;
	}
	if(list->indexType[index] == 2){
		SLLNode* temp = ((SLL*)ALGetIndex(list->list,index))->root;
		while(((HTEntry*)temp->value)->name != name){
			temp = temp->next;
			if(temp == NULL){
				return NULL;
			}
		}
		return temp->value;
	}
	return ALGetIndex(list->list,index);
}

void HTChangeData(HT* list,void* name,void* value){
	assert(list != NULL);
	assert(name != NULL);
	HTGet(list,name)->data = value;
}

HTEntry* HTCreateEntry(HT* list,void* name,void* data){
	assert(name != NULL);
	HTEntry* temp = malloc(sizeof(HTEntry));
	assert(temp != NULL);
	temp->name = name;
	temp->data = data;
	temp->key = HTFunction(list,name);
	return temp;
}

void HTRemove(HT* list,void* key){
	assert(list != NULL);
	assert(key != NULL);
	uint64_t* hash = HTFunction(list,key);
	int index = hash[0]%list->size;
	free(hash);
	int indexType = list->indexType[index];
	if(indexType == 0){
		return;
	}
	void* temp = ALGetIndex(list->list,index);
	if(indexType == 2){
		SLLNode* tempNode = ((SLL*)temp)->root;
		int count = 0;
		while(list->type->equalFn(((HTEntry*)(tempNode->value))->name,key)){
			tempNode = tempNode->next;
			if(temp == NULL){
				return;
			}
			count+=1;
		}
		list->count-=1;
		SLLRemove(temp,count);
		return;
	}
	list->count-=1;
	list->indexType[index] = 0;
	free(((HTEntry*)temp)->key);
	free(temp);
	ALSet(list->list,index,NULL);
}

uint64_t** HTKeys(HT* list){
	assert(list != NULL);
	uint64_t** array = malloc(sizeof(uint64_t)*list->count);
	assert(array != NULL);
	void* temp;
	SLLNode* tempNode;
	int indexType;
	int counter = 0;
	for(int i=0;i<list->size;i++){
		indexType = list->indexType[i];
		if(indexType == 0){
			continue;
		}
		temp = ALGetIndex(list->list,i);
		if(indexType == 1){
			array[counter] = ((HTEntry*)temp)->key;
			counter+=1;
		}
		else{
			tempNode = ((SLL*)temp)->root;
			while(tempNode != NULL){
				array[counter] = ((HTEntry*)tempNode->value)->key;
				counter+=1;
				tempNode = tempNode->next;
			}
		}
	}
	return array;
}
			
AL* HTValues(HT* list){
	assert(list != NULL);
	AL* array = ALCreate(0,VOID);
	assert(array != NULL);
	void* temp;
	SLLNode* tempNode;
	int indexType;
	int counter = 0;
	for(int i=0;i<list->size;i++){
		indexType = list->indexType[i];
		if(indexType == 0){
			continue;
		}
		temp = ALGetIndex(list->list,i);
		if(indexType == 1){
			ALAddEnd(array,(temp));
			counter+=1;
		}
		else{
			tempNode = ((SLL*)temp)->root;
			while(tempNode != NULL){
				ALAddEnd(array,tempNode->value);
				counter+=1;
				tempNode = tempNode->next;
			}
		}
	}
	return array;
}

void HTFree(HT* list,int dataFree){
	void* temp;
	SLLNode* tempNode;
	int index = 0;
	for(int i=0;i<list->size;i++){
		index = list->indexType[i];
		if(index == 0){
			continue;
		}
		temp = ALGetIndex(list->list,i);
		if(index == 1){
			free(((HTEntry*)temp)->key);
			if(dataFree == 1){
				free(((HTEntry*)temp)->data);
			}
			free(temp);
		}
		else{
			tempNode = ((SLL*)temp)->root;
			while(tempNode != NULL){
				//free(((HTEntry*)tempNode->value)->key);
				free(tempNode->value);
				tempNode = tempNode->next;
			}
			SLLFree((SLL*)temp);
		}
	}
	ALFree(list->list);
	free(list->type);
	free(list->indexType);
	free(list);
}

void HTHalfFree(HT* list){
	void* temp;
	int index = 0;
	for(int i=0;i<list->size;i++){
		temp = ALGetIndex(list->list,i);
		index = list->indexType[i];
		if(index == 2){
			SLLFree((SLL*)temp);
		}
	}
	ALFree(list->list);
	free(list->type);
	free(list->indexType);
	free(list);
}

HT* HTReSize(HT* list){
	HT* newList = HTCreate(list->size*2,list->type->type);
	AL* entries = HTValues(list);
	for(int i=0;i<list->count;i++){
		HTAdd(&newList,(HTEntry*)ALGetIndex(entries,i));
	}
	HTHalfFree(list);
	ALFree(entries);
	return newList;
}

void HTPrint(HT* list){
	assert(list != NULL);
	void* temp;
	SLLNode* tempList;
	int indexType;
	for(int i=0;i<list->size;i++){
		temp = ALGetIndex(list->list,i);
		if(temp == NULL){
			printf("%i->",i);
			list->type->printFn(NULL);
			printf(", ");
			continue;
		}
		indexType = list->indexType[i];
		if(indexType == 1){
			printf("%i->",i);
			list->type->printFn(((HTEntry*)temp)->name);
			printf(", ");
		}
		else if(indexType == 2){
			SLLNode* tempList = ((SLL*)temp)->root;
			while(tempList != NULL){
				printf("%i->",i);
				list->type->printFn(((HTEntry*)(tempList->value))->name);
				printf(", ");
				tempList = tempList->next;
			}
		}
	}
}
#endif
