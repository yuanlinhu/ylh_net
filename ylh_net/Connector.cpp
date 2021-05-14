#include "Connector.h"
#include "Sock.h"
#include "Channel.h"
#include "ConnectChannel.h"


Connector::Connector(EventLoop* loop)
	:m_owner_loop(loop)
{
}


Connector::~Connector()
{
}

void Connector::start()
{
	//m_connect_sock = new Sock();
	//m_connect_sock->create_non_block_sock();
}

void Connector::connect(string& ip, int port)
{
	if (m_connect_state == kConnected)
	{
		return;
	}

	m_connect_sock = new Sock();
	m_connect_sock->create_non_block_sock();


	hostent *host = gethostbyname(ip.c_str());
	if (host == NULL)
	{
		return ;
	}

	// Setup our socket address structure
	SOCKADDR_IN sin;
	sin.sin_port = htons(port);
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = *((unsigned long*)host->h_addr);


	int ret = ::connect(m_connect_sock->get_socket(), (struct sockaddr*)&sin, sizeof(sockaddr));
	if (ret != 0)
	{
		return;
	}


	m_channel = new ConnectChannel(m_connect_sock, m_owner_loop);
	m_channel->enableWriting();






}
