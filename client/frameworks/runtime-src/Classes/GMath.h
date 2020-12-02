#pragma once
#include <stdint.h>
#include <cmath>        /* abs, sqrt */
#include <cassert>      /* assert */
#include <algorithm>    /* max, min */
typedef float	float32;
typedef double	float64;
const float32	PI = 3.141592741f;
const float32	EPSILON = 0.0001f;
class GVec2 {
public:
	union {
		float32 m[1][1];
		float32 v[2];
		struct {
			float32 x;
			float32 y;
		}
		;
	}
	;
	GVec2()
	{
		x = y = 0.0f;
	}


	GVec2(float32 x_, float32 y_)
		: x(x_)
		, y(y_)
	{
	}


	void set(float32 x_, float32 y_)
	{
		x = x_;
		y = y_;
	}


	GVec2 operator-(void) const
	{
		return(GVec2(-x, -y));
	}


	GVec2 operator*(float32 s) const
	{
		return(GVec2(x * s, y * s));
	}


	GVec2 operator/(float32 s) const
	{
		return(GVec2(x / s, y / s));
	}


	void operator*=(float32 s)
	{
		x *= s;
		y *= s;
	}


	GVec2 operator+(const GVec2 & rhs) const
	{
		return(GVec2(x + rhs.x, y + rhs.y));
	}


	GVec2 operator+(float32 s) const
	{
		return(GVec2(x + s, y + s));
	}


	void operator+=(const GVec2 & rhs)
	{
		x += rhs.x;
		y += rhs.y;
	}


	GVec2 operator-(const GVec2 & rhs) const
	{
		return(GVec2(x - rhs.x, y - rhs.y));
	}


	void operator-=(const GVec2 & rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
	}


	float32 lenSqr(void) const
	{
		return(x * x + y * y);
	}


	float32 length(void) const
	{
		return(std::sqrt(x * x + y * y));
	}


	void rotate(float32 radians)
	{
		float32 c = std::cos(radians);
		float32 s = std::sin(radians);
		float32 xp = x * c - y * s;
		float32 yp = x * s + y * c;
		x = xp;
		y = yp;
	}


	void normalize(void)
	{
		float32 len = length();
		if (len > EPSILON)
		{
			float32 invLen = 1.0f / len;
			x *= invLen;
			y *= invLen;
		}
	}
}
;
inline GVec2 operator*(float s, const GVec2 & v)
{
	return(GVec2(s * v.x, s * v.y));
}


class GMat2 {
public:
	union {
		struct {
			float32 m00, m01;
			float32 m10, m11;
		}
		;
		float32 m[2][2];
		float32 v[4];
	}
	;
	GMat2()
	{
	}


	GMat2(float32 radians)
	{
		float32 c = std::cos(radians);
		float32 s = std::sin(radians);
		m00 = c;
		m01 = -s;
		m10 = s;
		m11 = c;
	}


	GMat2(float32 a, float32 b, float32 c, float32 d)
		: m00(a), m01(b)
		, m10(c), m11(d)
	{
	}


	void set(float32 radians)
	{
		float32 c = std::cos(radians);
		float32 s = std::sin(radians);
		m00 = c;
		m01 = -s;
		m10 = s;
		m11 = c;
	}


	GMat2 abs(void) const
	{
		return(GMat2(std::abs(m00), std::abs(m01), std::abs(m10), std::abs(m11)));
	}


	GVec2 axisX(void) const
	{
		return(GVec2(m00, m10));
	}


	GVec2 axisY(void) const
	{
		return(GVec2(m01, m11));
	}


	GMat2 transpose(void) const
	{
		return(GMat2(m00, m10, m01, m11));
	}


	const GVec2 operator*(const GVec2 & rhs) const
	{
		return(GVec2(m00 * rhs.x + m01 * rhs.y, m10 * rhs.x + m11 * rhs.y));
	}


	const GMat2 operator*(const GMat2 & rhs) const
	{
		/*
		 * [00 01] [00 01]
		 * [10 11] [10 11]
		 */
		return(GMat2(
			m[0][0] * rhs.m[0][0] + m[0][1] * rhs.m[1][0],
			m[0][0] * rhs.m[0][1] + m[0][1] * rhs.m[1][1],
			m[1][0] * rhs.m[0][0] + m[1][1] * rhs.m[1][0],
			m[1][0] * rhs.m[0][1] + m[1][1] * rhs.m[1][1]
		));
	}
};

class GVec3
{
public:
	union {
		float32 v[3];
		struct {
			float32 x;
			float32 y;
			float32 z;
		}
		;
	}
	;
	GVec3()
	{
		x = y = z = 0.0f;
	}
};


inline GVec2 min(const GVec2 & a, const GVec2 & b)
{
	return(GVec2(std::min(a.x, b.x), std::min(a.y, b.y)));
}


inline GVec2 max(const GVec2 & a, const GVec2 & b)
{
	return(GVec2(std::max(a.x, b.x), std::max(a.y, b.y)));
}


inline float32 dot(const GVec2 & a, const GVec2 & b)
{
	return(a.x * b.x + a.y * b.y);
}


inline float32 distSqr(const GVec2 & a, const GVec2 & b)
{
	GVec2 c = a - b;
	return(dot(c, c));
}


inline GVec2 cross(const GVec2 & v, float32 a)
{
	return(GVec2(a * v.y, -a * v.x));
}


inline GVec2 cross(float32 a, const GVec2 & v)
{
	return(GVec2(-a * v.y, a * v.x));
}


inline float32 cross(const GVec2 & a, const GVec2 & b)
{
	return(a.x * b.y - a.y * b.x);
}


/* Comparison with tolerance of EPSILON */
inline bool equal(float32 a, float32 b)
{
	/* <= instead of < for NaN comparison safety */
	return(std::abs(a - b) <= EPSILON);
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