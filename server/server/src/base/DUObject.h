//
//  DUObject.hpp
//  NNNN
//
//  Created by 方程 on 17/1/17.
//  Copyright © 2017年 lianshi. All rights reserved.
//

#ifndef DUObject_hpp
#define DUObject_hpp

#include <iostream>
#include <assert.h>


void MyLog(const char* format, ...);

#define DU_LOG(format, ...) MyLog(format, ##__VA_ARGS__)
#define DU_ASSERT(x) assert(x)

#define DU_SAFE_DELETE(x) if(x) { delete x; x = NULL; }
#define DU_SAFE_DELETE_ARRAY(x) if(x) { delete []x; x = NULL; }

#define DU_MAX(x, y) ((x) > (y)) ? (x) : (y)
#define DU_MIN(x, y) ((x) < (y)) ? (x) : (y)

class DUObject
{
public:
    DUObject();
    
    ~DUObject();
    
    virtual DUObject* retain();
    
    virtual void release();
    
    void printCount();
    
protected:
    unsigned int m_count;
};

#endif /* DUObject_hpp */
