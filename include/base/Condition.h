#ifndef CONDITION_H
#define CONDITION_H
#include <errno.h>
#include <pthread.h>
#include <time.h>
#include <cstdint>
#include "MutexLock.h"
#include "noncopyable.h"


class Condition : noncopyable
{
public:
    explicit Condition(MutexLock& mutex_):mutex(mutex_)
    {
        pthread_cond_init(&cond,NULL);
    }
    ~Condition()
    {
        pthread_cond_destroy(&cond);
    }
    void wait(){pthread_cond_wait(&cond,mutex.get());}
    void notify(){pthread_cond_signal(&cond);}
    void notifyAll(){pthread_cond_broadcast(&cond);}
    bool waitForSeconds(int seconds)
    {
        struct timespec abtime;
        clock_gettime(CLOCK_REALTIME, &abtime);
        abtime.tv_sec += static_cast<time_t>(seconds);
        return ETIMEDOUT == pthread_cond_timedwait(&cond,mutex.get(),&abtime);
    }

private:
    MutexLock &mutex;
    pthread_cond_t cond;
};



#endif