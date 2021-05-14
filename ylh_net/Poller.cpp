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
		//ÐÂ½¨
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

void Poller::poll(int timeoutMs, std::vector<Channel*>& active_channel_list)
{
	FD_ZERO(&m_read_fd);
	FD_ZERO(&m_write_fd);
	FD_ZERO(&m_error_fd);

	int max_fd = 0;
	for (auto iter : m_pollFd_list)
	{
		pollfd& tmp_fd = iter.second;
		if (tmp_fd.events & (POLLIN |POLLPRI))
		{
			FD_SET(tmp_fd.fd, &m_read_fd);
		}
		if (tmp_fd.events & (POLLOUT))
		{
			FD_SET(tmp_fd.fd, &m_write_fd);
		}
		{
			FD_SET(tmp_fd.fd, &m_error_fd);
		}
		max_fd++;
	}

	timeval time_out;
	time_out.tv_sec = timeoutMs / 1000;
	time_out.tv_sec = (int)(timeoutMs % 1000) * 1000;

	int active_num = ::select(max_fd, &m_read_fd, &m_write_fd, &m_error_fd, &time_out);
	if (active_num > 0)
	{
		fill_active_channels(active_num, active_channel_list);
	}
}


void Poller::fill_active_channels(int active_num, std::vector<Channel*>& active_channel_list)
{
	for (auto iter : m_pollFd_list)
	{
		pollfd& tmp_fd = iter.second;
		int revent = 0;
		if (FD_ISSET(tmp_fd.fd, &m_read_fd))
		{
			revent |= POLLIN;
		}
		if (FD_ISSET(tmp_fd.fd, &m_write_fd))
		{
			revent |= POLLOUT;
		}


		if (revent > 0)
		{
			--active_num;

			auto iter_channel = m_channel_list.find(tmp_fd.fd);
			if (iter_channel == m_channel_list.end())
			{
				continue;
			}

			Channel* channel = iter_channel->second;
			channel->set_revent(revent);
			active_channel_list.push_back(channel);
		}

		if (active_num <= 0)
		{
			break;
		}
	}
}