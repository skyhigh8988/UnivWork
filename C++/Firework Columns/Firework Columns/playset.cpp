#include "playset.h"

void playset::initialize(){

	srand((unsigned)time(NULL));

	level = levels;
	cross = crosss;
	bomb = bombs;
	score = 0;
	goal = 0;
	combo = -1;
	maxcb = 0;
	if(cheat == 1) dcheat();
	slevel();
	start = time(NULL);
	opt = 0;

	for(int i = 0; i < 6; i++){
		for(int j = 0; j < 13; j++)	map[i][j] = 0;
	}
	for(int i = 0; i < 6; i++) map[i][13] = -1;

	return;
}

void playset::dcheat(){

	setcolor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
	gotoxy(62, 16);
	cout << "¡ò x";
	gotoxy(62, 17);
	cout << "¡³ x";
	
	setcolor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
	gotoxy(67, 16);
	cout << cross;
	gotoxy(67, 17);
	cout << bomb;

	setcolor(FOREGROUND_INTENSITY | FOREGROUND_BLUE);
	gotoxy(4, 23);
	cout << "[C] Use (¡ò) block     [B] Use (¡³) block     [¡ô] Control blocks";

	gotoxy(80, 25);
	return;
}

void playset::random(){

	next[0] = rand() % pattern + 1;
	next[1] = rand() % pattern + 1;
	next[2] = rand() % pattern + 1;

	dnext();
	return;
}

void playset::dnext(){

	gotoxy(64, 11);
	g_pattern(next[0]);
	gotoxy(64, 12);
	g_pattern(next[1]);
	gotoxy(64, 13);
	g_pattern(next[2]);

	gotoxy(80, 25);
	return;
}

void playset::slevel(){
	goal += level * 500 + 1500;

	gotoxy(18, 10);
	setcolor(BACKGROUND_INTENSITY | FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
	cout << level;
	Sleep(200);
	gotoxy(18, 10);
	setcolor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
	cout << level;
	gotoxy(80, 25);

	delay = (8 - level) * 10;
	pattern = level + 2;

	return;
}

void playset::drop(){

	int count = delay;
	x = 3, y = -1;
	char key;

	now[0] = next[0];
	now[1] = next[1];
	now[2] = next[2];
	random();

	while(1){
		if(count == delay){
			count = 0;
			if(map[x][y + 1] == 0){
				y++;
				dmapp(0, 1);
			}else if(y < 2){
				if(y >= 0) map[x][y] = now[2];
				if(y >= 1) map[x][y - 1] = now[1];
				gameover();
				break;
			}else{
				map[x][y] = now[2];
				map[x][y - 1] = now[1];
				map[x][y - 2] = now[0];

				if(dmask() > 0) remove();

				combo = -1;
				x = 3, y = -1;
				now[0] = next[0];
				now[1] = next[1];
				now[2] = next[2];
				random();
			}
		}
		if(_kbhit()){
			key=_getch();
			move(key);
			if(opt == 4) break;
			else if(opt == 1) resume();
			else if(opt == 2) restart();
			else if(opt == 3) help();
			else if(opt == 5) exit(0);
			opt = 0;
		}
		Sleep(10);
		count++;
	}
	return;
}

void playset::move(char key){

	switch(key){
		case Right:
			if(x != 5 && map[x + 1][y] == 0){
				x++;
				dmapp(1, 0);
			}
			break;
		case Left:
			if(x != 0 && map[x - 1][y] == 0){
				x--;
				dmapp(-1, 0);
			}
			break;
		case Down:
			if(map[x][y + 1] == 0){
				y++;
				dmapp(0, 1);
			}
			break;
		case Up:
			if(y > 0 && cheat == 1){
				y--;
				dmapp(0, -1);
			}
			break;
		case 'C':
		case 'c':
			if(cross > 0){
				next[2] = 9;
				dnext();
				cross --;
				gotoxy(67, 16);
				setcolor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
				cout << cross;
				gotoxy(80, 25);
			}
			break;
		case 'B':
		case 'b':
			if(bomb > 0){
				next[2] = 10;
				dnext();
				bomb--;
				gotoxy(67, 17);
				setcolor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
				cout << bomb;
				gotoxy(80, 25);
			}
			break;
		case 32:
			trans();
			break;
		case 27:
			g_pause();
			opt = k_pause();
			break;
	}
	return;
}

void playset::dmapp(int dx, int dy){

	if(dx != 0 || dy != 0){
		gotoxy(35 + (x - dx) * 2, 7 + y - dy);
		cout << ((y - dy) > -1 ? "¡@" : "");
		gotoxy(35 + (x - dx) * 2, 6 + y - dy);
		cout << ((y - dy) > 0 ? "¡@" : "");
		gotoxy(35 + (x - dx) * 2, 5 + y - dy);
		cout << ((y - dy) > 1? "¡@" : "");
	}

	gotoxy(35 + x * 2, 7 + y);
	if(y > -1) g_pattern(now[2]);
	gotoxy(35 + x * 2, 6 + y);
	if(y > 0) g_pattern(now[1]);
	gotoxy(35 + x * 2, 5 + y);
	if(y > 1) g_pattern(now[0]);
	
	gotoxy(80, 25);
	return;
}

void playset::dmapa(){

	for(int i = 0; i < 6; i++){
		for(int j = 0; j < 13; j++){
			gotoxy(35 + i * 2, 7 + j);
			g_pattern(map[i][j]);
			gotoxy(80, 25);
		}
	}
	return;
}

void playset::trans(){

	int tmp = now[2];
	now[2] = now[1];
	now[1] = now[0];
	now[0] = tmp;
	dmapp(0, 0);

	gotoxy(80, 25);
	return;
}

int equal(int a, int b, int c){
	if(a == 0 || b == 0 || c == 0) return 0;
	return ((a == 8 || b == 8 || a == b) && (a == 8 || c == 8 || a == c) && (c == 8 || b == 8 || c == b));
}

int playset::dmask(){
	int i, j, k ,l;
	int count = 0;

	for(i = 0; i < 6; i++){
		for(j = 0; j < 13; j++) mark[i][j] = 0;
	}
	
	for(i = 0; i < 6; i++){
		for(j = 1; j < 12; j++){
			if(equal(map[i][j], map[i][j - 1], map[i][j + 1])){
				mark[i][j - 1] = mark[i][j] = mark[i][j + 1] = 1;
				count++;
			}
		}
	}

	for(i = 1; i < 5; i++){
		for(j = 0; j < 13; j++){
			if(equal(map[i][j], map[i - 1][j], map[i + 1][j])){
				mark[i - 1][j] = mark[i][j] = mark[i + 1][j] = 1;
				count++;
			}
		}
	}

	for(i = 1; i < 5; i++){
		for(j = 1; j < 12; j++){
			if(equal(map[i][j], map[i - 1][j - 1], map[i + 1][j + 1])){
				mark[i - 1][j - 1] = mark[i][j] = mark[i + 1][j + 1] = 1;
				count++;
			}
		}
	}

	for(i = 1; i < 5; i++){
		for(j = 1; j < 12; j++){
			if(equal(map[i][j], map[i + 1][j - 1], map[i - 1][j + 1])){
				mark[i + 1][j - 1] = mark[i][j] = mark[i - 1][j + 1] = 1;
				count++;
			}
		}
	}

	for(i = 0; i < 6; i++){
		for(j = 0; j < 13; j++){
			if(map[i][j] == 9){
				for(k = 0; k < 6; k++) mark[k][j] = 2;
				for(k = 0; k < 13; k++) mark[i][k] = 2;
				count++;
			}
		}
	}

	for(i = 0; i < 6; i++){
		for(j = 0; j < 13; j++){
			if(map[i][j] == 10){
				for(k = -1; k < 2; k++){
					for(l = -1; l < 2; l++){
						if((i + k) >= 0 && (i + k) <= 5 && (j + l) <= 12) mark[i + k][j + l] = 2;
					}
				}
				count++;
			}
		}
	}

	return count;
}

void playset::remove(){
	int i, j;
	int count = -3;
	combo++;
	if(combo > maxcb) maxcb = combo;
	if(combo > 0 && ranbow == 1){
		if(combo == 1) next[2] = 8;
		if(combo == 2) next[1] = 8;
		if(combo == 3) next[0] = 8;
		dnext();
	}

	if(efct == 1){
		for(i = 0; i < 3; i++){
			effect();
			Sleep(200);
		}
	}

	for(i = 0; i < 6; i++){
		for(j = 0; j < 13; j++){
			if(mark[i][j] > 0){
				map[i][j] = 0;
				if(mark[i][j] == 1) count++;
			}
		}
	}
	dmapa();

	sscore(count);
	cdrop();
	return;
}

void playset::effect(){

	for(int i = 0; i < 6; i++){
		for(int j = 0; j < 13; j++){
			if(mark[i][j] > 0){
				gotoxy(35 + i * 2, 7 + j);
				setcolor(BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
				g_pattern(-map[i][j]);
			}
		}
	}

	Sleep(300);

	for(int i = 0; i < 6; i++){
		for(int j = 0; j < 13; j++){
			if(mark[i][j] > 0){
				gotoxy(35 + i * 2, 7 + j);
				setcolor(0);
				g_pattern(map[i][j]);
			}
		}
	}

	gotoxy(80, 25);
	return;
}

void playset::sscore(int count){

	int plus = 200 + (count + combo) * 100;
	score += plus;
	
	if(efct == 1){
		setcolor(FOREGROUND_INTENSITY | FOREGROUND_RED);
		for(int i = 0; i < 6; i++){
			gotoxy(17, 19 - i);
			cout << plus;
			Sleep(100);
			gotoxy(17, 19 - i);
			cout << "¡@¡@";
		}
	}

	gotoxy(16, 13);
	setcolor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
	if(score == 0) cout << "  0  ";
	else cout << (score < 10000 ? " " : "") << score << (score < 1000 ? " " : "");
	gotoxy(80, 25);

	if(score >= goal && level < 5){
		level++;
		slevel();
	}
	return;
}

void playset::cdrop(){
	int i, j, k;
	
	for(i = 0; i < 6; i++){
		for(j = 12; j > -1; j--){
			if(map[i][j] == 0){
				for(k = j - 1; k > -1; k--){
					if(map[i][k] != 0){
						map[i][j] = map[i][k];
						map[i][k] = 0;
						break;
					}
				}
			}
		}
	}
	dmapa();
	Sleep(100);
	if(dmask() > 0) remove();
	return;
}

void playset::gameover(){
	int i,j;

	end = time(NULL);
	second = (int)difftime(end, start);

	setcolor(FOREGROUND_INTENSITY);
	for(i = 0; i < 13; i++){
		for(j = 0; j < 6; j++){
			if(map[j][i] != 0){
				gotoxy(35 + j * 2, 7 + i);
				cout << "¡´";
			}
		}
		Sleep(200);
	}
	for(i = 0; i < 13; i++){
		gotoxy(35, 7 + i);
		cout << "¡@¡@¡@¡@¡@¡@";
		Sleep(100);
	}
	gotoxy(36, 13);
	setcolor(FOREGROUND_INTENSITY | FOREGROUND_RED);
	cout << "GAME  OVER";

	gotoxy(80, 25);
	return;
}

void playset::record(rank* rrank){
	
	if(rec == 1 && score > (*rrank).getlow()){
		g_record();
		sresult();
		char name[30];
		setcolor(BACKGROUND_INTENSITY);
		cin.getline(name, 30);
		(*rrank).add(score, level, maxcb, (int)second, (double)score / second, ctime(&end), name);
	}
	return;
}

void playset::sresult(){
	
	gotoxy(9, 9);
	setcolor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
	cout << (score < 10000 ? " " : "") << score;
	gotoxy(21, 9);
	cout << level << "           " << maxcb;
	gotoxy(45, 9);
	cout << (second < 600 ? "0" : "") << (int)second / 60 << ":" << (((int)second % 60) < 10 ? "0" : "") << (int)second % 60;
	gotoxy(62, 9);
	cout << fixed << setprecision(3) << (double)score / second;

	gotoxy(26, 15);

	return;
}

void playset::resume(){

	g_gamef();
	setcolor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
	gotoxy(18, 10);
	cout << level;
	gotoxy(16, 13);
	if(score == 0) cout << "  0  ";
	else cout << (score < 10000 ? " " : "") << score << (score < 1000 ? " " : "");
	if(cheat == 1) dcheat();
	dnext();
	dmapa();
	dmapp(0, 0);

	return;
}

void playset::restart(){

	g_gamef();
	initialize();
	x = 3, y = -1;
	random();
	now[0] = next[0];
	now[1] = next[1];
	now[2] = next[2];
	random();

	return;
}

void playset::help(){

	g_help();
	k_wait();
	resume();

	return;
}

int playset::set(){
	
	char key;
	int flash = 0;
	int row = 1;

	levels = 1;
	efct = 1;
	if(cheat == 1){
		rec = 0;
		ranbow = 1;
		crosss = 5;
		bombs = 5;
	}else{
		rec = 1;
		ranbow = 0;
		crosss = 0;
		bombs = 0;
	}

	while(1){
		switch (row){
			case 1:
				if(_kbhit()){
					key = _getch();
					if(key == Left && levels != 1){
						gotoxy(27 + (levels - 1) * 5, 10);
						setcolor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
						cout << levels;
						levels--;
					}else if(key == Right && levels != 5){
						gotoxy(27 + (levels - 1) * 5, 10);
						setcolor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
						cout << levels;
						levels++;
					}else if(key == Up){
						gotoxy(27 + (levels - 1) * 5, 10);
						setcolor(BACKGROUND_INTENSITY | FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
						cout << levels;
						row = (cheat == 1 ? 6 : 3);
						break;
					}else if(key == Down){
						gotoxy(27 + (levels - 1) * 5, 10);
						setcolor(BACKGROUND_INTENSITY | FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
						cout << levels;
						row = 2;
						break;
					}else if(key == '\r' || key == ' '){
						return 1;
					}else if(key == 27){
						return 0;
					}
				}
				if(flash == 19){
					gotoxy(27 + (levels - 1) * 5, 10);
					setcolor(BACKGROUND_INTENSITY | FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
					cout << levels;
				}else if(flash == 39){
					gotoxy(27 + (levels - 1) * 5, 10);
					setcolor(FOREGROUND_INTENSITY);
					cout << levels;
				}
				break;
			case 2:
				if(_kbhit()){
					key = _getch();
					if(key == Left && efct == 0){
						gotoxy(32, 12);
						setcolor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
						cout << "No";
						efct++;
					}else if(key == Right && efct == 1){
						gotoxy(27, 12);
						setcolor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
						cout << "Yes";
						efct--;
					}else if(key == Up){
						gotoxy(32 - efct * 5, 12);
						setcolor(BACKGROUND_INTENSITY | FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
						cout << (efct == 1 ? "Yes" : "No");
						row = 1;
						break;
					}else if(key == Down){
						gotoxy(32 - efct * 5, 12);
						setcolor(BACKGROUND_INTENSITY | FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
						cout << (efct == 1 ? "Yes" : "No");
						row = (cheat == 1 ? 4 : 3);
						break;
					}else if(key == '\r' || key == ' '){
						return 1;
					}else if(key == 27){
						return 0;
					}
				}
				if(flash == 19){
					gotoxy(32 - efct * 5, 12);
					setcolor(BACKGROUND_INTENSITY | FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
					cout << (efct == 1 ? "Yes" : "No");
				}else if(flash == 39){
					gotoxy(32 - efct * 5, 12);
					setcolor(FOREGROUND_INTENSITY);
					cout << (efct == 1 ? "Yes" : "No");
				}
				break;
			case 3:
				if(_kbhit()){
					key = _getch();
					if(key == Left && rec == 0){
						gotoxy(32, 14);
						setcolor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
						cout << "No";
						rec++;
					}else if(key == Right && rec == 1){
						gotoxy(27, 14);
						setcolor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
						cout << "Yes";
						rec--;
					}else if(key == Up){
						gotoxy(32 - rec * 5, 14);
						setcolor(BACKGROUND_INTENSITY | FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
						cout << (rec == 1 ? "Yes" : "No");
						row = 2;
						break;
					}else if(key == Down){
						gotoxy(32 - rec * 5, 14);
						setcolor(BACKGROUND_INTENSITY | FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
						cout << (rec == 1 ? "Yes" : "No");
						row = 1;
						break;
					}else if(key == '\r' || key == ' '){
						return 1;
					}else if(key == 27){
						return 0;
					}
				}
				if(flash == 19){
					gotoxy(32 - rec * 5, 14);
					setcolor(BACKGROUND_INTENSITY | FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
					cout << (rec == 1 ? "Yes" : "No");
				}else if(flash == 39){
					gotoxy(32 - rec * 5, 14);
					setcolor(FOREGROUND_INTENSITY);
					cout << (rec == 1 ? "Yes" : "No");
				}
				break;
			case 4:
				if(_kbhit()){
					key = _getch();
					if(key == Left && ranbow == 0){
						gotoxy(32, 16);
						setcolor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
						cout << "No";
						ranbow++;
					}else if(key == Right && ranbow == 1){
						gotoxy(27, 16);
						setcolor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
						cout << "Yes";
						ranbow--;
					}else if(key == Up){
						gotoxy(32 - ranbow * 5, 16);
						setcolor(BACKGROUND_INTENSITY | FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
						cout << (ranbow == 1 ? "Yes" : "No");
						row = 2;
						break;
					}else if(key == Down){
						gotoxy(32 - ranbow * 5, 16);
						setcolor(BACKGROUND_INTENSITY | FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
						cout << (ranbow == 1 ? "Yes" : "No");
						row = 5;
						break;
					}else if(key == '\r' || key == ' '){
						return 1;
					}else if(key == 27){
						return 0;
					}
				}
				if(flash == 19){
					gotoxy(32 - ranbow * 5, 16);
					setcolor(BACKGROUND_INTENSITY | FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
					cout << (ranbow == 1 ? "Yes" : "No");
				}else if(flash == 39){
					gotoxy(32 - ranbow * 5, 16);
					setcolor(FOREGROUND_INTENSITY);
					cout << (ranbow == 1 ? "Yes" : "No");
				}
				break;
			case 5:
				if(_kbhit()){
					key = _getch();
					if(key == Left && crosss != 0){
						gotoxy(27 + crosss * 5, 18);
						setcolor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
						cout << crosss;
						crosss--;
					}else if(key == Right && crosss != 9){
						gotoxy(27 + crosss * 5, 18);
						setcolor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
						cout << crosss;
						crosss++;
					}else if(key == Up){
						gotoxy(27 + crosss * 5, 18);
						setcolor(BACKGROUND_INTENSITY | FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
						cout << crosss;
						row = 4;
						break;
					}else if(key == Down){
						gotoxy(27 + crosss * 5, 18);
						setcolor(BACKGROUND_INTENSITY | FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
						cout << crosss;
						row = 6;
						break;
					}else if(key == '\r' || key == ' '){
						return 1;
					}else if(key == 27){
						return 0;
					}
				}
				if(flash == 19){
					gotoxy(27 + crosss * 5, 18);
					setcolor(BACKGROUND_INTENSITY | FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
					cout << crosss;
				}else if(flash == 39){
					gotoxy(27 + crosss * 5, 18);
					setcolor(FOREGROUND_INTENSITY);
					cout << crosss;
				}
				break;
			case 6:
				if(_kbhit()){
					key = _getch();
					if(key == Left && bombs != 0){
						gotoxy(27 + bombs * 5, 20);
						setcolor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
						cout << bombs;
						bombs--;
					}else if(key == Right && bombs != 9){
						gotoxy(27 + bombs * 5, 20);
						setcolor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
						cout << bombs;
						bombs++;
					}else if(key == Up){
						gotoxy(27 + bombs * 5, 20);
						setcolor(BACKGROUND_INTENSITY | FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
						cout << bombs;
						row = 5;
						break;
					}else if(key == Down){
						gotoxy(27 + bombs * 5, 20);
						setcolor(BACKGROUND_INTENSITY | FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
						cout << bombs;
						row = 1;
						break;
					}else if(key == '\r' || key == ' '){
						return 1;
					}else if(key == 27){
						return 0;
					}
				}
				if(flash == 19){
					gotoxy(27 + bombs * 5, 20);
					setcolor(BACKGROUND_INTENSITY | FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
					cout << bombs;
				}else if(flash == 39){
					gotoxy(27 + bombs * 5, 20);
					setcolor(FOREGROUND_INTENSITY);
					cout << bombs;
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