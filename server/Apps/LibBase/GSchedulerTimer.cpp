#include "GSchedulerTimer.h"
#include "GScheduler.h"

SchedulerTimer::SchedulerTimer()
: m_TimesExecuted(0)
, m_Timing(0.0f)
, m_Infinite(false)
, m_Interval(0.0f)
, m_Delay(0.0f)
, m_Total(0.0f)
, m_Repeat(0)
, m_Paused(true)
, m_UseDelay(false)
, m_Delete(false)
{
    m_Timing = 0.0f;
    m_Total = 0.0f;
}

void SchedulerTimer::setupTimerWithInterval(float seconds, unsigned int repeat, float delay, bool infinite, bool pause)
{
    this->m_TimesExecuted = 0;
    this->m_Timing = -1.0f;
    this->m_Total = 0.0f;
    this->m_Paused = pause;
    this->m_Interval = seconds;
    this->m_Infinite = infinite;
    this->m_Delay = delay;
    this->m_Repeat = repeat;
    this->m_UseDelay = (delay > 0.0f) ? true : false;
}

void SchedulerTimer::update(float dt)
{
    if(m_Timing == -1.0f)
    {
        m_Timing = 0.0f;
        m_TimesExecuted = 0;
        return;
    }
    m_Timing += dt;
    
    if(m_UseDelay)
    {
		if (m_Timing < m_Delay)
		{
			return;
		}
		trigger(m_Delay);
		m_Timing = m_Timing - m_Delay;
		m_TimesExecuted += 1;
		m_UseDelay = false;
		// after delay, the rest time should compare with interval
		if (!m_Infinite && m_TimesExecuted > m_Repeat)
		{    //unschedule timer
			cancel();
			return;
		}
    }

	float interval = (m_Interval > 0) ? m_Interval : m_Timing;
	while (m_Timing >= interval)
	{
		trigger(interval);
		m_Timing -= interval;
		m_TimesExecuted += 1;

		if (!m_Infinite && m_TimesExecuted > m_Repeat)
		{
			cancel();
			break;
		}

		if (m_Timing <= 0.f)
		{
			break;
		}
	}
}

//******************TimerTargetSelector
TimerTargetSelector::TimerTargetSelector()
{
    m_Selector = NULL;
    m_Object = NULL;
}

void TimerTargetSelector::init(GScheduler* scheduler, GScheduler_SEL pfnSelector, GObject *pTarget, float fInterval, unsigned int repeat, float delay, bool infinite, bool paused)
{
    m_Scheduler = scheduler;
    m_Selector = pfnSelector;
    m_Object = pTarget;
    this->setupTimerWithInterval(fInterval, repeat, delay, infinite, paused);
}

void TimerTargetSelector::trigger(float dt)
{
    if(m_Selector && m_Object)
    {
        (m_Object->*m_Selector)(dt);
    }
}

void TimerTargetSelector::cancel()
{
    m_Scheduler->unScheduleBySelector(m_Selector, m_Object);
}

bool TimerTargetSelector::isEqual(SchedulerTimer* otherTimer)
{
    TimerTargetSelector* other = dynamic_cast<TimerTargetSelector*>(otherTimer);
    if(other && (other->m_Object == this->m_Object) && (other->m_Selector == this->m_Selector))
        return true;
    return false;
}

bool TimerTargetSelector::isEqual(SchedulerTimerPtr otherTimer)
{
    TimerTargetSelector* other = dynamic_cast<TimerTargetSelector*>(otherTimer.GetPtr());
    if(other && (other->m_Object == this->m_Object) && (other->m_Selector == this->m_Selector))
        return true;
    return false;
}

bool TimerTargetSelector::isEqual(GScheduler_SEL pfnSelector, GObject *pTarget)
{
    return ((this->m_Object == pTarget) && (this->m_Selector == pfnSelector));
}

bool TimerTargetSelector::isEqual(void* object, const std::string& key)
{
    return false;
}

//******************TimerTargetCallback

TimerTargetCallback::TimerTargetCallback()
{
    m_Callback = NULL;
    m_Object = NULL;
}

void TimerTargetCallback::init(GScheduler* scheduler, duSchedulerFunc callback, void *pTarget, const std::string key, float fInterval, unsigned int repeat, float delay, bool infinite, bool paused)
{
    m_Scheduler = scheduler;
    m_Callback = callback;
    m_Object = pTarget;
    m_Key = key;
    this->setupTimerWithInterval(fInterval, repeat, delay, infinite, paused);
}

void TimerTargetCallback::trigger(float dt)
{
    m_Callback(dt);
}

void TimerTargetCallback::cancel()
{
	m_Scheduler->unSchedule(m_Object, m_Key);
}

bool TimerTargetCallback::isEqual(SchedulerTimer* otherTimer)
{
    TimerTargetCallback* other = dynamic_cast<TimerTargetCallback*>(otherTimer);
    if(other && (other->m_Object == this->m_Object) && (other->m_Key == this->m_Key))
        return true;
    return false;
}

bool TimerTargetCallback::isEqual(SchedulerTimerPtr otherTimer)
{
    TimerTargetCallback* other = dynamic_cast<TimerTargetCallback*>(otherTimer.GetPtr());
    if(other && (other->m_Object == this->m_Object) && (other->m_Key == this->m_Key))
        return true;
    return false;
}

bool TimerTargetCallback::isEqual(GScheduler_SEL pfnSelector, GObject *pTarget)
{
    return false;
}

bool TimerTargetCallback::isEqual(void* object, const std::string& key)
{
    return ((object == this->m_Object) && (key == this->m_Key));
}
