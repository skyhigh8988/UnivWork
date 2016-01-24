#include <iostream>
#include <fstream>
#include <conio.h>

using namespace std;

#define MAX 100

typedef struct graphNode{
	struct graphNode *link;
	int vertex;
	int edge;
} NODE;

NODE *list[MAX];
short int visited[MAX];
short int flag;

void readFile(char *fileName){

	//變數宣告
	NODE *node, *temp, *last;
	short int i, tempChar;
	int v = 0, e = 0;
	int edgeTemp[MAX];

	//初始化
	flag = 1;
	for(i = 0; i < MAX; i++){
		edgeTemp[i] = -1;
		list[i] = NULL;
		visited[i] = 0;
	}

	//開啟檔案
	fstream fileInput;
	fileInput.open(fileName, ios::in|ios::binary);

	//Not Found
	if(!fileInput){
		cout << fileName << " not found.";
		return;
	}

	while(!fileInput.eof()){

		tempChar = fileInput.get();
		//1或0
		if(tempChar - 48){

			if(edgeTemp[e] == -1) edgeTemp[e] = v;
			else{

				//虛設節點
				if(!list[v]){
					node = new NODE;
					list[v] = node;
					node -> vertex = -1;
					node -> link = NULL;
				}

				//插入節點
				node = new NODE;
				node -> vertex = edgeTemp[e];
				node -> edge = e;
				for(temp = list[v]; 1; last = temp, temp = temp -> link){
					if(temp -> vertex > edgeTemp[e]){
						node -> link = last -> link;
						last -> link = node;
						break;
					}else if(!(temp -> link)){
						temp -> link = node;
						node -> link = NULL;
						break;
					}
				}

				//虛設節點
				if(!list[edgeTemp[e]]){
					node = new NODE;
					list[edgeTemp[e]] = node;
					node -> vertex = -1;
					node -> link = NULL;
				}

				//插入節點
				node = new NODE;
				node -> vertex = v;
				node -> edge = e;
				for(temp = list[edgeTemp[e]]; 1; last = temp, temp = temp -> link){
					if(temp -> vertex > v){
						node -> link = last -> link;
						last -> link = node;
						break;
					}else if(!(temp -> link)){
						temp -> link = node;
						node -> link = NULL;
						break;
					}
				}
			}
		}

		tempChar = fileInput.get();
		//結束
		if(tempChar == -1){
			break;
		//換行
		}else if(tempChar == 13){
			fileInput.get();
			e = 0;
			v++;
		//TAB
		}else if(tempChar == 9){
			e++;
		//Error
		}else{
			cout << "File fomat error";
			list[0] = NULL;
			return;
		}
	}

	return;
}

void depthFirstSearch(int v){

	NODE *node;
	visited[v] = 1;
	//cout << v;
	for(node = list[v] -> link; node; node = node -> link)
		if(!visited[node -> vertex]){
			if(flag) flag = 0;
			else cout << " -> ";
			//cout << "--(e" << node -> edge << ")->";
			cout << "e" << node -> edge;
			depthFirstSearch(node -> vertex);
		}

	return;
}

int main(void){

	cout << "**  F74976120  李睿哲  **";
	cout << "\nM1:\n";
	readFile("m1.txt");
	if(list[0]) depthFirstSearch(0);
	cout << "\nM2:\n";
	readFile("m2.txt");
	if(list[0]) depthFirstSearch(0);
	cout << "\nM3:\n";
	readFile("m3.txt");
	if(list[0]) depthFirstSearch(0);

	_getch();
	return 0;
}