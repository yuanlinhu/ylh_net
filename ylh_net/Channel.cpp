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

void Channel::handle_event()
{
	if ((m_events&POLLHUP) && !(m_events&POLLIN))
	{
		handle_close();
	}
	if (m_events&(POLLIN | POLLPRI))
	{
		handle_read();
	}
	if (m_events&POLLOUT)
	{
		handle_write();
	}

}

void Channel::handle_read()
{

}

void Channel::handle_write()
{

}

void Channel::handle_close()
{

}


