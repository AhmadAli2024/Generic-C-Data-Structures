#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H
#include "GenericFunctions.h"
#include "Queue.h"

typedef struct BSTNode{
	struct BSTNode* parent;
	struct BSTNode* left;
	struct BSTNode* right;
	void* value;
} BSTNode;

typedef struct BST{
	struct BSTNode* root;
	int size;
	GenericOperations* type;
} BST;

BST* BSTCreate(GenericTypes types){
	BST* temp = malloc(sizeof(BST));
	assert(temp != NULL);
	temp->size = 0;
	temp->root = NULL;
	temp->type = getOperations(types);
	return temp;
}

void BSTPreOrder(BSTNode* list,void (*printFn)(void*)){
	if(list == NULL){
		return;
	}
	printFn(list->value);
	printf(" ");
	BSTPreOrder(list->left,printFn);
	BSTPreOrder(list->right,printFn);
}

void BSTInOrder(BSTNode* list,void (*printFn)(void*)){
	if(list == NULL){
		return;
	}
	BSTInOrder(list->left,printFn);
	printFn(list->value);
	printf(" ");
	BSTInOrder(list->right,printFn);
}

void BSTPostOrder(BSTNode* list,void (*printFn)(void*)){
	if(list == NULL){
		return;
	}
	BSTPostOrder(list->left,printFn);
	BSTPostOrder(list->right,printFn);
	printFn(list->value);
	printf(" ");
}

void BSTLevelOrder(BST* list){
	assert(list != NULL);
	Queue* tempQueue = queueCreate(VOID);
	BSTNode* tempNode = list->root;
	queueAdd(tempQueue,(void*)tempNode);
	while(queueSize(tempQueue) != 0){
		tempNode = (BSTNode*)queuePop(tempQueue);
		list->type->printFn(tempNode->value);
		printf(" ");
		if(tempNode->left != NULL){
			queueAdd(tempQueue,(void*)tempNode->left);
		}
		if(tempNode->right != NULL){
			queueAdd(tempQueue,(void*)tempNode->right);
		}
	}
	queueFree(tempQueue);
}

void BSTPrint(BST* list,int type){
	assert(list->root != NULL);
	switch(type){
		case 1:{
			BSTPreOrder(list->root,list->type->printFn);
			return;
		}
		case 2:{
			BSTInOrder(list->root,list->type->printFn);
			return;
		}
		case 3:{
			BSTPostOrder(list->root,list->type->printFn);
			return;
		}
		case 4:{
			BSTLevelOrder(list);
			return;
		}
	}
}

void BSTInsert(BST* list,void* value){
	assert(list != NULL);
	assert(value != NULL);
	BSTNode* tempNode = malloc(sizeof(BSTNode));
	tempNode->left = NULL;
	tempNode->right = NULL;
	tempNode->value = value;
	tempNode->parent = NULL;
	if(list->root == NULL){
		list->size+=1;
		list->root = tempNode;
		return;
	}
	BSTNode* parentTemp = list->root;
	while(1){
		if(list->type->equalFn(parentTemp->value,value) == 1){
			return;
		}
		if(list->type->compFn(parentTemp->value,value) == 1){
			if(parentTemp->left == NULL){
				parentTemp->left = tempNode;
				tempNode->parent = parentTemp;
				list->size+=1;
				return;
			}
			parentTemp = parentTemp->left;
		}
		else{
			if(parentTemp->right == NULL){
				parentTemp->right = tempNode;
				tempNode->parent = parentTemp;
				list->size+=1;
				return;
			}
			parentTemp = parentTemp->right;
		}
	}
}

BSTNode* BSTFind(BST* list,void* value){
	assert(list != NULL);
	assert(value != NULL);
	BSTNode* tempRoot = list->root;
	while(tempRoot != NULL){
		if(list->type->equalFn(tempRoot->value,value)){
			return tempRoot;
		}
		if(list->type->compFn(tempRoot->value,value) == 1){
			tempRoot = tempRoot->left;
		}
		else{
			tempRoot = tempRoot->right;
		}
	}
	return NULL;
}

int BSTCase1(BSTNode* value){
	if(value->left == NULL && value->right == NULL){
		if(value->parent != NULL){
			BSTNode* temp = value->parent;
			if(temp->left == value){
				free(value);
				temp->left = NULL;
				return 1;
			}
			else{
				free(value);
				temp->right = NULL;
				return 1;
			}
		}
		free(value);
		return 1;
	}
	return 0;
}

int BSTCase2(BSTNode* value,int side){
	BSTNode* parent = value->parent;
	BSTNode* left = value->left;
	BSTNode* right = value->right;
	if(left == NULL && right != NULL){
		free(value);
		if(side == 1){
			parent->right = right;
		}
		else{
			parent->left = right;
		}
		return 1;
	}
	return 0;
}

int BSTCase3(BSTNode* value,int side){
	BSTNode* parent = value->parent;
	BSTNode* left = value->left;
	BSTNode* right = value->right;
	if(left != NULL && right == NULL){
		free(value);
		if(side == 1){
			parent->right = left;
		}
		else{
			parent->left = left;
		}
		return 1;
	}
	return 0;
}

int BSTCase4(BSTNode* value){
	BSTNode* smallestNode = value->right;
	while(smallestNode->left != NULL){
		smallestNode = smallestNode->left;
	}
	value->value = smallestNode->value;
	BSTNode* parent = smallestNode->parent;
	BSTNode* right = value->right;
	if(BSTCase1(smallestNode) == 1){
		return 1;
	}
	if(BSTCase2(smallestNode,0) == 1){
		return 1;
	}
	return 0;
}

int BSTCase5(BST* list){
	BSTNode* temp;
	if(list->root->left == NULL){
		temp = list->root->right;
		free(list->root);
		list->root = temp;
		return 1;
	}
	temp = list->root->left;
	free(list->root);
	list->root = temp;
	return 1;
}

void BSTRemove(BST* list,void* value){
	assert(list != NULL);
	BSTNode* node = BSTFind(list,value);
	if(list->root == node){
		if(BSTCase1(node) == 1){ return;}
		if(BSTCase5(list) == 1){ return;}
		if(BSTCase4(node) == 1){ return;}
		return;
	}
	int side;
	if(node->parent->left == node){
		side = 0;
	}
	else{
		side = 1;
	}
	if(BSTCase1(node) == 1){ return;}
	if(BSTCase2(node,side) == 1){ return;}
	if(BSTCase3(node,side) == 1){ return;}
	if(BSTCase4(node) == 1){ return;}
}

void BSTFree(BST* list){
	assert(list != NULL);
	Queue* tempQueue = queueCreate(VOID);
	BSTNode* tempNode = list->root;
	queueAdd(tempQueue,(void*)tempNode);
	void* left;
	void* right;
	while(queueSize(tempQueue) != 0){
		tempNode = (BSTNode*)queuePop(tempQueue);
		left = tempNode->left;
		right = tempNode->right;
		free(tempNode);
		if(left != NULL){
			queueAdd(tempQueue,(void*)left);
		}
		if(right != NULL){
			queueAdd(tempQueue,(void*)right);
		}
	}
	queueFree(tempQueue);
	free(list->type);
	free(list);
}
#endif
