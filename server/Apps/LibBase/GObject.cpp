#include "GObject.h"
#include "GScheduler.h"

static unsigned int __objectCount = 0;

GObject::GObject()
{
    __objectCount++;
    //DU_LOG("object count is %d\n", __objectCount);
	m_count = 1;
}

GObject::~GObject()
{
    GScheduler::getInstance()->unScheduleByObject(this);
    __objectCount--;
    //DU_LOG("~object count is %d\n", __objectCount);
}

GObject* GObject::retain()
{
	m_count++;
    return this;
}

void GObject::release()
{
	m_count--;
    if(m_count <= 0)
    {
        delete this;
    }
}

void GObject::printCount()
{
	LOG(INFO) << this << "count is " << m_count;
}
