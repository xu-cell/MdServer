#ifndef EVENTLOOP_H
#define EVENTLOOP_H
#include <atomic>
#include <functional>
#include <memory>
#include <vector>
#include "Channel.h"
#include "Epoll.h"
#include "Util.h"
#include "CurrentThread.h"
#include "Logging.h"
#include "Thread.h"
#include <iostream>

using namespace std;



class EventLoop
{
public:
    using Functor = function<void()>;
    EventLoop();
    ~EventLoop();
    void loop();
    void quit();
    void runInLoop(Functor &&cb);
    void queueInLoop(Functor &&cb);
    bool isInLoopThread() const {return threadId_ == CurrentThread::tid();}
     void assertInLoopThread() { assert(isInLoopThread()); }
    void shutdown(shared_ptr<Channel>channel){ shutDownWR(channel->getfd());}
    void removeFromPoller(shared_ptr<Channel>channel)
    {
        poller_->epoll_del(channel);
    }
    void updatePoller(shared_ptr<Channel>channel,int timeout = 0)
    {
        poller_->epoll_mod(channel,timeout);
    }
    void addToPoller(shared_ptr<Channel>channel,int timeout = 0)
    {
        poller_->epoll_add(channel,timeout);
    }


private:
    atomic_bool looping_; 
    atomic_bool quit_;
    atomic_bool callingPengingFunctors_;
    atomic_bool eventHandling_;

    int wakeupfd_;
    shared_ptr<Channel>pwakeupChannel_;
    shared_ptr<Epoll>poller_;
    vector<Functor>pendingFunctors_;
    const pid_t threadId_;
    mutable MutexLock mutex_;

    void wakeup();
    void handleRead();
    void doPendingFunctors();
    void handleConn();

};



#endif