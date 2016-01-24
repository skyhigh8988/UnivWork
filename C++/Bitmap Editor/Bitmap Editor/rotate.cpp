#include <iostream>
using namespace std;

#include "rotate.h"
#include <math.h>

BYTE** rotate(BYTE** PIXEL1, LONG* biHeight, LONG* biWidth, DWORD* bfSize, DWORD bfOffbytes){

	short i, j;
	double angle, rad;
	double sinA, cosA;
	double x1, x2, x3, y1, y2, y3;
	double maxWidth, maxHeight, minWidth, minHeight;
	double x0, y0;
	LONG newWidth, newHeight;
	BYTE** PIXEL2;

	cout << "Enter the angle(0~360): ";
	cin >> angle;
	while(angle > 360 || angle < 0){
		cout << "Out of range, enter again(0~360): ";
		cin >> angle;
	}

cout << "test\n";

	rad = angle * 3.1415926535898 / 180;								//單位轉換
    sinA = sin(rad);
    cosA = cos(rad);
    x1 = -*biHeight * sinA;												//計算座標
    y1 =  *biHeight * cosA;
    x2 =  *biWidth  * cosA - (*biHeight) * sinA;
    y2 =  *biHeight * cosA + (*biWidth)  * sinA;
    x3 =  *biWidth  * cosA;
    y3 =  *biWidth  * sinA;
	minWidth  = x3 > (x1 > x2 ? x2 : x1) ? (x1 > x2 ? x2 : x1) : x3;	//計算旋轉後大小
    minWidth  = minWidth > 0 ? 0 : minWidth;
    minHeight = y3 > (y1 > y2 ? y2 : y1) ? (y1 > y2 ? y2 : y1) : y3;
    minHeight = minHeight > 0 ? 0 : minHeight;
    maxWidth  = x3 > (x1 > x2 ? x1 : x2) ? x3 : (x1 > x2 ? x1 : x2);
    maxWidth  = maxWidth > 0 ? maxWidth : 0;
    maxHeight = y3 > (y1 > y2 ? y1 : y2) ? y3 : (y1 > y2 ? y1 : y2);
    maxHeight = maxHeight > 0 ? maxHeight : 0;
    newWidth  = (LONG)(maxWidth  - minWidth );
    newHeight = (LONG)(maxHeight - minHeight);
	if(newWidth % 4) newWidth = (newWidth / 4 + 1) * 4;					//寬度調整

cout << "test\n";
    
    PIXEL2 = new BYTE* [newHeight];
	for(i = 0; i < newHeight; i++){
		PIXEL2[i] = new BYTE [newWidth];
        for(j = 0; j < newWidth; j++){
            x0 = (j + minWidth ) * cosA + (i + minHeight) * sinA;		//計算對應原圖座標
            y0 = (i + minHeight) * cosA - (j + minWidth ) * sinA;
            if(x0 >= 0 && x0 <= *biWidth && y0 >= 0 && y0 <= *biHeight){
                PIXEL2[i][j] = PIXEL1[(int)y0][(int)x0];
            }else{
                PIXEL2[i][j] = 0;										//塗黑
            }
        }
    }

	cout << "test\n";

	*biWidth  = newWidth;
    *biHeight = newHeight;
    *bfSize   = bfOffbytes + *biHeight * *biWidth;

	return PIXEL2;
}