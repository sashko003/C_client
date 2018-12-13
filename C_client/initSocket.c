#include "header.h"

int initializeSocket(void)
{
#ifdef WINDOWS
	// initialize winsocket
	WSADATA wsaData;
	WORD wVersion = MAKEWORD(2, 2);
	return WSAStartup(wVersion, &wsaData);
#endif // WINDOWS
#ifdef LINUX
	return 0;
#endif // LINUX

}