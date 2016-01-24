#include <fstream>
#include <iomanip>
#include "conshift.h"
using namespace std;

class rank{
	private:
		typedef struct node{
			int score;
			int level;
			int chain;
			int second;
			double sps;
			char date[31];
			char name[31];
			struct node *next;
		}NODE;
		NODE *head;
		int line;
	public:
		void read();
		int getlow();
		void add(int, int, int, int, double, char*, char*);
		void srank();
		void save();

};