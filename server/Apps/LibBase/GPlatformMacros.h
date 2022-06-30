#pragma once

#include "net_uv.h"
#include <iostream>
#include <assert.h>
#include "easylogging++.h"
#include "GPlatformConfig.h"

#define G_ASSERT(x) assert(x)

#define G_DEBUG _DEBUG

#define G_SAFE_DELETE(x) if(x) { delete x; x = NULL; }
#define G_SAFE_DELETE_ARRAY(x) if(x) { delete []x; x = NULL; }

#define G_BREAK_IF(cond)           if(cond) break

#define G_ARRAY_LEN(array) sizeof(array) / sizeof(array[0])

// G_FORCEINLINE
#if defined(AE_VCPP) || defined(AE_ICC)
#define G_FORCEINLINE __forceinline
#elif defined(AE_GCC)
//#define G_FORCEINLINE __attribute__((always_inline)) 
#define G_FORCEINLINE inline
#else
#define G_FORCEINLINE inline
#endif

#define G_CHECK_NULL_RETURN(con) if(con == NULL) { LOG(ERROR) << "file:" << __FILE__ << "function:" << __FUNCTION__ << "line:" << __LINE__; return; }
#define G_CHECK_NULL_RETURN_NULL(con) if(con == NULL) { LOG(ERROR) << "file:" << __FILE__ << "function:" << __FUNCTION__ << "line:" << __LINE__; return NULL; }

#define G_SYNTHESIZE(varType, varName, funName)\
protected: varType varName; public: virtual inline varType get##funName(void) const { return varName; } virtual inline void set##funName(varType var){ varName = var; }

#define G_SYNTHESIZE_READONLY(varType, varName, funName)\
protected: varType varName; public: virtual inline varType get##funName(void) const { return varName; }

#define G_SYNTHESIZE_PASS_BY_REF(varType, varName, funName)\
protected: varType varName; public: virtual inline const varType& get##funName(void) const { return varName; } virtual inline void set##funName(const varType& var){ varName = var; }

#define G_PROPERTY(varType, varName, funName)\
protected: varType varName; public: virtual varType get##funName(void) const; virtual void set##funName(varType var);

#define G_PROPERTY_READONLY(varType, varName, funName)\
protected: varType varName; public: virtual varType get##funName(void)

#define G_PROPERTY_PASS_BY_REF(varType, varName, funName)\
protected: varType varName; public: virtual const varType& get##funName(void) const; virtual void set##funName(const varType& var);

