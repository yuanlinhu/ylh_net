#include <windows.h>
#include "Sock.h"
#include "EventLoop.h"
#include "Acceptor.h"

int main()
{
	Sock::init();

	EventLoop loop;
	Acceptor acceptor(&loop, 1111, true);
	acceptor.listen();
	return 0;
}