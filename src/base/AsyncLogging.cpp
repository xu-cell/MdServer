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
//具体的写操作
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
            currentBuffer_ = std::move(nextBuffer_);
        }
        else
        {
            currentBuffer_.reset(new Buffer);
        }
        currentBuffer_->append(logline,len);
        cond_.notify();
    }
}
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
        {
            MutexLockGuard lock(mutex_);
            if(buffers_.empty())
            {
                cond_.waitForSeconds(flushInterval_);
            }

            buffers_.push_back(currentBuffer_);
            currentBuffer_.reset();
            currentBuffer_ = std::move(newBuffer1);

            buffersToWrite.swap(buffers_);
            if(!nextBuffer_)
            {
                nextBuffer_ = std::move(newBuffer2);
            }
        }

        assert(!buffersToWrite.empty());

        if(buffersToWrite.size() > 25)
        {
            buffersToWrite.erase(buffersToWrite.begin() + 2,buffersToWrite.end());     
        }
        for(size_t i = 0;i < buffersToWrite.size();i++)
        {
            output.append(buffersToWrite[i]->data(),buffersToWrite[i]->length());
        }
        if(buffersToWrite.size() > 2)
        {
            buffersToWrite.resize(2);
        }
        //当前写vector中有两个buffer在使用。newBuffer没有使用
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