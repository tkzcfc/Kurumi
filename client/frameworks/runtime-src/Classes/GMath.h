#pragma once
#include <stdint.h>
#include <cmath>        /* abs, sqrt */
#include <cassert>      /* assert */
#include <algorithm>    /* max, min */
typedef float	float32;
typedef double	float64;
const float32	G_PI = 3.141592741f;
const float32	G_EPSILON = 0.0001f;


/*
 * inline int32_t round( float32 a )
 * {
 * return (int32_t)(a + 0.5f);
 * }
 * inline float32 random( float32 l, float32 h )
 * {
 * float32 a = (float32)rand( );
 * a /= RAND_MAX;
 * a = (h - l) * a + l;
 * return a;
 * }
 * inline bool biasGreaterThan( float32 a, float32 b )
 * {
 * const float32 k_biasRelative = 0.95f;
 * const float32 k_biasAbsolute = 0.01f;
 * return a >= b * k_biasRelative + a * k_biasAbsolute;
 * }
 * const f32 gravityScale = 5.0f;
 * const GVec2 gravity( 0, 10.0f * gravityScale );
 * const float dt = 1.0f / 60.0f;
 */