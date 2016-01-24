#include <winsock2.h>
#include <conio.h>
#include <time.h>
#include <string.h>
#include <iostream>
#include <fstream>

using namespace std;

#define SERVER_PORT 5432
#define MAX_PENDING 2
#define MAX_MESSAGE 256
#define MAX_STRING 128

int main (void) {
	
	time_t tt;
	struct tm timeinfo;
	char timeString[MAX_STRING];
	WSADATA info;

	if (WSAStartup(MAKEWORD(1,1), &info) !=0) {
		tt = time(NULL);
		localtime_s(&timeinfo, &tt);
		strftime(timeString, MAX_STRING, "[%x %X] ", &timeinfo);
		cout << timeString << "Error: Winsock startup failed\n";
		_getch();
		exit(1);
	}

	struct sockaddr_in server_address;
	struct sockaddr_in client_address;
	SOCKET s, new_s;
	
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = INADDR_ANY;
	server_address.sin_port = htons(SERVER_PORT);
	memset(&(server_address.sin_zero),'\0', 8);

	s = socket(PF_INET, SOCK_STREAM, 0);
	if (s == INVALID_SOCKET) {
		tt = time(NULL);
		localtime_s(&timeinfo, &tt);
		strftime(timeString, MAX_STRING, "[%x %X] ", &timeinfo);
		cout << timeString << "Error: Socket creation failed\n";
		_getch();
		exit(1);
	}

	if (bind(s, (struct sockaddr *)&server_address, sizeof(server_address)) == SOCKET_ERROR) {
		tt = time(NULL);
		localtime_s(&timeinfo, &tt);
		strftime(timeString, MAX_STRING, "[%x %X] ", &timeinfo);
		cout << timeString << "Error: Bind failed\n";
		exit(1);
	}

	tt = time(NULL);
	localtime_s(&timeinfo, &tt);
	strftime(timeString, MAX_STRING, "[%x %X] ", &timeinfo);
	cout << timeString << "System: Server ready\n";

	listen(s, MAX_PENDING);
	char buff[MAX_MESSAGE];
	char user[MAX_STRING];
	char filename[MAX_STRING];
	int n, len = sizeof(client_address);
	fstream file;

	while (1) {
		new_s = accept(s, (struct sockaddr *)&client_address, &len);
		if (new_s == INVALID_SOCKET) {
			tt = time(NULL);
			localtime_s(&timeinfo, &tt);
			strftime(timeString, MAX_STRING, "[%x %X] ", &timeinfo);
			cout << timeString << "Error: Accepting connection failed\n";
		} else {
			n = recv(new_s, buff, MAX_MESSAGE, 0);
			if (n > 0) {
				buff[n] = '\0';

				if (buff[0] == '/') {
					switch (buff[1]) {
						case 'u':
						case 'U':
							send(new_s, "M", MAX_MESSAGE, 0);
							strcpy_s(user, buff + 3);
							tt = time(NULL);
							localtime_s(&timeinfo, &tt);
							strftime(timeString, MAX_STRING, "[%x %X] ", &timeinfo);
							cout << timeString << "System: Accepting connection \"" << user << "(" << inet_ntoa(client_address.sin_addr) << ")\"\n";
							break;
						case 'f':
						case 'F':
							strcpy_s(filename, buff + 3);
							file.open(filename, ios::in|ios::binary);
							if (file.is_open()) {
								file.seekg(0, ios::end);
								n = (int)file.tellg();
								file.seekg(0, ios::beg);
								_itoa_s(n, buff, 10);
								send(new_s, buff, MAX_MESSAGE, 0);	

								tt = time(NULL);
								localtime_s(&timeinfo, &tt);
								strftime(timeString, MAX_STRING, "[%x %X] ", &timeinfo);
								cout << timeString << "System: \"" << filename << "(" << buff << " bytes)" << "\" start transfer.\n";

								while (!file.eof()) {
									new_s = accept(s, (struct sockaddr *)&client_address, &len);
									n = recv(new_s, buff, MAX_MESSAGE, 0);

									file.read(buff, MAX_MESSAGE);
									send(new_s, buff, MAX_MESSAGE, 0);
								}
								
								tt = time(NULL);
								localtime_s(&timeinfo, &tt);
								strftime(timeString, MAX_STRING, "[%x %X] ", &timeinfo);
								cout << timeString << "System: \"" << filename << "\" transfer complete.\n";
								cout << timeString << "System: Server ready\n";
								file.close();
							} else {
								send(new_s, "N", MAX_MESSAGE, 0);
								tt = time(NULL);
								localtime_s(&timeinfo, &tt);
								strftime(timeString, MAX_STRING, "[%x %X] ", &timeinfo);
								cout << timeString << "System: \"" << filename << "\" not exist.\n";
							}
							break;
						default:
							send(new_s, "E", MAX_MESSAGE, 0);
					}
				} else {
					send(new_s, "M", MAX_MESSAGE, 0);
					tt = time(NULL);
					localtime_s(&timeinfo, &tt);
					strftime(timeString, MAX_STRING, "[%x %X] ", &timeinfo);
					cout << timeString << user << ": " << buff << "\n";
				}
			}
		}
	}

	closesocket(s);
	WSACleanup();

	_getch();
	return 0;
}