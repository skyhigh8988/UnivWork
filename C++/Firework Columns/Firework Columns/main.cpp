#include "playset.h"

int main(){

	int opt, flag = -1;
	SetConsoleTitle("Firework Columns");
	rank rrank;
	rrank.read();

	while(1){
		opt = 1;
		g_title();
		_getch();
		g_menu();
		while(k_menu(&opt) == 1){
			flag *= -1;
			g_cheat(flag);
		}

		switch(opt){
			case 1:
				playset game;
				game.cheat = flag;
				g_setf(flag);
				if(game.set() == 0) break;
				g_gamef();
				game.initialize();
				game.random();
				game.drop();
				if(game.opt == 4) break;
				if(k_wait() == 0) break;
				game.record(&rrank);
				g_rank();
				rrank.srank();
				if(k_wait() == 0) break;
				break;
			case 2:
				g_help();
				k_wait();
				break;
			case 3:
				g_rank();
				rrank.srank();
				k_wait();
				break;
			case 4:
				exit(0);
				break;
		}

	}
	return 0;
}