#include "Acceptor.h"

#include "Channel.h"
#include <functional>
#include "InetAddress.h"
#include <iostream>
using namespace std;

Acceptor::Acceptor(EventLoop* loop, bool reuse_port)
	:m_ownerEventLoop(loop)
{
	m_accept_sock = new Sock();
	m_accept_sock->create_non_block_sock();
	m_accept_sock->set_reuse_addr(true);
	m_accept_sock->set_reuse_port(reuse_port);

	m_accept_channel = new Channel(loop, m_accept_sock);

	m_accept_channel->setReadCallback(std::bind(&Acceptor::handle_read, this,std::placeholders::_1));
	cout << "开启accept fd:" << m_accept_sock->get_fd() << endl;
}


Acceptor::~Acceptor()
{
}

void Acceptor::listen(int port)
{
	m_accept_sock->bind_sock(port);
	m_accept_sock->start_listen();
	m_accept_channel->enableReading();
}

void Acceptor::handle_read(int fd)
{
	int kk = 0;
	kk++;

	InetAddress peerAddr;
	int connfd = m_accept_sock->accept(&peerAddr);
	cout << "接收一个连接请求 fd:" << connfd << endl;


	if (connfd > 0)
	{
		if (newConnectionCallback_)
		{
			newConnectionCallback_(connfd, peerAddr);
		}
		else
		{
			//sockets::close(connfd);
		}
	}
}
