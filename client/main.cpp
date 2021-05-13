
#include "EventLoop.h"
#include "Connector.h"
#include "Sock.h"

int main()
{
	Sock::init();

	EventLoop event_loop;

	Connector conn(&event_loop);
	conn.start();


	event_loop.loop();

	return 0;
}