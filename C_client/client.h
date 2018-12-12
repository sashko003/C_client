#ifndef C_CLIENT_CLIENT_H_
#define C_CLIENT_CLIENT_H_
#include "header.h"

typedef struct stClient Client;

struct stClient
{
	char *_chIpAddress;
	int _iPort;
	SOCKET _sckSocket;

	int (*pfCreateSocket)(SOCKET *sock);

};

#endif // !C_CLIENT_CLIENT_H_
