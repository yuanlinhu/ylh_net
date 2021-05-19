#include <windows.h>
#include "Sock.h"
#include "EventLoop.h"
#include "Acceptor.h"
#include "TcpServer.h"

#include <iostream>
#include <thread>
#include <functional>
#include "EventLoopThread.h"

using namespace std;

void print(EventLoop*)
{
	thread::id tid = std::this_thread::get_id();
	cout << "threadId: " << tid << endl;
}

void test_event_loop()
{

	EventLoop event_loop;
	TcpServer server(&event_loop);
	server.listen(4567);
	event_loop.loop();
}

void test_event_loop_thread()
{
	print(NULL);

	{
		EventLoopThread th1;

		EventLoop* event_loop = th1.startLoop();
		event_loop->runInLoop(std::bind(print, event_loop));
		std::this_thread::sleep_for(std::chrono::seconds(5));
	}
}

int main()
{
	Sock::init();

	//test_event_loop();

	test_event_loop_thread();

	return 0;
}