#ifndef GObject_hpp
#define GObject_hpp

#include "GPlatformMacros.h"

class GObject
{
public:
    GObject();
    
    virtual ~GObject();
    
    virtual GObject* retain();
    
    virtual void release();
    
    void printCount();
    
protected:
    unsigned int m_count;
};

#endif /* GObject_hpp */
