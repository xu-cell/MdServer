#ifndef TIMER_H
#define TIMER_H
#include <deque>
#include <memory>
#include <queue>
#include "HttpData.h"
#include "MutexLock.h"
#include "noncopyable.h"
class HttpData;

class TimerNode
{
public:
    TimerNode(std::shared_ptr<HttpData>requestData,int timeout);
     ~TimerNode();
    TimerNode(TimerNode &tn);
   
    bool isValid();
    void clearReq();
    void setDeleted(){deleted_ = true;}
    bool isDeleted(){return deleted_;}
    void update(int timeout);
    size_t getExpTime() const  {return expiredTime_;}
private:
    bool deleted_;
    size_t expiredTime_;
    std::shared_ptr<HttpData>SPHttpData;
};

//比较重载
struct TimerCmp
{
    bool operator()(std::shared_ptr<TimerNode>&a,std::shared_ptr<TimerNode>&b)const
    {
        return a->getExpTime() > b->getExpTime();
    }
};

class TimerManager
{
public:
    TimerManager();
    ~TimerManager();
    void addTimer(std::shared_ptr<HttpData>SPHttpData,int timeout);
    void handleExpiredEvent();

private:
    using SPTimerNode = std::shared_ptr<TimerNode>;
    std::priority_queue<SPTimerNode,std::deque<SPTimerNode>,TimerCmp>timerNodeQueue;
};


#endif