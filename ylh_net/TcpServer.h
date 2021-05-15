#pragma once
#include <map>
#include "InetAddress.h"

class EventLoop;
class Acceptor;
class TcpConnection;


class TcpServer
{
public:
	explicit TcpServer(EventLoop* loop);
	~TcpServer();


	void listen(int port);

	void handle_connection(int sockfd, const InetAddress& addr);

private:
	EventLoop* m_owner_loop = nullptr;
	Acceptor* m_acceptor = nullptr;
	std::map<int, TcpConnection*> m_map_tcp_connection;

};

