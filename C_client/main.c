#include "header.h"

int initWinsock(void);

int main()
{
	char* strIpAddress = "127.0.0.1";
	int port = 9999;

#ifdef WINDOWS
	// initialize winsocket
	if (initWinsock() != 0) {
		printf("Can't initialize winsock.\n");
		return -1;
	}
#endif // WINDOWS

	// create socket
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) {
		printf( "Can't create socket.\n");
		return -1;
	}

	// fill in hont structure
	struct sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	InetPton(AF_INET, strIpAddress, &hint.sin_addr);

	// connect to server
	int conResult = connect(sock, (struct sockaddr*)&hint, sizeof(hint));
	if (conResult == SOCKET_ERROR) {
		printf("Can't connect to server.\n");
		return -1;
	}

	// do-while loop to send and receive data
	char buffer[4096];
	char *userInput;

	do {
		// prompt the user for some text
		printf(">");
		scanf("%s", &userInput);
		if (strlen(userInput) > 0) {
			// send the text
			int sendResult = send(sock, userInput, strlen(userInput) + 1, 0);
			if (sendResult != SOCKET_ERROR) {
				// wait for response
				ZeroMemory(buffer, 4096);
				int byteReceived = recv(sock, buffer, 4096, 0);
				if (byteReceived > 0) {
					// echo response to console
					printf("SERVER>%s", buffer);
				}
			}
		}
	} while (strlen(userInput) > 0);

	// close down everything
	closesocket(sock);
	WSACleanup();
	return 0;
}

int initWinsock(void)
{
	WSADATA wsaData;
	WORD wVersion = MAKEWORD(2, 2);
	return WSAStartup(wVersion, &wsaData);
}