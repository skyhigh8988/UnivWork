#include <iostream>
#include <cmath>

using namespace std;

int main(void){

	char i[12];
	int d, b, n, c;
	int *t, *p;

	do{
		system("cls");

		//取得樹之深度及防呆
		cout << "Enter the depth of the tree: ";
		cin >> i;
		d = atoi(i);
		while(d < 1 || d > 30){
			cout << "Error! The depth shoud be a integer bigger than '0' and smaller then '30'\nEnter the depth of the tree: ";
			cin >> i;
			d = atoi(i);
		}

		n = (int) pow(2.0, d - 1);

		//取得球的編號及防呆
		cout << "Enter the number of the ball: ";
		cin >> i;
		b = atoi(i);
		while(b < 1){
			cout << "Error! The number shoud be a integer bigger than '0'!\nEnter the number of the ball: ";
			cin >> i;
			b = atoi(i);
		}
		if(b > n) b %= n;

		//分配陣列空間
		p = new int[d - 1];
		t = new int[n];
		for(d = 1; d < n; d++) t[d] = 0;

		//計算球的落點和路徑
		for(; b > 0; b--) for(c = 1, d = 0; c < n; p[d++] = c, t[c] = !t[c], c = c * 2 + !t[c]);

		//印出結果
		cout << "\nThe ball finally fell in node(" << c << ")\nThe path of the ball: ";
		for(n = 0; n < d; n++) cout << p[n] << " -> ";
		cout << c << "\n\n";

		//釋放空間
		delete t;
		delete p;

		//判斷是否繼續
		cout << "Enter '1' if you want to run the program again: ";
		cin >> i;
		c = atoi(i);

	}while(c == 1);

	return 0;
}