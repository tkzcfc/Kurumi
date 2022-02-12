#pragma once

#include "Fixed64.h"

// range[-2147483648.000000 2147483648.000000]
class fixed_number64
{
public:
	fixed_number64(double _data)
		: m_data(Fixed64::FromDouble(_data))
    {}

	fixed_number64(float _data)
		: m_data(Fixed64::FromFloat(_data))
    {}
	
    fixed_number64()
		: m_data(0)
    {}

	fixed_number64(const fixed_number64& other)
		: m_data(other.m_data)
    {}

    static fixed_number64 make(const Fixed64::FP_LONG& ival)
    {
		return fixed_number64(ival);
    }

    fixed_number64& operator +=(const fixed_number64& other)
    {
		m_data = Fixed64::Add(m_data, other.m_data);
        return *this;
    }

    fixed_number64& operator -=(const fixed_number64& other)
    {
		m_data = Fixed64::Sub(m_data, other.m_data);
        return *this;
    }

    fixed_number64& operator *=(const fixed_number64& other)
    {
		m_data = Fixed64::Mul(m_data, other.m_data);
        return *this;
    }

    fixed_number64& operator /=(const fixed_number64& other)
    {
		m_data = Fixed64::Div(m_data, other.m_data);
        return *this;
    }

    fixed_number64& operator %=(const fixed_number64& other)
    {
		m_data = Fixed64::Mod(m_data, other.m_data);
        return *this;
    }

    fixed_number64 operator+ (const fixed_number64& other) const
    {
		return fixed_number64(m_data) += other;
    }

    fixed_number64 operator- (const fixed_number64& other) const
    {
		return fixed_number64(m_data) -= other;
    }

    fixed_number64 operator* (const fixed_number64& other) const
    {
		return fixed_number64(m_data) *= other;
    }

    fixed_number64 operator/ (const fixed_number64& other) const
    {
		return fixed_number64(m_data) /= other;
    }

    fixed_number64 operator% (const fixed_number64& other) const
    {
		return fixed_number64(m_data) %= other;
    }

    fixed_number64 operator -() const
    {
		return fixed_number64(-m_data);
    }

    bool operator > (const fixed_number64& other) const
    {
		return m_data > other.m_data;
    }

    bool operator >= (const fixed_number64& other) const
    {
		return m_data >= other.m_data;
    }

    bool operator < (const fixed_number64& other) const
    {
		return m_data < other.m_data;
    }

    bool operator <= (const fixed_number64& other) const
    {
		return m_data <= other.m_data;
    }

    bool operator == (const fixed_number64& other) const
    {
		return m_data == other.m_data;
    }

    bool operator != (const fixed_number64& other) const
    {
		return m_data != other.m_data;
    }
	
    fixed_number64 floor() const
    {
		return Fixed64::Floor(m_data);
    }

    fixed_number64 ceil() const
    {
		return Fixed64::Ceil(m_data);
    }

    fixed_number64 abs() const
    {
		return Fixed64::Abs(m_data);
    }

    fixed_number64 sqrt() const
    {
		return Fixed64::Sqrt(m_data);
    }

    fixed_number64 pow(const fixed_number64& other) const
    {
		return Fixed64::Pow(m_data, other.m_data);
    }

    fixed_number64 sin() const
    {
		return Fixed64::Sin(m_data);
    }

    fixed_number64 cos() const
    {
		return Fixed64::Cos(m_data);
    }

    fixed_number64 tan() const
    {
		return Fixed64::Tan(m_data);
    }

    fixed_number64 asin() const
    {
		return Fixed64::Asin(m_data);
    }

    fixed_number64 acos() const
    {
		return Fixed64::Acos(m_data);
    }

    fixed_number64 atan() const
    {
		return Fixed64::Atan(m_data);
    }

    fixed_number64 atan(const fixed_number64& x) const
    {
		return Fixed64::Atan2(m_data, x.m_data);
    }

    fixed_number64 exp() const
    {
		return Fixed64::Exp(m_data);
    }

    fixed_number64 log() const
    {
		return Fixed64::Log(m_data);
    }

	float to_float() const
	{
		return Fixed64::ToFloat(m_data);
	}

	double to_double() const
	{
		return Fixed64::ToDouble(m_data);
	}

	Fixed64::FP_LONG data() const
	{
		return m_data;
	}

	bool isZero() const
	{
		return m_data == Fixed64::Zero;
	}

	void setZero()
	{
		m_data = Fixed64::Zero;
	}
	
private:
	fixed_number64(Fixed64::FP_LONG _data)
		: m_data(_data)
	{}

private:
	Fixed64::FP_LONG m_data;

public:

};
