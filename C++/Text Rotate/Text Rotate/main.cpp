#include <iostream>
#include <fstream>
using namespace std;

int main(void){

	fstream fin, fout;

	char ain[128][128];
	int row = 0, column = 0;
	int i, j;

	for(i = 0; i < 128; i++){
		for(j = 0; j < 128; j++){
			ain[i][j] = ' ';
		}
	}

	fin.open("input.txt", ios::in|ios::binary);
	while(!fin.eof()){
		fin.getline(ain[row++], 128);
		if((fin.gcount() - 2) > column) column = fin.gcount() - 2;
	}
	fin.close();

	fout.open("output.txt", ios::out|ios::binary);
	for(i = 0; i < column; i++){
		fout << (i != 0 ? "\r\n" : "");
		for(j = 0; j < row; j++){
			fout.put(ain[j][column - i - 1]);
		}
	}
	fout.close();

	return 0;
}