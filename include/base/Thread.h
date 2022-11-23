#ifndef THREAD_H
#define THREAD_H
#include <memory>
#include <pthread.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <functional>
#include <string>
#include "CountDownLatch.h"
#include "noncopyable.h"

class Thread : noncopyable
{
public:
    using ThreadFunc = std::function<void()>;
    explicit Thread(const ThreadFunc&,const std::string& name = std::string());
    ~Thread();

    void start();
    int join();
    bool started() const {return started_;}
    pid_t tid() const {return tid_;}

    const std::string& name()const{return name_;}


private:
    void setDefaultName();
    pid_t tid_;
    std::string name_;
    bool started_;
    bool joined_;
    pthread_t pthreadId_;
    ThreadFunc func_;
    CountDownLatch latch_; //同步辅助，一般用于主线程通知众多的子线程开始运行
};


#endif