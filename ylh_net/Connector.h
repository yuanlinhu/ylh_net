#pragma once

#include <functional>
#include <string>
using std::string;

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
	typedef std::function<void(int sockfd)> NewConnectionCallback;

public:
	explicit Connector(EventLoop* loop);
	~Connector();

	void connect(string& ip, int port);


	void handle_writing();




	void setNewConnectionCallback(const NewConnectionCallback& cb) { newConnectionCallback_ = cb; }

private:
	void start();

private:
	EventLoop* m_owner_loop = nullptr;
	States m_connect_state = kDisconnected;
	
	Channel* m_channel = nullptr;
	Sock* m_connect_sock = nullptr;
	NewConnectionCallback newConnectionCallback_;

};

