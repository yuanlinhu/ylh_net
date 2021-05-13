#pragma once


class Channel;

class EventLoop
{
public:
	EventLoop();
	~EventLoop();

	void updateChannel(Channel* channel);
};

