#include <windows.h>
#include "Sock.h"
#include "EventLoop.h"
#include "Acceptor.h"

int main()
{
	Sock::init();

	EventLoop event_loop;
	Acceptor acceptor(&event_loop, 1111, true);
	acceptor.listen();

	event_loop.loop();
	return 0;
}