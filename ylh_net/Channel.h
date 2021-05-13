#pragma once

#include "Sock.h"

class EventLoop;

const int kNoneEvent = 0;
const int kReadEvent = POLLIN | POLLPRI;
const int kWriteEvent = POLLOUT;

class Channel
{
public:
	Channel(Sock* sock, EventLoop* loop);
	~Channel();

	void enableReading();
	void disableReading();

	void update();

private:

	int m_events = 0;

	EventLoop* m_owner_loop = nullptr;


	Sock* m_sock = nullptr;
	int m_fd;
};

