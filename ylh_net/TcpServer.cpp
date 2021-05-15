#include "TcpServer.h"

#include "Acceptor.h"
#include <functional>

TcpServer::TcpServer(EventLoop* loop)
	:m_owner_loop(loop)
{
	m_acceptor = new Acceptor(m_owner_loop, true);
}


TcpServer::~TcpServer()
{
}

void TcpServer::listen(int port)
{
	m_acceptor->setNewConnectionCallback(std::bind(&TcpServer::handle_connection, this, std::placeholders::_1, std::placeholders::_2));
	m_acceptor->listen(port);
}

void TcpServer::handle_connection(int sockfd, const InetAddress& addr)
{
	int jj = 0;
	jj++;
}