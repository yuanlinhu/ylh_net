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


class InetAddress;

class Sock
{
public:
	Sock();
	~Sock();

	static bool init();

	bool create_non_block_sock();
	
	bool bind_sock(int port);

	bool start_listen();

	void set_reuse_addr(bool on);
	void set_reuse_port(bool reuse_port);
	void setNonDelay();
	int accept(InetAddress* peeraddr);

	void setNonBlock();

	int get_fd()
	{ 
		return m_sock; 
	}

	SOCKET get_socket() 
	{
		return m_sock;
	}

	void set_sock(int fd);

private:
	bool create_sock();


private:
	SOCKET m_sock = 0;
};

