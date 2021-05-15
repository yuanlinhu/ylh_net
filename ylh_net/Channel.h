#pragma once

#include <functional>
//#include <timestamp.h>

#include "Sock.h"

class EventLoop;

const int kNoneEvent = 0;
const int kReadEvent = POLLIN | POLLPRI;
const int kWriteEvent = POLLOUT;

class Channel
{
	typedef std::function<void()> EventCallback;
	typedef std::function<void(int)> ReadEventCallback;

public:
	Channel(Sock* sock, EventLoop* loop);
	~Channel();

	void enableReading();
	void disableReading();

	void enableWriting();
	void disableWriting();

	void disableAll();
	

	void update();

	int get_fd() { return m_sock->get_fd(); }

	void set_revent(int revt) { m_events = revt; }
	int get_events() { return m_events; }


	void handle_event();


	void setReadCallback(const ReadEventCallback& cb)
	{
		readCallback_ = cb;
	}
	void setWriteCallback(const EventCallback& cb)
	{
		writeCallback_ = cb;
	}
	void setCloseCallback(const EventCallback& cb)
	{
		closeCallback_ = cb;
	}
	void setErrorCallback(const EventCallback& cb)
	{
		errorCallback_ = cb;
	}


private:
	virtual void handle_read();
	virtual void handle_write();
	virtual void handle_close();
	

private:

	int m_events = 0;

	EventLoop* m_owner_loop = nullptr;
	Sock* m_sock = nullptr;



	ReadEventCallback readCallback_;
	EventCallback writeCallback_;
	EventCallback closeCallback_;
	EventCallback errorCallback_;
};

