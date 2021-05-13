#pragma once

#include <map>
#include <vector>
#include <WinSock2.h>

class Channel;
struct pollfd;

class Poller
{
public:
	Poller();
	~Poller();

	void updateChannel(Channel* channel);

	void poll(int timeoutMs, std::vector<Channel*>& active_channel_list);

private:

	void fill_active_channels(int active_num, std::vector<Channel*>& active_channel_list);
private:
	std::map<int, Channel*> m_channel_list;

	std::map<int, pollfd> m_pollFd_list;

	fd_set m_read_fd;
	fd_set m_write_fd;
	fd_set m_error_fd;
};

