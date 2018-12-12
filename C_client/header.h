#ifndef C_CLIENT_HEADER_H_
#define C_CLIENT_HEADER_H_
#include "os.h"

#include <stdio.h>
#include <string.h>

#ifdef WINDOWS
#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment (lib, "ws2_32.lib")
#endif // WINDOWS

#ifdef LINUX
#include <sys/socket.h> //socket
#include <arpa/inet.h> // inet_addr

#define SOCKET int
#define INVALID_SOCKET -1
#define 
#endif // LINUX

#endif // !C_CLIENT_HEADER_H_
