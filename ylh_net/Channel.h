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

	int get_fd() { return m_sock->get_fd(); }

	int get_events() { return m_events; }

private:

	int m_events = 0;

	EventLoop* m_owner_loop = nullptr;


	Sock* m_sock = nullptr;
};

