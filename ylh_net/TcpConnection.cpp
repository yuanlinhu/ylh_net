#include "TcpConnection.h"

#include "Sock.h"
#include "Channel.h"
#include <iostream>

using namespace std;

TcpConnection::TcpConnection(int fd, const InetAddress& addr, EventLoop* loop)
	:m_fd(fd)
	,m_addr(addr)
	, m_owner_loop(loop)
{
	m_fd = fd;
	m_addr = addr;

	m_sock = new Sock();
	m_sock->set_sock(fd);
	m_channel = new Channel(m_sock, m_owner_loop);

	m_channel->setReadCallback(std::bind(&TcpConnection::handleRead, this, std::placeholders::_1));
	m_channel->setWriteCallback(std::bind(&TcpConnection::handleWrite, this));
}


TcpConnection::~TcpConnection()
{
}

void TcpConnection::send(string& msg)
{
	int n = ::send((SOCKET)m_fd, msg.c_str(), msg.size(), 0);

	cout << "sendmsg [" << n << "]" << endl;
}

void TcpConnection::handleRead(int receiveTime)
{
	char buff[4096] = {0};
	int buff_size = recv(m_fd, static_cast<char*>(buff), 4096, 0);

	string str(buff, buff_size);
	printf("recv:[%s]\n", str.c_str());
	//send(str);
}

void TcpConnection::handleWrite()
{

}