#pragma once

#include "InetAddress.h"
#include <functional>

class EventLoop;
class Channel;
class Sock;


class Acceptor
{
	typedef std::function<void(int sockfd, const InetAddress&)> NewConnectionCallback;

public:
	explicit Acceptor(EventLoop* loop, bool reuse);
	~Acceptor();

	void listen(int port);


	void handle_read(int fd);

	void setNewConnectionCallback(const NewConnectionCallback& call_back) { newConnectionCallback_ = call_back; }
private:
	EventLoop* m_ownerEventLoop = nullptr;
	Channel* m_accept_channel = nullptr;
	Sock* m_accept_sock = nullptr;


	NewConnectionCallback newConnectionCallback_;
};

