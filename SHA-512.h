#ifndef SHA512_H
#define SHA512_H
#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include "SHA512Constants.h"
#include "bit.h"

// k = 895 - l
uint64_t* SHA512Padding(void* message,unsigned int size,int* M){
	int k = 895 - (size*8);
	*M = 1;
	while(k < 0){ *M+=1; k = (895*(*M)) - (size*8); }
	uint64_t* paddedMessage = calloc(16*(*M),sizeof(uint64_t));
	uint8_t* chunkPointer = (uint8_t*)paddedMessage;
	uint8_t* messagePointer = (uint8_t*)message;
	int chunkCounter = 0;
	int bitCounter = 0;
	int byteCounter = 0;
	for(unsigned int i=0;i<size;i++){
		chunkPointer[7-(byteCounter%8)] = messagePointer[i];
		bitCounter+=8;
		byteCounter+=1;
		if(byteCounter == 8){
			byteCounter = 0;
			chunkCounter+=1;
			chunkPointer = (uint8_t*)&(paddedMessage[chunkCounter]);
		}
	}
	chunkPointer[7-(byteCounter%8)] = 0;
	chunkPointer[7-(byteCounter%8)] = setBitPos8(chunkPointer[7-(byteCounter%8)],7,1);
	bitCounter+=1;
	for(unsigned int i=0;i<k;i++){
		chunkPointer[7-(byteCounter%8)] = setBitPos8(chunkPointer[7-(byteCounter%8)],bitCounter%8,0);
		bitCounter+=1;
		if(bitCounter%8 == 0){
			byteCounter+=1;
		}
		if(byteCounter == 8){
			byteCounter = 0;
			chunkCounter+=1;
			chunkPointer = (uint8_t*)&(paddedMessage[chunkCounter]);
		}
	}
	bitCounter+=64;
	paddedMessage[chunkCounter] = 0;
	chunkCounter+=1;
	chunkPointer = (uint8_t*)&(paddedMessage[chunkCounter]);
	paddedMessage[chunkCounter] = (uint64_t)(size*8);
	return paddedMessage;
}

uint64_t** SHA512Parsing(uint64_t* message,int* MCounter){
	uint64_t** M = calloc(*MCounter,sizeof(uint64_t*));
	int counter = 0;
	for(int i=0;i<*MCounter;i++){
		M[i] = calloc(16,sizeof(uint64_t));
		for(int j=0;j<16;j++){
			M[i][j] = message[counter];
			counter+=1;
		}
	}
	free(message);
	return M;
}

int SHAComp(uint64_t* x,uint64_t* y){
	for(int i=0;i<8;i++){
		if(x[i] != y[i]){
			return 0;
		}
	}
	return 1;
}

uint64_t* SHA512Hash(uint64_t** message,int* MCounter){
	uint64_t a = 0;
	uint64_t b = 0;
	uint64_t c = 0;
	uint64_t d = 0;
	uint64_t e = 0;
	uint64_t f = 0;
	uint64_t g = 0;
	uint64_t h = 0;
	uint64_t T1 = 0;
	uint64_t T2 = 0;
	*MCounter+=1;
	uint64_t** Hx = calloc(*MCounter,sizeof(uint64_t*));
	for(int i=0;i<*MCounter;i++){
		Hx[i] = malloc(8*sizeof(uint64_t));
	}
	H0Get(Hx[0]);
	uint64_t* KList = getK(); 
	uint64_t* W = malloc(80*sizeof(uint64_t));
	uint8_t* printer;
	for(int M=1;M<*MCounter;M++){
		for(int t=0;t<16;t++){
			W[t] = message[M-1][t];
		}
		for(int t=16;t<80;t++){
			W[t] = SIG1(W[t-2])+W[t-7]+SIG0(W[t-15])+W[t-16];
		}
		a = Hx[M-1][0];
		b = Hx[M-1][1];
		c = Hx[M-1][2];
		d = Hx[M-1][3];
		e = Hx[M-1][4];
		f = Hx[M-1][5];
		g = Hx[M-1][6];
		h = Hx[M-1][7];
		for(int t=0;t<80;t++){
			T1 = h+SUM1(e)+Ch(e,f,g)+KList[t]+W[t];
			T2 = SUM0(a)+Maj(a,b,c);
			h = g;
			g = f;
			f = e;
			e = d + T1;
			d = c;
			c = b;
			b = a;
			a = T1 + T2;
		}
		Hx[M][0] = a + Hx[M-1][0];
		Hx[M][1] = b + Hx[M-1][1];
		Hx[M][2] = c + Hx[M-1][2];
		Hx[M][3] = d + Hx[M-1][3];
		Hx[M][4] = e + Hx[M-1][4];
		Hx[M][5] = f + Hx[M-1][5];
		Hx[M][6] = g + Hx[M-1][6];
		Hx[M][7] = h + Hx[M-1][7];
	}
	uint64_t* hash = malloc(sizeof(uint64_t)*8);
	for(int i=0;i<8;i++){
		hash[i] = Hx[*MCounter-1][i];
	}
	for(int i=0;i<*MCounter;i++){
		free(Hx[i]);
	}
	free(Hx);
	free(W);
	free(KList);
	for(int i=0;i<*MCounter-1;i++){
		free(message[i]);
	}
	free(message);
	return hash;
}

uint64_t* SHA512(void* message,int size){
	int M = 0;
	return SHA512Hash(SHA512Parsing(SHA512Padding(message,size,&M),&M),&M);
}
#endif
