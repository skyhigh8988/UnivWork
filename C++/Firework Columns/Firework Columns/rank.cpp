#include "rank.h"

void rank::read(){

	fstream file;
	file.open("rank", ios::in|ios::binary);

	if(!file){
		NODE *newnode = new NODE;
		head = newnode;
		newnode -> score = 0;
		newnode -> level = 0;
		newnode -> chain = 0;
		newnode -> second = 0;
		newnode -> sps = 0.0;
		strcpy_s(newnode -> date, "Xxx Xxx 00 00:00:00 0000");
		strcpy_s(newnode -> name, "system");
		newnode -> next = NULL;
		line = 1;
	}else{

		NODE *previous = NULL;
		head = NULL;
		file >> line;

		while(!file.eof()){
	
			NODE *newnode = new NODE;

			if(head == NULL) head = newnode;
			else previous -> next = newnode;
			file >> newnode -> score;
			file >> newnode -> level;
			file >> newnode -> chain;
			file >> newnode -> second;
			file >> newnode -> sps;
			file.seekg(1, ios_base::cur);
			file.getline(newnode -> date, 31, ';');
			file.getline(newnode -> name, 31);
			newnode -> next = NULL;
			previous = newnode;

		}
		file.close();
	}
	save();
	return;
}

int rank::getlow(){
	return head -> score;
}

void rank::srank(){

	NODE *current;
	current = head;

	for(int i = line; i > 0; i--){
		if(current -> score > 0){
			setcolor((i % 2 == 1) ? FOREGROUND_INTENSITY | FOREGROUND_GREEN : FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
			gotoxy(5, 10 + i);
			cout << i;
			gotoxy(8, 10 + i);
			cout << current -> name;
			gotoxy(23, 10 + i);
			cout << "  " << current -> score << "     ";
			gotoxy(32, 10 + i);
			cout << current -> level << "  " << current -> chain << "     ";
			gotoxy(38, 10 + i);
			cout << (current -> second < 600 ? "0" : "") << current -> second / 60 << ":" << ((current -> second % 60) < 10 ? "0" : "") << current -> second % 60;
			gotoxy(45, 10 + i);
			cout << fixed << setprecision(3) << current -> sps;
			gotoxy(53, 10 + i);
			cout << current -> date;
		}
		current = current -> next;
	}

	gotoxy(80, 25);
	return;
}

void rank::save(){
	fstream file;
	file.open("rank", ios::out|ios::binary);

	file << line;

	NODE *current;
	current = head;

	while(1){
		file << "\r\n" << current -> score << ' ' << current -> level << ' ' << current -> chain << ' ' << current -> second << ' ' << current -> sps << ' ';
		file << current -> date << ';' << current -> name;
		if(current -> next == NULL) break;
		current = current -> next;
	}
	file.close();
	return;
}

void rank::add(int sc, int lv, int cb, int sec, double ss, char *d, char *n){

	NODE *newnode = new NODE;
	NODE *current, *previous;
	current = head;

	while(current -> score < sc){
		previous = current;
		current = current -> next;
		if(current == NULL) break;
	}

	previous -> next = newnode;
	newnode -> score = sc;
	newnode -> level = lv;
	newnode -> chain = cb;
	newnode -> second = sec;
	newnode -> sps = ss;
	strcpy_s(newnode -> date, d);
	strcpy_s(newnode -> name, n);
	newnode -> next = current;
	if(++line > 10){
		head = head -> next;
		line--;
	}

	save();
	return;
}