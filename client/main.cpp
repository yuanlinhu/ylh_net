
#include "EventLoop.h"
#include "TcpClient.h"
#include "Sock.h"

#include <string>
using std::string;

int main()
{
	Sock::init();

	EventLoop event_loop;

	TcpClient client(&event_loop);
	client.connect(string("192.168.1.133"), 4567);



	event_loop.loop();

	return 0;
}