#include <iostream>
#include <fstream>
using namespace std; 

#include <windows.h>
#include "mean_filter.h"
#include "median_filter.h"
#include "change_palettet.h"
#include "embossment.h"
#include "ripple.h"
#include "rotate.h"

int main(){

    short i, effect;
	fstream bitmap_file;
    char file_name[1024];

    WORD  bfType;
    DWORD bfSize;
    WORD  bfReserved1;
    WORD  bfReserved2;
    DWORD bfOffbytes;
    DWORD biSize;
    LONG  biWidth;
    LONG  biHeight;
    WORD  biPlanes;
    WORD  biBitCount;
    DWORD biCompression;
    DWORD biSizeImage;
    LONG  biXPelsPerMeter;
    LONG  biYPelsPerMeter;
    DWORD biClrUsed;
    DWORD biClrImportant;
	BYTE  RGBQUAD[256][4];

    cout << "Open file: ";
    cin >> file_name;

    bitmap_file.open(file_name, ios::in|ios::binary);
	if(!bitmap_file){												//檔案存在檢查
		cout << "Open file error";
		exit(1);
	}

    bitmap_file.read((char*)&bfType         , sizeof(WORD));
	if(bfType != 19778){											//BMP格式檢查
		cout << "File format error";
		exit(1);
	}

    bitmap_file.read((char*)&bfSize         , sizeof(DWORD));
    bitmap_file.read((char*)&bfReserved1    , sizeof(WORD));
    bitmap_file.read((char*)&bfReserved2    , sizeof(WORD));
    bitmap_file.read((char*)&bfOffbytes     , sizeof(DWORD));
    bitmap_file.read((char*)&biSize         , sizeof(DWORD));
    bitmap_file.read((char*)&biWidth        , sizeof(LONG));
    bitmap_file.read((char*)&biHeight       , sizeof(LONG));
    bitmap_file.read((char*)&biPlanes       , sizeof(WORD));
    bitmap_file.read((char*)&biBitCount     , sizeof(WORD));
    bitmap_file.read((char*)&biCompression  , sizeof(DWORD));
    bitmap_file.read((char*)&biSizeImage    , sizeof(DWORD));
    bitmap_file.read((char*)&biXPelsPerMeter, sizeof(LONG));
    bitmap_file.read((char*)&biYPelsPerMeter, sizeof(LONG));
    bitmap_file.read((char*)&biClrUsed      , sizeof(DWORD));
    bitmap_file.read((char*)&biClrImportant , sizeof(DWORD));
    bitmap_file.read((char*)RGBQUAD[0]      , sizeof(RGBQUAD));
    
    BYTE **PIXEL;
	PIXEL = new BYTE *[biHeight];
	for(i = 0; i < biHeight; i++){
		PIXEL[i] = new BYTE [biWidth];
		bitmap_file.read((char*)PIXEL[i], biWidth);
	}
    bitmap_file.close();

	cout << "\n\t(1) Mean Filter\n\t(2) Median Filter\n\t(3) Embossment\n\t(4) Change Palette\n\t(5) Ripple\n\t(6) Rotate\n\t(*) Any other key to exit\n\nPlease select one effect: ";
	cin >> effect;

	switch(effect){													//處理分岐
		case 1:
			PIXEL = mean_filter(PIXEL, biHeight, biWidth);
			break;
		case 2:
			PIXEL = median_filter(PIXEL, biHeight, biWidth);
			break;
		case 3:
			PIXEL = embossment(PIXEL, biHeight, biWidth);
			break;
		case 4:
			change_palettet(RGBQUAD);
			break;
		case 5:
			PIXEL = ripple(PIXEL, biHeight, biWidth);
			break;
		case 6:
			PIXEL = rotate(PIXEL, &biHeight, &biWidth, &bfSize, bfOffbytes);
			break;
		default:
			exit(0);
	}

    cout << "Save as: ";
    cin >> file_name;
    
    bitmap_file.open(file_name, ios::out|ios::binary);
    bitmap_file.write((char*)&bfType         , sizeof(WORD));
    bitmap_file.write((char*)&bfSize         , sizeof(DWORD));
    bitmap_file.write((char*)&bfReserved1    , sizeof(WORD));
    bitmap_file.write((char*)&bfReserved2    , sizeof(WORD));
    bitmap_file.write((char*)&bfOffbytes     , sizeof(DWORD));
    bitmap_file.write((char*)&biSize         , sizeof(DWORD));
    bitmap_file.write((char*)&biWidth        , sizeof(LONG));
    bitmap_file.write((char*)&biHeight       , sizeof(LONG));
    bitmap_file.write((char*)&biPlanes       , sizeof(WORD));
    bitmap_file.write((char*)&biBitCount     , sizeof(WORD));
    bitmap_file.write((char*)&biCompression  , sizeof(DWORD));
    bitmap_file.write((char*)&biSizeImage    , sizeof(DWORD));
    bitmap_file.write((char*)&biXPelsPerMeter, sizeof(LONG));
    bitmap_file.write((char*)&biYPelsPerMeter, sizeof(LONG));
    bitmap_file.write((char*)&biClrUsed      , sizeof(DWORD));
    bitmap_file.write((char*)&biClrImportant , sizeof(DWORD));
    bitmap_file.write((char*)RGBQUAD[0]      , sizeof(RGBQUAD));

	for(i = 0; i < biHeight; i++){
		bitmap_file.write((char*)PIXEL[i], biWidth);
	}

    bitmap_file.close();
	delete PIXEL;

    return 0; 
}