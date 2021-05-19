#include "ConnectChannel.h"



ConnectChannel::ConnectChannel(Sock* sock, EventLoop* loop)
	:Channel(loop, sock)
{

}


ConnectChannel::~ConnectChannel()
{

}


void ConnectChannel::handle_read()
{

}

void ConnectChannel::handle_write()
{

}

void ConnectChannel::handle_close()
{

}
