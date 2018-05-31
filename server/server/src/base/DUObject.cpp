//
//  DUObject.cpp
//  NNNN
//
//  Created by 方程 on 17/1/17.
//  Copyright © 2017年 lianshi. All rights reserved.
//

#include "DUObject.h"
#include "DUScheduler.h"
#include <stdarg.h>

void MyLog(const char* format, ...)
{
    va_list list;
    va_start(list, format);
    vprintf(format, list);
    va_end(list);
}

static unsigned int __objectCount = 0;

DUObject::DUObject()
{
    __objectCount++;
    //DU_LOG("object count is %d\n", __objectCount);
	m_count = 1;
}

DUObject::~DUObject()
{
    DUScheduler::getInstance()->unScheduleByObject(this);
    __objectCount--;
    //DU_LOG("~object count is %d\n", __objectCount);
}

DUObject* DUObject::retain()
{
	m_count++;
    return this;
}

void DUObject::release()
{
	m_count--;
    if(m_count <= 0)
    {
        delete this;
    }
}

void DUObject::printCount()
{
    DU_LOG("[%p]count is %d\n", this, m_count);
}
