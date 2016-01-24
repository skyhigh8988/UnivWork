#include "keyctrl.h"

int k_menu(int *opt){

	char key;
	int c = 0;

	setcolor(FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
	while(1){
		if(_kbhit()){
			key = _getch();
			if(key == Up){
				gotoxy(29, 17 + *opt);
				cout << "¡@¡@";
				gotoxy(49, 17 + *opt);
				cout << "¡@¡@";
				*opt != 1 ? (*opt)-- : *opt = 4;
				gotoxy(29, 17 + *opt);
				cout << "¡¹¡¹";
				gotoxy(49, 17 + *opt);
				cout << "¡¹¡¹";
				gotoxy(80, 25);
				if(c == 0 || c == 1) c++;
				else c = 1;
			}else if(key == Down){
				gotoxy(29, 17 + *opt);
				cout << "¡@¡@";
				gotoxy(49, 17 + *opt);
				cout << "¡@¡@";
				*opt != 4 ? (*opt)++ : *opt = 1;
				gotoxy(29, 17 + *opt);
				cout << "¡¹¡¹";
				gotoxy(49, 17 + *opt);
				cout << "¡¹¡¹";
				gotoxy(80, 25);
				if(c == 2 || c == 3) c++;
				else c = 0;
			}else if(key == Left){
				if(c == 4 || c == 6) c++;
				else c = 0;
			}else if(key == Right){
				if(c == 5 || c == 7) c++;
				else c = 0;
			}else if(key == 'B' || key == 'b'){
				if(c == 8) c++;
				else c = 0;
			}else if(key == 'A' || key == 'a'){
				if(c == 9) return 1;
				else c = 0;
			}else if(key == '\r' || key == ' '){
				return 0;
			}
		}
		Sleep(10);
	}
	return 0;
}

int k_difm(){

	char key;
	int opt = 1;

	while(1){
		if(_kbhit()){
			key = _getch();
			if(key == Left && opt != 1){
				gotoxy(35 + (opt-1) * 6, 12);
				setcolor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
				cout << opt;
				opt--;
				gotoxy(35 + (opt-1) * 6, 12);
				setcolor(BACKGROUND_INTENSITY | FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
				cout << opt;
				gotoxy(80, 25);
			}else if(key == Right && opt != 5){
				gotoxy(35 + (opt-1) * 6, 12);
				setcolor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
				cout << opt;
				opt++;
				gotoxy(35 + (opt-1) * 6, 12);
				setcolor(BACKGROUND_INTENSITY | FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
				cout << opt;
				gotoxy(80, 25);
			}else if(key == '\r' || key == ' '){
				return opt;
			}else if(key == 27){
				return 0;
			}
		}
		Sleep(10);
	}
	return 1;
}



int k_wait(){

	char key;

	while(1){
		if(_kbhit()){
			key = _getch();
			if(key == '\r' || key == ' ') return 1;
			else if(key == 27) return 0;
		}
		Sleep(10);
	}
	return 1;
}


int k_pause(){

	char key;
	int opt = 1;

	setcolor(FOREGROUND_INTENSITY | FOREGROUND_RED);
	while(1){
		if(_kbhit()){
			key = _getch();
			if(key == Up){
				gotoxy(34, 9 + opt * 2);
				cout << "¡@";
				gotoxy(46, 9 + opt * 2);
				cout << "¡@";
				opt != 1 ? opt-- : opt = 5;
				gotoxy(34, 9 + opt * 2);
				cout << "¡»";
				gotoxy(46, 9 + opt * 2);
				cout << "¡»";
				gotoxy(80, 25);
			}else if(key == Down){
				gotoxy(34, 9 + opt * 2);
				cout << "¡@";
				gotoxy(46, 9 + opt * 2);
				cout << "¡@";
				opt != 5 ? opt++ : opt = 1;
				gotoxy(34, 9 + opt * 2);
				cout << "¡»";
				gotoxy(46, 9 + opt * 2);
				cout << "¡»";
				gotoxy(80, 25);
			}else if(key == '\r' || key == ' ')	return opt;
			else if(key == 27)	return 1;
		}
		Sleep(10);
	}
	return 0;
}