#pragma once

#include "mugen/base/GObject.h"

NS_G_BEGIN


struct GFixedVec2
{
	GFixedVec2() {}

	GFixedVec2(fixedPoint _x, fixedPoint _y) 
		: x(_x)
		, y(_y)
	{}

	GFixedVec2(const GFixedVec2& other)
	{
		x = other.x;
		y = other.y;
	}


	void set(fixedPoint x_, fixedPoint y_)
	{
		x = x_;
		y = y_;
	}

	void setZero()
	{
		x.setZero();
		y.setZero();
	}

	GFixedVec2 operator-(void) const
	{
		return(GFixedVec2(-x, -y));
	}


	GFixedVec2 operator*(fixedPoint s) const
	{
		return(GFixedVec2(x * s, y * s));
	}


	GFixedVec2 operator/(fixedPoint s) const
	{
		return(GFixedVec2(x / s, y / s));
	}


	void operator*=(fixedPoint s)
	{
		x *= s;
		y *= s;
	}


	GFixedVec2 operator+(const GFixedVec2 & rhs) const
	{
		return(GFixedVec2(x + rhs.x, y + rhs.y));
	}


	GFixedVec2 operator+(fixedPoint s) const
	{
		return(GFixedVec2(x + s, y + s));
	}


	void operator+=(const GFixedVec2 & rhs)
	{
		x += rhs.x;
		y += rhs.y;
	}


	GFixedVec2 operator-(const GFixedVec2 & rhs) const
	{
		return(GFixedVec2(x - rhs.x, y - rhs.y));
	}


	void operator-=(const GFixedVec2 & rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
	}


	fixedPoint lenSqr(void) const
	{
		return(x * x + y * y);
	}


	fixedPoint length(void) const
	{
		auto tmp = x * x + y * y;
		return tmp.sqrt();
	}


	void rotate(fixedPoint radians)
	{
		fixedPoint c = radians.cos();
		fixedPoint s = radians.sin();
		fixedPoint xp = x * c - y * s;
		fixedPoint yp = x * s + y * c;
		x = xp;
		y = yp;
	}


	void normalize(void)
	{
		fixedPoint len = length();
		if (len > 0.0001f)
		{
			fixedPoint invLen = fixedPoint(1.0f) / len;
			x *= invLen;
			y *= invLen;
		}
	}

	fixedPoint x;
	fixedPoint y;
};


G_FORCEINLINE GFixedVec2 operator*(fixedPoint s, const GFixedVec2 & v)
{
	return(GFixedVec2(s * v.x, s * v.y));
}


G_FORCEINLINE fixedPoint dot(const GFixedVec2 & a, const GFixedVec2 & b)
{
	return(a.x * b.x + a.y * b.y);
}

G_FORCEINLINE fixedPoint distSqr(const GFixedVec2 & a, const GFixedVec2 & b)
{
	GFixedVec2 c = a - b;
	return(dot(c, c));
}


G_FORCEINLINE GFixedVec2 cross(const GFixedVec2 & v, fixedPoint a)
{
	return(GFixedVec2(a * v.y, -a * v.x));
}


G_FORCEINLINE GFixedVec2 cross(fixedPoint a, const GFixedVec2 & v)
{
	return(GFixedVec2(-a * v.y, a * v.x));
}


G_FORCEINLINE fixedPoint cross(const GFixedVec2 & a, const GFixedVec2 & b)
{
	return(a.x * b.y - a.y * b.x);
}


NS_G_END
