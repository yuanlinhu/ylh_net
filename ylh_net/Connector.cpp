#include "Connector.h"
#include "Sock.h"
#include "Channel.h"
#include "ConnectChannel.h"
#include <functional>
#include "EventLoop.h"

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

void Connector::handle_writing()
{
	if (m_connect_state == kConnected)
	{
		return;
	}

	m_connect_state = kConnected;

	int fd = m_channel->get_fd();

	if (newConnectionCallback_)
	{
		newConnectionCallback_(fd);
	}

	//ÖØÖÃchannel£¬ ²¢´ÓpollerÉ¾³ý
	m_channel->disableAll();
	m_owner_loop->remove_channel(m_channel);
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

	int savedErrno = 0;
	int ret = ::connect(m_connect_sock->get_socket(), (struct sockaddr*)&sin, sizeof(sockaddr));
	if (ret != 0)
	{
		savedErrno = GetLastError();
		if (savedErrno != WSAEWOULDBLOCK)
		{
			return;
		}
	}


	m_channel = new Channel(m_connect_sock, m_owner_loop);
	m_channel->setWriteCallback(std::bind(&Connector::handle_writing, this));
	m_channel->enableWriting();






}


