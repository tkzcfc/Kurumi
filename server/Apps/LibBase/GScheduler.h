#ifndef GScheduler_hpp
#define GScheduler_hpp


#include <string>
#include <vector>
#include <mutex>
#include "uthash.h"
#include "GSchedulerTimer.h"
//#include "lua_function/LuaFunction.h"
#include <map>


struct HashSchedulerUpdateEntry;

class GScheduler : public GObject
{
    static GScheduler* GSchedulerInstance;
    GScheduler();
public:
    
    static GScheduler* getInstance();
    
    ~GScheduler();
    
    void update(float delay);
    
public:
    
    //add
    void schedule(GScheduler_SEL pfnSelector, GObject *pTarget, float fInterval, unsigned int repeat, float delay, bool paused = false, bool infinite = false);
    
    void schedule(GScheduler_SEL pfnSelector, GObject *pTarget, float fInterval, bool bPaused = false);
    
    void scheduleSelector(const duSchedulerFunc& callback, void *target, float interval, unsigned int repeat, float delay, bool paused, const std::string& key, bool infinite = false);
    
    void scheduleSelector(const duSchedulerFunc& callback, void *target, float interval, bool paused, const std::string& key);
    
    void scheduleSelector(const duSchedulerFunc& callback, float interval, unsigned int repeat, float delay, bool paused, const std::string& key, bool infinite = false);
    
    void scheduleSelector(const duSchedulerFunc& callback, float interval, bool paused, const std::string& key);
    
    //pause
    void pauseSchedule(GObject* pTarget);
    
    void pauseSchedule(GObject *pTarget, GScheduler_SEL pfnSelector);
    
    void pauseSchedule(void *pTarget, const std::string& key);
    
    void pauseSchedule(const std::string& key);
    
    //resume
    void resumeSchedule(GObject* pTarget);
    
    void resumeSchedule(GObject *pTarget, GScheduler_SEL pfnSelector);
    
    void resumeSchedule(void *pTarget, const std::string& key);
    
    void resumeSchedule(const std::string& key);
    
    //cancel
    void unScheduleBySelector(GScheduler_SEL pfnSelector, GObject *pTarget);
    
    void unScheduleByObject(GObject *pTarget);
    
    void unScheduleSeletorByKey(void *pTarget, const std::string& key);
    
    void unScheduleSeletorByKey(const std::string& key);
    
    void unScheduleSeletorByObject(void *pTarget);
    
    void unScheduleAll();

	// 
	//std::string registerScripSchedule(const LuaFunction& func, float interval, bool paused);
    
	//void unRegisterScripSchedule(const std::string& key);

	void performInMainThread(const std::function<void()>& call);

protected:
    
    void addTimerForHashMap(GObject *pTarget, SchedulerTimer* timerData);
    
    SchedulerTimerPtr findSchedulerTimer(HashSchedulerUpdateEntry* hashMap, GObject *pTarget, SchedulerTimerPtr timer);
    
    void clearOperationEntry();
    
    void removeEntryFormHash(HashSchedulerUpdateEntry* entry);
    
protected:
    
    struct HashSchedulerUpdateEntry* m_currentRunEntry;
    struct HashSchedulerUpdateEntry* m_operationEntry;

	//std::map<std::string, LuaFunction*> m_scripCall;
    
    std::mutex m_performMutex;
	std::vector<std::function<void()>> m_functionsToPerform;
};

#endif /* GScheduler_hpp */
