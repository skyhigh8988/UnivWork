#include "median_filter.h"

BYTE** median_filter(BYTE** PIXEL1, LONG biHeight, LONG biWidth){

	short i, j, k ,l;
	BYTE** PIXEL2;

	PIXEL2 = new BYTE *[biHeight];
    for(i = 0; i < biHeight; i++){
		PIXEL2[i] = new BYTE [biWidth];
        for(j = 0; j < biWidth; j++){
            if(i == 0 || j == 0 || i == biHeight - 1 || j == biWidth - 1) PIXEL2[i][j] = PIXEL1[i][j];
            else{
                BYTE TEMP[] = {PIXEL1[i-1][j-1], PIXEL1[i-1][j], PIXEL1[i-1][j+1], PIXEL1[i][j-1], PIXEL1[i][j], PIXEL1[i][j+1], PIXEL1[i+1][j-1], PIXEL1[i+1][j], PIXEL1[i+1][j+1]}, tmp;
                for(k = 0; k < 8; k++){						//排序
                    for(l = 0; l < 8 - k; l++){
                        if(TEMP[l] > TEMP[l + 1]){
                            tmp = TEMP[l];
                            TEMP[l] = TEMP[l + 1];
                            TEMP[l + 1] = tmp;
                        }
                    }
                }
                PIXEL2[i][j] = TEMP[4];						//中位數
            }
        }
    }

	return PIXEL2;

}