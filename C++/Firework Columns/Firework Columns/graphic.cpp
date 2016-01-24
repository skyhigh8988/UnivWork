#include "graphic.h"

void g_title(){
	clrscr();
	gotoxy(1, 3);
	setcolor(FOREGROUND_INTENSITY | FOREGROUND_RED);
	cout << "¡@¢i¢i¢i¢i¢i¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¢i\n";
	cout << "¡@¢i¢m¡@¡@¡@¡@¢i¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¢i\n";
	cout << "¡@¢i¢m¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¢i\n";
	cout << "¡@¢i¢i¢i¢i¢o¡@¢i¡@¢i¡@¢¨¢i¡@¢¨¢i¢i¢©¡@¢i¡@¢i¡@¢i¡@¢¨¢i¢i¢©¡@¢i¡@¢¨¢i¡@¢i¡@¢¨¢i\n";
	cout << "¡@¢i¢m¡@¡@¡@¡@¢i¡@¢i¢¨¢«¡@¡@¢i¡@¡@¢i¡@¢i¡@¢i¡@¢i¡@¢i¡@¡@¢i¡@¢i¢¨¢«¡@¡@¢i¢¨¢«\n";
	cout << "¡@¢i¢m¡@¡@¡@¡@¢i¡@¢i¢«¡@¡@¡@¢i¢i¢i¢«¡@¢i¡@¢i¡@¢i¡@¢i¡@¡@¢i¡@¢i¢«¡@¡@¡@¢i¢i¢©\n";
	cout << "¡@¢i¢m¡@¡@¡@¡@¢i¡@¢i¡@¡@¡@¡@¢i¡@¡@¡@¡@¢i¡@¢i¡@¢i¡@¢i¡@¡@¢i¡@¢i¡@¡@¡@¡@¢i¢ª¢i¢©\n";
	cout << "¡@¢i¢m¡@¡@¡@¡@¢i¡@¢i¡@¡@¡@¡@¢ª¢i¢i¢«¡@¢ª¢i¢i¢i¢«¡@¢ª¢i¢i¢«¡@¢i¡@¡@¡@¡@¢i¡@¢ª¢i\n\n";
	setcolor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
	cout << "¡@¡@¡@¡@¡@¢i¢i¢i¡@¢i¢i¢i¡@¢i¡@¡@¡@¢i¡@¢i¡@¢i¢©¢¨¢i¡@¢i¢©¡@¢i¡@¢i¢i¢i\n";
	cout << "¡@¡@¡@¡@¡@¢i¡@¡@¡@¢i¡@¢i¡@¢i¡@¡@¡@¢i¡@¢i¡@¢i¢ª¢«¢i¡@¢i¢ª¢©¢i¡@¢ª¢i¢©\n";
	cout << "¡@¡@¡@¡@¡@¢i¢i¢i¡@¢i¢i¢i¡@¢i¢i¢i¡@¢i¢i¢i¡@¢i¡@¡@¢i¡@¢i¡@¢ª¢i¡@¢i¢i¢i";

	gotoxy(29, 20);
	setcolor(BACKGROUND_INTENSITY | FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_BLUE);
	cout << "-Press Any Key to Start-";

	gotoxy(80, 25);
	return;
}

void g_menu(){

	gotoxy(29, 18);
	setcolor(FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "¡¹¡¹   GAME START   ¡¹¡¹";
	gotoxy(29, 19);
	cout << "¡@¡@      HELP      ¡@¡@";
	gotoxy(29, 20);
	cout << "¡@¡@      RANK      ¡@¡@";
	gotoxy(29, 21);
	cout << "¡@¡@      EXIT      ¡@¡@";

	gotoxy(80, 25);
	return;
}

void g_setf(int flag){
	clrscr();

	setcolor(FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
	gotoxy(16, 3);
	cout << "¢¨¢i¢i¡@¢i¢i¢i¡@¢i¢i¢i¡@¢i¢i¢i¡@¢i¡@¢i¡@¢i¡@¢¨¢i¢©";
	gotoxy(16, 4);
	cout << "¢i¡@¡@¡@¢i¡Å¡Å¡@¡@¢i¡@¡@¡@¢i¡@¡@¢i¡@¢i¢©¢i¡@¢i";
	gotoxy(16, 5);
	cout << "¢ª¢i¢©¡@¢i¢i¢i¡@¡@¢i¡@¡@¡@¢i¡@¡@¢i¡@¢i¢i¢i¡@¢i¢ª¢i";
	gotoxy(16, 6);
	cout << "¢c¢c¢i¡@¢i¢c¢c¡@¡@¢i¡@¡@¡@¢i¡@¡@¢i¡@¢i¢ª¢i¡@¢i¢c¢i";
	gotoxy(16, 7);
	cout << "¢i¢i¢«¡@¢i¢i¢i¡@¡@¢i¡@¡@¡@¢i¡@¡@¢i¡@¢i¡@¢i¡@¢ª¢i¢«";

	setcolor(FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	gotoxy(7, 10);
	cout << "Difficulty";
	gotoxy(7, 12);
	cout << "Enable Effect";
	if(flag == 1) setcolor(FOREGROUND_INTENSITY);
	gotoxy(7, 14);
	cout << "Save Score";
	if(flag == 1) setcolor(FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	else setcolor(FOREGROUND_INTENSITY);
	gotoxy(7, 16);
	cout << "Enable (¡·)";
	gotoxy(7, 18);
	cout << "Times of (¡ò)";
	gotoxy(7, 20);
	cout << "Times of (¡³)";

	setcolor(BACKGROUND_INTENSITY | FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
	gotoxy(27, 10);
	cout << "1";
	gotoxy(27, 12);
	cout << "Yes";
	gotoxy(27, 14);
	cout << "Yes";
	setcolor(BACKGROUND_INTENSITY);
	gotoxy(32, 16);
	cout << "No";
	gotoxy(27, 18);
	cout << "0";
	gotoxy(27, 20);
	cout << "0";

	setcolor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	gotoxy(32, 10);
	cout << "2    3    4    5";
	gotoxy(32, 12);
	cout << "No";
	gotoxy(32, 14);
	cout << "No";
	setcolor(FOREGROUND_INTENSITY);
	gotoxy(27, 16);
	cout << "Yes";
	gotoxy(32, 18);
	cout << "1    2    3    4    5    6    7    8    9";
	gotoxy(32, 20);
	cout << "1    2    3    4    5    6    7    8    9";

	if(flag == 1){
		setcolor(BACKGROUND_INTENSITY);
		gotoxy(32, 14);
		cout << "No";
		setcolor(FOREGROUND_INTENSITY);
		gotoxy(27, 14);
		cout << "Yes";
		setcolor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		gotoxy(32, 16);
		cout << "No";
		gotoxy(27, 18);
		cout << "0    1    2    3    4    5    6    7    8    9";
		gotoxy(27, 20);
		cout << "0    1    2    3    4    5    6    7    8    9";
		setcolor(BACKGROUND_INTENSITY | FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
		gotoxy(27, 16);
		cout << "Yes";
		gotoxy(52, 18);
		cout << "5";
		gotoxy(52, 20);
		cout << "5";
	}

	setcolor(FOREGROUND_INTENSITY | FOREGROUND_BLUE);
	gotoxy(4, 23);
	cout << "[ESC] Back to title";
	gotoxy(4, 24);
	cout << "[¡ô][¡õ] Change item    [¡ö][¡÷] Change value    [Space][Enter] Game start";

	gotoxy(80, 25);
	return;
}

void g_gamef(){
	clrscr();
	gotoxy(33, 6);
	cout << "ùÝùùùùùùùùùùùùùß";
	gotoxy(33, 7);
	cout << "ùø¡@¡@¡@¡@¡@¡@ùø";
	gotoxy(33, 8);
	cout << "ùø¡@¡@¡@¡@¡@¡@ùø";
	gotoxy(33, 9);
	cout << "ùø¡@¡@¡@¡@¡@¡@ùø";
	gotoxy(33, 10);
	cout << "ùø¡@¡@¡@¡@¡@¡@ùø";
	gotoxy(33, 11);
	cout << "ùø¡@¡@¡@¡@¡@¡@ùø";
	gotoxy(33, 12);
	cout << "ùø¡@¡@¡@¡@¡@¡@ùø";
	gotoxy(33, 13);
	cout << "ùø¡@¡@¡@¡@¡@¡@ùø";
	gotoxy(33, 14);
	cout << "ùø¡@¡@¡@¡@¡@¡@ùø";
	gotoxy(33, 15);
	cout << "ùø¡@¡@¡@¡@¡@¡@ùø";
	gotoxy(33, 16);
	cout << "ùø¡@¡@¡@¡@¡@¡@ùø";
	gotoxy(33, 17);
	cout << "ùø¡@¡@¡@¡@¡@¡@ùø";
	gotoxy(33, 18);
	cout << "ùø¡@¡@¡@¡@¡@¡@ùø";
	gotoxy(33, 19);
	cout << "ùø¡@¡@¡@¡@¡@¡@ùø";
	gotoxy(33, 20);
	cout << "ùãùùùùùùùùùùùùùå";
	gotoxy(60, 10);
	cout << "ùÝùùùùùùùß";
	gotoxy(60, 11);
	cout << "ùø¡@¡@¡@ùø";
	gotoxy(60, 12);
	cout << "ùø¡@¡@¡@ùø";
	gotoxy(60, 13);
	cout << "ùø¡@¡@¡@ùø";
	gotoxy(60, 14);
	cout << "ùãùùùùùùùå";

	setcolor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
	gotoxy(16, 9);
	cout << "LEVEL";
	gotoxy(16, 12);
	cout << "SCORE";
	gotoxy(63, 9);
	cout << "NEXT";
	gotoxy(18, 13);
	setcolor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
	cout << "0";

	setcolor(FOREGROUND_INTENSITY | FOREGROUND_BLUE);
	gotoxy(4, 24);
	cout << "[ESC] Pause     [¡õ][¡ö][¡÷] Control blocks     [Space] Shift blocks";

	gotoxy(80, 25);
	return;
}

void g_record(){

	clrscr();
	gotoxy(9, 5);
	setcolor(FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	cout << "Congratulations!!";
	gotoxy(2, 7);
	setcolor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	for(int i = 0; i < 39; i++)	cout << "ùù";
	gotoxy(2, 10);
	for(int i = 0; i < 39; i++)	cout << "ùù";
	gotoxy(9, 8);
	setcolor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
	cout << "Score     Level     Max Chain     Play Time     Score per Second";
	gotoxy(9, 12);
	setcolor(FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "Please enter your name:";
	gotoxy(26, 15);
	setcolor(BACKGROUND_INTENSITY | FOREGROUND_INTENSITY);
	for(int i = 0; i < 30; i++) cout << ' ';

	gotoxy(80, 25);
	return;
}

void g_rank(){

	clrscr();
	setcolor(FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
	gotoxy(26, 3);
	cout << "¢i¢i¢©¡@¢¨¢i¢©¡@¢i¡@¢i¡@¢i¢¨¢«";
	gotoxy(26, 4);
	cout << "¢i¡@¢i¡@¢i¡@¢i¡@¢i¢©¢i¡@¢i¢«";
	gotoxy(26, 5);
	cout << "¢i¢i¢«¡@¢i¢i¢i¡@¢i¢ª¢i¡@¢i¢©";
	gotoxy(26, 6);
	cout << "¢i¢ª¢©¡@¢i¡@¢i¡@¢i¡@¢i¡@¢i¢ª¢©";

	setcolor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	gotoxy(3, 8);
	for(int i = 0; i < 38; i++)cout << "ùù";
	gotoxy(3, 10);
	for(int i = 0; i < 38; i++)cout << "¢w";
	gotoxy(3, 21);
	for(int i = 0; i < 38; i++)cout << "ùù";

	setcolor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
	gotoxy(5, 9);
	cout << "#  Name             Score  L  C  Time   S/T     Date";

	setcolor(FOREGROUND_INTENSITY | FOREGROUND_BLUE);
	gotoxy(4, 24);
	cout << "[ESC][Space][Enter] Back to title";

	gotoxy(80, 25);
	return;
}

void g_cheat(int flag){
	gotoxy(33, 24);
	setcolor(FOREGROUND_INTENSITY | FOREGROUND_RED);
	cout << "-Cheat Mode " << (flag == 1 ? "On- " : "Off-");
	gotoxy(80, 25);
	return;
}

void g_pause(){

	setcolor(FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
	gotoxy(22, 3);
	cout << "¢i¢i¢©¡@¢¨¢i¢©¡@¢i¡@¢i¡@¢¨¢i¢i¡@¢i¢i¢i";
	gotoxy(22, 4);
	cout << "¢i¡@¢i¡@¢i¡@¢i¡@¢i¡@¢i¡@¢i¡@¡@¡@¢i¡Å¡Å";
	gotoxy(22, 5);
	cout << "¢i¢d¢i¡@¢i¢d¢i¡@¢i¡@¢i¡@¢ª¢i¢©¡@¢i¢i¢i";
	gotoxy(22, 6);
	cout << "¢i¢i¢«¡@¢i¢i¢i¡@¢i¢e¢i¡@¢c¢c¢i¡@¢i¢c¢c";
	gotoxy(22, 7);
	cout << "¢i¡@¡@¡@¢i¡@¢i¡@¢ª¢i¢«¡@¢i¢i¢«¡@¢i¢i¢i";
	
	setcolor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	gotoxy(30, 9);
	cout << "----------------------";
	gotoxy(30, 21);
	cout << "----------------------";

	setcolor(FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	gotoxy(34, 11);
	cout << "¡@¡@RESUME¡@¡@";
	gotoxy(34, 13);
	cout << "¡@¡@RESTART ¡@";
	gotoxy(34, 15);
	cout << "¡@¡@HELP¡@¡@¡@";
	gotoxy(34, 17);
	cout << "¡@¡@TITLE ¡@¡@";
	gotoxy(34, 19);
	cout << "¡@¡@EXIT¡@¡@¡@";

	for(int i = 0; i < 14; i += 2){
		gotoxy(34, 8 + i);
		cout << "¡@¡@¡@¡@¡@¡@¡@";
	}
	gotoxy(64, 11);
	cout << "¡@";
	gotoxy(64, 12);
	cout << "¡@";
	gotoxy(64, 13);
	cout << "¡@";

	setcolor(FOREGROUND_INTENSITY | FOREGROUND_RED);
	gotoxy(34, 11);
	cout << "¡»";
	gotoxy(46, 11);
	cout << "¡»";

	setcolor(FOREGROUND_INTENSITY | FOREGROUND_BLUE);
	gotoxy(4, 23);
	cout << "                                                                 ";
	gotoxy(4, 24);
	cout << "[ESC] Resume     [¡ô][¡õ] Change Option     [Space][Enter] OK       ";


	gotoxy(80, 25);
	return;
}

void g_pattern(int num){

	switch(num){
		case 0:
			//setcolor(0);
			cout << "¡@";
			break;
		case 1:
			setcolor(FOREGROUND_INTENSITY | FOREGROUND_RED);
			cout << "¡´";
			break;
		case 2:
			setcolor(FOREGROUND_INTENSITY | FOREGROUND_GREEN);
			cout << "¡´";
			break;
		case 3:
			setcolor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
			cout << "¡´";
			break;
		case 4:
			setcolor(FOREGROUND_INTENSITY | FOREGROUND_BLUE);
			cout << "¡´";
			break;
		case 5:
			setcolor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
			cout << "¡´";
			break;
		case 6:
			setcolor(FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
			cout << "¡´";
			break;
		case 7:
			setcolor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			cout << "¡´";
			break;
		case 8:
			setcolor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			cout << "¡·";
			break;
		case 9:
			setcolor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			cout << "¡ò";
			break;
		case 10:
			setcolor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			cout << "¡³";
			break;
		case -10:
			setcolor(BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_INTENSITY);
			cout << "¡³";
			break;
		case -9:
			setcolor(BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_INTENSITY);
			cout << "¡ò";
			break;
		case -8:
			setcolor(BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_INTENSITY);
			cout << "¡·";
			break;
		case -7:
			setcolor(BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_INTENSITY);
			cout << "¡´";
			break;
		case -6:
			setcolor(BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_INTENSITY | FOREGROUND_RED);
			cout << "¡´";
			break;
		case -5:
			setcolor(BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_INTENSITY | FOREGROUND_GREEN);
			cout << "¡´";
			break;
		case -4:
			setcolor(BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
			cout << "¡´";
			break;
		case -3:
			setcolor(BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_INTENSITY | FOREGROUND_BLUE);
			cout << "¡´";
			break;
		case -2:
			setcolor(BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
			cout << "¡´";
			break;
		case -1:
			setcolor(BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
			cout << "¡´";
			break;
	}
	return;
}

void g_help(){

	clrscr();

	setcolor(FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	gotoxy(6, 3);
	cout << "Instructions";

	setcolor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
	gotoxy(6, 5);
	cout << "  Arrange the blocks so that 3 or more blocks of the same color from a\r\n";
	cout << "     straight line horizontally, vertically or diagonally. When a line is\r\n";
	cout << "     formed, the blocks will disappear and you gain points. Every 3 blocks\r\n";
	cout << "     can give you 200 points and you get some bonus points when you make a\r\n";
	cout << "     chain or make more than 3 blocks disappear at once. You lost the game\r\n";
	cout << "     when the bombs pile up to the top of the screen.\r\n\r\n";
	cout << "       Use keys [¡õ][¡ö][¡÷] to move the falling blocks, press [Space] key\r\n";
	cout << "     to rotate the falling blocks.\r\n\r\n";
	cout << "       You can enter the cheat codes in main menu to turn the cheat mode on. \r\n";
	cout << "     In cheat mode, press [C] key to use the (¡ò) block, which can make all\r\n";
	cout << "     blocks in the same row and column disappear but cost 100 points, press\r\n";
	cout << "     [B] key to use the (¡³) block, which can make the blocks in the 3x3 area\r\n";
	cout << "     near it disappear and also cost 100 points. In cheat mode, make a chain\r\n";
	cout << "     not only get bonus points but also get a (¡·) block, which can be a\r\n";
	cout << "     block of any color. You can also use [¡ô] key to control the falling\r\n";
	cout << "     blocks in cheat mode.";

	setcolor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	gotoxy(17, 12);
	cout << "[¡õ][¡ö][¡÷]";
	gotoxy(64, 12);
	cout << "[Space]";
	gotoxy(27, 16);
	cout << "[C]";
	gotoxy(46, 16);
	cout << "(¡ò)";
	gotoxy(6, 18);
	cout << "[B]";
	gotoxy(25, 18);
	cout << "(¡³)";
	gotoxy(47, 20);
	cout << "(¡·)";
	gotoxy(43, 21);
	cout << "[¡ô]";

	setcolor(FOREGROUND_INTENSITY | FOREGROUND_BLUE);
	gotoxy(4, 24);
	cout << "[ESC][Space][Enter] Back";

	gotoxy(80, 25);
	return;
}