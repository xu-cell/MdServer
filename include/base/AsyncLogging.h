/*启动一个线程 将日志写入日志文件*/
#ifndef ASYNCLOGGING_H
#define ASYNCLOGGING_H
#include "noncopyable.h"
#include <functional>
#include <vector>
#include "CountDownLatch.h"
#include "LogStream.h"
#include "MutexLock.h"
#include "Thread.h"
#include <string>
class AsyncLogging : noncopyable
{
public:
        AsyncLogging(const std::string basename,int flushInterval = 2);
        ~AsyncLogging()
        {
            if(running_) stop();
        }
        void append(const char* logline, int len);

        void start()
        {
            running_ = true;
            thread_ .start();
            latch_.wait();
        }
        void stop()
        {
            running_ = false;
            cond_.notify();
            thread_.join();
        }


private:
    void threadFunc();
    using Buffer = FixedBuffer<kLargeBuffer>;
    using BufferPtr = std::shared_ptr<Buffer>;
    using BufferVector = std::vector<std::shared_ptr<Buffer>>;
   

    Condition cond_;
    MutexLock mutex_;
    Thread thread_;
    std::string basename_;
    bool running_;
    const int flushInterval_;
    CountDownLatch latch_;
    BufferVector buffers_; //已填满的buffer pool
    BufferPtr nextBuffer_; //下一个可供交换的buffer
    BufferPtr currentBuffer_; //当前写的buffer
    
};


#endif