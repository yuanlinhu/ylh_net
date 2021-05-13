#include "Acceptor.h"

#include "Channel.h"


Acceptor::Acceptor(EventLoop* loop, int port, bool reuse_port)
	:m_ownerEventLoop(loop)
{
	m_accept_sock = new Sock();
	m_accept_sock->create_non_block_sock();
	m_accept_sock->bind_sock(port);
	m_accept_sock->set_reuse_addr(true);
	m_accept_sock->set_reuse_port(reuse_port);

	m_accept_channel = new Channel(m_accept_sock, loop);
}


Acceptor::~Acceptor()
{
}

void Acceptor::listen()
{
	m_accept_sock->start_listen();
	m_accept_channel->enableReading();
}
