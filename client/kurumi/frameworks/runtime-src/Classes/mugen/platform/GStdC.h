#pragma once

#include <stdint.h>
#include "GPlatformDefine.h"
#include <vector>
#include <string>
#include <unordered_map>
#include <map>
#include "../fixPoint/fixed_number32.h"
#include "../fixPoint/fixed_number64.h"

typedef uint8_t byte;
typedef float float32;
typedef double float64;

#define USE_FIXPOINT_32_BIT 0

#if USE_FIXPOINT_32_BIT
typedef fixed_number32 fixedPoint;
#else
typedef fixed_number64 fixedPoint;
#endif

inline float deal_float(float x)
{
	return int(x * 10000.0f) / 10000.0f;
}

