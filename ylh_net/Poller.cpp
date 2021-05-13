#include "Poller.h"
#include "Channel.h"


Poller::Poller()
{
}


Poller::~Poller()
{
}

void Poller::updateChannel(Channel* channel)
{
	int fd = channel->get_fd();
	auto iter = m_pollFd_list.find(fd);
	if (iter == m_pollFd_list.end())
	{
		//ĞÂ½¨
		pollfd pfd;
		pfd.fd = fd;
		pfd.events = channel->get_events();
		pfd.revents = 0;
		
		m_pollFd_list[fd] = pfd;
		m_channel_list[fd] = channel;
	}
	else
	{
		iter->second.events = channel->get_events();
		iter->second.revents = 0;
	}
}
