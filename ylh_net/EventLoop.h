#pragma once

#include <vector>
#include <thread>
#include <mutex>

using std::thread;
using namespace std;


class Channel;
class Poller;

struct stPipe
{
	int pipe_read = 0;
	int pipe_write = 0;
};


class EventLoop
{
	typedef std::function<void()> Functor;
public:
	EventLoop();
	~EventLoop();

	void loop();

	void updateChannel(Channel* channel);

	void remove_channel(Channel* channel);


	void runInLoop(const Functor& cb);
	void queueInLoop(const Functor& cb);

private:
	bool isInLoopThread() const;
	void wakeup();
	void handle_read();

	void init_pipe();


private:
	Poller*	m_pooler;
	thread::id m_thread_id;

	std::mutex m_mutex;
	std::vector<Functor> m_pending_functors;
	bool m_call_pending_functors = false;

	stPipe m_wakeup_fd;
	std::shared_ptr<Channel> m_wakeup_channel;

	std::vector<Channel*> m_active_channel_list;
	bool m_quit = false;
};

