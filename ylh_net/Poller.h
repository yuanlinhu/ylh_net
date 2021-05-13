#pragma once

#include <map>

class Channel;
struct pollfd;

class Poller
{
public:
	Poller();
	~Poller();

	void updateChannel(Channel* channel);


private:
	std::map<int, Channel*> m_channel_list;

	std::map<int, pollfd> m_pollFd_list;
};

