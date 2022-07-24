#ifndef SHA512CONSTANTS_H
#define SHA512CONSTANTS_H
#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
//getting bit of a uint64_t number
int getBitPos(uint64_t x,int pos){
	return ((x & (1 << pos)) != 0);
}

//setting the bit of a uint64_t number
int setBitPos(uint64_t x,int pos,int value){
	return x | (value << pos);
}
//
//getting bit of a uint64_t number
int getBitPos8(uint8_t x,int pos){
	return ((x & (1 << pos)) != 0);
}

//setting the bit of a uint64_t number
int setBitPos8(uint8_t x,int pos,int value){
	return x | (value << pos);
}

//inital Values for K0-K79
uint64_t* getK(){
	uint64_t* KList = malloc(sizeof(uint64_t)*80);
	KList[0] = 0x428a2f98d728ae22;
	KList[1] = 0x7137449123ef65cd;
	KList[2] = 0xb5c0fbcfec4d3b2f;
	KList[3] = 0xe9b5dba58189dbbc;
	KList[4] = 0x3956c25bf348b538;
	KList[5] = 0x59f111f1b605d019;
	KList[6] = 0x923f82a4af194f9b;
	KList[7] = 0xab1c5ed5da6d8118;
	KList[8] = 0xd807aa98a3030242;
	KList[9] = 0x12835b0145706fbe;
	KList[10] = 0x243185be4ee4b28c;
	KList[11] = 0x550c7dc3d5ffb4e2;
	KList[12] = 0x72be5d74f27b896f;
	KList[13] = 0x80deb1fe3b1696b1;
	KList[14] = 0x9bdc06a725c71235;
	KList[15] = 0xc19bf174cf692694;
	KList[16] = 0xe49b69c19ef14ad2;
	KList[17] = 0xefbe4786384f25e3;
	KList[18] = 0x0fc19dc68b8cd5b5;
	KList[19] = 0x240ca1cc77ac9c65;
	KList[20] = 0x2de92c6f592b0275;
	KList[21] = 0x4a7484aa6ea6e483;
	KList[22] = 0x5cb0a9dcbd41fbd4;
	KList[23] = 0x76f988da831153b5;
	KList[24] = 0x983e5152ee66dfab;
	KList[25] = 0xa831c66d2db43210;
	KList[26] = 0xb00327c898fb213f;
	KList[27] = 0xbf597fc7beef0ee4;
	KList[28] = 0xc6e00bf33da88fc2;
	KList[29] = 0xd5a79147930aa725;
	KList[30] = 0x06ca6351e003826f;
	KList[31] = 0x142929670a0e6e70;
	KList[32] = 0x27b70a8546d22ffc;
	KList[33] = 0x2e1b21385c26c926;
	KList[34] = 0x4d2c6dfc5ac42aed;
	KList[35] = 0x53380d139d95b3df;
	KList[36] = 0x650a73548baf63de;
	KList[37] = 0x766a0abb3c77b2a8;
	KList[38] = 0x81c2c92e47edaee6;
	KList[39] = 0x92722c851482353b;
	KList[40] = 0xa2bfe8a14cf10364;  
	KList[41] = 0xa81a664bbc423001;
	KList[42] = 0xc24b8b70d0f89791;
	KList[43] = 0xc76c51a30654be30;
	KList[44] = 0xd192e819d6ef5218;  
	KList[45] = 0xd69906245565a910;
	KList[46] = 0xf40e35855771202a;
	KList[47] = 0x106aa07032bbd1b8;
	KList[48] = 0x19a4c116b8d2d0c8;
	KList[49] = 0x1e376c085141ab53;
	KList[50] = 0x2748774cdf8eeb99;
	KList[51] = 0x34b0bcb5e19b48a8;
	KList[52] = 0x391c0cb3c5c95a63;
	KList[53] = 0x4ed8aa4ae3418acb;
	KList[54] = 0x5b9cca4f7763e373;
	KList[55] = 0x682e6ff3d6b2b8a3;
	KList[56] = 0x748f82ee5defb2fc;  
	KList[57] = 0x78a5636f43172f60;
	KList[58] = 0x84c87814a1f0ab72;
	KList[59] = 0x8cc702081a6439ec;
	KList[60] = 0x90befffa23631e28;  
	KList[61] = 0xa4506cebde82bde9;
	KList[62] = 0xbef9a3f7b2c67915;
	KList[63] = 0xc67178f2e372532b;
	KList[64] = 0xca273eceea26619c;  
	KList[65] = 0xd186b8c721c0c207;
	KList[66] = 0xeada7dd6cde0eb1e;
	KList[67] = 0xf57d4f7fee6ed178;
	KList[68] = 0x06f067aa72176fba;  
	KList[69] = 0x0a637dc5a2c898a6;
	KList[70] = 0x113f9804bef90dae;
	KList[71] = 0x1b710b35131c471b;
	KList[72] = 0x28db77f523047d84;  
	KList[73] = 0x32caab7b40c72493;
	KList[74] = 0x3c9ebe0a15c9bebc;
	KList[75] = 0x431d67c49c100d4c;
	KList[76] = 0x4cc5d4becb3e42b6;
	KList[77] = 0x597f299cfc657e2a;
	KList[78] = 0x5fcb6fab3ad6faec;
	KList[79] = 0x6c44198c4a475817;
	return KList;
}

//inital values for H0-H7
void H0Get(uint64_t* H0){
	H0[0] = 0x6a09e667f3bcc908;
	H0[1] = 0xbb67ae8584caa73b;
	H0[2] = 0x3c6ef372fe94f82b;
	H0[3] = 0xa54ff53a5f1d36f1;
	H0[4] = 0x510e527fade682d1;
	H0[5] = 0x9b05688c2b3e6c1f;
	H0[6] = 0x1f83d9abfb41bd6b;
	H0[7] = 0x5be0cd19137e2179;
}

//SHA-512 predefined functions
uint64_t ROTL(int n,uint64_t x){
	return (x << n) | (x >> (64-n));
}

uint64_t ROTR(int n,uint64_t x){
	return (x >> n) | (x << (64-n));
}

uint64_t SHR(int n,uint64_t x){
	return (x >> n);
}

uint64_t SUM0(uint64_t x){
	return ROTR(28,x) ^ ROTR(34,x) ^ ROTR(39,x);
}

uint64_t SUM1(uint64_t x){
	return ROTR(14,x) ^ ROTR(18,x) ^ ROTR(41,x);
}

uint64_t SIG0(uint64_t x){
	return ROTR(1,x) ^ ROTR(8,x) ^ SHR(7,x);
}

uint64_t SIG1(uint64_t x){
	return ROTR(19,x) ^ ROTR(61,x) ^ SHR(6,x);
}

uint64_t Ch(uint64_t x,uint64_t y,uint64_t z){
	return (x & y) ^ (~x & z);
}

uint64_t Maj(uint64_t x,uint64_t y,uint64_t z){
	return (x & y) ^ (x & z) ^ (y & z);
}

uint64_t MS(uint64_t message,int j){
	return setBitPos(message,j,SIG1(getBitPos(message,j-2))+getBitPos(message,j-7)+SIG0(getBitPos(message,j-15))+getBitPos(message,j-16));
}
#endif
