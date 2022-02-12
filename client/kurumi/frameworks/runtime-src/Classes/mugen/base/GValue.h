#pragma once

#include "../platform/GStdC.h"

NS_G_BEGIN

typedef enum _ValueType
{
	eNullValue = 0,
	eBoolValue,
	eInt8Value,
	eByteValue,
	eInt16Value,
	eUint16Value,
	eInt32Value,
	eUint32Value,
	eInt64Value,
	eUint64Value,
	eFloat32Value,
	eFloat64Value,
	eTimeValue,
	eStringValue,
	eBinaryValue

} GValueType;

typedef union _ValueData
{
	bool m_bool;
	int8_t m_int8;
	byte m_byte;
	int16_t m_int16;
	uint16_t m_uint16;
	int32_t m_int32;
	uint32_t m_uint32;
	int64_t m_int64;
	uint64_t m_uint64;
	float32 m_float32;
	float64 m_float64;
	time_t m_time;
	void* m_ptr;

} GValueData;

class GValue
{
public:
	GValue();
	GValue(const bool& value);
	GValue(const int8_t& value);
	GValue(const byte& value);
	GValue(const int16_t& value);
	GValue(const uint16_t& value);
	GValue(const int32_t& value);
	GValue(const uint32_t& value);
	GValue(const int64_t& value);
	GValue(const uint64_t& value);
	GValue(const float32& value);
	GValue(const float64& value);
	GValue(time_t time);
	GValue(const std::string& str);
	GValue(const char* str);
	GValue(const void* ptr, size_t len);
	GValue(const GValue& other);
	virtual ~GValue();

	GValue& operator=(const GValue& other);
	bool operator<(const GValue &other) const;
	bool operator<=(const GValue &other) const;
	bool operator>=(const GValue &other) const;
	bool operator>(const GValue &other) const;
	bool operator==(const GValue &other) const;
	bool operator!=(const GValue &other) const;

	const bool& getBool() const { return m_uData.m_bool; }
	void setBool(const bool& value) { m_uData.m_bool = value; }

	const int8_t& getInt8() const { return m_uData.m_int8; }
	void setInt8(const int8_t& value) { m_uData.m_int8 = value; }

	const byte& getByte() const { return m_uData.m_byte; }
	void setByte(const byte& value) { m_uData.m_byte = value; }

	const int16_t& getInt16() const { return m_uData.m_int16; }
	void setInt16(const int16_t& value) { m_uData.m_int16 = value; }

	const uint16_t& getUint16() const { return m_uData.m_uint16; }
	void setUint16(const uint16_t& value) { m_uData.m_uint16 = value; }

	const int32_t& getInt32() const { return m_uData.m_int32; }
	void setInt32(const int32_t& value) { m_uData.m_int32 = value; }

	const uint32_t& getUint32() const { return m_uData.m_uint32; }
	void setUint32(const uint32_t& value) { m_uData.m_uint32 = value; }

	const int64_t& getInt64() const { return m_uData.m_int64; }
	void setInt64(const int64_t& value) { m_uData.m_int64 = value; }

	const uint64_t& getUint64() const { return m_uData.m_uint64; }
	void setUint64(const uint64_t& value) { m_uData.m_uint64 = value; }

	const float32& getFloat32() { return m_uData.m_float32; }
	void setFloat32(const float32& value) { m_uData.m_float32 = value; }

	const float64& getFloat64() const { return m_uData.m_float64; }
	void setFloat64(const float64& value) { m_uData.m_float64 = value; }

	const void* getVoid() const { return m_uData.m_ptr; }
	void setVoid(void* value) { m_uData.m_ptr = value; }
	
	GValueType getType() { return m_eType; }

private:
	GValueData m_uData;
	size_t m_iLen;
	GValueType m_eType;
};

NS_G_END
