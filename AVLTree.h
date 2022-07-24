#ifndef AVLTREE_H 
#define AVLTREE_H
#include "GenericFunctions.h"
#include "Queue.h"

typedef struct AVLNode{
	struct AVLNode* parent;
	struct AVLNode* left;
	struct AVLNode* right;
	int BF;
	int Height;
	void* value;
} AVLNode;

typedef struct AVL{
	struct AVLNode* root;
	int size;
	GenericOperations* type;
} AVL;

AVL* AVLCreate(GenericTypes types){
	AVL* temp = malloc(sizeof(AVL));
	assert(temp != NULL);
	temp->size = 0;
	temp->root = NULL;
	temp->type = getOperations(types);
	return temp;
}

void AVLUpdate(AVLNode* node){
	int lh = node->left == NULL ? -1 : node->left->Height;
	int rh = node->right == NULL ? -1 : node->right->Height;
	if(lh >= rh){
		node->Height = lh + 1;
	}
	else{
		node->Height = rh + 1;
	}
	node->BF = rh - lh;
}

AVLNode* AVLRightRotate(AVL* list,AVLNode* A){
	AVLNode* P = A->parent;
	AVLNode* B = A->left;
	if(B->right != NULL){
		B->right->parent = A;
	}
	A->left = A->left->right;
	B->right = A;
	A->parent = B;
	B->parent = P;
	if(P != NULL){
		if(P->left = A){
			P->left = B;
		}
		else{
			P->right = B;
		}
	}
	if(list->root == A){
		list->root = B;
	}
	AVLUpdate(A);
	AVLUpdate(B);
	return B;
}

AVLNode* AVLLeftRotate(AVL* list,AVLNode* A){
	AVLNode* P = A->parent;
	AVLNode* B = A->right;
	if(B->left != NULL){
		B->left->parent = A;
	}
	A->right = A->right->left;
	B->left = A;
	A->parent = B;
	B->parent = P;
	if(P != NULL){
		if(P->left = A){
			P->left = B;
		}
		else{
			P->right = B;
		}
	}
	if(list->root == A){
		list->root = B;
	}
	AVLUpdate(A);
	AVLUpdate(B);
	return B;
}

AVLNode* LLC(AVL* list,AVLNode* A){
	return AVLRightRotate(list,A);
}

AVLNode* LRC(AVL* list,AVLNode* A){
	A->left = AVLLeftRotate(list,A->left);
   return LLC(list,A);
}

AVLNode* RRC(AVL* list,AVLNode* A){
	return AVLLeftRotate(list,A);
}

AVLNode* RLC(AVL* list,AVLNode* A){
	A->right = AVLRightRotate(list,A->right);
	return RRC(list,A);
}

AVLNode* AVLBalance(AVL* list,AVLNode* node){
	if(node->BF == -2){
		if(node->left->BF <= 0){
			return LLC(list,node);
		}
		else{
			return LRC(list,node);
		}
	}
	else if(node->BF == 2){
		if(node->right->BF >= 0){
			return RRC(list,node);
		}
		else{
			return RLC(list,node);
		}
	}
	return node;
}

void AVLPreOrder(AVLNode* list,void (*printFn)(void*)){
	if(list == NULL){
		return;
	}
	printFn(list->value);
	printf(" ");
	AVLPreOrder(list->left,printFn);
	AVLPreOrder(list->right,printFn);
}

void AVLInOrder(AVLNode* list,void (*printFn)(void*)){
	if(list == NULL){
		return;
	}
	AVLInOrder(list->left,printFn);
	printFn(list->value);
	printf(" ");
	AVLInOrder(list->right,printFn);
}

void AVLPostOrder(AVLNode* list,void (*printFn)(void*)){
	if(list == NULL){
		return;
	}
	AVLPostOrder(list->left,printFn);
	AVLPostOrder(list->right,printFn);
	printFn(list->value);
	printf(" ");
}

void AVLLevelOrder(AVL* list){
	assert(list != NULL);
	Queue* tempQueue = queueCreate(VOID);
	AVLNode* tempNode = list->root;
	queueAdd(tempQueue,(void*)tempNode);
	while(queueSize(tempQueue) != 0){
		tempNode = (AVLNode*)queuePop(tempQueue);
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

void AVLPrint(AVL* list,int type){
	assert(list->root != NULL);
	switch(type){
		case 1:{
			AVLPreOrder(list->root,list->type->printFn);
			return;
		}
		case 2:{
			AVLInOrder(list->root,list->type->printFn);
			return;
		}
		case 3:{
			AVLPostOrder(list->root,list->type->printFn);
			return;
		}
		case 4:{
			AVLLevelOrder(list);
			return;
		}
	}
}

AVLNode* insertHelper(AVL* list,AVLNode* node,void* value){
	if(node == NULL){
		AVLNode* temp = malloc(sizeof(AVLNode));
		temp->left = NULL;
		temp->right = NULL;
		temp->parent = NULL;
		temp->BF = 0;
		temp->Height = 0;
		temp->value = value;
		return temp;
	}
	if(list->type->equalFn(value,node->value) == 1){
		return NULL;
	}
	if(list->type->compFn(value,node->value) != 1){
		AVLNode* temp = insertHelper(list,node->left,value);
		if(temp == NULL){
			return NULL;
		}
		node->left = temp;
	}
	else{
		AVLNode* temp = insertHelper(list,node->right,value);
		if(temp == NULL){
			return NULL;
		}
		node->right = temp;
	}
	AVLUpdate(node);
	return AVLBalance(list,node);
}

void AVLInsert(AVL* list,void* value){
	assert(value != NULL);
	if(list->root == NULL){
		AVLNode* temp = malloc(sizeof(AVLNode));
		temp->left = NULL;
		temp->right = NULL;
		temp->parent = NULL;
		temp->BF = 0;
		temp->Height = 0;
		temp->value = value;
		list->root = temp;
		return;
	}
	AVLNode* newRoot = insertHelper(list,list->root,value);
	int insertedNode = newRoot == NULL ? 1 : 0;
	if(insertedNode){
		list->size+=1;
		list->root = newRoot;
	}
}

AVLNode* AVLFind(AVL* list,void* value){
	assert(list != NULL);
	assert(value != NULL);
	AVLNode* tempRoot = list->root;
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

AVLNode* AVLFindMax(AVLNode* A){
	AVLNode* temp = A;
	while(temp != NULL){
		temp = temp->right;
	}
	return temp;
}

AVLNode* AVLFindMin(AVLNode* A){
	AVLNode* temp = A;
	while(temp != NULL){
		temp = temp->left;
	}
	return temp;
}

AVLNode* AVLRemoveHelper(AVL* list,AVLNode* node,void* value){
	if(node == NULL){
		return NULL;
	}
	if(list->type->compFn(value,node->value) == 0){
		node->left = AVLRemoveHelper(list,node->left,value);
	}
	else{
		node->right = AVLRemoveHelper(list,node->right,value);
	}
	if(list->type->equalFn(node->value,value) == 1){
		if(node->left == NULL){
			return node->right;
		}
		else if(node->right == NULL){
			return node->left;
		}
		else{
			if(node->left->Height > node->right->Height){
				void* sucValue = AVLFindMax(node->left)->value;
				node->value = sucValue;
				node->left = AVLRemoveHelper(list,node->left,sucValue);
			}
			else{
				void* sucValue = AVLFindMin(node->right)->value;
				node->value = sucValue;
				node->right = AVLRemoveHelper(list,node->right,sucValue);
			}
		}
	}
	AVLUpdate(node);
	return AVLBalance(list,node);
}

void AVLRemove(AVL* list,void* value){
	assert(value != NULL);
	if(AVLFind(list,value) != NULL){
		list->root = AVLRemoveHelper(list,list->root,value);
		list->size-=1;
	}
}

void AVLFree(AVL* list){
	assert(list != NULL);
	Queue* tempQueue = queueCreate(VOID);
	AVLNode* tempNode = list->root;
	queueAdd(tempQueue,(void*)tempNode);
	void* left;
	void* right;
	while(queueSize(tempQueue) != 0){
		tempNode = (AVLNode*)queuePop(tempQueue);
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
