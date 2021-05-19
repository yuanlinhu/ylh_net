#include "EventLoop.h"
#include "Poller.h"
#include "Channel.h"
#include <iostream>

EventLoop::EventLoop()
:m_wakeup_channel(new Channel(m_wakeup_fd.pipe_read, this))
{
	m_pooler = new Poller();

	m_thread_id = std::this_thread::get_id();

	init_pipe();

	m_wakeup_channel->setReadCallback(std::bind(&EventLoop::handle_read, this));
	m_wakeup_channel->enableReading();
}




EventLoop::~EventLoop()
{
	m_wakeup_channel->disableAll();
	m_wakeup_channel->remove();
}

void EventLoop::init_pipe()
{
	m_wakeup_fd.pipe_read = -1;
	m_wakeup_fd.pipe_write = -1;

	int tcp1, tcp2;
	sockaddr_in name;
	memset(&name, 0, sizeof(name));
	name.sin_family = AF_INET;
	name.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	int namelen = sizeof(name);
	tcp1 = tcp2 = -1;
	int tcp = socket(AF_INET, SOCK_STREAM, 0);
	if (tcp == -1) {
		goto clean;
	}
	if (::bind((SOCKET)tcp, (sockaddr*)&name, namelen) == -1) {
		goto clean;
	}
	if (::listen(tcp, 5) == -1) {
		goto clean;
	}
	if (getsockname(tcp, (sockaddr*)&name, &namelen) == -1) {
		goto clean;
	}
	tcp1 = socket(AF_INET, SOCK_STREAM, 0);
	if (tcp1 == -1) {
		goto clean;
	}
	if (-1 == connect(tcp1, (sockaddr*)&name, namelen)) {
		goto clean;
	}
	tcp2 = accept(tcp, (sockaddr*)&name, &namelen);
	if (tcp2 == -1) {
		goto clean;
	}
	if (closesocket(tcp) == -1) {
		goto clean;
	}
	m_wakeup_fd.pipe_read = tcp1;
	m_wakeup_fd.pipe_write = tcp2;
	//return sock_pipe;
	return;
clean:
	if (tcp != -1) {
		closesocket(tcp);
	}
	if (tcp2 != -1) {
		closesocket(tcp2);
	}
	if (tcp1 != -1) {
		closesocket(tcp1);
	}
	//return sock_pipe;
	return;
}

void EventLoop::loop()
{
	while (false == m_quit)
	{
		m_active_channel_list.clear();
		m_pooler->poll(1, m_active_channel_list);

		for (auto iter : m_active_channel_list)
		{
			(iter)->handle_event();
		}
	}
}

void EventLoop::updateChannel(Channel* channel)
{
	m_pooler->updateChannel(channel);
}

void EventLoop::remove_channel(Channel* channel)
{
	m_pooler->remove_channel(channel);
}

bool EventLoop::isInLoopThread() const
{ 
	auto cur_thread_id = std::this_thread::get_id();
	cout << "m_thread_id: " << m_thread_id 
		<< ", cur_id: "<< cur_thread_id << endl;
	return m_thread_id == std::this_thread::get_id();
}

void EventLoop::runInLoop(const Functor& cb)
{
	if (isInLoopThread())
	{
		cb();
	}
	else
	{
		queueInLoop(cb);
	}
}

void EventLoop::queueInLoop(const Functor& cb)
{
	{
		std::unique_lock<std::mutex> lck(m_mutex);
		m_pending_functors.push_back(cb);
	}

	if (false == isInLoopThread() || m_call_pending_functors)
	{
		wakeup();
	}
}

void EventLoop::wakeup()
{
	uint64_t one = 1;
	int n = ::send(m_wakeup_fd.pipe_write, (char*)&one, sizeof(one), 0);
	if (n != sizeof(one))
	{
		cout << "EventLoop::wakeup() writes" << n << " bytes instead of 8(int64_t)";
	}
}

void EventLoop::handle_read()
{
	uint64_t one = 1;
	int n = ::recv(m_wakeup_fd.pipe_read, (char*)&one, sizeof(one), 0);
	if (n != sizeof(one))
	{
		cout << "EventLoop::wakeup() writes" << n << " bytes instead of 8(int64_t)";
	}
}