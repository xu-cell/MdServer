#include "EventLoop.h"
#include <sys/epoll.h>
#include <sys/eventfd.h>
#include <iostream>
#include "Util.h"
#include "Logging.h"
using namespace std;
//防止一个线程创建多个EventLoop
__thread EventLoop* t_loopInThisThread = 0;
//利用系统函数创建wakeupfd，能够进行进程间的通信
int creadteEventfd()
{
    int wakeupfd = eventfd(0,EFD_NONBLOCK | EFD_CLOEXEC);
    if(wakeupfd < 0)
    {
        LOG << "Failed in eventfd";
    }
    return wakeupfd;
}


EventLoop::EventLoop()
    :looping_(false)
    ,quit_(false)
    ,poller_(new Epoll())
    ,wakeupfd_(creadteEventfd())
    ,eventHandling_(false)
    ,callingPengingFunctors_(false)
    ,threadId_(CurrentThread::tid())
    ,pwakeupChannel_(new Channel(this,wakeupfd_))
{
    if(t_loopInThisThread)
    {
        //其他的事件循环存在于这个线程,也就是我们的t_loopInThisThread
    }
    else
    {
        t_loopInThisThread = this;
    }
    //为wakeupchannel加入事件循环中。并设置会回调
    pwakeupChannel_->setEvents(EPOLLIN | EPOLLET);
    pwakeupChannel_->setReadHandler(bind(&EventLoop::handleRead,this));
    pwakeupChannel_->setConnHandler(bind(&EventLoop::handleConn,this));
    poller_->epoll_add(pwakeupChannel_,0);
    

}
EventLoop::~EventLoop()
{
    close(wakeupfd_);
    t_loopInThisThread = NULL;
}
//开始事件循环，监听fds。如果有事件相应执行相应的回调
void EventLoop::loop()
{
    assert(!looping_);
    assert(isInLoopThread());
    looping_ = true;
    quit_ = false;
    std::vector<SP_Channel>ret;
    while(!quit_)
    {
        ret.clear();
        ret = poller_->poll();
        eventHandling_ = true;
        for(auto& it :ret)
        {
            it->handleEvents();
        }
        eventHandling_ = false;
        doPendingFunctors();
        poller_->handleExpired();
    }
    looping_ = false;

}
void EventLoop::quit()
{
    quit_ = true;
    if(!isInLoopThread())
    {
        wakeup();
    }
}
void EventLoop::runInLoop(Functor &&cb)
{
    if(isInLoopThread())
    {
        cb();
    }
    else
    {
        queueInLoop(std::move(cb));
    }
}
void EventLoop::queueInLoop(Functor &&cb)
{
    {
        MutexLockGuard lcok(mutex_);
        pendingFunctors_.push_back(std::move(cb));
    }
    if(!isInLoopThread() || callingPengingFunctors_)wakeup();
}
void EventLoop::wakeup()
{
    uint64_t one = 1;
    ssize_t n = writen(wakeupfd_,(char*)(&one), sizeof one);
    if(n != sizeof one)
    {
        LOG << "EventLoop::wakeup() writes " << n << "bytes instead of 8 ";
    }
}
void EventLoop::handleRead()
{
    uint64_t one = 1;
    ssize_t n = readn(wakeupfd_,&one,sizeof one);
    if(n != sizeof one)
    {
         LOG << "EventLoop::wakeup() read " << n << "bytes instead of 8 ";
    }
    pwakeupChannel_->setEvents(EPOLLIN | EPOLLET);

}
//使用局部栈对象，可以避免在原来的vector中操作：回调一个删除一个。这样原来的vector，mainloop可以继续添加回调。不影响调用回调
//每个事件循环当相应的事件发生了时候，事件执行相应的回调，但是我们有一些回调需要当执行到相应的函数的时候才回调
//比如server调用start（）的时候，启动监听的回调，io线程建立连接完了之后，进行建立连接成功的回调
//当移除一个连接时，调用移除连接的回调
//为mainloop行个方便
void EventLoop::doPendingFunctors()
{
    std::vector<Functor>functors;
    callingPengingFunctors_ = true;
    {
        MutexLockGuard lock(mutex_);
        functors.swap(pendingFunctors_);
    }
    for(size_t i = 0; i < functors.size();i++)
    {
        functors[i]();
    }
    callingPengingFunctors_ = false;
}
void EventLoop::handleConn()
{
    updatePoller(pwakeupChannel_,0);
}