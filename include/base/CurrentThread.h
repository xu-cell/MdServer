#ifndef CURRENTTHREAD_H
#define CURRENTTHREAD_H
#include <unistd.h>
#include <sys/syscall.h>
#include <assert.h>
#include <stdio.h>
#include <stdint.h>
namespace CurrentThread
{
    extern __thread int t_cacheTid;
    extern __thread char t_tidString[32];
    extern __thread int t_tidStringLength;
    extern __thread const char *t_threadName;
    void cacheTid()
    {
        if(t_cacheTid == 0)
        {
            t_cacheTid = static_cast<pid_t>(::syscall(SYS_gettid));
            snprintf(t_tidString,sizeof t_tidString,"%d ",t_cacheTid);
        }
    }

    inline int tid()
    {
        if (__builtin_expect(t_cacheTid == 0, 0))
        {
            cacheTid();
        }
        return t_cacheTid;
    }
    inline const char *tidString()
    {
        return t_tidString;
    }
    inline int tidStringLength()
    {
        return t_tidStringLength;
    }
    inline const char *name()
    {
        return t_threadName;
    }
}
#endif