#include "Sock.h"
#include "InetAddress.h"


Sock::Sock()
{
}


Sock::~Sock()
{
}

bool Sock::init()
{
	WORD sockVer = MAKEWORD(2, 2);

	WSADATA wsaData;
	if (WSAStartup(sockVer, &wsaData) != 0)
	{
		return false;
	}

	return true;
}

bool Sock::create_sock()
{
	m_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_sock == INVALID_SOCKET)
	{
		return false;
	}

	return true;
}

bool Sock::create_non_block_sock()
{
	create_sock();
	//setNonDelay();

	return true;
}


void Sock::setNonDelay()
{
	BOOL nodelay = TRUE;
	int ret = setsockopt(m_sock, IPPROTO_TCP, TCP_NODELAY, (char*)&nodelay, sizeof(nodelay));
	if (ret == SOCKET_ERROR)
	{
	}
}

bool Sock::bind_sock(int port)
{
	sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.S_un.S_addr = INADDR_ANY;
	if (bind(m_sock, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR)
	{
		return false;
	}

	return true;
}

bool Sock::start_listen()
{
	//¿ªÊ¼¼àÌý  
	if (listen(m_sock, 5) == SOCKET_ERROR)
	{
		return false;
	}

	return true;
}

void Sock::set_reuse_addr(bool on)
{
	int opt_val = on ? 1 : 0;
	::setsockopt(m_sock, IPPROTO_TCP, SO_REUSEADDR, 
		(char*)&opt_val, sizeof(opt_val));
}

void Sock::set_reuse_port(bool reuse_port)
{
	int opt_val = reuse_port ? 1 : 0;
	//::setsockopt(m_sock, SOL_SOCKET, SO_REUSEPORT,
	//	(char*)&opt_val, sizeof(opt_val));
}


int Sock::accept(InetAddress* peeraddr)
{
	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));

	socklen_t addrlen = static_cast<socklen_t>(sizeof(addr));
	int connfd = ::accept(m_sock, (sockaddr*)&addr, &addrlen);
	
	BOOL nodelay = TRUE;
	int ret = setsockopt(connfd, IPPROTO_TCP, TCP_NODELAY, (char*)&nodelay, sizeof(nodelay));

	if (connfd > 0)
	{
		peeraddr->setSockAddrIn(addr);
	}
	return connfd;
}
