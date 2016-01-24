#include "Rat.h"

rat::rat(map MAP){

	int i, j;
	for(i = 0; i < 75; i++){
		for(j = 0; j <25; j++){
			maze[i][j] = MAP.maze[i][j];
		}
	}

	x = 0;
	y = MAP.stack[0] % 25;

	for(i = 0; i < 1024; i++) stack[i] = y;
	top = 0;
	delay = 50;

	setcolor(FOREGROUND_INTENSITY | FOREGROUND_RED);
	gotoxy(x + 1, y + 1);
	cout << '@';
}

void rat::print_rat(){

	gotoxy(stack[top - 1] / 25 + 1, stack[top - 1] % 25 + 1);
	cout << ' ';

	gotoxy(stack[top + 1] / 25 + 1, stack[top + 1] % 25 + 1);
	cout << ' ';

	gotoxy(stack[top] / 25 + 1, stack[top] % 25 + 1);
	cout << '@';

	return;
}

void rat::run(){

	while(x < 74){
		if(maze[x + 1][y] == 0){
			maze[x][y] = 1;
			x++;
			stack[++top] = x * 25 + y;
			print_rat();
		}else if(maze[x][y + 1] == 0){
			maze[x][y] = 1;
			y++;
			stack[++top] = x * 25 + y;
			print_rat();
		}else if(maze[x][y - 1] == 0){
			maze[x][y] = 1;
			y--;
			stack[++top] = x * 25 + y;
			print_rat();
		}else{
			maze[x][y] = 1;
			top--;
			x = stack[top] / 25;
			y = stack[top] % 25;
			print_rat();
		}
		Sleep(delay);
	}

	gotoxy(80, 25);
	return;
}


rat2::rat2(map2 MAP, int oratai, int odelay, int oratc, int opathc){

	int i, j;
	for(i = 0; i < 40; i++){
		for(j = 0; j <23; j++){
			maze[i][j] = MAP.maze[i][j];
		}
	}

	x = 0;
	y = MAP.stack[0] % 23;

	for(i = 0; i < 1024; i++) stack[i] = y;
	top = 0;

	delay = odelay * 10;
	ratai = oratai;

	switch(opathc){
		case 1:
			pathc = BACKGROUND_RED;
			break;
		case 2:
			pathc = BACKGROUND_GREEN | BACKGROUND_RED;
			break;
		case 3:
			pathc = BACKGROUND_GREEN;
			break;
		case 4:
			pathc = BACKGROUND_GREEN | BACKGROUND_BLUE;
			break;
		case 5:
			pathc = BACKGROUND_BLUE;
			break;
		case 6:
			pathc = BACKGROUND_BLUE | BACKGROUND_RED;
			break;
		case 7:
			pathc = 0;
			break;
	}

	switch(oratc){
		case 1:
			ratc = FOREGROUND_INTENSITY | FOREGROUND_RED | pathc;
			break;
		case 2:
			ratc = FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_RED | pathc;
			break;
		case 3:
			ratc = FOREGROUND_INTENSITY | FOREGROUND_GREEN | pathc;
			break;
		case 4:
			ratc = FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE | pathc;
			break;
		case 5:
			ratc = FOREGROUND_INTENSITY | FOREGROUND_BLUE | pathc;
			break;
		case 6:
			ratc = FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED | pathc;
			break;
		case 7:
			ratc = FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | pathc;
			break;
	}

	setcolor(ratc);
	gotoxy(x + 1, y + 2);
	cout << "¡´";

	ttime = 0;
	step = 0;
	fail = 0;
}

void rat2::print_rat(){

	gotoxy((stack[top - 1] / 23) * 2 + 1, stack[top - 1] % 23 + 2);
	cout << "¡@";

	gotoxy((stack[top + 1] / 23) * 2 + 1, stack[top + 1] % 23 + 2);
	cout << "¡@";

	gotoxy((stack[top] / 23) * 2 + 1, stack[top] % 23 + 2);
	cout << "¡´";

	step++;
	return;
}

void rat2::run(){

	switch(ratai){
		case 1:
			run1();
			break;
		case 2:
			run2();
			break;
		case 3:
			run3();
			break;
		case 4:
			run4();
			break;
		case 5:
			run5();
			break;
	}

	for(int i = 0; i <= top; i++){
		x = stack[i] / 23;
		y = stack[i] % 23;
		setcolor(BACKGROUND_INTENSITY | ratc);
		gotoxy(x * 2 + 1, y + 2);
		cout << (i == top ? "¡´" : "¡@");
	}

	gotoxy(80, 25);
	return;
}

void rat2::run1(){

	int reset = 0;
	int direction = 0;

	while(x < 39){
		if(maze[x + 1][y] == 1 && maze[x][y + 1] == 1 && maze[x][y - 1] == 1 && maze[x - 1][y] == 1){
			maze[x][y] = 1;
			top--;
			x = stack[top] / 23;
			y = stack[top] % 23;
			print_rat();
			if(reset == 1){
				fail++;
				reset = 0;
			}
		}else{
			while(1){
				if(direction == 0 && maze[x + 1][y] == 0){
					maze[x][y] = 1;
					x++;
					stack[++top] = x * 23 + y;
					print_rat();
					reset = 1;
					direction = (direction + 1) % 4;
					break;
				}else if(direction == 1 && maze[x][y + 1] == 0){
					maze[x][y] = 1;
					y++;
					stack[++top] = x * 23 + y;
					print_rat();
					reset = 1;
					direction = (direction + 1) % 4;
					break;
				}else if(direction == 3 && maze[x][y - 1] == 0){
					maze[x][y] = 1;
					y--;
					stack[++top] = x * 23 + y;
					print_rat();
					reset = 1;
					direction = (direction + 1) % 4;
					break;
				}else if(direction == 2 && maze[x - 1][y] == 0){
					maze[x][y] = 1;
					x--;
					stack[++top] = x * 23 + y;
					print_rat();
					reset = 1;
					direction = (direction + 1) % 4;
					break;
				}else direction = (direction + 1) % 4;
			}
		}

		setcolor(FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
		gotoxy(6, 1);
		cout << step;
		gotoxy(26, 1);
		ttime = (delay * step) / 1000.0;
		cout << fixed << setprecision(3) << ttime;
		gotoxy(46, 1);
		cout << fail;
		setcolor(ratc);
		Sleep(delay);
	}

	gotoxy(80, 25);
	return;
}

void rat2::run2(){

	int reset = 0;
	int direction;

	while(x < 39){
		if(maze[x + 1][y] == 1 && maze[x][y + 1] == 1 && maze[x][y - 1] == 1 && maze[x - 1][y] == 1){
			maze[x][y] = 1;
			top--;
			x = stack[top] / 23;
			y = stack[top] % 23;
			print_rat();
			if(reset == 1){
				fail++;
				reset = 0;
			}
		}else{
			while(1){
				direction = rand() % 4;
				if(direction == 0 && maze[x + 1][y] == 0){
					maze[x][y] = 1;
					x++;
					stack[++top] = x * 23 + y;
					print_rat();
					reset = 1;
					break;
				}else if(direction == 1 && maze[x][y + 1] == 0){
					maze[x][y] = 1;
					y++;
					stack[++top] = x * 23 + y;
					print_rat();
					reset = 1;
					break;
				}else if(direction == 2 && maze[x][y - 1] == 0){
					maze[x][y] = 1;
					y--;
					stack[++top] = x * 23 + y;
					print_rat();
					reset = 1;
					break;
				}else if(direction == 3 && maze[x - 1][y] == 0){
					maze[x][y] = 1;
					x--;
					stack[++top] = x * 23 + y;
					print_rat();
					reset = 1;
					break;
				}
			}
		}

		setcolor(FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
		gotoxy(6, 1);
		cout << step;
		gotoxy(26, 1);
		ttime = (delay * step) / 1000.0;
		cout << fixed << setprecision(3) << ttime;
		gotoxy(46, 1);
		cout << fail;
		setcolor(ratc);
		Sleep(delay);
	}

	gotoxy(80, 25);
	return;
}

void rat2::run3(){

	int reset = 0;

	while(x < 39){
		if(maze[x + 1][y] == 0){
			maze[x][y] = 1;
			x++;
			stack[++top] = x * 23 + y;
			print_rat();
			reset = 1;
		}else if(maze[x][y + 1] == 0){
			maze[x][y] = 1;
			y++;
			stack[++top] = x * 23 + y;
			print_rat();
			reset = 1;
		}else if(maze[x][y - 1] == 0){
			maze[x][y] = 1;
			y--;
			stack[++top] = x * 23 + y;
			print_rat();
			reset = 1;
		}else if(maze[x - 1][y] == 0){
			maze[x][y] = 1;
			x--;
			stack[++top] = x * 23 + y;
			print_rat();
			reset = 1;
		}else{
			maze[x][y] = 1;
			top--;
			x = stack[top] / 23;
			y = stack[top] % 23;
			print_rat();
			if(reset == 1){
				fail++;
				reset = 0;
			}
		}

		setcolor(FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
		gotoxy(6, 1);
		cout << step;
		gotoxy(26, 1);
		ttime = (delay * step) / 1000.0;
		cout << fixed << setprecision(3) << ttime;
		gotoxy(46, 1);
		cout << fail;
		setcolor(ratc);
		Sleep(delay);
	}

	gotoxy(80, 25);
	return;
}

void rat2::run4(){

	int reset = 0;
	int direction = 0;

	while(x < 39){
		if(maze[x + 1][y] == 1 && maze[x][y + 1] == 1 && maze[x][y - 1] == 1 && maze[x - 1][y] == 1){
			maze[x][y] = 1;
			top--;
			x = stack[top] / 23;
			y = stack[top] % 23;
			print_rat();
			if(reset == 1){
				fail++;
				reset = 0;
			}
		}else{
			while(1){
				if(direction == 0 && maze[x + 1][y] == 0){
					maze[x][y] = 1;
					x++;
					stack[++top] = x * 23 + y;
					print_rat();
					reset = 1;
					break;
				}else if(direction == 1 && maze[x][y + 1] == 0){
					maze[x][y] = 1;
					y++;
					stack[++top] = x * 23 + y;
					print_rat();
					reset = 1;
					break;
				}else if(direction == 3 && maze[x][y - 1] == 0){
					maze[x][y] = 1;
					y--;
					stack[++top] = x * 23 + y;
					print_rat();
					reset = 1;
					break;
				}else if(direction == 2 && maze[x - 1][y] == 0){
					maze[x][y] = 1;
					x--;
					stack[++top] = x * 23 + y;
					print_rat();
					reset = 1;
					break;
				}else direction = (direction + 1) % 4;
			}
		}

		setcolor(FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
		gotoxy(6, 1);
		cout << step;
		gotoxy(26, 1);
		ttime = (delay * step) / 1000.0;
		cout << fixed << setprecision(3) << ttime;
		gotoxy(46, 1);
		cout << fail;
		setcolor(ratc);
		Sleep(delay);
	}

	gotoxy(80, 25);
	return;
}

void rat2::run5(){

	int ptop = 0;

	while(x < 39){
		if(maze[x + 1][y] == 0){
			maze[x][y] = 1;
			x++;
			stack[++ptop] = x * 23 + y;
		}else if(maze[x][y + 1] == 0){
			maze[x][y] = 1;
			y++;
			stack[++ptop] = x * 23 + y;
		}else if(maze[x][y - 1] == 0){
			maze[x][y] = 1;
			y--;
			stack[++ptop] = x * 23 + y;
		}else if(maze[x - 1][y] == 0){
			maze[x][y] = 1;
			x--;
			stack[++ptop] = x * 23 + y;
		}else{
			maze[x][y] = 1;
			ptop--;
			x = stack[ptop] / 23;
			y = stack[ptop] % 23;
		}
	}

	for(int i = 0; i < ptop; i++){
		print_rat();
		top++;

		setcolor(FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
		gotoxy(6, 1);
		cout << step;
		gotoxy(26, 1);
		ttime = (delay * step) / 1000.0;
		cout << fixed << setprecision(3) << ttime;
		gotoxy(46, 1);
		cout << fail;
		setcolor(ratc);
		Sleep(delay);
	}

	gotoxy(80, 25);
	return;
}

void rat2::result(){

	setcolor(FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_RED);
	gotoxy(20, 13);
	cout << (char)(ratai + 64);
	gotoxy(20, 13);
	if(ratai == 5) cout << "PIKA";
	gotoxy(20, 14);
	cout << delay;
	gotoxy(20, 15);
	cout << top;
	gotoxy(20, 16);
	cout << step;
	gotoxy(20, 17);
	cout << fixed << setprecision(3) << ttime;
	gotoxy(20, 18);
	cout << fail;

	gotoxy(80, 25);
	return;
}