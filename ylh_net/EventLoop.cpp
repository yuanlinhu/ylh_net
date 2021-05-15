#include "EventLoop.h"
#include "Poller.h"
#include "Channel.h"


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

		for (auto iter : m_active_channel_list)
		{
			(iter)->handle_event();
		}
	}
}

void EventLoop::updateChannel(Channel* channel)
{
	m_pooler->updateChannel(channel);
}

void EventLoop::remove_channel(Channel* channel)
{
	m_pooler->remove_channel(channel);
}
