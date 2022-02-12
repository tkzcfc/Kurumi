#ifndef GSchedulerTimer_hpp
#define GSchedulerTimer_hpp

#include "GSmartPtr.h"
#include <functional>

typedef std::function<void(float)> duSchedulerFunc;

typedef void (GObject::*GScheduler_SEL) (float);
#define scheduler_selector(SELECTOR) (GScheduler_SEL)(&SELECTOR)

class SchedulerTimer;
typedef GSmartPtr<SchedulerTimer> SchedulerTimerPtr;

class GScheduler;
class SchedulerTimer : public GObject
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
    virtual bool isEqual(GScheduler_SEL pfnSelector, GObject *pTarget) = 0;
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
    
    GScheduler* m_Scheduler;
};

class TimerTargetSelector : public SchedulerTimer
{
    friend class GScheduler;
public:
    TimerTargetSelector();
    
    void init(GScheduler* scheduler, GScheduler_SEL pfnSelector, GObject *pTarget, float fInterval, unsigned int repeat, float delay, bool infinite, bool bPaused);
    
    virtual void trigger(float dt);
    
    virtual void cancel();
    
    virtual bool isEqual(SchedulerTimer* otherTimer);
    virtual bool isEqual(SchedulerTimerPtr otherTimer);
    virtual bool isEqual(GScheduler_SEL pfnSelector, GObject *pTarget);
    virtual bool isEqual(void* object, const std::string& key);
    
protected:
    
    GScheduler_SEL m_Selector;
    GObject* m_Object;
};

class TimerTargetCallback : public SchedulerTimer
{
    friend class GScheduler;
public:
    TimerTargetCallback();
    
    void init(GScheduler* scheduler, duSchedulerFunc callback, void *pTarget, const std::string key, float fInterval, unsigned int repeat, float delay, bool infinite, bool bPaused);
    
    virtual void trigger(float dt);
    
    virtual void cancel();
    
    virtual bool isEqual(SchedulerTimer* otherTimer);
    virtual bool isEqual(SchedulerTimerPtr otherTimer);
    virtual bool isEqual(GScheduler_SEL pfnSelector, GObject *pTarget);
    virtual bool isEqual(void* object, const std::string& key);
protected:
    
    duSchedulerFunc m_Callback;
    void* m_Object;
    std::string m_Key;
};


#endif /* GSchedulerTimer_hpp */
