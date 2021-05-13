#include "EventLoop.h"
#include "Poller.h"


EventLoop::EventLoop()
{
	m_pooler = new Poller();
}


EventLoop::~EventLoop()
{
}

void EventLoop::updateChannel(Channel* channel)
{
	m_pooler->updateChannel(channel);
}
