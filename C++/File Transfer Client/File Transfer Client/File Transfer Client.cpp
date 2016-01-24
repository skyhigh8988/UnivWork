#include <winsock2.h>
#include <conio.h>
#include <time.h>
#include <iostream>
#include <fstream>

using namespace std;

#define SERVER_PORT 4321
#define MAX_MESSAGE 256
#define MAX_STRING 128

int main (void) {

	time_t tt, tc = time(NULL);
	clock_t cr, cs, co;
	struct tm timeinfo;
	char timeString[MAX_STRING];
	fstream log;
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
	char filename[MAX_STRING];
	char logname[MAX_STRING];

	while (1) {
		cout << "Host: ";
		cin.getline(servername, MAX_STRING);
		cout << "File: ";
		cin.getline(filename, MAX_STRING);
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

			s = socket(PF_INET, SOCK_DGRAM, 0);
			if (s == INVALID_SOCKET) {
				tt = time(NULL);
				localtime_s(&timeinfo, &tt);
				strftime(timeString, MAX_STRING, "[%x %X] ", &timeinfo);
				cout << timeString << "Error: Socket creation failed\n";
			} else {
				char bufOut[MAX_MESSAGE], bufIn[MAX_MESSAGE];
				int len = sizeof(server_address);
				tt = time(NULL);
				localtime_s(&timeinfo, &tt);
				strftime(logname, MAX_STRING, "Log_%Y%m%d%H%M%S_", &timeinfo);
				strcat_s(logname, inet_ntoa(server_address.sin_addr));
				strcat_s(logname, "_");
				strcat_s(logname, filename);
				strcat_s(logname, ".txt");

				strcpy_s(bufOut, filename);
				sendto(s, bufOut, MAX_MESSAGE, 0, (struct sockaddr *)&server_address, len);
				int n = recvfrom(s, bufIn, MAX_MESSAGE, 0, (struct sockaddr *)&server_address, &len);
				if (n > 0) {
					bufIn[n] = '\0';
					if (strcmp(bufIn, "N") == 0) {
						tt = time(NULL);
						localtime_s(&timeinfo, &tt);
						strftime(timeString, MAX_STRING, "[%x %X] ", &timeinfo);
						cout << timeString << "Server: \"" << filename << "\" not exist.\n";
					} else {
						co = clock();
						tt = time(NULL);
						localtime_s(&timeinfo, &tt);
						strftime(timeString, MAX_STRING, "[%x %X] ", &timeinfo);
						cout << timeString << "Server: \"" << filename << "(" << bufIn << " bytes)" << "\" start transfer.\n";
						log.open(logname, ios::out|ios::binary|ios::app);
						log << "-------------------------------------------------------------------------\r\n";
						log << timeString << "Server: \"" << filename << "(" << bufIn << " bytes)" << "\" start transfer.\r\n";
						log.close();
									
						int size = atoi(bufIn);
						int remain = size;
						double avg = 0.0;
						int count = 0;
						fstream file;
						file.open(filename, ios::out|ios::binary);

						while (remain > 0) {
							sendto(s, "/f", MAX_MESSAGE, 0, (struct sockaddr *)&server_address, len);
							cs = clock();
							n = recvfrom(s, bufIn, MAX_MESSAGE, 0, (struct sockaddr *)&server_address, &len);
							cr = clock();
							avg += ((double)(cr - cs) - avg) / ++count;

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
						
						cr = clock();
						tt = time(NULL);
						localtime_s(&timeinfo, &tt);
						strftime(timeString, MAX_STRING, "[%x %X] ", &timeinfo);
						cout << "\r" << timeString << "Server: Transfer complete.          \b\b\b\b\b\b\b\b\b\b\n"  << flush;
						log.open(logname, ios::out|ios::binary|ios::app);
						log << timeString << "Server: Transfer complete.\r\n";
						log << "-------------------------------------------------------------------------\r\n";
						log << "Server:       " << inet_ntoa(server_address.sin_addr) << ":" << SERVER_PORT << "\r\n";
						log << "File Name:    " << filename << "\r\n";
						log << "File Size:    " << size << " bytes\r\n";
						log << "Cost:         " << cr - co << " millisecond\r\n";
						log << "Package:      " << count << " (256 bytes/1 packages)\r\n";
						log << "RTT Avg:      " << avg << " millisecond\r\n";
						log << "Throughput:   " << (double)size / (double)(cr - co) << " bytes/millisecond\r\n";
						log << "-------------------------------------------------------------------------\r\n";
						log.close();
						file.close();
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