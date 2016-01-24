#include "Keyctrl.h"

int K_Menu(int *opt){

	char key;
	int c = 0;

	setcolor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
	while(1){
		if(_kbhit()){
			key = _getch();
			if(key == Up){
				gotoxy(9, 18 + *opt);
				cout << "¡@";
				*opt != 1 ? (*opt)-- : *opt = 3;
				gotoxy(9, 18 + *opt);
				cout << "¡»";
				gotoxy(80, 25);
				if(c == 0 || c == 1) c++;
				else c = 1;
			}else if(key == Down){
				gotoxy(9, 18 + *opt);
				cout << "¡@";
				*opt != 3 ? (*opt)++ : *opt = 1;
				gotoxy(9, 18 + *opt);
				cout << "¡»";
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

int K_MOption(int *density, int *complex, int *roadc, int *wallc){
	
	char key;
	int flash = 0;
	int row = 1;

	while(1){
		switch (row){
			case 1:
				if(_kbhit()){
					key = _getch();
					if(key == Left && *density != 1){
						setcolor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
						gotoxy(14 + *density * 7, 11);
						cout << ' ';
						gotoxy(19 + *density * 7, 11);
						cout << ' ';
						(*density)--;
						gotoxy(14 + *density * 7, 11);
						cout << '[';
						gotoxy(19 + *density * 7, 11);
						cout << ']';
					}else if(key == Right && *density != 5){
						setcolor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
						gotoxy(14 + *density * 7, 11);
						cout << ' ';
						gotoxy(19 + *density * 7, 11);
						cout << ' ';
						(*density)++;
						gotoxy(14 + *density * 7, 11);
						cout << '[';
						gotoxy(19 + *density * 7, 11);
						cout << ']';
					}else if(key == Up){
						setcolor(FOREGROUND_INTENSITY);
						gotoxy(14 + *density * 7, 11);
						cout << '[';
						gotoxy(19 + *density * 7, 11);
						cout << ']';
						row = 4;
						break;
					}else if(key == Down){
						setcolor(FOREGROUND_INTENSITY);
						gotoxy(14 + *density * 7, 11);
						cout << '[';
						gotoxy(19 + *density * 7, 11);
						cout << ']';
						row = 2;
						break;
					}else if(key == '\r' || key == ' '){
						return 1;
					}else if(key == 27){
						return 0;
					}
				}
				if(flash == 19){
					setcolor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
					gotoxy(14 + *density * 7, 11);
					cout << '[';
					gotoxy(19 + *density * 7, 11);
					cout << ']';
				}else if(flash == 39){
					setcolor(FOREGROUND_INTENSITY);
					gotoxy(14 + *density * 7, 11);
					cout << '[';
					gotoxy(19 + *density * 7, 11);
					cout << ']';
				}
				break;
			case 2:
				if(_kbhit()){
					key = _getch();
					if(key == Left && *complex != 1){
						setcolor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
						gotoxy(14 + *complex * 7, 13);
						cout << ' ';
						gotoxy(19 + *complex * 7, 13);
						cout << ' ';
						(*complex)--;
						gotoxy(14 + *complex * 7, 13);
						cout << '[';
						gotoxy(19 + *complex * 7, 13);
						cout << ']';
					}else if(key == Right && *complex != 4){
						setcolor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
						gotoxy(14 + *complex * 7, 13);
						cout << ' ';
						gotoxy(19 + *complex * 7, 13);
						cout << ' ';
						(*complex)++;
						gotoxy(14 + *complex * 7, 13);
						cout << '[';
						gotoxy(19 + *complex * 7, 13);
						cout << ']';
					}else if(key == Up){
						setcolor(FOREGROUND_INTENSITY);
						gotoxy(14 + *complex * 7, 13);
						cout << '[';
						gotoxy(19 + *complex * 7, 13);
						cout << ']';
						row = 1;
						break;
					}else if(key == Down){
						setcolor(FOREGROUND_INTENSITY);
						gotoxy(14 + *complex * 7, 13);
						cout << '[';
						gotoxy(19 + *complex * 7, 13);
						cout << ']';
						row = 3;
						break;
					}else if(key == '\r' || key == ' '){
						return 1;
					}else if(key == 27){
						return 0;
					}
				}
				if(flash == 19){
					setcolor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
					gotoxy(14 + *complex * 7, 13);
					cout << '[';
					gotoxy(19 + *complex * 7, 13);
					cout << ']';
				}else if(flash == 39){
					setcolor(FOREGROUND_INTENSITY);
					gotoxy(14 + *complex * 7, 13);
					cout << '[';
					gotoxy(19 + *complex * 7, 13);
					cout << ']';
				}
				break;
			case 3:
				if(_kbhit()){
					key = _getch();
					if(key == Left && *roadc != 1){
						setcolor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
						gotoxy(14 + *roadc * 7, 15);
						cout << ' ';
						gotoxy(19 + *roadc * 7, 15);
						cout << ' ';
						(*roadc)--;
						gotoxy(14 + *roadc * 7, 15);
						cout << '[';
						gotoxy(19 + *roadc * 7, 15);
						cout << ']';
					}else if(key == Right && *roadc != 7){
						setcolor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
						gotoxy(14 + *roadc * 7, 15);
						cout << ' ';
						gotoxy(19 + *roadc * 7, 15);
						cout << ' ';
						(*roadc)++;
						gotoxy(14 + *roadc * 7, 15);
						cout << '[';
						gotoxy(19 + *roadc * 7, 15);
						cout << ']';
					}else if(key == Up){
						setcolor(FOREGROUND_INTENSITY);
						gotoxy(14 + *roadc * 7, 15);
						cout << '[';
						gotoxy(19 + *roadc * 7, 15);
						cout << ']';
						row = 2;
						break;
					}else if(key == Down){
						setcolor(FOREGROUND_INTENSITY);
						gotoxy(14 + *roadc * 7, 15);
						cout << '[';
						gotoxy(19 + *roadc * 7, 15);
						cout << ']';
						row = 4;
						break;
					}else if(key == '\r' || key == ' '){
						return 1;
					}else if(key == 27){
						return 0;
					}
				}
				if(flash == 19){
					setcolor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
					gotoxy(14 + *roadc * 7, 15);
					cout << '[';
					gotoxy(19 + *roadc * 7, 15);
					cout << ']';
				}else if(flash == 39){
					setcolor(FOREGROUND_INTENSITY);
					gotoxy(14 + *roadc * 7, 15);
					cout << '[';
					gotoxy(19 + *roadc * 7, 15);
					cout << ']';
				}
				break;
			case 4:
				if(_kbhit()){
					key = _getch();
					if(key == Left && *wallc != 1){
						setcolor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
						gotoxy(14 + *wallc * 7, 17);
						cout << ' ';
						gotoxy(19 + *wallc * 7, 17);
						cout << ' ';
						(*wallc)--;
						gotoxy(14 + *wallc * 7, 17);
						cout << '[';
						gotoxy(19 + *wallc * 7, 17);
						cout << ']';
					}else if(key == Right && *wallc != 7){
						setcolor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
						gotoxy(14 + *wallc * 7, 17);
						cout << ' ';
						gotoxy(19 + *wallc * 7, 17);
						cout << ' ';
						(*wallc)++;
						gotoxy(14 + *wallc * 7, 17);
						cout << '[';
						gotoxy(19 + *wallc * 7, 17);
						cout << ']';
					}else if(key == Up){
						setcolor(FOREGROUND_INTENSITY);
						gotoxy(14 + *wallc * 7, 17);
						cout << '[';
						gotoxy(19 + *wallc * 7, 17);
						cout << ']';
						row = 3;
						break;
					}else if(key == Down){
						setcolor(FOREGROUND_INTENSITY);
						gotoxy(14 + *wallc * 7, 17);
						cout << '[';
						gotoxy(19 + *wallc * 7, 17);
						cout << ']';
						row = 1;
						break;
					}else if(key == '\r' || key == ' '){
						return 1;
					}else if(key == 27){
						return 0;
					}
				}
				if(flash == 19){
					setcolor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
					gotoxy(14 + *wallc * 7, 17);
					cout << '[';
					gotoxy(19 + *wallc * 7, 17);
					cout << ']';
				}else if(flash == 39){
					setcolor(FOREGROUND_INTENSITY);
					gotoxy(14 + *wallc * 7, 17);
					cout << '[';
					gotoxy(19 + *wallc * 7, 17);
					cout << ']';
				}
				break;
		}

		gotoxy(80, 25);
		flash++;
		if(flash == 40) flash = 0;
		Sleep(10);
	}

	return 1;
}

int K_ROption(int *ratai, int *delay, int *ratc, int *pathc, int flag){
	
	char key;
	int flash = 0;
	int row = 1;

	while(1){
		switch (row){
			case 1:
				if(_kbhit()){
					key = _getch();
					if(key == Left && *ratai != 1){
						setcolor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
						gotoxy(14 + *ratai * 7, 11);
						cout << ' ';
						gotoxy(19 + *ratai * 7, 11);
						cout << ' ';
						(*ratai)--;
						gotoxy(14 + *ratai * 7, 11);
						cout << '[';
						gotoxy(19 + *ratai * 7, 11);
						cout << ']';
					}else if(key == Right && *ratai != (flag == 1 ? 5 : 4)){
						setcolor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
						gotoxy(14 + *ratai * 7, 11);
						cout << ' ';
						gotoxy(19 + *ratai * 7, 11);
						cout << ' ';
						(*ratai)++;
						gotoxy(14 + *ratai * 7, 11);
						cout << '[';
						gotoxy(19 + *ratai * 7, 11);
						cout << ']';
					}else if(key == Up){
						setcolor(FOREGROUND_INTENSITY);
						gotoxy(14 + *ratai * 7, 11);
						cout << '[';
						gotoxy(19 + *ratai * 7, 11);
						cout << ']';
						row = 4;
						break;
					}else if(key == Down){
						setcolor(FOREGROUND_INTENSITY);
						gotoxy(14 + *ratai * 7, 11);
						cout << '[';
						gotoxy(19 + *ratai * 7, 11);
						cout << ']';
						row = 2;
						break;
					}else if(key == '\r' || key == ' '){
						return 1;
					}else if(key == 27){
						return 0;
					}
				}
				if(flash == 19){
					setcolor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
					gotoxy(14 + *ratai * 7, 11);
					cout << '[';
					gotoxy(19 + *ratai * 7, 11);
					cout << ']';
				}else if(flash == 39){
					setcolor(FOREGROUND_INTENSITY);
					gotoxy(14 + *ratai * 7, 11);
					cout << '[';
					gotoxy(19 + *ratai * 7, 11);
					cout << ']';
				}
				break;
			case 2:
				if(_kbhit()){
					key = _getch();
					if(key == Left && *delay != 1){
						setcolor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
						gotoxy(14 + *delay * 7, 13);
						cout << ' ';
						gotoxy(19 + *delay * 7, 13);
						cout << ' ';
						(*delay)--;
						gotoxy(14 + *delay * 7, 13);
						cout << '[';
						gotoxy(19 + *delay * 7, 13);
						cout << ']';
					}else if(key == Right && *delay != 7){
						setcolor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
						gotoxy(14 + *delay * 7, 13);
						cout << ' ';
						gotoxy(19 + *delay * 7, 13);
						cout << ' ';
						(*delay)++;
						gotoxy(14 + *delay * 7, 13);
						cout << '[';
						gotoxy(19 + *delay * 7, 13);
						cout << ']';
					}else if(key == Up){
						setcolor(FOREGROUND_INTENSITY);
						gotoxy(14 + *delay * 7, 13);
						cout << '[';
						gotoxy(19 + *delay * 7, 13);
						cout << ']';
						row = 1;
						break;
					}else if(key == Down){
						setcolor(FOREGROUND_INTENSITY);
						gotoxy(14 + *delay * 7, 13);
						cout << '[';
						gotoxy(19 + *delay * 7, 13);
						cout << ']';
						row = 3;
						break;
					}else if(key == '\r' || key == ' '){
						return 1;
					}else if(key == 27){
						return 0;
					}
				}
				if(flash == 19){
					setcolor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
					gotoxy(14 + *delay * 7, 13);
					cout << '[';
					gotoxy(19 + *delay * 7, 13);
					cout << ']';
				}else if(flash == 39){
					setcolor(FOREGROUND_INTENSITY);
					gotoxy(14 + *delay * 7, 13);
					cout << '[';
					gotoxy(19 + *delay * 7, 13);
					cout << ']';
				}
				break;
			case 3:
				if(_kbhit()){
					key = _getch();
					if(key == Left && *ratc != 1){
						setcolor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
						gotoxy(14 + *ratc * 7, 15);
						cout << ' ';
						gotoxy(19 + *ratc * 7, 15);
						cout << ' ';
						(*ratc)--;
						gotoxy(14 + *ratc * 7, 15);
						cout << '[';
						gotoxy(19 + *ratc * 7, 15);
						cout << ']';
					}else if(key == Right && *ratc != 7){
						setcolor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
						gotoxy(14 + *ratc * 7, 15);
						cout << ' ';
						gotoxy(19 + *ratc * 7, 15);
						cout << ' ';
						(*ratc)++;
						gotoxy(14 + *ratc * 7, 15);
						cout << '[';
						gotoxy(19 + *ratc * 7, 15);
						cout << ']';
					}else if(key == Up){
						setcolor(FOREGROUND_INTENSITY);
						gotoxy(14 + *ratc * 7, 15);
						cout << '[';
						gotoxy(19 + *ratc * 7, 15);
						cout << ']';
						row = 2;
						break;
					}else if(key == Down){
						setcolor(FOREGROUND_INTENSITY);
						gotoxy(14 + *ratc * 7, 15);
						cout << '[';
						gotoxy(19 + *ratc * 7, 15);
						cout << ']';
						row = 4;
						break;
					}else if(key == '\r' || key == ' '){
						return 1;
					}else if(key == 27){
						return 0;
					}
				}
				if(flash == 19){
					setcolor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
					gotoxy(14 + *ratc * 7, 15);
					cout << '[';
					gotoxy(19 + *ratc * 7, 15);
					cout << ']';
				}else if(flash == 39){
					setcolor(FOREGROUND_INTENSITY);
					gotoxy(14 + *ratc * 7, 15);
					cout << '[';
					gotoxy(19 + *ratc * 7, 15);
					cout << ']';
				}
				break;
			case 4:
				if(_kbhit()){
					key = _getch();
					if(key == Left && *pathc != 1){
						setcolor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
						gotoxy(14 + *pathc * 7, 17);
						cout << ' ';
						gotoxy(19 + *pathc * 7, 17);
						cout << ' ';
						(*pathc)--;
						gotoxy(14 + *pathc * 7, 17);
						cout << '[';
						gotoxy(19 + *pathc * 7, 17);
						cout << ']';
					}else if(key == Right && *pathc != 7){
						setcolor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
						gotoxy(14 + *pathc * 7, 17);
						cout << ' ';
						gotoxy(19 + *pathc * 7, 17);
						cout << ' ';
						(*pathc)++;
						gotoxy(14 + *pathc * 7, 17);
						cout << '[';
						gotoxy(19 + *pathc * 7, 17);
						cout << ']';
					}else if(key == Up){
						setcolor(FOREGROUND_INTENSITY);
						gotoxy(14 + *pathc * 7, 17);
						cout << '[';
						gotoxy(19 + *pathc * 7, 17);
						cout << ']';
						row = 3;
						break;
					}else if(key == Down){
						setcolor(FOREGROUND_INTENSITY);
						gotoxy(14 + *pathc * 7, 17);
						cout << '[';
						gotoxy(19 + *pathc * 7, 17);
						cout << ']';
						row = 1;
						break;
					}else if(key == '\r' || key == ' '){
						return 1;
					}else if(key == 27){
						return 0;
					}
				}
				if(flash == 19){
					setcolor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
					gotoxy(14 + *pathc * 7, 17);
					cout << '[';
					gotoxy(19 + *pathc * 7, 17);
					cout << ']';
				}else if(flash == 39){
					setcolor(FOREGROUND_INTENSITY);
					gotoxy(14 + *pathc * 7, 17);
					cout << '[';
					gotoxy(19 + *pathc * 7, 17);
					cout << ']';
				}
				break;
		}

		gotoxy(80, 25);
		flash++;
		if(flash == 40) flash = 0;
		Sleep(10);
	}

	return 1;
}

int K_Result(){

	char key;
	int opt = 1;

	setcolor(FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	while(1){
		if(_kbhit()){
			key = _getch();
			if(key == Up){
				gotoxy(44, 11 + opt);
				cout << "¡@";
				opt != 1 ? opt-- : opt = 6;
				gotoxy(44, 11 + opt);
				cout << "¡»";
				gotoxy(80, 25);
			}else if(key == Down){
				gotoxy(44, 11 + opt);
				cout << "¡@";
				opt != 6 ? opt++ : opt = 1;
				gotoxy(44, 11 + opt);
				cout << "¡»";
				gotoxy(80, 25);
			}else if(key == '\r' || key == ' '){
				return opt;
			}
		}
		Sleep(10);
	}
	return opt;
}