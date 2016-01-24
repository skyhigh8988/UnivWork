#include "counter.h"
#include <string>

#define SERVER_PORT 5432
#define MAX_MESSAGE 128
#define MAX_STRING 128

void counter::process_func() {

	WSADATA info;
	if (WSAStartup(MAKEWORD(1,1), &info) !=0) {
		printf("Error: Winsock startup failed\n");
		exit(1);
	}

	struct hostent *hp;
	hp = gethostbyname("localhost");
	if (!hp) {
		printf("Error: Unknown server\n");
		exit(1);
	}

	SOCKET s_1;
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;  
	server_address.sin_addr = *((struct in_addr *)hp->h_addr);
	server_address.sin_port = htons(SERVER_PORT);
	memset(&(server_address.sin_zero), '\0', 8);

	s_1 = socket(PF_INET, SOCK_STREAM, 0);
	if (s_1 == INVALID_SOCKET) {
		printf("Error: Socket creation failed\n");
		exit(1);
	}
	if (connect(s_1, (struct sockaddr *)&server_address, sizeof(server_address)) == SOCKET_ERROR) {
		printf("Error: Connecting to server failed\n");
		exit(1);
	}

	printf("\n               Connect to server successed\n");

	int s = 0;
	int m = 0;
	int h = 9;
	int hi = 9;
	char t[] = "AM";
	char sc[] = "0";
	char mc[] = "0";
	char hc[] = "0";
	char bufOut[MAX_MESSAGE];

	while(1) {

		sprintf(bufOut, "%s%d : %s%d : %s%d %s", hc,hi,mc,m,sc,s,t);
		send(s_1, bufOut, MAX_MESSAGE, 0);

		wait();

		s++;
		if (s > 9) sc[0] = '\0';
		if (s == 60) {
			m++;
			s = 0;
			sc[0] = '0';
			if (m > 9) mc[0] = '\0';
			if (m == 60) {
				h++;
				m = 0;
				mc[0] = '0';
				if (h < 12) {
					t[0] = 'A';
					hi = h;
				} else if (h == 12) {
					hi = 12;
					t[0] = 'P';
				} else if (h > 12 && h != 12 && h != 24) {
					t[0] = 'P';
					hi = h - 12;
				} else if (h == 24) {
					h = 0;
					hi = 0;
					t[0] = 'A';
				}
				if (hi > 9) hc[0] = '\0';
				else hc[0] = '0';
			}
		}
	}

	closesocket(s_1);
	WSACleanup();
}