#include "Channel.h"
#include "EventLoop.h"


Channel::Channel(Sock* sock, EventLoop* loop)
	:m_sock(sock)
	,m_owner_loop(loop)
{
}


Channel::~Channel()
{
}

void Channel::enableReading()
{
	m_events |= kReadEvent;
	update();
}

void Channel::disableReading()
{
	m_events &= ~kReadEvent;
	update();
}

void Channel::enableWriting()
{
	m_events |= kWriteEvent;
	update();
}

void Channel::disableWriting()
{
	m_events &= ~kWriteEvent;
	update();
}


void Channel::disableAll()
{
	m_events = kNoneEvent;
	update();
}

void Channel::update()
{
	m_owner_loop->updateChannel(this);
}

void Channel::handle_event()
{
	if (m_events&(POLLIN | POLLPRI))
	{
		if (readCallback_)
		{
			readCallback_(0);
		}
	}
	if (m_events&POLLOUT)
	{
		if (writeCallback_)
		{
			writeCallback_();
		}
	}

}

void Channel::handle_read()
{

}

void Channel::handle_write()
{
	//auto conn = (new TcpConnection(loop_,
	//	connName,
	//	sockfd,
	//	localAddr,
	//	peerAddr));
}

void Channel::handle_close()
{

}


