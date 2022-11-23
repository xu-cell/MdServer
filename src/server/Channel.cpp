#include "Channel.h"
#include <sys/epoll.h>
#include <unistd.h>

Channel::Channel(EventLoop *loop)
    :loop_(loop)
    ,fd_(0)
    ,revents_(0)
    ,events_(0)

{
}
Channel::Channel(EventLoop *loop, int fd)
    :loop_(loop)
    ,fd_(fd)
    ,revents_(0)
    ,events_(0)
{
}
Channel::~Channel()
{
}

void Channel::setfd(int fd)
{
    fd_ = fd;
}
int Channel::getfd()
{
    return fd_;
}

void Channel::setHolder(std::shared_ptr<HttpData> holder)
{
    holder_ = holder;
}
std::shared_ptr<HttpData> Channel::getHolder()
{
    //将弱指针提升为强指针获取http连接的对象
    std::shared_ptr<HttpData>ret(holder_.lock());
    return ret;
}
//使用c++11 move 实现资源的转移
void Channel::setReadHandler(Callback cb)
{
    readHandler_ = std::move(cb);
}
void Channel::setWriteHandler(Callback cb)
{
    writeHandler_ = std::move(cb);
}
void Channel::setErroeHandler(Callback cb)
{
    errorHandler_ = std::move(cb);
}
void Channel::setConnHandler(Callback cb)
{
    connHandler_ = std::move(cb);
}
//检测revents上的具体事件，回调绑定的操作
void Channel::handleEvents()
{
    events_ = 0;
    if((revents_ & EPOLLHUP) && !(revents_ & EPOLLIN))
    {
        events_ = 0;
        return;
    }
    if(revents_ & EPOLLERR)
    {
        if(errorHandler_) errorHandler_();
        events_ = 0;
        return;
    }
    if(revents_ &(EPOLLIN | EPOLLPRI | EPOLLRDHUP))
    {
        handleRead();
    }
    if(revents_ & EPOLLOUT)
    {
        handleWrite();
    }
    handleConn();
}
//具体的操作
void Channel::handleRead()
{
    if(readHandler_)
    {
        readHandler_();
    }
}
void Channel::handleWrite()
{
    if(writeHandler_)
    {
        readHandler_();
    }
}
void Channel::handleError(int fd, int err_num, std::string short_msg)
{
    if(errorHandler_)
    {
        errorHandler_();
    }
}
void Channel::handleConn()
{
    if(connHandler_)
    {
        connHandler_();
    }
}
//为channel设置感兴趣的事件
void Channel::setRevents(__uint32_t ev)
{
    revents_ = ev;
}
void Channel::setEvents(__uint32_t ev)
{
    events_ = ev;
}
__uint32_t &Channel::getEvents()
{
    return events_;
}

bool Channel::EqualAndUpdateLastEvents()
{
    bool ret = (lastEvents_ == events_);
    lastEvents_ = events_;
    return ret;
}
__uint32_t Channel::getLastEvents()
{
    return lastEvents_;
}