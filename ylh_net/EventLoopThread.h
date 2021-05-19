#pragma once

#include <functional>
#include <thread>
#include <mutex>

class EventLoop;

class EventLoopThread
{
	typedef std::function<void(EventLoop*)> ThreadInitCallback;
public:
	EventLoopThread(const ThreadInitCallback& cb = ThreadInitCallback());
	~EventLoopThread();


	EventLoop* startLoop();

private:
	void thread_func();


private:
	EventLoop* m_event_loop = nullptr;
	std::thread* m_thread;
	bool m_thread_started = false;

	std::mutex m_mutex;
	std::condition_variable m_condition;
	ThreadInitCallback m_call_back = nullptr;
};

