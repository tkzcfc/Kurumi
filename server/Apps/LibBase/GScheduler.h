#ifndef GScheduler_hpp
#define GScheduler_hpp


#include <string>
#include <vector>
#include <mutex>
#include "Algorithm/uthash.h"
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
    void scheduleSelector(GScheduler_SEL pfnSelector, GObject *pTarget, float fInterval, unsigned int repeat, float delay, bool paused = false, bool infinite = false);
    
    void scheduleSelector(GScheduler_SEL pfnSelector, GObject *pTarget, float fInterval, bool bPaused = false);

	void scheduleSelectorOnce(GScheduler_SEL pfnSelector, GObject *pTarget, float fInterval);
    
    void schedule(const duSchedulerFunc& callback, void *target, float interval, unsigned int repeat, float delay, bool paused, const std::string& key, bool infinite = false);
    
    void schedule(const duSchedulerFunc& callback, void *target, float interval, bool paused, const std::string& key);
    
	void scheduleOnce(const duSchedulerFunc& callback, void *target, float interval, const std::string& key);

    void scheduleGlobal(const duSchedulerFunc& callback, float interval, unsigned int repeat, float delay, bool paused, const std::string& key, bool infinite = false);
    
    void scheduleGlobal(const duSchedulerFunc& callback, float interval, bool paused, const std::string& key);

	void scheduleGlobalOnce(const duSchedulerFunc& callback, float interval, const std::string& key);
    
    //pause
    void pauseByObject(GObject* pTarget);
    
    void pauseByObject(GObject *pTarget, GScheduler_SEL pfnSelector);
    
    void pauseSchedule(void *pTarget, const std::string& key);
    
    void pauseGlobalSchedule(const std::string& key);
    
    //resume
    void resumeByObject(GObject* pTarget);
    
    void resumeByObject(GObject *pTarget, GScheduler_SEL pfnSelector);
    
    void resumeSchedule(void *pTarget, const std::string& key);
    
    void resumeGlobalSchedule(const std::string& key);
    
    //cancel
    void unScheduleBySelector(GScheduler_SEL pfnSelector, GObject *pTarget);
    
    void unScheduleByObject(GObject *pTarget);
    
    void unSchedule(void *pTarget, const std::string& key);
    
    void unScheduleGlobal(const std::string& key);
    
    void unScheduleTarget(void *pTarget);
    
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
