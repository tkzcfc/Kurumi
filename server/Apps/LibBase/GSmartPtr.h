#ifndef GSmartPtr_hpp
#define GSmartPtr_hpp

#include "GObject.h"

template <typename T>
class GSmartPtr
{
    T* m_ptr;
public:
    
    GSmartPtr()
    {
        m_ptr = NULL;
    }
    
    GSmartPtr(T* ptr)
    {
        m_ptr = ptr;
        if(m_ptr)
        {
            m_ptr->retain();
        }
    }
    
    GSmartPtr(const GSmartPtr& other)
    {
        m_ptr = other.m_ptr;
        if(m_ptr)
        {
            m_ptr->retain();
        }
    }
    
    ~GSmartPtr()
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
    
    const GSmartPtr& operator = (const GSmartPtr& other)
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
    
    const GSmartPtr& operator = (T* other)
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
    
    bool operator == (const GSmartPtr& other)
    {
        return (m_ptr == other.m_ptr);
    }
};

#endif /* GSmartPtr_hpp */
