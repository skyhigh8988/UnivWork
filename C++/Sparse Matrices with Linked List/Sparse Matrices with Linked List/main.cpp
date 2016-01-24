#include <iostream>
#include <fstream>
#include <conio.h>
#include <math.h>
using namespace std;

#define MAX_SIZE 50

typedef struct entryNode{
	int row;
	int col;
	int value;
} NNODE;

typedef struct matrixNode{
	struct matrixNode *down;
	struct matrixNode *right;
	int tag;
	union{
		struct matrixNode *next;
		NNODE entry;
	} u;
} MNODE;

MNODE *head[MAX_SIZE];

//讀取矩陣
MNODE* mread(char *fileName){

	int numTerms = 0, numHeads = 0;
	int row, col, value;
	int i, m, tmp;
	MNODE *temp, *last, *node;

	//開啟檔案
	fstream fileInput;
	fileInput.open(fileName, ios::in|ios::binary);

	//檔案錯誤對策
	if(!fileInput || fileInput.eof()) return NULL;
	else{
		//分配起始點空間
		node = new MNODE;
		node -> tag = 1;

		//讀取檔案至檔案結束
		for(row = col = 0; !fileInput.eof(); col++){

			//沒有該行的Head則初始化之
			if(!head[col]){
				numHeads++;
				temp = new MNODE;
				head[col] = temp;
				head[col] -> tag = 0;
				head[col] -> right = temp;
				head[col] -> u.next = temp;
			}

			//初始化last
			if(col == 0 && row == 0) last = head[0];

			//每次從檔案讀取1字元直到/t,/n,EOF
			for(tmp = fileInput.get(), i = value = 0, m = 1; tmp != 9 && tmp != 13 && tmp != -1; tmp = fileInput.get(), i++){
				
				//讀到/r時表即將換行
				if(tmp == 10){

					//再多讀取1/t,/r,/n以外的字元
					for(tmp = fileInput.get(); tmp == 9 || tmp == 10 || tmp == 13; tmp = fileInput.get());

					//若為EOF表下行為空行 離開迴圈
					if(tmp == -1){
						col--;
						break;
					}else{

						//換列處理
						last -> right = head[row];
						last = head[++row];
						col = 0;

						//沒有該列的Head則初始化之
						if(!head[row]){
							numHeads++;
							temp = new MNODE;
							head[row] = temp;
							head[row] -> tag = 0;
							head[row] -> right = temp;
							head[row] -> u.next = temp;
						}
					}
				}

				//讀到負號之處理
				if(tmp == 45) i = m = -1;

				//讀到數字則計算出值
				else value = tmp - 48 + value * (int)pow(10.0, i);
			}

			//如果值非零則新增節點
			if(value){
				numTerms++;
				temp = new MNODE;
				temp -> tag = 1;
				temp -> u.entry.col = col;
				temp -> u.entry.row = row;
				temp -> u.entry.value = value * m;
				last -> right = temp;
				last = temp;
				head[col] -> u.next -> down = temp;
				head[col] -> u.next = temp;
			}
		}

		//完成最後一列之連接
		last -> right = head[row];

		//存入陣列的長寬及非零值數量
		node -> u.entry.row = row + 1;
		node -> u.entry.col = col;
		node -> u.entry.value = numTerms;

		//連接Head
		for(i = 0; i < col; i++) head[i] -> u.next -> down = head[i];
		for(i = 0; i < numHeads - 1; i++) head[i] -> u.next = head[i + 1];
		head[numHeads - 1] -> u.next = node;
		node -> right = head[0];

		//重置Head
		for(i = 0; i < numHeads; i++) head[i] = NULL;
	}

	//關閉檔案
	fileInput.close();

	return node;
}

//印出矩陣
void mwrite(MNODE *node){

	MNODE *temp, *head;
	int i;

	//輸出陣列長寬及非零值個數
	cout << '(' << node -> u.entry.row << ", " << node -> u.entry.col << ", " << node -> u.entry.value << ")\n";

	//依序輸出節點
	for(head = node -> right, i = 0; i < node -> u.entry.row; i++, head = head -> u.next)
		for(temp = head -> right; temp != head; temp = temp -> right) cout << '(' << temp -> u.entry.row << ", " << temp -> u.entry.col << ", " << temp -> u.entry.value << ")\n";

	return;
}

//輸出矩陣
void moutput(MNODE *node, char *fileName){

	MNODE *temp, *head;
	int i, j, col = 0;
	fstream fileOutput;

	fileOutput.open(fileName, ios::out|ios::binary);
	head = node -> right;

	for(i = 0; i < node -> u.entry.row; i++, head = head -> u.next, col = 0){
		if(i != 0) fileOutput << "\r\n";
		for(temp = head -> right; temp != head; temp = temp -> right){
			for(j = col; j < temp -> u.entry.col; j++) fileOutput << (j > 0 ? "\t" : "") << '0';
			fileOutput << (temp -> u.entry.col > 0 ? "\t" : "") << temp -> u.entry.value;
			col = temp -> u.entry.col + 1;
		}
		for(j = col; j < node -> u.entry.col; j++) fileOutput << (col > 0 ? "\t" : "") << '0';
	}

	fileOutput.close();
	return;
}

//轉置矩陣
MNODE* mtrans(MNODE *nodei){

	MNODE *node, *temp, *last, *tempi, *headi;
	int i, numHeads;

	//矩陣不存在對策
	if(!nodei) return NULL;
	else{

		//計算Head數量
		numHeads = (nodei -> u.entry.row > nodei -> u.entry.col) ? nodei -> u.entry.row : nodei -> u.entry.col;

		//初始化Node
		node = new MNODE;
		node -> tag = 1;
		node -> u.entry.row = nodei -> u.entry.col;
		node -> u.entry.col = nodei -> u.entry.row;
		node -> u.entry.value = nodei -> u.entry.value;

		//初始化Head
		for(i = 0; i < numHeads; i++){
			temp = new MNODE;
			head[i] = temp;
			head[i] -> tag = 0;
			head[i] -> right = temp;
			head[i] -> u.next = temp;
		}

		//依序處理每列
		for(i = 0, headi = nodei -> right; i < node -> u.entry.row; i++){
			last = head[i];

			//依序讀取來源第i行之值放入第i列中
			for(tempi = headi -> down; tempi != headi; tempi = tempi -> down){
				temp = new MNODE;
				temp -> tag = 1;
				temp -> u.entry.col = tempi -> u.entry.row;
				temp -> u.entry.row = tempi -> u.entry.col;
				temp -> u.entry.value = tempi -> u.entry.value;
				head[tempi -> u.entry.row] -> u.next -> down = temp;
				head[tempi -> u.entry.row] -> u.next = temp;
				last -> right = temp;
				last = temp;
			}
			headi = headi -> u.next;
			last -> right = head[i];
		}

		//連接Head
		for(i = 0; i < nodei -> u.entry.row; i++) head[i] -> u.next -> down = head[i];
		for(i = 0; i < numHeads -1; i++) head[i] -> u.next = head[i + 1];
		head[numHeads - 1] -> u.next = node;
		node -> right = head[0];
		for(i = 0; i < numHeads; i++) head[i] = NULL;
	}

	return node;
}

//矩陣相加
MNODE* madd(MNODE *nodea, MNODE *nodeb){

	MNODE *nodec, *heada, *headb, *tempa, *tempb, *temp, *last;
	int i, numTerms = 0, numHeads;

	//矩陣不存在或大小不相等對策
	if(nodea -> u.entry.row != nodeb -> u.entry.row || nodea -> u.entry.col != nodeb -> u.entry.col || !nodea) return NULL;
	else{
		numHeads = (nodea -> u.entry.row > nodea -> u.entry.col) ? nodea -> u.entry.row : nodea -> u.entry.col;
		nodec = new MNODE;
		nodec -> tag = 1;
		nodec -> u.entry.row = nodea -> u.entry.row;
		nodec -> u.entry.col = nodea -> u.entry.col;

		for(i = 0; i < numHeads; i++){
			temp = new MNODE;
			head[i] = temp;
			head[i] -> tag = 0;
			head[i] -> right = temp;
			head[i] -> u.next = temp;
		}

		heada = nodea -> right;
		headb = nodeb -> right;

		//依序處理每列
		for(i = 0; i < nodea -> u.entry.row; i++){
			last = head[i];

			//分別讀取該列值
			for(tempa = heada -> right, tempb = headb -> right; tempa != heada || tempb != headb; numTerms++){

				//兩矩陣行列相等則相加後存入
				if(tempa -> u.entry.col == tempb -> u.entry.col){
					if(tempa -> u.entry.value + tempb -> u.entry.value){
						temp = new MNODE;
						temp -> tag = 1;
						temp -> u.entry.col = tempa -> u.entry.col;
						temp -> u.entry.row = tempa -> u.entry.row;
						temp -> u.entry.value = tempa -> u.entry.value + tempb -> u.entry.value;
						head[tempa -> u.entry.col] -> u.next -> down = temp;
						head[tempa -> u.entry.col] -> u.next = temp;
						last -> right = temp;
						last = temp;
					}
					tempa = tempa -> right;
					tempb = tempb -> right;

				//不相等則單獨存入行較小者
				}else if(tempb == headb || (tempa -> u.entry.col < tempb -> u.entry.col && tempa != heada)){
					temp = new MNODE;
					temp -> tag = 1;
					temp -> u.entry.col = tempa -> u.entry.col;
					temp -> u.entry.row = tempa -> u.entry.row;
					temp -> u.entry.value = tempa -> u.entry.value;
					head[tempa -> u.entry.col] -> u.next -> down = temp;
					head[tempa -> u.entry.col] -> u.next = temp;
					tempa = tempa -> right;
					last -> right = temp;
					last = temp;
				}else{
					temp = new MNODE;
					temp -> tag = 1;
					temp -> u.entry.col = tempb -> u.entry.col;
					temp -> u.entry.row = tempb -> u.entry.row;
					temp -> u.entry.value = tempb -> u.entry.value;
					head[tempb -> u.entry.col] -> u.next -> down = temp;
					head[tempb -> u.entry.col] -> u.next = temp;
					tempb = tempb -> right;
					last -> right = temp;
					last = temp;
				}
			}
			heada = heada -> u.next;
			headb = headb -> u.next;
			last -> right = head[i];
		}
		for(i = 0; i < nodea -> u.entry.col; i++) head[i] -> u.next -> down = head[i];
		for(i = 0; i < numHeads -1; i++) head[i] -> u.next = head[i + 1];
		head[numHeads - 1] -> u.next = nodec;
		nodec -> right = head[0];
		nodec -> u.entry.value = numTerms;
		for(i = 0; i < numHeads; i++) head[i] = NULL;
	}

	return nodec;
}

//相乘
MNODE* mmult(MNODE *nodea, MNODE *nodeb){

	MNODE *nodec, *heada, *headb, *tempa, *tempb, *temp, *last;
	int i, j, numTerms = 0, numHeads, value = 0;

	//無法相乘對策
	if(nodea -> u.entry.col != nodeb -> u.entry.row || !nodea || !nodeb) return NULL;
	else{
		numHeads = (nodea -> u.entry.row > nodeb -> u.entry.col) ? nodea -> u.entry.row : nodeb -> u.entry.col;
		nodec = new MNODE;
		nodec -> tag = 1;
		nodec -> u.entry.row = nodea -> u.entry.row;
		nodec -> u.entry.col = nodeb -> u.entry.col;

		for(i = 0; i < numHeads; i++){
			temp = new MNODE;
			head[i] = temp;
			head[i] -> tag = 0;
			head[i] -> right = temp;
			head[i] -> u.next = temp;
		}

		heada = nodea -> right;
		headb = nodeb -> right;

		//依序處理每列
		for(i = 0; i < nodea -> u.entry.row; i++){
			last = head[i];

			//依序處理每行
			for(j = 0; j < nodeb -> u.entry.col; j++){

				//分別讀取對應行及列的值
				for(tempa = heada -> right, tempb = headb -> down; tempa != heada && tempb != headb; ){

					//行列不相等
					if(tempa -> u.entry.col < tempb -> u.entry.row) tempa = tempa -> right;
					else if(tempa -> u.entry.col > tempb -> u.entry.row) tempb = tempb -> down;

					//行列相等則相乘加入暫存
					else{
						value += tempa -> u.entry.value * tempb -> u.entry.value;
						tempa = tempa -> right;
						tempb = tempb -> down;
					}
				}

				//若該位置有存入值
				if(value){
					numTerms++;
					temp = new MNODE;
					temp -> tag = 1;
					temp -> u.entry.col = j;
					temp -> u.entry.row = i;
					temp -> u.entry.value = value;
					head[j] -> u.next -> down = temp;
					head[j] -> u.next = temp;
					last -> right = temp;
					last = temp;
					value = 0;
				}
				headb = headb -> u.next;
			}
			headb = nodeb -> right;
			heada = heada -> u.next;
			last -> right = head[i];
		}
		for(i = 0; i < nodeb -> u.entry.col; i++) head[i] -> u.next -> down = head[i];
		for(i = 0; i < numHeads -1; i++) head[i] -> u.next = head[i + 1];
		head[numHeads - 1] -> u.next = nodec;
		nodec -> right = head[0];
		nodec -> u.entry.value = numTerms;
		for(i = 0; i < numHeads; i++) head[i] = NULL;
	}

	return nodec;
}

//清除矩陣
void merase(MNODE **node){

	MNODE *x, *y, *head;
	int i;

	head = (*node) -> right;

	//依序處理每列
	for(i = 0; i < (*node) -> u.entry.row; i++){
		y = head -> right;

		//依序刪除節點
		while(y != head){
			x = y;
			y = y -> right;
			delete x;
		}
		x = head;
		head = head -> u.next;
		delete x;
	}
	y = head;

	//依序刪除Head
	while(y != (*node)){
		x = y;
		y = y -> u.next;
		delete x;
	}

	//刪除起點
	delete (*node);
	*node = NULL;

	return;
}



int main(void){

	MNODE *m[3];
	int i;
	char flag, v1, v2, v3, str[MAX_SIZE];

	for(i = 0; i < 3; i++) m[i] = NULL;

	while(1){

		//印出變數狀況
		system("cls");
		if(m[0]) cout << "x:" << m[0] -> u.entry.row << "x" << m[0] -> u.entry.col << "(" << m[0] -> u.entry.value << ")\t";
		else cout << "x: empty\t";
		if(m[1]) cout << "y:" << m[1] -> u.entry.row << "x" << m[1] -> u.entry.col << "(" << m[1] -> u.entry.value << ")\t";
		else cout << "y: empty\t";
		if(m[2]) cout << "z:" << m[2] -> u.entry.row << "x" << m[2] -> u.entry.col << "(" << m[2] -> u.entry.value << ")\n\n";
		else cout << "z: empty\n\n";

		//印出選單
		cout << "(a) Read      (b) Print     (c) Erase     (d) Add\n(e) Multiple  (f) Transpose (g) Output    (h) Exit\n";
		cout << "Please select a program to execute: ";
		flag = _getch();
		
		switch(flag){
			case 65:
			case 97:

				//讀取
				cout << "(a) Read a matrix from a file\nPlease enter the name of the file you want to read: ";
				cin >> str;
				cout << "Please chose a variable to store the matrix: ";
				v1 = _getch();
				if(v1 < 120 || v1 > 122) break;
				m[v1 - 120] = mread(str);
				break;
			case 66:
			case 98:

				//印出
				cout << "(b) Print a matrix on screen\nPlease chose a matrix to print: ";
				v1 = _getch();
				if(v1 < 120 || v1 > 122) break;
				cout << '(' << v1 << ") Print " << v1 << "\n\n";
				if(!m[v1 - 120]) break;
				mwrite(m[v1 - 120]);
				cout << "\nPress any key to continue...";
				_getch();
				break;
			case 67:
			case 99:

				//清除
				cout << "(c) Erase a matrix\nPlease chose a matrix you want to erase: ";
				v1 = _getch();
				if(v1 < 120 || v1 > 122) break;
				if(!m[v1 - 120]) break;
				merase(&m[v1 - 120]);
				break;
			case 68:
			case 100:

				//加法
				cout << "(d) Calculate the summation of A and B\nPlease chose the matrix A: ";
				v1 = _getch();
				if(v1 < 120 || v1 > 122) break;
				cout << '(' << v1 << ") Augend:" << v1 << "\nPlease chose the matrix B: ";
				v2 = _getch();
				if(v2 < 120 || v2 > 122) break;
				cout << '(' << v2 << ") Addend:" << v2 << "\nPlease chose a variable to store the summation: ";
				v3 = _getch();
				if(v3 < 120 || v3 > 122) break;
				if(!m[v1 - 120] || !m[v2 - 120]) break;
				m[v3 - 120] = madd(m[v1 - 120], m[v2 - 120]);
				break;
			case 69:
			case 101:

				//乘法
				cout << "(e) Calculate the product of A and B\nPlease chose the matrix A: ";
				v1 = _getch();
				if(v1 < 120 || v1 > 122) break;
				cout << '(' << v1 << ") Multiplicand:" << v1 << "\nPlease chose the matrix B: ";
				v2 = _getch();
				if(v2 < 120 || v2 > 122) break;
				cout << '(' << v2 << ") Multiplicator:" << v2 << "\nPlease chose a variable to store the product: ";
				v3 = _getch();
				if(v3 < 120 || v3 > 122) break;
				if(!m[v1 - 120] || !m[v2 - 120]) break;
				m[v3 - 120] = mmult(m[v1 - 120], m[v2 - 120]);
				break;
			case 70:
			case 102:

				//轉置
				cout << "(f) Calculate the transpose of a matrix\nPlease chose a matrix you want to transpose: ";
				v1 = _getch();
				if(v1 < 120 || v1 > 122) break;
				cout << '(' << v1 << ") Transpose of " << v1 << "\nPlease chose a variable to store the transpose: ";
				v2 = _getch();
				if(v2 < 120 || v2 > 122) break;
				if(!m[v1 - 120]) break;
				m[v2 - 120] = mtrans(m[v1 - 120]);
				break;
			case 71:
			case 103:

				//輸出
				cout << "(g) Output a matrix to a file\nPlease chose a matrix to output: ";
				v1 = _getch();
				if(v1 < 120 || v1 > 122) break;
				cout << '(' << v1 << ") Output " << v1 << "\nPlease enter the name of the output file: ";
				if(!m[v1 - 120]) break;
				cin >> str;
				moutput(m[v1 - 120], str);
				break;
			case 72:
			case 104:

				//離開
				exit(0);
				break;
			default:
				;
		}
	}

	return 0;
}