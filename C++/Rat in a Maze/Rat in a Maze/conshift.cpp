#include "conshift.h"

void setcolor(int c){
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, c);
	return;
}

void gotoxy(int px, int py){
	static HANDLE hConsole = 0;
	static int instanceCount = 0;
	COORD coord;
 	if(instanceCount == 0){
		hConsole = GetStdHandle( STD_OUTPUT_HANDLE );
		instanceCount = 1;
	}
	coord.X = px - 1;
	coord.Y = py - 1;
	SetConsoleCursorPosition(hConsole, coord);
	return;
}

void clrscr(){
	setcolor(0);
	system("cls");
	return;
}