#include <iostream>
#include <conio.h>

using namespace std;

#define MAX_SIZE 100

typedef enum {lp, rp, pl, mi, ti, di, mo, eo, op} precedence;

char expr[MAX_SIZE];
int est[MAX_SIZE];
precedence pst[MAX_SIZE];
int etop, ptop;

void epush(int x){

	//存入推疊
	if(etop < MAX_SIZE - 1) est[++etop] = x;
	else{
		cout << "Stack is full";
		exit(1);
	}
	return;
}

int epop(){

	//取出
	return est[etop--];
}

void ppush(precedence x){

	//存入
	if(etop < MAX_SIZE - 1) pst[++ptop] = x;
	else{
		cout << "Stack is full";
		exit(1);
	}
	return;
}

precedence ppop(){

	//取出
	return pst[ptop--];
}

precedence getToken(char *sb, int *n){

	//轉換
	*sb = expr[(*n)--];
	switch(*sb){
		case '(':return lp;
		case ')':return rp;
		case '+':return pl;
		case '-':return mi;
		case '/':return di;
		case '*':return ti;
		case '%':return mo;
		case '\0':return eo;
		default:return op;
	}
}

char transToken(precedence tk){

	//還原
	switch(tk){
		case lp:return '(';
		case rp:return ')';
		case pl:return '+';
		case mi:return '-';
		case di:return '/';
		case ti:return '*';
		case mo:return '%';
	}
	return '\0';
}

int eval(void){

	precedence tk;
	char sb;
	int op1, op2, n = strlen(expr) - 1;
	etop = -1;

	//依序讀取字元並處理
	for(tk = getToken(&sb, &n);tk != eo;tk = getToken(&sb, &n)){
		if(tk == op) epush(sb - 48);
		else{
			op1 = epop();
			op2 = epop();
			switch(tk){
				case pl:
					epush(op1+op2);
					break;
				case mi:
					epush(op1-op2);
					break;
				case ti:
					epush(op1*op2);
					break;
				case di:
					epush(op1/op2);
					break;
				case mo:
					epush(op1%op2);
			}
		}
	}

	return epop();
}

void prefix(void){

	//優先權
	int isp[] = {19, 0, 12, 12, 13, 13, 13, 0};
	int icp[] = {19, 20, 12, 12, 13, 13, 13, 0};

	char sb, fix[MAX_SIZE];
	precedence tk;
	int n = strlen(expr) - 1, c = 0;
	ptop = 0;
	pst[0] = eo;

	//依序讀取字元並處理
	for(tk = getToken(&sb, &n);tk != eo;tk = getToken(&sb, &n)){
		if(tk == op) fix[c++] = sb;
		else if(tk == lp){
			while(pst[ptop] != rp) fix[c++] = transToken(ppop());
			ppop();
		}else{
			while(isp[pst[ptop]] > icp[tk]) fix[c++] = transToken(ppop());
			ppush(tk);
		}
	}

	//取出剩餘
	while((tk = ppop()) != eo) fix[c++] = transToken(tk);
	fix[c] = '\0';

	//反向輸出
	for(int i = strlen(fix) - 1; i >= 0; i--) cout << fix[i];
	return;
}

int main(void){

	cout << "Please select program b or c to execute: ";
	char m = _getch();

	cout << m << "\nPlease enter the expression: ";
	cin >> expr;

	if(m == 'b') cout << eval();
	else if(m == 'c') prefix();
	else cout << "Enter argument error";

	_getch();
	return 0;
}