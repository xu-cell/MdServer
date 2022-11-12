#ifndef MUTEXLOCK_H
#define MUTEXLOCK_H
#include "noncopyable.h"
#include <pthread.h>
#include <cstdio>
#include "CurrentThread.h"
class MutexLock : noncopyable
{
public:
    MutexLock():holder(0)
    {
        pthread_mutex_init(&mutex_,NULL);
    }
    ~MutexLock()
    {   
        assert(holder == 0); //确保解完锁之后，锁才能被析构
        pthread_mutex_destroy(&mutex_);
    }
private:
    void lock() //仅供MutexLockGuard使用
    {
        pthread_mutex_lock(&mutex_);
        holder = CurrentThread::tid(); //顺序不能反
    }
    void unlock() //仅供MutexLockGuard使用
    {
        holder = 0;
        pthread_mutex_unlock(&mutex_); // 顺序不能反
    }
    pthread_mutex_t* get() //仅供Condition使用
    {
        return &mutex_;
    }

private:
    pid_t holder;
    pthread_mutex_t mutex_;
    friend class Condition;
    friend class MutexLockGuard;
};


class MutexLockGuard : noncopyable
{
public:
    explicit MutexLockGuard(MutexLock& lock):lock_(lock)
    {
        lock_.lock();
    }
    ~MutexLockGuard()
    {
        lock_.unlock();
    }

private:
    MutexLock &lock_; //不允许拷贝构造和赋值，只能传递锁指针
};




#endif