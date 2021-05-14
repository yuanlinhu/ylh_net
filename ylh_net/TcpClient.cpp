#include "TcpClient.h"
#include "Connector.h"


TcpClient::TcpClient(EventLoop* loop)
	:m_owner_loop(loop)
{
	m_connector = new Connector(m_owner_loop);
}


TcpClient::~TcpClient()
{
}

void TcpClient::connect(string& ip, int port)
{
	m_connector->connect(ip, port);
}
