#ifndef _PGM_H
#define _PGM_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define BYTE unsigned char

unsigned long f_sz;
BYTE **X;
FILE *img;
BYTE c, A[20]; //...Eater & Header
int iW = 0, iH = 0, iG = 0, nA = 2;

void pgm_to_mtx() {
	int i, j, x;
//...Verify Magic Number
	x = fread(A, 3, 1, img);
	if(A[0]=='P' && A[1]=='5')
		printf("File Format: .PGM\n");
	else
		perror("Image File Corrupted!\n");
//...Get Image_Width
	while(fread(&c, 1, 1, img) && (c!=0x20)){
		iW = (iW * 10) + (c-'0');
		A[nA++]=c;
	}
	A[nA++]=c;
//...Get Image_Height
	while(fread(&c, 1, 1, img) && (c!=0x0a)){
		iH = (iH * 10) + (c-'0');
		A[nA++]=c;
	}
	A[nA++]=c;
	printf("%d %d\n", iW, iH);
//...Get Image_GrayScale
	while(fread(&c, 1, 1, img) && (c!=0x0a)){
		iG = (iG * 10) + c-'0';
		A[nA++]=c;
	}
	A[nA++]=c;
	printf("Maximum Grayscale val: %d\n", iG);

for(i=0; i<nA; printf("%02x ",A[i++]));
printf("\n");

	X = (BYTE**)malloc(iH * sizeof(BYTE*));
	for(i = 0; i < iH; i++)
		X[i] = (BYTE*)malloc(iW);

	for(i = 0; i < iH; i++){
		for(j = 0; j < iW; j++){
			x = fread(&c, 1, 1, img);
			X[i][j] = c;
		}
	}
	printf("Matrix Generation Successful\n");
}

void mtx_to_pgm() {
//...Making Header
	int i, j, x, nn;
A[0] = 'P', A[1] = '5';
nA = 2;
//...Putting Image_Width
	x = iW, nn = 0;
	while(x) {
		++nn, x /= 10;
	}
	nA += (nn - 1), x = iW;
	for(i = 0; i < nn; i++) {
		A[nA - i] = (x % 10) + '0';
		x /= 10;
	}
++nA;
A[nA++] = 0x20;
//...Putting Image_Height
	x = iH, nn = 0;
	while(x) {
		++nn, x /= 10;
	}
	nA += (nn - 1), x = iH;
	for(i = 0; i < nn; i++) {
		A[nA - i] = (x % 10) + '0';
		x /= 10;
	}
	++nA;
A[nA++] = 0x0a;
A[nA++] = 0x32, A[nA++] = 0x35, A[nA++] = 0x35;
A[nA++] = 0x0a;

//...Printing Header
	for(i = 0; i < nA; printf("%02x ", A[i++]));
	printf("\n");
//...Writing File
	x = fwrite(A, nA, 1, img);
	for(i = 0; i < iH; i++) {
		for(j = 0; j < iW; j++)
			x = fwrite(&X[i][j], 1, 1, img);
	}
	printf("Output Creation Successful\nReturning to Main\n");
}

#endif
