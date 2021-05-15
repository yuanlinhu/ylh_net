#pragma once

#include <string>
using std::string;

class EventLoop;
class Connector;
class TcpConnection;



class TcpClient
{
public:
	explicit TcpClient(EventLoop* loop);
	~TcpClient();

	void connect(string& ip, int port);

	void newConnection(int sockfd);

private:
	EventLoop*	m_owner_loop = nullptr;
	Connector* m_connector = nullptr;
	TcpConnection* m_tcp_connection = nullptr;
};

