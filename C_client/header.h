#ifndef C_CLIENT_HEADER_H_
#define C_CLIENT_HEADER_H_
#include "os.h"
#define LINUX
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef WINDOWS
#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment (lib, "ws2_32.lib")
#endif // WINDOWS

#ifdef LINUX
#include <sys/socket.h> //socket
#include <arpa/inet.h> // inet_addr
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <unistd.h>

#define SOCKET int
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1

#endif // LINUX

#include "mouseActivities.h"

#define IP_ADDRESS "127.0.0.1"
#define PORT 9999
#define X_COORD 0
#define Y_COORD 1
#define TIME 500

int initializeSocket(void);
int closeSocket(SOCKET);

#endif // !C_CLIENT_HEADER_H_
