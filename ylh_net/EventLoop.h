#pragma once

#include <vector>

class Channel;
class Poller;

class EventLoop
{
public:
	EventLoop();
	~EventLoop();

	void updateChannel(Channel* channel);


private:
	Poller*	m_pooler;

	std::vector<Channel*> m_active_channel_list;
};

