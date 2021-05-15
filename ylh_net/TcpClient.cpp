#include "TcpClient.h"
#include "Connector.h"
#include "TcpConnection.h"
#include "InetAddress.h"
#include <iostream>

using namespace std;

TcpClient::TcpClient(EventLoop* loop)
	:m_owner_loop(loop)
{
	m_connector = new Connector(m_owner_loop);
	m_connector->setNewConnectionCallback(std::bind(&TcpClient::newConnection, this, std::placeholders::_1));
}


TcpClient::~TcpClient()
{
}

void TcpClient::connect(string& ip, int port)
{
	m_connector->connect(ip, port);
}

void TcpClient::newConnection(int sockfd)
{
	InetAddress peerAddr;

	m_tcp_connection = new TcpConnection(sockfd, peerAddr, m_owner_loop);

	//m_tcp_connection->send(string("hello_server"));
	cout << "连接服务器成功 fd:" << sockfd << endl;
}