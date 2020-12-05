#pragma once

#include <stdint.h>
#include <cmath>        /* abs, sqrt */
#include <cassert>      /* assert */
#include <algorithm>    /* max, min */

typedef float	float32;
typedef double	float64;
typedef float   real;

const float32	G_PI = 3.141592741f;
const float32	G_EPSILON = 0.0001f;



inline bool equal(float32 a, float32 b)
{
	return(std::abs(a - b) <= G_EPSILON);
}


inline float32 sqr(float32 a)
{
	return(a * a);
}


inline float32 clamp(float32 min, float32 max, float32 a)
{
	if (a < min)
		return(min);
	if (a > max)
		return(max);
	return(a);
}

#ifndef MIN
#define MIN(x,y) (((x) > (y)) ? (y) : (x))
#endif  // MIN

#ifndef MAX
#define MAX(x,y) (((x) < (y)) ? (y) : (x))
#endif  // MAX

