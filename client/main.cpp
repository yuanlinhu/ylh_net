
#include "EventLoop.h"
#include "Connector.h"
#include "Sock.h"

#include <string>
using std::string;

int main()
{
	Sock::init();

	EventLoop event_loop;

	Connector conn(&event_loop);
	conn.connect(string("192.168.1.133"), 4567);



	event_loop.loop();

	return 0;
}