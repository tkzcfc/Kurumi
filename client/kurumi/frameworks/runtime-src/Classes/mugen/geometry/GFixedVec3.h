#pragma once

#include "mugen/base/GObject.h"

NS_G_BEGIN

struct GFixedVec3
{
	GFixedVec3() {}

	GFixedVec3(fixedPoint _x, fixedPoint _y, fixedPoint _z)
		: x(_x)
		, y(_y)
		, z(_z)
	{}

	GFixedVec3(const GFixedVec3& other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
	}

	void setZero()
	{
		x.setZero();
		y.setZero();
		z.setZero();
	}


	GFixedVec3 operator-(void) const
	{
		return(GFixedVec3(-x, -y, -z));
	}


	GFixedVec3 operator*(fixedPoint s) const
	{
		return(GFixedVec3(x * s, y * s, z * s));
	}


	GFixedVec3 operator/(fixedPoint s) const
	{
		return(GFixedVec3(x / s, y / s, z / s));
	}


	void operator*=(fixedPoint s)
	{
		x *= s;
		y *= s;
		z *= s;
	}


	GFixedVec3 operator+(const GFixedVec3 & rhs) const
	{
		return(GFixedVec3(x + rhs.x, y + rhs.y, z + rhs.z));
	}


	GFixedVec3 operator+(fixedPoint s) const
	{
		return(GFixedVec3(x + s, y + s, z + s));
	}


	void operator+=(const GFixedVec3 & rhs)
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
	}


	GFixedVec3 operator-(const GFixedVec3 & rhs) const
	{
		return(GFixedVec3(x - rhs.x, y - rhs.y, z - rhs.z));
	}


	void operator-=(const GFixedVec3 & rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
	}

	fixedPoint x;
	fixedPoint y;
	fixedPoint z;

	/** equals to GFixedVec3(0,0,0) */
	static const GFixedVec3 ZERO;
	/** equals to GFixedVec3(1,1,1) */
	static const GFixedVec3 ONE;
	/** equals to GFixedVec3(1,0,0) */
	static const GFixedVec3 UNIT_X;
	/** equals to GFixedVec3(0,1,0) */
	static const GFixedVec3 UNIT_Y;
	/** equals to GFixedVec3(0,0,1) */
	static const GFixedVec3 UNIT_Z;
};


G_FORCEINLINE GFixedVec3 operator*(fixedPoint s, const GFixedVec3 & v)
{
	return(GFixedVec3(s * v.x, s * v.y, s * v.z));
}


NS_G_END
