#include "GScheduler.h"

#define OPEN_DEBUG_SCHEDULER 0


#define SCHEDULER_TIMER_ITERATOR(vec)\
std::vector<SchedulerTimerPtr>::iterator itTimer;\
for(itTimer = vec.begin(); itTimer != vec.end(); ++itTimer)


typedef struct HashSchedulerUpdateEntry
{
    //Key
    void* Target;
    //Value
    std::vector<SchedulerTimerPtr> Timer;
    //Attribute
    bool Pause;
    bool Delete;
    //Hash
    UT_hash_handle hh;
}HashSchedulerUpdateEntry_t;


//******************

GScheduler* GScheduler::GSchedulerInstance = NULL;

GScheduler* GScheduler::getInstance()
{
    if(GSchedulerInstance == NULL)
    {
        GSchedulerInstance = new GScheduler();
    }
    return GSchedulerInstance;
}

GScheduler::GScheduler()
{
    m_currentRunEntry = NULL;
    m_operationEntry = NULL;
	m_functionsToPerform.reserve(10);
}

GScheduler::~GScheduler()
{
    clearOperationEntry();
    HashSchedulerUpdateEntry* data, *tmp;
    HASH_ITER(hh, m_currentRunEntry, data, tmp)
    {
        removeEntryFormHash(data);
    }
}

void GScheduler::update(float delay)
{
    clearOperationEntry();
    HashSchedulerUpdateEntry* data, *tmp;
    HASH_ITER(hh, m_currentRunEntry, data, tmp)
    {
        if(data->Delete || data->Pause)
            continue;
        SCHEDULER_TIMER_ITERATOR(data->Timer)
        {
            (*itTimer)->update(delay);
        }
    }

	if (!m_functionsToPerform.empty())
	{
		if (m_performMutex.try_lock())
		{
			auto temp = std::move(m_functionsToPerform);
			m_performMutex.unlock();

			for (const auto &it : temp) {
				it();
			}
		}
	}	
}

void GScheduler::scheduleSelector(GScheduler_SEL pfnSelector, GObject *pTarget, float fInterval, unsigned int repeat, float delay, bool paused/* = false*/, bool infinite/* = false*/)
{
    if(pfnSelector == NULL || pTarget == NULL)
        return;
    TimerTargetSelector* selectorData = new TimerTargetSelector();
    selectorData->init(this, pfnSelector, pTarget, fInterval, repeat, delay, infinite, paused);
    addTimerForHashMap(pTarget, selectorData);
    selectorData->release();
}

void GScheduler::scheduleSelector(GScheduler_SEL pfnSelector, GObject *pTarget, float fInterval, bool bPaused/* = false*/)
{
    this->scheduleSelector(pfnSelector, pTarget, fInterval, 0, 0.0f, bPaused, true);
}

void GScheduler::scheduleSelectorOnce(GScheduler_SEL pfnSelector, GObject *pTarget, float fInterval)
{
	this->scheduleSelector(pfnSelector, pTarget, fInterval, 1, 0.0f, false, false);
}

void GScheduler::schedule(const duSchedulerFunc& callback, void *target, float interval, unsigned int repeat, float delay, bool paused, const std::string& key, bool infinite/* = false*/)
{
    if(callback == NULL)
        return;
    G_ASSERT(key != "");
    TimerTargetCallback* callbackData = new TimerTargetCallback();
    callbackData->init(this, callback, target, key, interval, repeat, delay, infinite, paused);
    addTimerForHashMap((GObject*)target, callbackData);
    callbackData->release();
}

void GScheduler::schedule(const duSchedulerFunc& callback, void *target, float interval, bool paused, const std::string& key)
{
	G_ASSERT(target != NULL);
    this->schedule(callback, target, interval, 0, 0.0f, paused, key, true);
}

void GScheduler::scheduleOnce(const duSchedulerFunc& callback, void *target, float interval, const std::string& key)
{
	G_ASSERT(target != NULL);
	this->schedule(callback, target, interval, 1, 0.0f, false, key, false);
}

void GScheduler::scheduleGlobal(const duSchedulerFunc& callback, float interval, unsigned int repeat, float delay, bool paused, const std::string& key, bool infinite/* = false*/)
{
    this->schedule(callback, NULL, interval, repeat, delay, paused, key, infinite);
}

void GScheduler::scheduleGlobal(const duSchedulerFunc& callback, float interval, bool paused, const std::string& key)
{
    this->schedule(callback, NULL, interval, 0, 0.0f, paused, key, true);
}

void GScheduler::scheduleGlobalOnce(const duSchedulerFunc& callback, float interval, const std::string& key)
{
	this->schedule(callback, NULL, interval, 1, 0.0f, false, key, false);
}

//pause
void GScheduler::pauseByObject(GObject* pTarget)
{
    std::vector<SchedulerTimerPtr>::iterator itTimer;
    HashSchedulerUpdateEntry *data, *tmp;
    HASH_ITER(hh, m_currentRunEntry, data, tmp)
    {
        if(data->Target == (void*)pTarget)
        {
            data->Pause = true;
            for(itTimer = data->Timer.begin(); itTimer != data->Timer.end(); ++itTimer)
            {
                (*itTimer)->m_Paused = true;
            }
        }
    }
    HASH_ITER(hh, m_operationEntry, data, tmp)
    {
        if(data->Target == (void*)pTarget)
        {
            data->Pause = true;
            for(itTimer = data->Timer.begin(); itTimer != data->Timer.end(); ++itTimer)
            {
                (*itTimer)->m_Paused = true;
            }
        }
    }
}

void GScheduler::pauseByObject(GObject *pTarget, GScheduler_SEL pfnSelector)
{
    std::vector<SchedulerTimerPtr>::iterator itTimer;
    HashSchedulerUpdateEntry *data, *tmp;
    
    HASH_ITER(hh, m_currentRunEntry, data, tmp)
    {
        if(data->Target == (void*)pTarget)
        {
            for(itTimer = data->Timer.begin(); itTimer != data->Timer.end(); ++itTimer)
            {
                if((*itTimer)->isEqual(pfnSelector, pTarget))
                {
                    (*itTimer)->m_Paused = true;
                }
            }
        }
    }
    HASH_ITER(hh, m_operationEntry, data, tmp)
    {
        if(data->Target == (void*)pTarget)
        {
            for(itTimer = data->Timer.begin(); itTimer != data->Timer.end(); ++itTimer)
            {
                if((*itTimer)->isEqual(pfnSelector, pTarget))
                {
                    (*itTimer)->m_Paused = true;
                }
            }
        }
    }
}

void GScheduler::pauseSchedule(void *pTarget, const std::string& key)
{
    std::vector<SchedulerTimerPtr>::iterator itTimer;
    HashSchedulerUpdateEntry *data, *tmp;
    
    HASH_ITER(hh, m_currentRunEntry, data, tmp)
    {
        if(data->Target == (void*)pTarget)
        {
            for(itTimer = data->Timer.begin(); itTimer != data->Timer.end(); ++itTimer)
            {
                if((*itTimer)->isEqual(pTarget, key))
                {
                    (*itTimer)->m_Paused = true;
                }
            }
        }
    }
    HASH_ITER(hh, m_operationEntry, data, tmp)
    {
        if(data->Target == (void*)pTarget)
        {
            for(itTimer = data->Timer.begin(); itTimer != data->Timer.end(); ++itTimer)
            {
                if((*itTimer)->isEqual(pTarget, key))
                {
                    (*itTimer)->m_Paused = true;
                }
            }
        }
    }
}

void GScheduler::pauseGlobalSchedule(const std::string& key)
{
    this->pauseSchedule(NULL, key);
}

//resume
void GScheduler::resumeByObject(GObject* pTarget)
{
    std::vector<SchedulerTimerPtr>::iterator itTimer;
    HashSchedulerUpdateEntry *data, *tmp;
    
    HASH_ITER(hh, m_currentRunEntry, data, tmp)
    {
        if(data->Target == (void*)pTarget)
        {
            data->Pause = false;
            for(itTimer = data->Timer.begin(); itTimer != data->Timer.end(); ++itTimer)
            {
                (*itTimer)->m_Paused = false;
            }
        }
    }
    HASH_ITER(hh, m_operationEntry, data, tmp)
    {
        if(data->Target == (void*)pTarget)
        {
            data->Pause = false;
            for(itTimer = data->Timer.begin(); itTimer != data->Timer.end(); ++itTimer)
            {
                (*itTimer)->m_Paused = false;
            }
        }
    }
}

void GScheduler::resumeByObject(GObject *pTarget, GScheduler_SEL pfnSelector)
{
    std::vector<SchedulerTimerPtr>::iterator itTimer;
    HashSchedulerUpdateEntry *data, *tmp;
    
    HASH_ITER(hh, m_currentRunEntry, data, tmp)
    {
        if(data->Target == (void*)pTarget)
        {
            data->Pause = false;
            for(itTimer = data->Timer.begin(); itTimer != data->Timer.end(); ++itTimer)
            {
                if((*itTimer)->isEqual(pfnSelector, pTarget))
                {
                    (*itTimer)->m_Paused = false;
                }
            }
        }
    }
    HASH_ITER(hh, m_operationEntry, data, tmp)
    {
        if(data->Target == (void*)pTarget)
        {
            data->Pause = false;
            for(itTimer = data->Timer.begin(); itTimer != data->Timer.end(); ++itTimer)
            {
                if((*itTimer)->isEqual(pfnSelector, pTarget))
                {
                    (*itTimer)->m_Paused = false;
                }
            }
        }
    }
}

void GScheduler::resumeSchedule(void *pTarget, const std::string& key)
{
    std::vector<SchedulerTimerPtr>::iterator itTimer;
    HashSchedulerUpdateEntry *data, *tmp;
    
    HASH_ITER(hh, m_currentRunEntry, data, tmp)
    {
        if(data->Target == (void*)pTarget)
        {
            data->Pause = false;
            for(itTimer = data->Timer.begin(); itTimer != data->Timer.end(); ++itTimer)
            {
                if((*itTimer)->isEqual(pTarget, key))
                {
                    (*itTimer)->m_Paused = false;
                }
            }
        }
    }
    HASH_ITER(hh, m_operationEntry, data, tmp)
    {
        if(data->Target == (void*)pTarget)
        {
            data->Pause = false;
            for(itTimer = data->Timer.begin(); itTimer != data->Timer.end(); ++itTimer)
            {
                if((*itTimer)->isEqual(pTarget, key))
                {
                    (*itTimer)->m_Paused = false;
                }
            }
        }
    }
}

void GScheduler::resumeGlobalSchedule(const std::string& key)
{
    this->resumeSchedule(NULL, key);
}

//cancel
void GScheduler::unScheduleBySelector(GScheduler_SEL pfnSelector, GObject *pTarget)
{
    HashSchedulerUpdateEntry* hashData;
    SchedulerTimerPtr curTimer = NULL;
    HASH_FIND_PTR(m_currentRunEntry, &pTarget, hashData);
    if(hashData)
    {
        SCHEDULER_TIMER_ITERATOR(hashData->Timer)
        {
            curTimer = (*itTimer);
            if(curTimer->isEqual(pfnSelector, pTarget))
            {
                curTimer->m_Delete = true;
            }
        }
    }
    HASH_FIND_PTR(m_operationEntry, &pTarget, hashData);
    if(hashData)
    {
        SCHEDULER_TIMER_ITERATOR(hashData->Timer)
        {
            curTimer = (*itTimer);
            if(curTimer->isEqual(pfnSelector, pTarget))
            {
                curTimer->m_Delete = true;
            }
        }
    }
}

void GScheduler::unScheduleByObject(GObject *pTarget)
{
    HashSchedulerUpdateEntry* hashData;
    HASH_FIND_PTR(m_currentRunEntry, &pTarget, hashData);
    if(hashData)
    {
        SCHEDULER_TIMER_ITERATOR(hashData->Timer)
        {
            (*itTimer)->m_Delete = true;
        }
    }
    HASH_FIND_PTR(m_operationEntry, &pTarget, hashData);
    if(hashData)
    {
        SCHEDULER_TIMER_ITERATOR(hashData->Timer)
        {
            (*itTimer)->m_Delete = true;
        }
    }
}

void GScheduler::unSchedule(void *pTarget, const std::string& key)
{
    HashSchedulerUpdateEntry* hashData;
    SchedulerTimerPtr curTimer = NULL;
    HASH_FIND_PTR(m_currentRunEntry, &pTarget, hashData);
    if(hashData)
    {
        SCHEDULER_TIMER_ITERATOR(hashData->Timer)
        {
            curTimer = (*itTimer);
            if(curTimer->isEqual(pTarget, key))
            {
                curTimer->m_Delete = true;
            }
#if OPEN_DEBUG_SCHEDULER == 1
            else
            {
				LOG(INFO) << "unScheduleSeletorByKey : no key";
            }
#endif
        }
    }
    HASH_FIND_PTR(m_operationEntry, &pTarget, hashData);
    if(hashData)
    {
        SCHEDULER_TIMER_ITERATOR(hashData->Timer)
        {
            curTimer = (*itTimer);
            if(curTimer->isEqual(pTarget, key))
            {
                curTimer->m_Delete = true;
            }
        }
    }
}

void GScheduler::unScheduleGlobal(const std::string& key)
{
    this->unSchedule(NULL, key);
}

void GScheduler::unScheduleTarget(void *pTarget)
{
    HashSchedulerUpdateEntry* hashData;
    HASH_FIND_PTR(m_currentRunEntry, &pTarget, hashData);
    if(hashData)
    {
        SCHEDULER_TIMER_ITERATOR(hashData->Timer)
        {
            (*itTimer)->m_Delete = true;
        }
    }
    HASH_FIND_PTR(m_operationEntry, &pTarget, hashData);
    if(hashData)
    {
        SCHEDULER_TIMER_ITERATOR(hashData->Timer)
        {
            (*itTimer)->m_Delete = true;
        }
    }
}

void GScheduler::unScheduleAll()
{
    HashSchedulerUpdateEntry *data, *tmp;
    HASH_ITER(hh, m_currentRunEntry, data, tmp)
    {
        data->Delete = true;
    }
    HASH_ITER(hh, m_operationEntry, data, tmp)
    {
        data->Delete = true;
    }
}

//std::string GScheduler::registerScripSchedule(const LuaFunction& func, float interval, bool paused)
//{
//	LuaFunction* pFunc = new LuaFunction(func);
//
//	char szKey[64];
//	memset(szKey, 0, sizeof(szKey));
//	sprintf(szKey, "luafunc_%p", pFunc);
//	std::string strKey(szKey);
//
//	m_scripCall.insert(std::make_pair(strKey, pFunc));
//
//	this->scheduleSelector([=](float dt) {
//		pFunc->ppush();
//		pFunc->pusharg(dt);
//		pFunc->pcall();
//	}, interval, paused, strKey);
//
//	return strKey;
//}
//
//void GScheduler::unRegisterScripSchedule(const std::string& key)
//{
//	auto it = m_scripCall.find(key);
//	if (it != m_scripCall.end())
//	{
//		this->unScheduleSeletorByKey(key);
//		delete it->second;
//		m_scripCall.erase(it);
//	}
//}


void GScheduler::performInMainThread(const std::function<void()>& call)
{
	m_performMutex.lock();
	m_functionsToPerform.push_back(call);
	m_performMutex.unlock();
}

void GScheduler::clearOperationEntry()
{
    std::vector<SchedulerTimerPtr>::iterator itTimer;
    HashSchedulerUpdateEntry *data, *tmp, *curData;
    SchedulerTimerPtr timerTmp = NULL;
    
    HASH_ITER(hh, m_currentRunEntry, data, tmp)
    {
        if(data->Delete)
        {
            removeEntryFormHash(data);
#if OPEN_DEBUG_SCHEDULER == 1
			LOG(INFO) << "remove running data from hash Map";
#endif
        }
        else
        {
            for(itTimer = data->Timer.begin(); itTimer != data->Timer.end(); )
            {
                timerTmp = (*itTimer);
                if(timerTmp->m_Delete)
                {
#if OPEN_DEBUG_SCHEDULER == 1
                    timerTmp->printCount();
#endif
                    itTimer = data->Timer.erase(itTimer);
#if OPEN_DEBUG_SCHEDULER == 1
                    timerTmp->printCount();
					LOG(INFO) << "remove timer";
#endif
                }
                else
                {
                    itTimer++;
                }
            }
        }
    }
    timerTmp = NULL;
    if(HASH_COUNT(m_operationEntry) <= 0)
        return;
#if OPEN_DEBUG_SCHEDULER == 1
	LOG(INFO) << "m_operationEntry hash Map count is :" << HASH_COUNT(m_operationEntry);
#endif
    HASH_ITER(hh, m_operationEntry, data, tmp)
    {
        HASH_FIND_PTR(m_currentRunEntry, &data->Target, curData);
        for(itTimer = data->Timer.begin(); itTimer != data->Timer.end(); )
        {
            timerTmp = (*itTimer);
            if(timerTmp->m_Delete == false)
            {
                if(curData)
                {
                    curData->Timer.push_back(*itTimer);
                }
                else
                {
                    curData = new HashSchedulerUpdateEntry();
                    curData->Delete = false;
                    curData->Pause = false;
                    curData->Target = data->Target;
                    curData->Timer.push_back(timerTmp);
                    HASH_ADD_PTR(m_currentRunEntry, Target, curData);
#if OPEN_DEBUG_SCHEDULER == 1
					LOG(INFO) << "add new Data";
#endif
                }
                itTimer++;
            }
            else
            {
                itTimer = data->Timer.erase(itTimer);
            }
        }
    }
    HASH_ITER(hh, m_operationEntry, data, tmp)
    {
        HASH_DELETE(hh, m_operationEntry, data);
        G_SAFE_DELETE(data);
    }
}

void GScheduler::removeEntryFormHash(HashSchedulerUpdateEntry* entry)
{
    entry->Timer.clear();
    HASH_DELETE(hh, m_currentRunEntry, entry);
    G_SAFE_DELETE(entry);
}

void GScheduler::addTimerForHashMap(GObject *pTarget, SchedulerTimer* timerData)
{
    SchedulerTimerPtr timer = findSchedulerTimer(m_currentRunEntry, pTarget, timerData);
    if(timer.GetPtr() && timer->m_Delete == false)
    {
        return;
    }
    timer = findSchedulerTimer(m_operationEntry, pTarget, timerData);
    HashSchedulerUpdateEntry* hashData = NULL;
    if(timer == NULL)
    {
        hashData = new HashSchedulerUpdateEntry();
        hashData->Delete = false;
        hashData->Pause = false;
        hashData->Target = pTarget;
        hashData->Timer.push_back(timerData);
        HASH_ADD_PTR(m_operationEntry, Target, hashData);
    }
    else if(timer->m_Delete == false)
    {
        return;
    }
    else
    {
        HashSchedulerUpdateEntry* hashData;
        HASH_FIND_PTR(m_operationEntry, &pTarget, hashData);
        if(hashData)
        {
            hashData->Timer.push_back(timerData);
        }
    }
}

SchedulerTimerPtr GScheduler::findSchedulerTimer(HashSchedulerUpdateEntry* hashMap, GObject *pTarget, SchedulerTimerPtr timer)
{
    if(hashMap == NULL)
        return NULL;
    HashSchedulerUpdateEntry* hashData;
    HASH_FIND_PTR(hashMap, &pTarget, hashData);
    if(hashData)
    {
        std::vector<SchedulerTimerPtr>::iterator it;
        for(it = hashData->Timer.begin(); it != hashData->Timer.end(); ++it)
        {
            if((*it)->isEqual(timer))
            {
                return *it;
            }
        }
    }
    return NULL;
}
