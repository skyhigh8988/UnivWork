#include "main.h"

int main(void){

	int opt = 1, flag = -1, sn = 1, ropt;
	int density = 5, complex = 3, roadc = 7, wallc = 3, ratai = 4, delay = 3, ratc = 1, pathc = 6; 
	SetConsoleTitle("Rat in a Maze");

	while(1){

		if(flag == 1) G_Pika();
		else G_Rat();
		G_Logo();
		G_Menu(opt);
		while(K_Menu(&opt) == 1){
			flag *= -1;
			if(flag == 1) G_Pika();
			else G_Rat();
			G_Logo();
			G_Menu(opt);
		}

		switch(opt){
			case 1:
				{
					map MAP;
					MAP.creat_path();
					MAP.creat_branch();
					MAP.print_map();

					rat RAT(MAP);
					RAT.run();
				}
				break;
			case 2:
				{
					G_MOption(density, complex, roadc, wallc);
					if(K_MOption(&density, &complex, &roadc, &wallc) == 0) break;
					G_ROption(ratai, delay, ratc, pathc, flag);
					if(K_ROption(&ratai, &delay, &ratc, &pathc, flag) == 0) break;

					while(1){
					map2 MAP2(density, complex, roadc, wallc, &sn);
					MAP2.creat_path();
					MAP2.creat_branch();

						while(1){
							MAP2.print_map();

							rat2 RAT2(MAP2, ratai, delay, ratc, pathc);
							RAT2.run();
							_getch();

							while(1){
								G_Result();
								MAP2.result();
								RAT2.result();
								ropt = K_Result();
								if(ropt == 3){
									G_MOption(density, complex, roadc, wallc);
									K_MOption(&density, &complex, &roadc, &wallc);
								}else if(ropt == 4){
									G_ROption(ratai, delay, ratc, pathc, flag);
									K_ROption(&ratai, &delay, &ratc, &pathc, flag);
								}else if(ropt == 6){
									exit(0);
								}else{
									break;
								}
							}
							if(ropt > 1) break;
						}
						if(ropt == 5) break;
					}
				}
				break;
			case 3:
				exit(0);
				break;
		}

	}

	return 0;
}