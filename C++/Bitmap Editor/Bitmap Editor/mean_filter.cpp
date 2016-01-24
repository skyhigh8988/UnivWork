#include "mean_filter.h"

BYTE** mean_filter(BYTE** PIXEL1, LONG biHeight, LONG biWidth){

	short i, j;
	BYTE** PIXEL2;

	PIXEL2 = new BYTE *[biHeight];
    for(i = 0; i < biHeight; i++){
		PIXEL2[i] = new BYTE [biWidth];
        for(j = 0; j < biWidth; j++){
            if(i == 0 || j == 0 || i == biHeight - 1 || j == biWidth - 1) PIXEL2[i][j] = PIXEL1[i][j];
            else{														//­pºâ¥­§¡
                PIXEL2[i][j] = (PIXEL1[i-1][j-1] + PIXEL1[i-1][j] + PIXEL1[i-1][j+1] + PIXEL1[i][j-1] + PIXEL1[i][j] + PIXEL1[i][j+1] + PIXEL1[i+1][j-1] + PIXEL1[i+1][j] + PIXEL1[i+1][j+1]) / 9;
            }
        }
    }

	return PIXEL2;

}