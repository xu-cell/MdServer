#ifndef EVENTLOOPTHREADPOOL_H
#define EVENTLOOPTHREADPOOL_H
#include "EventLoop.h"
#include "EventLoopThread.h"
#include <vector>
#include <memory>
#include "noncopyable.h"
#include "Logging.h"


class EventLoopThreadPool
{
private:
    std::vector<EventLoop*>loops_;
    std::vector<std::shared_ptr<EventLoopThread>>threads_;
    int numThreads_;
    int next_;
    bool started_;
    EventLoop* baseLoop_;

public:
    EventLoopThreadPool(EventLoop* baseLoop, int numThreads);
    ~EventLoopThreadPool(){ LOG << "~EventLoopThread()";}
    void start();
    EventLoop* getNextLoop();
};
#endif