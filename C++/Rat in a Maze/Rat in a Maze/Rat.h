#include <iomanip>
#include "Map.h"

using namespace std;

class rat{
private:
	int maze[75][25];
	int stack[1024];
	int top;
	int delay;
	int x;
	int y;
public:
	rat(map);
	void print_rat();
	void run();
};

class rat2{
private:
	int maze[75][25];
	int stack[1024];
	int top;
	int delay;
	int ratai;
	int ratc;
	int pathc;
	int x;
	int y;
	int step;
	int fail;
	double ttime;
	void run1();
	void run2();
	void run3();
	void run4();
	void run5();
public:
	rat2(map2, int, int, int, int);
	void print_rat();
	void run();
	void result();
};