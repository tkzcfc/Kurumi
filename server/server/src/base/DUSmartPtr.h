//
//  DUSmartPtr.hpp
//  NNNN
//
//  Created by 方程 on 17/1/17.
//  Copyright © 2017年 lianshi. All rights reserved.
//

#ifndef DUSmartPtr_hpp
#define DUSmartPtr_hpp

#include "DUObject.h"

template <typename T>
class DUSmartPtr
{
    T* m_ptr;
public:
    
    DUSmartPtr()
    {
        m_ptr = NULL;
    }
    
    DUSmartPtr(T* ptr)
    {
        m_ptr = ptr;
        if(m_ptr)
        {
            m_ptr->retain();
        }
    }
    
    DUSmartPtr(const DUSmartPtr& other)
    {
        m_ptr = other.m_ptr;
        if(m_ptr)
        {
            m_ptr->retain();
        }
    }
    
    ~DUSmartPtr()
    {
        if(m_ptr)
        {
            m_ptr->release();
            m_ptr = NULL;
        }
    }
    
    T* operator ->()
    {
        return m_ptr;
    }
    
    T* GetPtr()
    {
        return m_ptr;
    }
    
    const DUSmartPtr& operator = (const DUSmartPtr& other)
    {
        if(m_ptr)
        {
            m_ptr->release();
            m_ptr = NULL;
        }
        m_ptr = other.m_ptr;
        if(m_ptr)
        {
            m_ptr->retain();
        }
        return *this;
    }
    
    const DUSmartPtr& operator = (T* other)
    {
        if(m_ptr)
        {
            m_ptr->release();
            m_ptr = NULL;
        }
        m_ptr = other;
        if(m_ptr)
        {
            m_ptr->retain();
        }
        return *this;
    }
    
    bool operator == (const T*& other)
    {
        return (m_ptr == other);
    }
    
    bool operator == (const DUSmartPtr& other)
    {
        return (m_ptr == other.m_ptr);
    }
};

#endif /* DUSmartPtr_hpp */
