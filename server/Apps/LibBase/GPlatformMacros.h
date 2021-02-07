#pragma once

#include "net_uv.h"
#include <iostream>
#include <assert.h>
#include "easylogging++.h"
#include "GPlatformConfig.h"

#define G_ASSERT(x) assert(x)

#define G_SAFE_DELETE(x) if(x) { delete x; x = NULL; }
#define G_SAFE_DELETE_ARRAY(x) if(x) { delete []x; x = NULL; }

#define G_BREAK_IF(cond)           if(cond) break

// G_FORCEINLINE
#if defined(AE_VCPP) || defined(AE_ICC)
#define G_FORCEINLINE __forceinline
#elif defined(AE_GCC)
//#define G_FORCEINLINE __attribute__((always_inline)) 
#define G_FORCEINLINE inline
#else
#define G_FORCEINLINE inline
#endif
