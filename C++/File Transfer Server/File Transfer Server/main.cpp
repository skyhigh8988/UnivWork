#include <winsock2.h>
#include <conio.h>
#include <time.h>
#include <string.h>
#include <iostream>
#include <fstream>

using namespace std;

#define SERVER_PORT 4321
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
	SOCKET s;
	
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = INADDR_ANY;
	server_address.sin_port = htons(SERVER_PORT);
	memset(&(server_address.sin_zero),'\0', 8);

	s = socket(PF_INET, SOCK_DGRAM, 0);
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

	char buff[MAX_MESSAGE];
	char filename[MAX_STRING];
	int n, len = sizeof(client_address);
	fstream file;

	while (1) {
		n = recvfrom(s, buff, MAX_MESSAGE, 0, (struct sockaddr *)&client_address, &len);
		if (n > 0) {
			buff[n] = '\0';
			strcpy_s(filename, buff);
			cout << timeString << "System: File \"" << filename << "\" request from \"" << inet_ntoa(client_address.sin_addr) << "\".\n";
			file.open(filename, ios::in|ios::binary);
			if (file.is_open()) {
				file.seekg(0, ios::end);
				n = (int)file.tellg();
				file.seekg(0, ios::beg);
				_itoa_s(n, buff, 10);
				sendto(s, buff, MAX_MESSAGE, 0, (struct sockaddr *)&client_address, len);

				tt = time(NULL);
				localtime_s(&timeinfo, &tt);
				strftime(timeString, MAX_STRING, "[%x %X] ", &timeinfo);
				cout << timeString << "System: \"" << filename << "(" << buff << " bytes)" << "\" start transfer.\n";

				while (!file.eof()) {
					n = recvfrom(s, buff, MAX_MESSAGE, 0, (struct sockaddr *)&client_address, &len);

					file.read(buff, MAX_MESSAGE);
					sendto(s, buff, MAX_MESSAGE, 0, (struct sockaddr *)&client_address, len);
				}
				
				tt = time(NULL);
				localtime_s(&timeinfo, &tt);
				strftime(timeString, MAX_STRING, "[%x %X] ", &timeinfo);
				cout << timeString << "System: \"" << filename << "\" transfer complete.\n";
				cout << timeString << "System: Server ready\n";

				file.close();
			} else {
				sendto(s, "N", MAX_MESSAGE, 0, (struct sockaddr *)&client_address, len);
				tt = time(NULL);
				localtime_s(&timeinfo, &tt);
				strftime(timeString, MAX_STRING, "[%x %X] ", &timeinfo);
				cout << timeString << "System: \"" << filename << "\" not exist.\n";
			}
		}
	}

	closesocket(s);
	WSACleanup();

	_getch();
	return 0;
}