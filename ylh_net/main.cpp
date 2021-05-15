#include <windows.h>
#include "Sock.h"
#include "EventLoop.h"
#include "Acceptor.h"
#include "TcpServer.h"

int main()
{
	Sock::init();

	EventLoop event_loop;
	//Acceptor acceptor(&event_loop, 4567, true);
	//acceptor.listen();

	TcpServer server(&event_loop);
	server.listen(4567);

	event_loop.loop();
	return 0;
}