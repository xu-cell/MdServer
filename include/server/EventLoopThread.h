#ifndef EVENTLOOPTHREAD_H
#define EVENTLOOPTHREAD_H
#include "noncopyable.h"
#include "Thread.h"
#include "EventLoop.h"
#include "Condition.h"
#include "MutexLock.h"

//启动线程，开启事件循环
class EventLoopThread : noncopyable
{
public:
    EventLoopThread();
    ~EventLoopThread();
    EventLoop* startLoop();

private:
    void threadFunc();
    Thread thread_;
    EventLoop* loop_;
    bool exiting_;
    MutexLock mutex_;
    Condition cond_;
};




#endif