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


void Channel::update()
{
	m_owner_loop->updateChannel(this);
}
