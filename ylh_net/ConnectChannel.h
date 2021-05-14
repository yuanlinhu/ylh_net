#pragma once

#include "Channel.h"

class ConnectChannel : public Channel
{
public:
	ConnectChannel(Sock* sock, EventLoop* loop);
	~ConnectChannel();


	virtual void handle_read();
	virtual void handle_write();
	virtual void handle_close();
};

