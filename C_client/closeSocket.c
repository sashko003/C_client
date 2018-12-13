#include "header.h"

int closeSocket(SOCKET sock)
{
	int iStatus = 0;

#ifdef WINDOWS
	iStatus = shutdown(sock, SD_BOTH);
	if (iStatus == 0) { 
		iStatus = closesocket(sock); 
	}
#endif
#ifdef LINUX
	iStatus = shutdown(sock, SHUT_RDWR);
	if (iStatus == 0) { 
		iStatus = close(sock); 
	}
#endif
#ifdef WINDOWS
	WSACleanup();
#endif
	return iStatus;
}
