#pragma once

#include "GVec2.h"

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
		this->set(0);
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


