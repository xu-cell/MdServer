#ifndef SERVER_H
#define SERVER_H

#include <memory>
#include "Channel.h"
#include "EventLoop.h"
#include "EventLoopThreadPool.h"

class Server
{
public:
    Server(EventLoop* baseloop,int threadnum,int port);
    ~Server(){}

    void start();
    void handNewConn();
    void handThisConn(){loop_->updatePoller(acceptChannel_,0);}
    

private:
    EventLoop* loop_;
    std::unique_ptr<EventLoopThreadPool>eventLoopThreadPool_;
    bool started_;
    int threadNum_;
    std::shared_ptr<Channel>acceptChannel_;
    int port_;
    int listenFd_;
    static const int MAXFDS = 100000;
};

#endif