#include "header.h"

int initWinsock(void);
int closeSocket(SOCKET);

typedef union unMouseActivities
{
	int iCoords[2];
	struct {
		char chX[sizeof(int)];
		char chY[sizeof(int)];
		char chClickType[3];
	};
	char chMessage[sizeof(int)*2+3];
} MouseActivities;

int findMouseCoordinates(MouseActivities *unMA);

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
//	hint.sin_addr.S_un.S_addr = inet_addr(strIpAddress);
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	inet_pton(AF_INET, strIpAddress, &hint.sin_addr);

	// connect to server
	int conResult = connect(sock, (struct sockaddr*)&hint, sizeof(hint));
	if (conResult < 0) {
		printf("Can't connect to server.\n");
		//return -1;
	}

	// do-while loop to send and receive data
	char buffer[4096];
	char *userInput[256];
	MouseActivities unMouse;
	do {
		// prompt the user for some text
		int i = findMouseCoordinates(&unMouse);
		if (i < 0)
			printf("Can't read coordinates\n");
		//char chX[4], chY[4];
		/*for (int i = 0; i < 4; i++) {
			chX[i] = unMouse.chMessage[i];
			chY[i] = unMouse.chMessage[i + 4];
		}*/
		printf("X: %d  Y: %d \n", *(int *)unMouse.chX, *(int *)unMouse.chY);
		//if (strlen(userInput) > 0) {
		//	// send the text
		//	int sendResult = send(sock, userInput, strlen(userInput) + 1, 0);
		//	if (sendResult != SOCKET_ERROR) {
		//		// wait for response
		//		ZeroMemory(buffer, 4096);
		//		int byteReceived = recv(sock, buffer, 4096, 0);
		//		if (byteReceived > 0) {
		//			// echo response to console
		//			printf("SERVER>%s", buffer);
		//			printf("\n");
		//		}
		//	}
		//}
		Sleep(500);
	} while (1);

	// close down everything
	closeSocket(sock);
#ifdef WINDOWS
	WSACleanup();
#endif
	return 0;
}

int initWinsock(void)
{
	WSADATA wsaData;
	WORD wVersion = MAKEWORD(2, 2);
	return WSAStartup(wVersion, &wsaData);
}

int closeSocket(SOCKET sock)
{
	int iStatus = 0;

#ifdef WINDOWS
	iStatus = shutdown(sock, SD_BOTH);
	if (iStatus == 0) { iStatus = closesocket(sock); }
#endif
#ifdef LINUX
	iStatus = shutdown(sock, SHUT_RDWR);
	if (iStatus == 0) { iStatus = close(sock); }
#endif

	return iStatus;
}

int findMouseCoordinates(MouseActivities *unMA)
{
	//POINT point;
	LPPOINT pCursor = (LPPOINT)malloc(sizeof(LPPOINT));
	//MouseActivities maCoords = {0,0};
		if (!GetCursorPos(pCursor))
			return -1;
		//Sleep(1000);
		unMA->iCoords[0] = pCursor->x;
		unMA->iCoords[1] = pCursor->y;
		/*printf("X: ", pCursor->x); printf(" Y: ", pCursor->y); printf("\n");
		if (GetAsyncKeyState(VK_LBUTTON)) {
			printf("Left mouse click: X: ", pCursor->x); printf(" Y: ", pCursor->y); printf("\n");
		}
		if (GetAsyncKeyState(VK_RBUTTON)) {
			printf("Right mouse click: X: ", pCursor->x); printf(" Y: ", pCursor->y); printf("\n");
		}*/
	//free((void*)pCursor);
	return 0;
}