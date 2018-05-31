//
//  DUScheduler.hpp
//  NNNN
//
//  Created by ·½³Ì on 16/11/14.
//  Copyright ? 2016Äê lianshi. All rights reserved.
//


#ifndef DUScheduler_hpp
#define DUScheduler_hpp


#include <string>
#include <vector>
#include <mutex>
#include "uthash.h"
#include "DUSchedulerTimer.h"


struct HashSchedulerUpdateEntry;

class DUScheduler : public DUObject
{
    static DUScheduler* DUSchedulerInstance;
    DUScheduler();
public:
    
    static DUScheduler* getInstance();
    
    ~DUScheduler();
    
    void update(float delay);
    
public:
    
    //add
    void schedule(DUScheduler_SEL pfnSelector, DUObject *pTarget, float fInterval, unsigned int repeat, float delay, bool paused = false, bool infinite = false);
    
    void schedule(DUScheduler_SEL pfnSelector, DUObject *pTarget, float fInterval, bool bPaused = false);
    
    void scheduleSelector(const duSchedulerFunc& callback, void *target, float interval, unsigned int repeat, float delay, bool paused, const std::string& key, bool infinite = false);
    
    void scheduleSelector(const duSchedulerFunc& callback, void *target, float interval, bool paused, const std::string& key);
    
    void scheduleSelector(const duSchedulerFunc& callback, float interval, unsigned int repeat, float delay, bool paused, const std::string& key, bool infinite = false);
    
    void scheduleSelector(const duSchedulerFunc& callback, float interval, bool paused, const std::string& key);
    
    //pause
    void pauseSchedule(DUObject* pTarget);
    
    void pauseSchedule(DUObject *pTarget, DUScheduler_SEL pfnSelector);
    
    void pauseSchedule(void *pTarget, const std::string& key);
    
    void pauseSchedule(const std::string& key);
    
    //resume
    void resumeSchedule(DUObject* pTarget);
    
    void resumeSchedule(DUObject *pTarget, DUScheduler_SEL pfnSelector);
    
    void resumeSchedule(void *pTarget, const std::string& key);
    
    void resumeSchedule(const std::string& key);
    
    //cancel
    void unScheduleBySelector(DUScheduler_SEL pfnSelector, DUObject *pTarget);
    
    void unScheduleByObject(DUObject *pTarget);
    
    void unScheduleSeletorByKey(void *pTarget, const std::string& key);
    
    void unScheduleSeletorByKey(const std::string& key);
    
    void unScheduleSeletorByObject(void *pTarget);
    
    void unScheduleAll();
    
protected:
    
    void addTimerForHashMap(DUObject *pTarget, SchedulerTimer* timerData);
    
    SchedulerTimerPtr findSchedulerTimer(HashSchedulerUpdateEntry* hashMap, DUObject *pTarget, SchedulerTimerPtr timer);
    
    void clearOperationEntry();
    
    void removeEntryFormHash(HashSchedulerUpdateEntry* entry);
    
protected:
    
    struct HashSchedulerUpdateEntry* m_currentRunEntry;
    struct HashSchedulerUpdateEntry* m_operationEntry;
    
    //std::mutex m_mutex;
};

#endif /* DUScheduler_hpp */
