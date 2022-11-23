#ifndef EPOLL_H
#define EPOLL_H

#include <sys/epoll.h>
#include <memory>
#include <unordered_map>
#include <vector>
#include "Channel.h"
#include "HttpData.h"
#include "Timer.h"

class Epoll
{
public:
    Epoll();
    ~Epoll();
    void epoll_add(SP_Channel request, int timeout);
    void epoll_mod(SP_Channel request, int timeout);
    void epoll_del(SP_Channel request);
    //开启事件循环
    std::vector<std::shared_ptr<Channel>> poll();
    //返回活跃事件的Channel数组
    std::vector<std::shared_ptr<Channel>> getEventsRequest(int events_num);

    void add_timer(std::shared_ptr<Channel> request,int timeout);

    int getEpollFd();

    void handleExpired();
private:
    static const int MAXFDS = 100000;
    int epollfd_;
    std::vector<epoll_event>events_; 
    std::shared_ptr<Channel> fd2chan_[MAXFDS]; //一个事件循环/一个io线程所管理的所有channel
    std::shared_ptr<HttpData> fd2http_[MAXFDS]; //一个事件循环/一个io线程所管理的所有连接
    TimerManager timerManager_;
};




#endif