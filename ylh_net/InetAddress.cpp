#include "InetAddress.h"


InetAddress::InetAddress(uint16_t port /* = 0 */, bool loopbackOnly /* = false */)
{
	memset(&addr_, 0, sizeof(addr_));
	addr_.sin_family = AF_INET;
	if (loopbackOnly)
	{
		addr_.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	}
	else
	{
		addr_.sin_addr.s_addr = htonl(INADDR_ANY);
	}
	addr_.sin_port = htons(port);
}
//InetAddress::InetAddress(StringArg ip, uint16_t port)
//{
//	memset(&addr_, 0, sizeof(addr_));
//	sockets::fromIpPort(ip.c_str(), port, &addr_);
//}
//string InetAddress::toIp() const
//{
//	char buf[64] = { 0 };
//	sockets::toIp(buf, sizeof(buf), getSockaddr());
//	return buf;
//}
//uint16_t InetAddress::toPort() const
//{
//	return sockets::networkToHost16(addr_.sin_port);
//}
//string InetAddress::toIpPort() const
//{
//	char buf[64] = { 0 };
//	sockets::toIpPort(buf, sizeof(buf), getSockaddr());
//	return buf;
//}
//uint32_t InetAddress::ipNetEndian() const
//{
//	return addr_.sin_addr.s_addr;
//}
