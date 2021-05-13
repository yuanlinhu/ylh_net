#include "EventLoop.h"
#include "Poller.h"


EventLoop::EventLoop()
{
	m_pooler = new Poller();
}


EventLoop::~EventLoop()
{
}

void EventLoop::loop()
{
	while (false == m_quit)
	{
		m_active_channel_list.clear();
		m_pooler->poll(1, m_active_channel_list);
	}
}

void EventLoop::updateChannel(Channel* channel)
{
	m_pooler->updateChannel(channel);
}
