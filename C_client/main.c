#include "header.h"
#define IP_MAX_SIZE 15
int main(void)
{
	/*char strIpAddress[IP_MAX_SIZE + 1] = {0};
	printf("Enter IP-address: ");
	fgets(strIpAddress, IP_MAX_SIZE+1, stdin);*/
	
	char *strIpAddress = IP_ADDRESS;
	// initialize winsocket
	if (initializeSocket() != 0) {
		printf("Can't initialize winsock.\n");
		return -1;
	}

	// create socket
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) {
		printf( "Can't create socket.\n");
		return -1;
	}

	// fill in hont structure
	struct sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(PORT);
	inet_pton(AF_INET, strIpAddress, &hint.sin_addr);// same: int.sin_addr.S_un.S_addr = inet_addr(strIpAddress);


	// connect to server
	int conResult = connect(sock, (struct sockaddr*)&hint, sizeof(hint));
	if (conResult < 0) {
		printf("Can't connect to server.\n");
		return -1;
	}

	// do-while loop to send and receive data
	MouseActivities unMouse; 
	unMouse.chClickType = NULL;
	do {
		// prompt the user for some text
		int iCheck = findMouseCoordinates(&unMouse);
		if (iCheck < 0) // define good result, bad result of findMouseCoordinates
			printf("Can't read coordinates\n");
		
		int sendResult = send(sock, unMouse.chMessage, sizeof(unMouse.chMessage) + 1, 0);
		printf("X: %d  Y: %d \n", *(int *)unMouse.chX, *(int *)unMouse.chY);
		if (sendResult == SOCKET_ERROR) {
			printf("Error in send().\n");
			break;
		}
		// wait for response
		ZeroMemory((void*)&unMouse, sizeof(unMouse));
		int byteReceived = recv(sock, unMouse.chMessage, sizeof(unMouse.chMessage), 0);
		
		if (byteReceived == SOCKET_ERROR) {
			printf("Error in recv().\n");
			break;
		}
		
		if (byteReceived == 0) {
			printf("Server disconnected. \n");
			break;
		}
			// echo response to console
		printf("SERVER> X: %d  Y: %d \n", unMouse.iCoords[0], unMouse.iCoords[1]);				
		ZeroMemory((void*)&unMouse, sizeof(unMouse));
		Sleep(TIME);
	} while (1);

	// close down everything
	closeSocket(sock);
	getchar();
	return 0;
}



