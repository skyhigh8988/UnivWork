#include <iostream> 
#include <fstream>
using namespace std; 

int main() { 

	fstream Input, Output;
	char array[64], array2[64];
	int i, n = -1;

	Input.open("input.txt", ios::in|ios::binary);
	Output.open("output.txt", ios::out|ios::binary);

	while(!Input.eof()){

		Output << (n == -1 ? "" : "\r\n");

		Input.getline(array, 64);

		n = strlen(array);

		if(array[n - 1] == '\r') n--;

		for(i = 0; i < n; i++){
			if(array[i] < 0){
				array2[n - i - 2] = array[i];
				array2[n - i - 1] = array[i + 1];
				i++;
			}else{
				array2[n - i - 1] = array[i];
			}
		}

		Output.write(array2, n);

	}

	Input.close();
	Output.close();

    return 0; 
} 