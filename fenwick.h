#ifndef FENWICK_H
#define FENWICK_H
#include "GenericFunctions.h"
#include "DynamicArray.h"
#include "bit.h"

typedef struct Fenwick{
	int size;
	AL* list;
	int init;
	GenericOperations* type;
} Fenwick;

Fenwick* fenwickCreate(GenericTypes types){
	Fenwick* temp = malloc(sizeof(Fenwick));
	assert(temp != NULL);
	temp->size = 0;
	temp->init = 0;
	temp->type = getOperations(types);
	assert(temp->type != NULL);
	temp->list = ALCreate(0,types);
	return temp;
}

void fenwickConstruct(Fenwick* list){
	assert(list != NULL);
	assert(list->init == 1);
	int j;
	int* temp = malloc(sizeof(int));
	for(int i=1;i<list->size;i++){
		*temp = i;
		j = i + LSB((void*)temp);
		if(j <= list->size){
			ALSet(list->list,j-1,list->type->add(ALGetIndex(list->list,i-1),ALGetIndex(list->list,j-1)));
		}
	}
}

void fenwickInit(Fenwick* list){
	assert(list != NULL);
	assert(list->init == 0);
	list->init = 1;
}

void fenwickAddEnd(Fenwick* list,void* x){
	assert(list != NULL);
	assert(list->init == 0);
	assert(x != NULL);
	ALAddEnd(list->list,x);
	list->size+=1;
}

void fenwickRemove(Fenwick* list,int index,void* x){
	assert(list != NULL);
	assert(list->init == 0);
	assert(x != NULL);
	ALRemove(list->list,index);
	list->size-=1;
}

void fenwickAdd(Fenwick* list,int index,void* x){
	assert(list != NULL);
	assert(list->init == 0);
	assert(x != NULL);
	ALAdd(list->list,index,x);
	list->size+=1;
}

int fenwickPrefixSum(Fenwick* list,int index){
	//assert(list != NULL);
	//assert(index >= 0 && index <= list->size-1);
	int sum = 0;
	index+=1;
	if(index == 1) { return 0; }
	while(index != 0){
		sum += *(int*)ALGetIndex(list->list,index-1);
		index -= LSB((void*)&index);
	}
	return sum;
}

int fenwickRangeQuery(Fenwick* list,int i,int j){
	//assert(list != NULL);
	//assert(i >= 0 && i <= list->size-1);
	//assert(j >= 0 && j <= list->size-1);
	//assert(i < j);
	return fenwickPrefixSum(list,j) - fenwickPrefixSum(list,i-1);
}

void fenwickUpdate(Fenwick* list,int i,void* x){
	i+=1;
	while(i < list->size){
		ALSet(list->list,i-1,list->type->add(ALGetIndex(list->list,i-1),x));
		i+=LSB((void*)&i);
	}
}
#endif
