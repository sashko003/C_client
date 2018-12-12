#ifndef C_CLIENT_OS_H
#define C_CLIENT_OS_H

#ifdef __UNIX || __UNIX__ || UNIX
#define LINUX
#endif // __UNIX
#ifdef _WIN32 || _WIN64
#define WINDOWS
#endif // _WIN32 || _WIN64


#endif // !C_CLIENT_OS_H

