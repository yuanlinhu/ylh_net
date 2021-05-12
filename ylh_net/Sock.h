#pragma once

//#ifndef UNICODE
//#define UNICODE 1
//#endif

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

//#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include<io.h>
#include <ws2tcpip.h>
#include <winsock2.h>


#pragma comment( lib, "ws2_32.lib"  )  // for select 
#pragma comment(lib,"ws2_32")


class Sock
{
public:
	Sock();
	~Sock();

	static bool init();

	bool create_sock();
	
	bool bind_sock(int port);

	bool start_listen();

private:
	SOCKET m_sock_listen;
};

