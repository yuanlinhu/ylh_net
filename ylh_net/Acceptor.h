#pragma once

class EventLoop;
class Channel;
class Sock;

class Acceptor
{
public:
	explicit Acceptor(EventLoop* loop, int port, bool reuse);
	~Acceptor();

	void listen();


private:
	EventLoop* m_ownerEventLoop = nullptr;
	Channel* m_accept_channel = nullptr;
	Sock* m_accept_sock = nullptr;
};

