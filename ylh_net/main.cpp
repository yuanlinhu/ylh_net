#include <windows.h>
#include "Sock.h"
#include "EventLoop.h"
#include "Acceptor.h"

int main()
{
	Sock::init();

	EventLoop event_loop;
	Acceptor acceptor(&event_loop, 4567, true);
	acceptor.listen();

	event_loop.loop();
	return 0;
}