#ifndef CHANNEL_H
#define CHANNEL_H
#include "noncopyable.h"
#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include "Timer.h"
/*
类分析：
channel封装了我们的fd.以及感兴趣的事件和具体发生的事件。
每个channel属于一个事件循环EventLoop.一个事件循环管理着很多的channel

对于我们的http服务器来说，一个http连接对应一个channel同时对应于一个一个i/o线程。
一个i/o线程开启一个事件循环，就可以监听多个fd,维护多个连接，处理多个http访问

我们可以给对应的channel设置回调，当事件发生的时候，就可以执行相应的回调。比如读事件，写事件，以及对于http服务器来说的conn事件

*/
class EventLoop;
class HttpData;
class Channel : noncopyable
{
public:
    using Callback = std::function<void()>;
    Channel(EventLoop* loop);
    Channel(EventLoop* loop,int fd);
    ~Channel();

    void setfd(int fd);
    int getfd();

    void setHolder(std::shared_ptr<HttpData> holder);
    std::shared_ptr<HttpData> getHolder();

    void setReadHandler(Callback cb);
    void setWriteHandler(Callback cb);
    void setErroeHandler(Callback cb);
    void setConnHandler(Callback cb);
    //检测revents上的具体事件，回调绑定的操作
    void handleEvents();
    //具体的操作
    void handleRead();
    void handleWrite();
    void handleError(int fd,int err_num,std::string short_msg);
    void handleConn();
    //为channel设置感兴趣的事件
    void setRevents(int ev);
    void setEvents(int ev);
    int &getEvents();

    bool EqualAndUpdateLastEvents();
    int getLastEvents();

private:
    EventLoop *loop_;
    int events_;
    int revents_;
    int lastEvents_;
    int fd_;
    //每一个channel都属于一个Eventloop，使用弱指针，能够监视上层持有该对象的状态,
    //通过提升，得到持有该channel的对象，一个http连接对应一个channel
    std::weak_ptr<HttpData> holder_;

    // http解析函数
    int parse_URI();
    int parse_Headers();
    int analysisRequest();

    //事件发生时，具体的回调操作
    Callback readHandler_;
    Callback writeHandler_;
    Callback errorHandler_;
    Callback connHandler_;
};

using SP_Channel = std::shared_ptr<Channel>;

#endif