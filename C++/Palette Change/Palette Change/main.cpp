#include <iostream>
#include <fstream>
#include <windows.h>
using namespace std;

int main(void){

	BITMAPFILEHEADER bh;
	BITMAPINFOHEADER bi;
	RGBQUAD bp[256];

	int i;
	int w;
	BYTE **pixel;
	fstream bmpf;
	bmpf.open("input.bmp", ios::in|ios::binary);

	bmpf.read((char*)&bh, sizeof(bh));
	bmpf.read((char*)&bi, sizeof(bi));
	bmpf.read((char*)&bp, sizeof(bp));

	w = bi.biWidth;
	while (w % 4 != 0) w++;

	pixel = new BYTE *[bi.biHeight];
	for(i = 0; i < bi.biHeight; i++){
		pixel[i] = new BYTE [w];
		bmpf.read((char*)pixel[i], w);
	}
    bmpf.close();

	for(i = 0; i < 256; i++){
		bp[i].rgbRed = 255;
	}

	bmpf.open("output.bmp", ios::out|ios::binary);
	bmpf.write((char*)&bh, sizeof(bh));
	bmpf.write((char*)&bi, sizeof(bi));
	bmpf.write((char*)&bp, sizeof(bp));

	for(i = 0; i < bi.biHeight; i++){
		bmpf.write((char*)pixel[i], w);
	}
	bmpf.close();

	return 0;
}