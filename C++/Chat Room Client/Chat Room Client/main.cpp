#include <winsock2.h>
#include <conio.h>
#include <time.h>
#include <iostream>
#include <fstream>

using namespace std;

#define SERVER_PORT 5432
#define MAX_MESSAGE 256
#define MAX_STRING 128

int main (void) {

	time_t tt, tc = time(NULL);
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

	struct hostent *hp;

	char servername[MAX_STRING];
	char username[MAX_STRING];
	char filename[MAX_STRING];
	char logname[MAX_STRING];

	while (1) {
		cout << "Host: ";
		cin.getline(servername, MAX_STRING);
		cout << "User: ";
		cin.getline(username, MAX_STRING);
		hp = gethostbyname(servername);
		if (!hp) {
			tt = time(NULL);
			localtime_s(&timeinfo, &tt);
			strftime(timeString, MAX_STRING, "[%x %X] ", &timeinfo);
			cout << timeString << "Error: Unknown server \"" << servername << "\"\n";
		} else {
			SOCKET s;
			struct sockaddr_in server_address;
			server_address.sin_family = AF_INET;  
			server_address.sin_addr = *((struct in_addr *)hp->h_addr);
			server_address.sin_port = htons(SERVER_PORT);
			memset(&(server_address.sin_zero), '\0', 8);

			s = socket(PF_INET, SOCK_STREAM, 0);
			if (s == INVALID_SOCKET) {
				tt = time(NULL);
				localtime_s(&timeinfo, &tt);
				strftime(timeString, MAX_STRING, "[%x %X] ", &timeinfo);
				cout << timeString << "Error: Socket creation failed\n";
			} else {
				if (connect(s, (struct sockaddr *)&server_address, sizeof(server_address)) == SOCKET_ERROR) {
					tt = time(NULL);
					localtime_s(&timeinfo, &tt);
					strftime(timeString, MAX_STRING, "[%x %X] ", &timeinfo);
					cout << timeString << "Error: Connecting to server \"" << inet_ntoa(server_address.sin_addr) << "\" failed\n";
				} else {
					char bufOut[MAX_MESSAGE], bufIn[MAX_MESSAGE];
					int i;

					strcpy_s(bufOut, "/u ");
					strcat_s(bufOut, username);
					send(s, bufOut, MAX_MESSAGE, 0);
					int n = recv(s, bufIn, MAX_MESSAGE, 0);
					if (n > 0) bufIn[n] = '\0';
					if (n > 0 && strcmp(bufIn, "M") == 0) {
						tt = time(NULL);
						localtime_s(&timeinfo, &tt);
						strftime(timeString, MAX_STRING, "[%x %X] ", &timeinfo);
						cout << timeString << "System: Connecting to server \"" << inet_ntoa(server_address.sin_addr) << "\" successful\n";
						fstream log;
						strftime(logname, MAX_STRING, "Log_%Y%m%d%H%M%S_", &timeinfo);
						strcat_s(logname, inet_ntoa(server_address.sin_addr));
						strcat_s(logname, ".txt");

						while (1) {
							s = socket(PF_INET, SOCK_STREAM, 0);
							connect(s, (struct sockaddr *)&server_address, sizeof(server_address));
							i = 0;

							cout << username << ": ";
							cin.getline(bufOut, MAX_MESSAGE);
							if (bufOut[0] == '/') {
								switch (bufOut[1]) {
									case 'u':
									case 'U':
										strcpy_s(username, bufOut + 3);
										break;
									case 'f':
									case 'F':
										strcpy_s(filename, bufOut + 3);
										break;
								}
							}
							send(s, bufOut, MAX_MESSAGE, 0);
							n = recv(s, bufIn, MAX_MESSAGE, 0);
							if (n > 0) {
								bufIn[n] = '\0';

								if (strcmp(bufIn, "M") != 0) {
									if (strcmp(bufIn, "N") == 0) {
										tt = time(NULL);
										localtime_s(&timeinfo, &tt);
										strftime(timeString, MAX_STRING, "[%x %X] ", &timeinfo);
										cout << timeString << "Server: \"" << filename << "\" not exist.\n";
									} else if (strcmp(bufIn, "E") == 0) {
										tt = time(NULL);
										localtime_s(&timeinfo, &tt);
										strftime(timeString, MAX_STRING, "[%x %X] ", &timeinfo);
										cout << timeString << "Server: Command error.\n";
									} else {
										tt = time(NULL);
										localtime_s(&timeinfo, &tt);
										strftime(timeString, MAX_STRING, "[%x %X] ", &timeinfo);
										cout << timeString << "Server: \"" << filename << "(" << bufIn << " bytes)" << "\" start transfer.\n";
										log.open(logname, ios::out|ios::binary|ios::app);
										log << timeString << "Server: \"" << filename << "(" << bufIn << " bytes)" << "\" start transfer.\r\n";
										log.close();
									
										int size = atoi(bufIn);
										int remain = size;
										fstream file;
										file.open(filename, ios::out|ios::binary);

										while (remain > 0) {
											s = socket(PF_INET, SOCK_STREAM, 0);
											connect(s, (struct sockaddr *)&server_address, sizeof(server_address));
											send(s, "/f", MAX_MESSAGE, 0);
											n = recv(s, bufIn, MAX_MESSAGE, 0);
											if (n > 0) {
												if (remain < MAX_MESSAGE) {
													file.write(bufIn, remain);
													remain = 0;
												} else {
													remain -= MAX_MESSAGE;
													file.write(bufIn, MAX_MESSAGE);
												}

												tt = time(NULL);
												if (tt != tc) {
													tc = tt;
													localtime_s(&timeinfo, &tt);
													strftime(timeString, MAX_STRING, "[%x %X] ", &timeinfo);
													cout << "\r" << timeString << "Server: Remain " << remain << " bytes.          \b\b\b\b\b\b\b\b\b\b" << flush;
												}
											}
										}

										tt = time(NULL);
										localtime_s(&timeinfo, &tt);
										strftime(timeString, MAX_STRING, "[%x %X] ", &timeinfo);
										cout << "\r" << timeString << "Server: Transfer complete.\n";
										log.open(logname, ios::out|ios::binary|ios::app);
										log << timeString << "Server: Transfer complete.\r\n";
										log.close();
										file.close();
									}
								} else {
									tt = time(NULL);
									localtime_s(&timeinfo, &tt);
									strftime(timeString, MAX_STRING, "[%x %X] ", &timeinfo);
									log.open(logname, ios::out|ios::binary|ios::app);
									log << timeString << username << ": " << bufOut << "\r\n";
									log.close();
								}
							} else {
								tt = time(NULL);
								localtime_s(&timeinfo, &tt);
								strftime(timeString, MAX_STRING, "[%x %X] ", &timeinfo);
								cout << timeString << "Error: Connecting to server \"" << inet_ntoa(server_address.sin_addr) << "\" failed\n";
								break;
							}
						}
					} else {
						tt = time(NULL);
						localtime_s(&timeinfo, &tt);
						strftime(timeString, MAX_STRING, "[%x %X] ", &timeinfo);
						cout << timeString << "Error: Connecting to server \"" << inet_ntoa(server_address.sin_addr) << "\" failed\n";
					}
				}
			}
			closesocket(s);
		}
	}
	WSACleanup();

	_getch();
	return 0;
}