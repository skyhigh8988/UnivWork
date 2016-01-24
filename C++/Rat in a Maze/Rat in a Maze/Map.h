#include <iostream>
#include <conio.h>
#include <time.h>
#include "conshift.h"

using namespace std;

class map{
private:
	int top;
	int road;
public:
	int maze[75][25];
	int stack[1024];
	map();
	void print_map();
	void creat_path();
	void creat_branch();

};

class map2{
private:
	int sn;
	int top;
	int density;
	int road;
	int complex;
	int wallc;
	int roadc;
public:
	int maze[40][23];
	int stack[1024];
	map2(int, int, int, int, int*);
	void print_map();
	void creat_path();
	void creat_branch();
	void result();
};