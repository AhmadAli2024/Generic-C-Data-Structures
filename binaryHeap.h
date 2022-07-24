#ifndef BINARYHEAP_H
#define BINARYHEAP_H
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"GenericFunctions.h"
#include"DynamicArray.h"

typedef struct BH{
	AL* list;
	int size;
	GenericOperations* type;
} BH;

BH* BHCreate(GenericTypes types){
	BH* temp = calloc(1,sizeof(BH));
	assert(temp != NULL);
	temp->list = ALCreate(0,types);
	temp->size = 0;
	temp->type = getOperations(types);
	return temp;	
}

void BHAdd(BH* list,void* value){
	assert(list != NULL);
	assert(value != NULL);
	ALAddEnd(list->list,value);
	list->size+=1;
	int newIndex = list->size-1;
	int parentIndex = (list->size-1)/2;
	while(list->type->compFn(ALGetIndex(list->list,newIndex),ALGetIndex(list->list,parentIndex)) == 0 && newIndex != 0){
		ALSet(list->list,parentIndex,ALSet(list->list,newIndex,ALGetIndex(list->list,parentIndex)));
		newIndex = parentIndex;
		parentIndex = (newIndex-1)/2;
	}
}

int BHGetValue(BH* list,void* value){
	assert(list != NULL);
	assert(value != NULL);
	return ALGetValue(list->list,value);
}

void BHPrint(BH* list){
	assert(list != NULL);
	int counter = 1;
	int tabCounter = log2(list->size);
	int printCounter = 0;
	int maxWidth = 1;
	while(maxWidth < list->size){
		maxWidth*=2;
	}
	maxWidth/=2;
	int width;
	for(int i=0;i<list->size;i++){
		width = 1;
		while(width-1 < i+1){
			width*=2;
		}
		width/=2;
		if(i == 0){
			width = 1;
		}
		if(printCounter == 0){
			for(int j=0;j<tabCounter;j++){
				printf("\t");
			}
			tabCounter-=1;
		}
		list->type->printFn(ALGetIndex(list->list,i));
		printCounter+=1;
		for(int j=0;j<(maxWidth-tabCounter-width)/width;j++){
			printf("\t");
		}
		if(counter == printCounter){
			printCounter = 0;
			counter*=2;
			printf("\n");
		}
	}
}

void BHPoll(BH* list){
	assert(list != NULL);
	if(list->size-1 == 0){
		ALRemove(list->list,0);
		list->size-=1;
		return;
	}
	ALSet(list->list,0,ALGetIndex(list->list,list->size-1));
	ALRemove(list->list,list->size-1);
	list->size-=1;
	int parent = 0;
	void* parentValue = ALGetIndex(list->list,parent);
	int left = 1;
	void* leftValue = ALGetIndex(list->list,left);
	int right = 2;
	void* rightValue = ALGetIndex(list->list,right);
	while((list->type->compFn(parentValue,leftValue) == 1 && leftValue != NULL) || (list->type->compFn(parentValue,rightValue) == 1 && rightValue != NULL)){
		if(leftValue == NULL){
			ALSet(list->list,parent,ALSet(list->list,right,parentValue));
			break;
		}
		if(rightValue == NULL){
			ALSet(list->list,parent,ALSet(list->list,left,parentValue));
			break;
		}
		if(list->type->compFn(leftValue,rightValue) == 1){
			ALSet(list->list,parent,ALSet(list->list,right,parentValue));
			parent = right;
		}
		else{
			ALSet(list->list,parent,ALSet(list->list,left,parentValue));
			parent = left;
		}
		parentValue = ALGetIndex(list->list,parent);
		left = parent*2+1;
		leftValue = ALGetIndex(list->list,left);
		right = parent*2+2;
		rightValue = ALGetIndex(list->list,right);
	}
}

void BHRemove(BH* list,void* value){
	assert(list != NULL);
	assert(value != NULL);
	int valueIndex = ALGetValue(list->list,value);
	if(valueIndex == -1){
		return;
	}
	ALSet(list->list,valueIndex,ALGetIndex(list->list,list->size-1));
	ALRemove(list->list,list->size-1);
	list->size-=1;
	int parent = (valueIndex-1)/2;
	void* parentValue = ALGetIndex(list->list,parent);
	while(list->type->compFn(parentValue,value) == 1  && parentValue != NULL){
		ALSet(list->list,parent,ALSet(list->list,valueIndex,parentValue));
		valueIndex = parent;
		parent = (valueIndex-1)/2;
		parentValue = ALGetIndex(list->list,parent);
	}
	int left = valueIndex*2+1;
	void* leftValue = ALGetIndex(list->list,left);
	int right = valueIndex*2+2;
	void* rightValue = ALGetIndex(list->list,right);
	while((list->type->compFn(value,leftValue) == 1 && leftValue != NULL) || (list->type->compFn(value,rightValue) == 1 && rightValue != NULL)){
		if(list->type->compFn(leftValue,rightValue) == 1){
			ALSet(list->list,valueIndex,ALSet(list->list,right,value));
			valueIndex = right;
		}
		else{
			ALSet(list->list,valueIndex,ALSet(list->list,left,value));
			valueIndex = left;
		}
		left = valueIndex*2+1;
		leftValue = ALGetIndex(list->list,left);
		right = valueIndex*2+2;
		rightValue = ALGetIndex(list->list,right);
	}
}

void* BHGetMin(BH* list){
	assert(list != NULL);
	return ALGetIndex(list->list,0);
}

void BHFree(BH* list){
	assert(list != NULL);
	ALFree(list->list);
	free(list);
}
#endif
