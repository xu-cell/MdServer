#include "EventLoopThreadPool.h"

EventLoopThreadPool::EventLoopThreadPool(EventLoop* baseloop,int numthread)
    :baseLoop_(baseloop)
    ,numThreads_(numthread)
    ,started_(false)
    ,next_(0)
{
    if(numThreads_ < 0)
    {
        LOG << "numThreads <= 0";
        abort();
    }
}

void EventLoopThreadPool::start()
{
    baseLoop_->assertInLoopThread();
    started_ = true;
    for(int i = 0; i < numThreads_;i++)
    {
        std::shared_ptr<EventLoopThread> t(new EventLoopThread());
        threads_.push_back(t);
        loops_.push_back(t->startLoop());
    }
}
EventLoop *EventLoopThreadPool::getNextLoop()
{
    baseLoop_->assertInLoopThread();
    assert(started_);
    EventLoop* loop = baseLoop_;
    if(loops_.size())
    {
        loop = loops_[next_];
        next_ = (next_+1) % numThreads_;
    }    
    return loop;
    
}
