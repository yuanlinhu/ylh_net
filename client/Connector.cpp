#include "Connector.h"
#include "Sock.h"


Connector::Connector(EventLoop* loop)
	:m_owner_loop(loop)
{
}


Connector::~Connector()
{
}

void Connector::start()
{
	m_connect_sock = new Sock();
	m_connect_sock->create_non_block_sock();

	connect();
}

void Connector::connect()
{
	if (m_connect_state == kConnected)
	{
		return;
	}




}
