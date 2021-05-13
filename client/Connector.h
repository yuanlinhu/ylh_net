#pragma once

class EventLoop;
class Channel;
class Sock;


enum States 
{ 
	kDisconnected, 
	kConnecting, 
	kConnected 
};

class Connector
{
public:
	explicit Connector(EventLoop* loop);
	~Connector();

	void start();
	void connect();


private:
	EventLoop* m_owner_loop = nullptr;
	States m_connect_state = kDisconnected;
	
	Channel* m_channel = nullptr;
	Sock* m_connect_sock = nullptr;


};

