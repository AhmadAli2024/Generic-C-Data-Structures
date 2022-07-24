#ifndef BIT_H
#define BIT_H
#include<stdint.h>
#include<string.h>
#include "GenericFunctions.h"
#include "SHA-512.h"

//returns value of the least significant bit
int LSB(void* x){
	int bitCounter = 0;
	int byteCounter = 0;
	uint8_t varInt = ((uint8_t*)x)[byteCounter];
	while(((varInt & (1 << bitCounter%8)) != 0) == 0){
		bitCounter+=1;
		if(bitCounter == 8){ byteCounter+=1; varInt = ((uint8_t*)x)[byteCounter]; }
	}
	return pow(2,bitCounter);
}

//sizeof returns number of bytes
uint8_t reverseBits(uint8_t x){
	uint8_t rev = 0;
	while((int)x > 0){
		rev <<=1;
		if(x & 1 == 1){
			rev ^=1;
		}
		x >>= 1;
	}
	rev <<=1;
	return rev;
}

uint64_t reverseBits64(uint64_t x){
	uint64_t rev = 0;
	for(int i=0;i<64;i++){
		rev = setBitPos(rev,i,getBitPos(x,63-i));
	}
	return rev;
}

int getBit(void* var,int pos,int (*toInt)(void*)){
	int varInt = toInt(var);
	return ((varInt & (1 << pos)) != 0);
}

int setBit(void* var, int pos,int (*toInt)(void*)){
	int varInt = toInt(var);
	return varInt | (1 << pos);
}

unsigned get4Bytes(uint8_t* var){
	unsigned final = 0;
	memcpy(&final,var,4);
	return final;
}

uint64_t* o1hash(void* key,size_t size){
	uint64_t* res = malloc(sizeof(uint64_t));
	uint8_t* pointer = (uint8_t*)key;
	if(size >=4){
		unsigned first = get4Bytes(pointer);
		unsigned middle = get4Bytes(pointer+(size>>1)-2);
		unsigned last = get4Bytes(pointer+size-4);
		*res = (uint64_t)(first+last)*middle;
		return res;
	}
	if(size){
		uint64_t tail =((((unsigned)pointer[0])<<16) | (((unsigned)pointer[size>>1])<<8) | pointer[size-1]);
		*res = tail*0xa0761d6478bd642full;
		return res;
    }
	return NULL;
}

#endif
