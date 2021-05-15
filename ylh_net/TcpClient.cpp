#include "TcpClient.h"
#include "Connector.h"
#include "TcpConnection.h"
#include "InetAddress.h"

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

	m_tcp_connection = new TcpConnection();

}