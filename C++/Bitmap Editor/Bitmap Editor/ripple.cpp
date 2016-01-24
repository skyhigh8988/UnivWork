#include <iostream>
using namespace std;

#include "ripple.h"
#include <math.h>

BYTE** ripple(BYTE** PIXEL1, LONG biHeight, LONG biWidth){

    LONG center_x, center_y;
	double weight;
	int **TEMP;
	BYTE** PIXEL2;
	short i, j;

	cout << "Enter the weight(0.00~1.00): ";
	cin >> weight;
	while(weight > 1.0 || weight < 0){
		cout << "Out of range, enter again(0.00~1.00): ";
		cin >> weight;
	}

	center_x = (LONG)((biWidth - 1) / 2 + 0.5);
	center_y = (LONG)((biHeight - 1) / 2 + 0.5);

	TEMP = new int *[biHeight];
	PIXEL2 = new BYTE *[biHeight];
    for(i = 0; i < biHeight; i++){
		TEMP[i] = new int [biWidth];
		PIXEL2[i] = new BYTE [biWidth];
		for(j = 0; j < biWidth; j++){
            TEMP[i][j] = (int)((sin(sqrt(pow(i - center_y, 2.0) + pow(j - center_x, 2.0))) + 1.0) * 127.5);	//產生波紋
            TEMP[i][j] = (int)(TEMP[i][j] + weight * PIXEL1[i][j]);											//合成
            PIXEL2[i][j] = TEMP[i][j] * 255 / 512;															//normalize
		}
	}

	return PIXEL2;
}