//异步写日志
#include "AsyncLogging.h"
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <functional>
#include "LogFile.h"

AsyncLogging::AsyncLogging(const std::string basename, int flushInterval)
    :flushInterval_(flushInterval)
    ,running_(false)
    ,basename_(basename)
    ,thread_(std::bind(&AsyncLogging::threadFunc,this),"Logging")
    ,mutex_()
    ,cond_(mutex_)
    ,currentBuffer_(new Buffer)
    ,nextBuffer_(new Buffer)
    ,buffers_()
    ,latch_(1)
{
    assert(basename.size() > 0);
    currentBuffer_->bzero();
    nextBuffer_->bzero();
    buffers_.reserve(6);
}
//前端调用具体的写操作
void AsyncLogging::append(const char *logline, int len)
{
    MutexLockGuard lock(mutex_);
    if(currentBuffer_->avail() > len)
    {
        currentBuffer_->append(logline,len);
    }
    else
    {
        //前端线程写满了就加入到vector中
        buffers_.push_back(currentBuffer_);
        //重置指针
        currentBuffer_.reset(); 
        if(nextBuffer_)
        {
            //移动指针
            currentBuffer_ = std::move(nextBuffer_);
        }
        else
        {
            //前端发送过快。新开buffer，很少会发生这个情况
            currentBuffer_.reset(new Buffer);
        }
        //追加日志
        currentBuffer_->append(logline,len);
        //唤醒后端开始写日志
        cond_.notify();
    }
}
//后端的写操作
void AsyncLogging::threadFunc()
{
    assert(running_ == true);
    latch_.countDown();
    LogFile output(basename_);
    BufferPtr newBuffer1(new Buffer);
    BufferPtr newBuffer2(new Buffer);
    newBuffer1->bzero();
    newBuffer2->bzero();
    //维护两个写缓冲区
    BufferVector buffersToWrite;
    buffersToWrite.reserve(16);
    while(running_)
    {
        assert(newBuffer1 && newBuffer1->length() == 0);
        assert(newBuffer2 && newBuffer2->length() == 0);
        assert(buffersToWrite.empty());
        
        //临界区交换：1：超时触发 2.前端写满buffer。
        {
            MutexLockGuard lock(mutex_);
            if(buffers_.empty())
            {
                //等待时间有上限，不一定非要写满才交换，就一定的时间就交换刷新
                cond_.waitForSeconds(flushInterval_);
            }
            // 这个buffer实际就是前端的nextBuffer_,现在buffers_里面就是一个满的buffer加一个可能是满的buffer
            buffers_.push_back(currentBuffer_);
            currentBuffer_.reset();
            currentBuffer_ = std::move(newBuffer1);
            
            //交换之后buffersTo存放着前端写满了的buffer的指针，buffers_里面还没有buffer的指针。等待前端加入。
            buffersToWrite.swap(buffers_);
            if(!nextBuffer_)
            {
                nextBuffer_ = std::move(newBuffer2);
            }
        }

        assert(!buffersToWrite.empty());
        //前端写太快，后面的所有直接扔掉，保留最开始的一部分信息供debug.
        if(buffersToWrite.size() > 25)
        {
            buffersToWrite.erase(buffersToWrite.begin() + 2,buffersToWrite.end());     
        }
        //具体的写文件操作
        for(size_t i = 0;i < buffersToWrite.size();i++)
        {
            output.append(buffersToWrite[i]->data(),buffersToWrite[i]->length());
        }
        if(buffersToWrite.size() > 2)
        {
            buffersToWrite.resize(2);
        }
        //写完之后。就有两个新的缓冲区可供交换
        if(!newBuffer1)
        {
            assert(!buffersToWrite.empty());
            newBuffer1 = buffersToWrite.back();
            buffersToWrite.pop_back();
            newBuffer1->reset();
        }
        if(!newBuffer2)
        {
            assert(!buffersToWrite.empty());
            newBuffer2 = buffersToWrite.back();
            buffersToWrite.pop_back();
            newBuffer2->reset();
        }
        buffersToWrite.clear();
        output.flush();
    }
    output.flush();
}