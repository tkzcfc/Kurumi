#pragma once

#include "GMathCommon.h"

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
		if (len > G_EPSILON)
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

