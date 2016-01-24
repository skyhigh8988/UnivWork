#include "embossment.h"

BYTE** embossment(BYTE** PIXEL1, LONG biHeight, LONG biWidth){

	short i, j;
	int **TEMP, max = -512, min = 512;
	BYTE** PIXEL2;

	TEMP = new int *[biHeight];
	PIXEL2 = new BYTE *[biHeight];
    for(i = 0; i < biHeight; i++){
		TEMP[i] = new int [biWidth];
		PIXEL2[i] = new BYTE [biWidth];
        for(j = 0; j < biWidth; j++){
            if(!(i == 0 || j == 0 || i == biHeight - 1 || j == biWidth - 1)){
                TEMP[i][j] = PIXEL1[i-1][j-1] * -2 + PIXEL1[i-1][j] * -2 + PIXEL1[i][j-1] * -2 + PIXEL1[i][j+1] * 2 + PIXEL1[i+1][j] * 2 + PIXEL1[i+1][j+1] * 2;
                if(TEMP[i][j] > max) max = TEMP[i][j];					//¬ö¿ý·¥­È
                if(TEMP[i][j] < min) min = TEMP[i][j];
            }
        }
    }
    for(i = 0; i < biHeight; i++){
        for(j = 0; j < biWidth; j++){
            if(i == 0 || j == 0 || i == biHeight - 1 || j == biWidth - 1) PIXEL2[i][j] = PIXEL1[i][j];
            else{
                PIXEL2[i][j] = (TEMP[i][j] - min) * 255 / (max - min);	//normalize
            }
        }
    }

	return PIXEL2;

}