#include "sha1.h"
#include <memory.h>
#include <algorithm>

unsigned char invTable[256] = {
	0x74, 0x85, 0x96, 0xA7, 0xB8, 0xC9, 0xDA, 0xEB, 0xFC, 0x0D, 0x1E, 0x2F, 0x40, 0x51, 0x62, 0x73,
	0x84, 0x95, 0xA6, 0xB7, 0xC8, 0xD9, 0xEA, 0xFB, 0x0C, 0x1D, 0x2E, 0x3F, 0x50, 0x61, 0x72, 0x83,
	0x94, 0xA5, 0xB6, 0xC7, 0xD8, 0xE9, 0xFA, 0x0B, 0x1C, 0x2D, 0x3E, 0x4F, 0x60, 0x71, 0x82, 0x93,
	0xA4, 0xB5, 0xC6, 0xD7, 0xE8, 0xF9, 0x0A, 0x1B, 0x2C, 0x3D, 0x4E, 0x5F, 0x70, 0x81, 0x92, 0xA3,
	0xB4, 0xC5, 0xD6, 0xE7, 0xF8, 0x09, 0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F, 0x80, 0x91, 0xA2, 0xB3,
	0xC4, 0xD5, 0xE6, 0xF7, 0x08, 0x19, 0x2A, 0x3B, 0x4C, 0x5D, 0x6E, 0x7F, 0x90, 0xA1, 0xB2, 0xC3,
	0xD4, 0xE5, 0xF6, 0x07, 0x18, 0x29, 0x3A, 0x4B, 0x5C, 0x6D, 0x7E, 0x8F, 0xA0, 0xB1, 0xC2, 0xD3,
	0xE4, 0xF5, 0x06, 0x17, 0x28, 0x39, 0x4A, 0x5B, 0x6C, 0x7D, 0x8E, 0x9F, 0xB0, 0xC1, 0xD2, 0xE3,
	0xF4, 0x05, 0x16, 0x27, 0x38, 0x49, 0x5A, 0x6B, 0x7C, 0x8D, 0x9E, 0xAF, 0xC0, 0xD1, 0xE2, 0xF3,
	0x04, 0x15, 0x26, 0x37, 0x48, 0x59, 0x6A, 0x7B, 0x8C, 0x9D, 0xAE, 0xBF, 0xD0, 0xE1, 0xF2, 0x03,
	0x14, 0x25, 0x36, 0x47, 0x58, 0x69, 0x7A, 0x8B, 0x9C, 0xAD, 0xBE, 0xCF, 0xE0, 0xF1, 0x02, 0x13,
	0x24, 0x35, 0x46, 0x57, 0x68, 0x79, 0x8A, 0x9B, 0xAC, 0xBD, 0xCE, 0xDF, 0xF0, 0x01, 0x12, 0x23,
	0x34, 0x45, 0x56, 0x67, 0x78, 0x89, 0x9A, 0xAB, 0xBC, 0xCD, 0xDE, 0xEF, 0x00, 0x11, 0x22, 0x33,
	0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, 0x10, 0x21, 0x32, 0x43,
	0x54, 0x65, 0x76, 0x87, 0x98, 0xA9, 0xBA, 0xCB, 0xDC, 0xED, 0xFE, 0x0F, 0x20, 0x31, 0x42, 0x53,
	0x64, 0x75, 0x86, 0x97, 0xA8, 0xB9, 0xCA, 0xDB, 0xEC, 0xFD, 0x0E, 0x1F, 0x30, 0x41, 0x52, 0x63
};

unsigned char table1[256] = {
	0x3A, 0x3F, 0x3E, 0x72, 0xBD, 0xA2, 0xD6, 0xB4, 0x63, 0xC0, 0x6E, 0x62, 0x59, 0x1E, 0xE2, 0x71,
	0xB5, 0x0D, 0xE8, 0x0C, 0x25, 0x38, 0xCE, 0x23, 0x7C, 0xB7, 0xAD, 0x16, 0xDF, 0x47, 0x3D, 0xB3,
	0x7E, 0x8C, 0xAA, 0x61, 0x31, 0x66, 0xBE, 0x4F, 0x97, 0x14, 0x54, 0xF0, 0x70, 0xEB, 0x30, 0xC4,
	0x27, 0x4E, 0xFA, 0x1A, 0x2B, 0x11, 0xF4, 0x45, 0x8E, 0x5D, 0x73, 0xED, 0x22, 0x2E, 0x7D, 0xA4,
	0x28, 0xDA, 0x2F, 0xC5, 0x92, 0x09, 0x05, 0x13, 0x9D, 0x32, 0x51, 0x4A, 0xC8, 0xBA, 0x96, 0xA7,
	0x6A, 0x50, 0xF3, 0xBC, 0x93, 0xBF, 0xB0, 0xD2, 0xD5, 0x82, 0x19, 0x98, 0x35, 0xCF, 0x6B, 0xB6,
	0x83, 0x56, 0x15, 0xF2, 0x9A, 0x9C, 0xCA, 0x74, 0x34, 0x58, 0x8D, 0xA6, 0x03, 0xFF, 0x46, 0x7B,
	0xD0, 0x7A, 0x33, 0x76, 0xDD, 0xAC, 0xCB, 0x24, 0x7F, 0xB1, 0x85, 0x60, 0xC3, 0x26, 0x8A, 0x1D,
	0x1C, 0x8F, 0x2A, 0xEF, 0x06, 0xDE, 0x67, 0x5E, 0xE7, 0xAE, 0xD9, 0xCC, 0x07, 0x6C, 0xF8, 0x0A,
	0xD3, 0x40, 0x36, 0x1F, 0x2D, 0x95, 0x43, 0xDB, 0x01, 0x89, 0x4B, 0xF7, 0xB9, 0x39, 0xC2, 0x52,
	0x53, 0xFD, 0x65, 0xF5, 0x68, 0xC1, 0xC7, 0x9F, 0x4D, 0xEA, 0xAF, 0x6D, 0x10, 0x44, 0x87, 0xD8,
	0xEE, 0x1B, 0xFE, 0x3C, 0xDC, 0x84, 0x69, 0x48, 0x6F, 0xD1, 0x57, 0x55, 0xD4, 0xA5, 0x49, 0x5B,
	0xE5, 0x0B, 0x94, 0xC9, 0x5F, 0xE1, 0x17, 0x81, 0xBB, 0xEC, 0xD7, 0xC6, 0x02, 0x4C, 0x42, 0x75,
	0xA3, 0x99, 0xE4, 0xA1, 0x9B, 0x5A, 0xF1, 0x29, 0xA0, 0x64, 0x9E, 0x18, 0x41, 0x80, 0x2C, 0x79,
	0x20, 0x8B, 0xAB, 0x90, 0x08, 0xB8, 0xA9, 0x77, 0x12, 0xF9, 0x0E, 0x88, 0xE9, 0x04, 0xFB, 0x86,
	0x0F, 0xE0, 0xA8, 0x5C, 0xE6, 0x21, 0xCD, 0x3B, 0x00, 0x78, 0xFC, 0xF6, 0xE3, 0x37, 0xB2, 0x91
};

unsigned char table2[256] = {
	0xF3, 0xE4, 0x1B, 0x38, 0xE5, 0x6F, 0xE8, 0x9D, 0x3E, 0x55, 0xBA, 0xC7, 0xAC, 0xEA, 0x66, 0xA2,
	0xB9, 0x7A, 0x34, 0x43, 0x02, 0x4E, 0xFE, 0x36, 0x41, 0x57, 0x1A, 0xB1, 0x31, 0x87, 0x04, 0x52,
	0x21, 0x22, 0xE1, 0x13, 0x7F, 0x03, 0x3A, 0x90, 0xF7, 0x69, 0x78, 0x12, 0x83, 0x0B, 0x9A, 0x97,
	0x4D, 0xB7, 0x8C, 0xBF, 0x2D, 0x94, 0xD1, 0x93, 0x2F, 0x42, 0x23, 0xA4, 0xE0, 0x92, 0xDC, 0x68,
	0xD3, 0xDD, 0xAF, 0x91, 0x9F, 0xED, 0x3D, 0x8F, 0xA1, 0x51, 0xD9, 0xE9, 0x70, 0x28, 0xEF, 0xB3,
	0x49, 0xA5, 0x0D, 0xC5, 0xD0, 0x60, 0xB4, 0x2B, 0x07, 0xF8, 0xDF, 0xE6, 0x16, 0xC0, 0x30, 0x71,
	0x85, 0xFD, 0x72, 0x95, 0x29, 0x79, 0x0A, 0x7B, 0x46, 0x11, 0x7D, 0x88, 0x1D, 0x2A, 0x48, 0x1F,
	0x45, 0x89, 0x47, 0xEE, 0xBB, 0xBE, 0x6E, 0xC3, 0x6C, 0xCE, 0x10, 0x5A, 0x2C, 0xCA, 0xFB, 0xB2,
	0xCB, 0x1C, 0x9C, 0xEC, 0x2E, 0x56, 0x59, 0x9B, 0xA6, 0x53, 0xAE, 0x17, 0x25, 0xC1, 0x3F, 0x6A,
	0x0F, 0x09, 0x01, 0xA3, 0xD6, 0xA0, 0xD8, 0x08, 0xE3, 0x74, 0x06, 0x6D, 0x19, 0x98, 0x1E, 0x77,
	0x76, 0xBC, 0xEB, 0x3C, 0xB0, 0xC4, 0xC8, 0x64, 0x0E, 0x86, 0x63, 0xD7, 0xDB, 0xBD, 0xA7, 0x82,
	0x39, 0x4F, 0x27, 0xD2, 0x5F, 0x73, 0xF4, 0x75, 0x6B, 0xC2, 0xD5, 0x67, 0x5D, 0x80, 0xAB, 0x81,
	0xDE, 0xF0, 0xAD, 0xAA, 0xCD, 0xB6, 0xF6, 0x7C, 0xFC, 0x33, 0x05, 0x14, 0x96, 0x15, 0xC9, 0x9E,
	0x35, 0x5C, 0x7E, 0x44, 0x54, 0x58, 0x3B, 0x40, 0x20, 0xA8, 0x8B, 0x5E, 0x4A, 0x24, 0x99, 0x8E,
	0xF5, 0xB5, 0x62, 0x00, 0x37, 0x5B, 0x18, 0x65, 0x8D, 0x32, 0xE2, 0xF9, 0xDA, 0x8A, 0xD4, 0xCC,
	0x26, 0xF2, 0xF1, 0xE7, 0x4B, 0xC6, 0xCF, 0xFF, 0x4C, 0x84, 0x61, 0xFA, 0xB8, 0x0C, 0xA9, 0x50
};

unsigned char fixed[18] = {
	0x67, 0x23, 0xFE, 0x30, 0x45, 0x33, 0xF8, 0x90, 0x99, 0x21, 0x07, 0xC1, 0xD0, 0x12, 0xB2, 0xA1, 0x07, 0x81
};

int GCD(int a, int b){
	while( 1 )
	{
		a = a % b;
		if( a == 0 )
			return b;
		b = b % a;
		if( b == 0 )
			return a;
	}
}

int LCM(int a, int b)
{
	if(a==0 || b==0)
		return 1;

	return (a*b)/GCD(a,b);
}


//pFWID -> 8 bytes
//pKey -> 64 byte buffer
void GenerateKey(unsigned char *pFWID, unsigned char *pKey){
	memset(pKey,0, 64);

	int i;
	unsigned char y[16] = {0};
	//take LCM of each two bytes in the FWID in turn
	for(i=0;i<4;i++){
		int a=pFWID[i*2];
		int b=pFWID[i*2+1];
		int lcm = LCM(a,b);

		unsigned char hi = (lcm & 0xFF00) >> 8;
		unsigned char lo = lcm & 0xFF;

		y[i*4] = ((table1[hi] * 0xB5) - 3);
		y[i*4 + 1] = ((table2[hi] * 0xB7) + 0x49);
		y[i*4 + 2] = ((table1[lo] * 0xB5) - 3);
		y[i*4 + 3] = ((table2[lo] * 0xB7) + 0x49);
	}

	//convert y
	for(i=0;i<16;i++){
		y[i] = invTable[y[i]];
	}

	//hash
	SHA1_CTX context;
	SHA1Init(&context);
	SHA1Update(&context, fixed, 18);
	SHA1Update(&context, y, 16);
	SHA1Final(pKey, &context);
}

//pDataBase -> iTunesDB
//pFWID -> 8 bytes
//pHash -> 20 byte buffer
void GenerateHash(unsigned char *pFWID, unsigned char *pDataBase0, long lSize, unsigned char *pHash)
{
	unsigned char *pDataBase = (unsigned char*)malloc(lSize);
	memcpy(pDataBase,pDataBase0,lSize);
	//generate invtable
	unsigned char key[64] = {0};
	GenerateKey(pFWID, key);

	//hmac sha1
	int i;
	for (i=0; i < 64; i++)
		key[i] ^= 0x36;

	SHA1_CTX context;

	SHA1Init(&context);
	SHA1Update(&context, key, 64);
	SHA1Update(&context, pDataBase, lSize);
	SHA1Final(pHash, &context);

	for (i=0; i < 64; i++)
		key[i] ^= 0x36 ^ 0x5c;

	SHA1Init(&context);
	SHA1Update(&context, key, 64);
	SHA1Update(&context, pHash, 20);
	SHA1Final(pHash, &context);

	free(pDataBase);
}
