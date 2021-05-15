#pragma once

#include <string>
#include "InetAddress.h"

using std::string;


class EventLoop;
class Channel;
class Sock;


class TcpConnection
{
public:
	TcpConnection(int fd, const InetAddress& addr, EventLoop* loop);
	~TcpConnection();

	void send(string& msg);


	void handleRead(int receiveTime);
	void handleWrite();

private:
	int m_fd = 0;
	InetAddress m_addr;
	Sock* m_sock = nullptr;
	EventLoop* m_owner_loop = nullptr;
	Channel* m_channel = nullptr;
};

