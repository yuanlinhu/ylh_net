#include "ConnectChannel.h"



ConnectChannel::ConnectChannel(Sock* sock, EventLoop* loop)
	:Channel(sock, loop)
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
