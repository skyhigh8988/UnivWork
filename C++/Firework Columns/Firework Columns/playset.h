#include <time.h>
#include "rank.h"
#include "keyctrl.h"
using namespace std;

class playset{
	private:
		int level;
		int levels;
		int delay;
		int pattern;
		int x, y;
		int map[6][14];
		int mark[6][13];
		int now[3];
		int next[3];
		int combo;
		int maxcb;
		int score;
		int goal;
		int cross;
		int crosss;
		int bomb;
		int bombs;
		int efct;
		int rec;
		int ranbow;
		time_t start;
		time_t end;
		double second;
		void slevel();
		void move(char);
		void dmapp(int, int);
		void dmapa();
		void trans();
		int dmask();
		void remove();
		void effect();
		void sscore(int);
		void cdrop();
		void gameover();
		void sresult();
		void resume();
		void restart();
		void help();
		void dnext();
		void dcheat();
	public:
		int opt;
		int cheat;
		int set();
		void initialize();
		void random();
		void drop();
		void record(rank*);
};

int equal(int, int, int);