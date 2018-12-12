#include "client.h"

int createSocket(SOCKET *sock)
{
	*sock = socket(AF_INET, SOCK_STREAM, 0);
	return *sock;
}
