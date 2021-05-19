#include "EventLoopThread.h"
#include "EventLoop.h"


EventLoopThread::EventLoopThread(const ThreadInitCallback& cb/* = ThreadInitCallback()*/)
{
	m_call_back = cb;
}


EventLoopThread::~EventLoopThread()
{
}

EventLoop* EventLoopThread::startLoop()
{
	m_thread = new std::thread(std::bind(&EventLoopThread::thread_func, this));
	m_thread_started = true;

	{
		std::unique_lock<std::mutex> lck(m_mutex);
		while (m_event_loop == NULL)
		{
			m_condition.wait(lck);
		}
	}

	return m_event_loop;
}

void EventLoopThread::thread_func()
{
	EventLoop loop;
	if (m_call_back)
	{
		m_call_back(&loop);
	}

	{
		std::unique_lock<std::mutex> lck(m_mutex);
		m_event_loop = &loop;
		m_condition.notify_one();
	}

	loop.loop();
	m_event_loop = nullptr;
}
