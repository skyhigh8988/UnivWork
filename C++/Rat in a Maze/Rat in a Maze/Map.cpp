#include "Map.h"

map::map(){

	int i, j;
	for(i = 0; i < 75; i++){
		for(j = 0; j <25; j++){
			maze[i][j] = 1;
		}
	}

	top = -1;
	road = 300;

	srand((unsigned)time(NULL));

}

void map::print_map(){

	int i, j;

	clrscr();
	for(i = 0; i < 25; i++){
		if(i != 0) cout << endl;
		for(j = 0; j < 75; j++){
			setcolor(maze[j][i] == 1 ? FOREGROUND_GREEN | BACKGROUND_GREEN : 0);
			cout << ' ';
		}
	}

	return;
}

void map::creat_path(){

	int x, y;

	x = -1;
	y = rand() % 23 + 1;

	while(x < 74){
		switch (rand() % 3){
			case 0:
				maze[++x][y] = 0;
				stack[++top] = x * 25 + y;
				maze[++x][y] = 0;
				stack[++top] = x * 25 + y;
				break;
			case 1:
				if((y + 2) < 24){
					maze[++x][y] = 0;
					stack[++top] = x * 25 + y;
					maze[++x][y] = 0;
					stack[++top] = x * 25 + y;
					maze[x][++y] = 0;
					stack[++top] = x * 25 + y;
					maze[x][++y] = 0;
					stack[++top] = x * 25 + y;
				}
				break;
			case 2:
				if((y - 2) > 0){
					maze[++x][y] = 0;
					stack[++top] = x * 25 + y;
					maze[++x][y] = 0;
					stack[++top] = x * 25 + y;
					maze[x][--y] = 0;
					stack[++top] = x * 25 + y;
					maze[x][--y] = 0;
					stack[++top] = x * 25 + y;
				}
				break;
		}
	}
	maze[++x][y] = 0;
	stack[++top] = x * 25 + y;

	return;
}

void map::creat_branch(){

	int loc, x, y, dx, dy;
	
	while(road > 0){

		loc = rand() % top;
		x = stack[loc] / 25;
		y = stack[loc] % 25;

		switch (rand() % 4){
			case 0:
				dx = 0;
				dy = 1;
				break;
			case 1:
				dx = 0;
				dy = -1;
				break;
			case 2:
				dx = 1;
				dy = 0;
				break;
			case 3:
				dx = -1;
				dy = 0;
				break;
		}

		if(x + dx * 2 > 0 && x + dx * 2 < 74 && y + dy * 2 > 0 && y + dy * 2 < 24){
			if(maze[x + dx][y + dy] == 1 && maze[x + dx *2][y + dy *2] == 1){
				if(maze[x + dx *2 + 1][y + dy *2] == 1 && maze[x + dx *2 - 1][y + dy *2] == 1 && 
				   maze[x + dx *2][y + dy *2 + 1] == 1 && maze[x + dx *2][y + dy *2 - 1] == 1 &&
				   maze[x + dx *2 + 1][y + dy *2 + 1] == 1 && maze[x + dx *2 - 1][y + dy *2 - 1] == 1 &&
				   maze[x + dx *2 - 1][y + dy *2 + 1] == 1 && maze[x + dx *2 + 1][y + dy *2 - 1] == 1){
					maze[x + dx][y + dy] = 0;
					stack[++top] = (x + dx) * 25 + y + dy;
					maze[x + dx *2][y + dy *2] = 0;
					stack[++top] = (x + dx *2) * 25 + y + dy *2;
					road--;
				}
			}
		}
	
	}

	return;
}


map2::map2(int odensity, int ocomplex, int oroadc, int owallc, int *osn){

	sn = *osn;
	(*osn)++;

	int i, j;
	for(i = 0; i < 40; i++){
		for(j = 0; j <23; j++){
			maze[i][j] = 1;
		}
	}

	top = -1;
	density = odensity * 10;
	road = odensity * 92;
	complex = 6 - ocomplex;
	
	switch(oroadc){
		case 1:
			roadc = FOREGROUND_RED | BACKGROUND_RED;
			break;
		case 2:
			roadc = FOREGROUND_GREEN | BACKGROUND_GREEN | FOREGROUND_RED | BACKGROUND_RED;
			break;
		case 3:
			roadc = FOREGROUND_GREEN | BACKGROUND_GREEN;
			break;
		case 4:
			roadc = FOREGROUND_GREEN | BACKGROUND_GREEN | FOREGROUND_BLUE | BACKGROUND_BLUE;
			break;
		case 5:
			roadc = FOREGROUND_BLUE | BACKGROUND_BLUE;
			break;
		case 6:
			roadc = FOREGROUND_BLUE | BACKGROUND_BLUE | FOREGROUND_RED | BACKGROUND_RED;
			break;
		case 7:
			roadc = 0;
			break;
	}

	switch(owallc){
		case 1:
			wallc = FOREGROUND_RED | BACKGROUND_RED;
			break;
		case 2:
			wallc = FOREGROUND_GREEN | BACKGROUND_GREEN | FOREGROUND_RED | BACKGROUND_RED;
			break;
		case 3:
			wallc = FOREGROUND_GREEN | BACKGROUND_GREEN;
			break;
		case 4:
			wallc = FOREGROUND_GREEN | BACKGROUND_GREEN | FOREGROUND_BLUE | BACKGROUND_BLUE;
			break;
		case 5:
			wallc = FOREGROUND_BLUE | BACKGROUND_BLUE;
			break;
		case 6:
			wallc = FOREGROUND_BLUE | BACKGROUND_BLUE | FOREGROUND_RED | BACKGROUND_RED;
			break;
		case 7:
			wallc = 0;
			break;
	}

	srand((unsigned)time(NULL));
}

void map2::print_map(){

	int i, j;

	clrscr();
	cout << endl;
	for(i = 0; i < 23; i++){
		for(j = 0; j < 40; j++){
			setcolor(maze[j][i] == 1 ? wallc : roadc);
			cout << "　";
		}
	}

	gotoxy(1,1);
	setcolor(FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << "STEP:               TIME:               FAIL:";

	return;
}

void map2::creat_path(){

	int x, y, c = 0;

	x = -1;
	y = rand() % 21 + 1;

	while(x < 38){
		if(c > 500){
			int loc = rand() % top;
			x = stack[loc] / 23;
			y = stack[loc] % 23;
		}
		switch (rand() % 4){
			case 0:
				while((rand() % complex) > 0){
					if(maze[x + 1][y] == 1 && maze[x + 1][y + 1] == 1 && maze[x + 1][y - 1] == 1 && maze[x + 2][y] == 1 && maze[x + 2][y + 1] == 1 && maze[x + 2][y - 1] == 1){
						maze[++x][y] = 0;
						stack[++top] = x * 23 + y;
						road--;
						c = 0;
					}
				}
				break;
			case 1:
				while((rand() % complex) > 0){
					if(y > 2 && y < 20 && x > 1 && maze[x - 1][y] == 1 && maze[x - 1][y + 1] == 1 && maze[x - 1][y - 1] == 1 && maze[x - 2][y] == 1 && maze[x - 2][y + 1] == 1 && maze[x - 2][y - 1] == 1){
						maze[--x][y] = 0;
						stack[++top] = x * 23 + y;
						road--;
						c = 0;
					}
				}
				break;
			case 2:
				while((rand() % complex) > 0){
					if(y < 21 && maze[x][y + 1] == 1 && maze[x + 1][y + 1] == 1 && maze[x - 1][y + 1] == 1 && maze[x][y + 2] == 1 && maze[x + 1][y + 2] == 1 && maze[x - 1][y + 2] == 1){
						maze[x][++y] = 0;
						stack[++top] = x * 23 + y;
						road--;
						c = 0;
					}
				}
				break;
			case 3:
				while((rand() % complex) > 0 ){
					if(y > 1 && maze[x][y - 1] == 1 && maze[x + 1][y - 1] == 1 && maze[x - 1][y - 1] == 1 && maze[x][y - 2] == 1 && maze[x + 1][y - 2] == 1 && maze[x - 1][y - 2] == 1){
						maze[x][--y] = 0;
						stack[++top] = x * 23 + y;
						road--;
						c = 0;
					}
				}
				break;
		}
		c++;
	}
	maze[++x][y] = 0;
	stack[++top] = x * 23 + y;
	road--;

	return;
}

void map2::creat_branch(){

	int loc, x, y, c = 0;
	
	while(road > 0){

		loc = rand() % top;
		x = stack[loc] / 23;
		y = stack[loc] % 23;

		switch (rand() % 4){
			case 0:
				while((rand() % complex) > 0){
					if(x < 38 && maze[x + 1][y] == 1 && maze[x + 1][y + 1] == 1 && maze[x + 1][y - 1] == 1 && maze[x + 2][y] == 1 && maze[x + 2][y + 1] == 1 && maze[x + 2][y - 1] == 1){
						maze[++x][y] = 0;
						stack[++top] = x * 23 + y;
						road--;
						c = 0;
					}
				}
				break;
			case 1:
				while((rand() % complex) > 0){
					if(x > 1 && maze[x - 1][y] == 1 && maze[x - 1][y + 1] == 1 && maze[x - 1][y - 1] == 1 && maze[x - 2][y] == 1 && maze[x - 2][y + 1] == 1 && maze[x - 2][y - 1] == 1){
						maze[--x][y] = 0;
						stack[++top] = x * 23 + y;
						road--;
						c = 0;
					}
				}
				break;
			case 2:
				while((rand() % complex) > 0){
					if(y < 21 && maze[x][y + 1] == 1 && maze[x + 1][y + 1] == 1 && maze[x - 1][y + 1] == 1 && maze[x][y + 2] == 1 && maze[x + 1][y + 2] == 1 && maze[x - 1][y + 2] == 1){
						maze[x][++y] = 0;
						stack[++top] = x * 23 + y;
						road--;
						c = 0;
					}
				}
				break;
			case 3:
				while((rand() % complex) > 0){
					if(y > 1 && maze[x][y - 1] == 1 && maze[x + 1][y - 1] == 1 && maze[x - 1][y - 1] == 1 && maze[x][y - 2] == 1 && maze[x + 1][y - 2] == 1 && maze[x - 1][y - 2] == 1){
						maze[x][--y] = 0;
						stack[++top] = x * 23 + y;
						road--;
						c = 0;
					}
				}
				break;
		}
		c++;
		if(c > 10000) road = 0;
	
	}

	return;
}

void map2::result(){

	setcolor(FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_RED);
	gotoxy(20, 10);
	cout << sn;
	gotoxy(20, 11);
	cout << density << '%';
	gotoxy(20, 12);
	cout << 6 - complex;

	gotoxy(80, 25);
	return;
}