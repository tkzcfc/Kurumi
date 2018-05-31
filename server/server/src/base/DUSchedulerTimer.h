//
//  DUSchedulerTimer.hpp
//  NNNN
//
//  Created by 方程 on 17/1/18.
//  Copyright ? 2017年 lianshi. All rights reserved.
//

#ifndef DUSchedulerTimer_hpp
#define DUSchedulerTimer_hpp

#include "DUSmartPtr.h"
#include <functional>

typedef std::function<void(float)> duSchedulerFunc;

typedef void (DUObject::*DUScheduler_SEL) (float);
#define scheduler_selector(SELECTOR) (DUScheduler_SEL)(&SELECTOR)

class SchedulerTimer;
typedef DUSmartPtr<SchedulerTimer> SchedulerTimerPtr;

class DUScheduler;
class SchedulerTimer : public DUObject
{
public:
    SchedulerTimer();
    
    inline float getInterval() const { return m_Interval; }
    
    inline void setInterval(float interval) { this->m_Interval = interval; }
    
    void setupTimerWithInterval(float seconds, unsigned int repeat, float delay, bool infinite, bool pause);
    
    virtual void trigger(float dt) = 0;
    virtual void cancel() = 0;
    virtual bool isEqual(SchedulerTimer* otherTimer) = 0;
    virtual bool isEqual(SchedulerTimerPtr otherTimer) = 0;
    virtual bool isEqual(DUScheduler_SEL pfnSelector, DUObject *pTarget) = 0;
    virtual bool isEqual(void* object, const std::string& key) = 0;
    
    void update(float dt);
    
public:
    unsigned int m_TimesExecuted;
    float m_Timing;   //
    bool m_UseDelay;
    
    bool m_Infinite;  //is loop
    float m_Interval; //interval
    float m_Delay;    //delay time
    float m_Total;    //total time
    unsigned int m_Repeat;//重复次数
    bool m_Paused;
    bool m_Delete;
    
    DUScheduler* m_Scheduler;
};

class TimerTargetSelector : public SchedulerTimer
{
    friend class DUScheduler;
public:
    TimerTargetSelector();
    
    void init(DUScheduler* scheduler, DUScheduler_SEL pfnSelector, DUObject *pTarget, float fInterval, unsigned int repeat, float delay, bool infinite, bool bPaused);
    
    virtual void trigger(float dt);
    
    virtual void cancel();
    
    virtual bool isEqual(SchedulerTimer* otherTimer);
    virtual bool isEqual(SchedulerTimerPtr otherTimer);
    virtual bool isEqual(DUScheduler_SEL pfnSelector, DUObject *pTarget);
    virtual bool isEqual(void* object, const std::string& key);
    
protected:
    
    DUScheduler_SEL m_Selector;
    DUObject* m_Object;
};

class TimerTargetCallback : public SchedulerTimer
{
    friend class DUScheduler;
public:
    TimerTargetCallback();
    
    void init(DUScheduler* scheduler, duSchedulerFunc callback, void *pTarget, const std::string key, float fInterval, unsigned int repeat, float delay, bool infinite, bool bPaused);
    
    virtual void trigger(float dt);
    
    virtual void cancel();
    
    virtual bool isEqual(SchedulerTimer* otherTimer);
    virtual bool isEqual(SchedulerTimerPtr otherTimer);
    virtual bool isEqual(DUScheduler_SEL pfnSelector, DUObject *pTarget);
    virtual bool isEqual(void* object, const std::string& key);
protected:
    
    duSchedulerFunc m_Callback;
    void* m_Object;
    std::string m_Key;
};


#endif /* DUSchedulerTimer_hpp */
