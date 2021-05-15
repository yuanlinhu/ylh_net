#ifndef CALM_NET_INETADDRESS_H_
#define CALM_NET_INETADDRESS_H_

#include <string>
#include <WinSock2.h>


using std::string;

//namespace calm
//{
//	namespace net
//	{
		class InetAddress
		{
		public:
			// mostly used in tcp server listening
			// loopbackOnly is refer to 127.0.0.1
			explicit InetAddress(uint16_t port = 0, bool loopbackOnly = false);
			explicit InetAddress(const struct sockaddr_in& addr)
				:addr_(addr)
			{}
			void setSockAddrIn(const struct sockaddr_in& addr) { addr_ = addr; }
			ADDRESS_FAMILY family()const { return addr_.sin_family; }
			//string toIp() const;
			//string toIpPort() const;
			//uint16_t toPort() const;
			////const struct sockaddr* getSockaddr() const  { return sockets::sockaddr_cast(&addr_); }

			//uint32_t ipNetEndian() const;
			//uint16_t portNetEndian() const { return addr_.sin_port; };
		private:
			struct sockaddr_in addr_;
		};
//	}//end namespace net
//}// end namespace calm

#endif //CALM_NET_INETADDRESS_H_