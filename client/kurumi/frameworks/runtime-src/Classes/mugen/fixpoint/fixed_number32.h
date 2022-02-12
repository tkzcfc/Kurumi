#pragma once

#include "Fixed32.h"

// range[-32768.000000 32768.000000] 
class fixed_number32
{
public:
	fixed_number32(double _data)
		: m_data(Fixed32::FromDouble(_data))
    {}

	fixed_number32(float _data)
		: m_data(Fixed32::FromFloat(_data))
    {}
	
    fixed_number32()
		: m_data(0)
    {}

    fixed_number32(const fixed_number32& other)
		: m_data(other.m_data)
    {}

    static fixed_number32 make(const Fixed32::FP_INT& ival)
    {
		return fixed_number32(ival);
    }

    fixed_number32& operator +=(const fixed_number32& other)
    {
		m_data = Fixed32::Add(m_data, other.m_data);
        return *this;
    }

    fixed_number32& operator -=(const fixed_number32& other)
    {
		m_data = Fixed32::Sub(m_data, other.m_data);
        return *this;
    }

    fixed_number32& operator *=(const fixed_number32& other)
    {
		m_data = Fixed32::Mul(m_data, other.m_data);
        return *this;
    }

    fixed_number32& operator /=(const fixed_number32& other)
    {
		m_data = Fixed32::Div(m_data, other.m_data);
        return *this;
    }

    fixed_number32& operator %=(const fixed_number32& other)
    {
		m_data = Fixed32::Mod(m_data, other.m_data);
        return *this;
    }

    fixed_number32 operator+ (const fixed_number32& other) const
    {
		return fixed_number32(m_data) += other;
    }

    fixed_number32 operator- (const fixed_number32& other) const
    {
		return fixed_number32(m_data) -= other;
    }

    fixed_number32 operator* (const fixed_number32& other) const
    {
		return fixed_number32(m_data) *= other;
    }

    fixed_number32 operator/ (const fixed_number32& other) const
    {
		return fixed_number32(m_data) /= other;
    }

    fixed_number32 operator% (const fixed_number32& other) const
    {
		return fixed_number32(m_data) %= other;
    }

    fixed_number32 operator -() const
    {
		return fixed_number32(-m_data);
    }

    bool operator > (const fixed_number32& other) const
    {
		return m_data > other.m_data;
    }

    bool operator >= (const fixed_number32& other) const
    {
		return m_data >= other.m_data;
    }

    bool operator < (const fixed_number32& other) const
    {
		return m_data < other.m_data;
    }

    bool operator <= (const fixed_number32& other) const
    {
		return m_data <= other.m_data;
    }

    bool operator == (const fixed_number32& other) const
    {
		return m_data == other.m_data;
    }

    bool operator != (const fixed_number32& other) const
    {
		return m_data != other.m_data;
    }
	
    fixed_number32 floor() const
    {
		return Fixed32::Floor(m_data);
    }

    fixed_number32 ceil() const
    {
		return Fixed32::Ceil(m_data);
    }

    fixed_number32 abs() const
    {
		return Fixed32::Abs(m_data);
    }

    fixed_number32 sqrt() const
    {
		return Fixed32::Sqrt(m_data);
    }

    fixed_number32 pow(const fixed_number32& other) const
    {
		return Fixed32::Pow(m_data, other.m_data);
    }

    fixed_number32 sin() const
    {
		return Fixed32::Sin(m_data);
    }

    fixed_number32 cos() const
    {
		return Fixed32::Cos(m_data);
    }

    fixed_number32 tan() const
    {
		return Fixed32::Tan(m_data);
    }

    fixed_number32 asin() const
    {
		return Fixed32::Asin(m_data);
    }

    fixed_number32 acos() const
    {
		return Fixed32::Acos(m_data);
    }

    fixed_number32 atan() const
    {
		return Fixed32::Atan(m_data);
    }

    fixed_number32 atan(const fixed_number32& x) const
    {
		return Fixed32::Atan2(m_data, x.m_data);
    }

    fixed_number32 exp() const
    {
		return Fixed32::Exp(m_data);
    }

    fixed_number32 log() const
    {
		return Fixed32::Log(m_data);
    }

	float to_float() const
	{
		return Fixed32::ToFloat(m_data);
	}

	double to_double() const
	{
		return Fixed32::ToDouble(m_data);
	}

	Fixed32::FP_INT data() const
	{
		return m_data;
	}

	bool isZero() const
	{
		return m_data == Fixed32::Zero;
	}

	void setZero()
	{
		m_data = Fixed32::Zero;
	}
	
private:
	fixed_number32(const Fixed32::FP_INT& _data)
		: m_data(_data)
	{}

private:
	Fixed32::FP_INT m_data;
};
