#pragma once

#include "../platform/GStdC.h"

NS_G_BEGIN

class GByteBuffer
{
public:
	GByteBuffer();
	GByteBuffer(uint32_t capacity);
	GByteBuffer(uint8_t* buffer, uint32_t capacity);
	virtual ~GByteBuffer();

	void resetPosition(uint32_t pos = 0U);
	void readFinish();
	void writeFinish();
	uint8_t* data();
	uint32_t len();

	bool getBool(bool& value);
	void writeBool(const bool& value);
	
	bool getInt8(int8_t& value);
	void writeInt8(const int8_t& value);
	
	bool getByte(byte& value);
	void writeByte(const byte& value);
	
	bool getInt16(int16_t& value);
	void writeInt16(const int16_t& value);
	
	bool getUint16(uint16_t& value);
	void writeUint16(const uint16_t& value);
	
	bool getInt32(int32_t& value);
	void writeInt32(const int32_t& value);
	
	bool getUint32(uint32_t& value);
	void writeUint32(const uint32_t& value);
	
	bool getInt64(int64_t& value);
	void writeInt64(const int64_t& value);

	bool getUint64(uint64_t& value);
	void writeUint64(const uint64_t& value);

	bool getFloat32(float32& value);
	void writeFloat32(const float32& value);

	bool getFloat64(float64& value);
	void writeFloat64(const float64& value);

	bool getFixedPoint(fixedPoint& value);
	void writeFixedPoint(const fixedPoint& value);

	bool getString(std::string& value);
	void writeString(const std::string& value);

	void writeBinary(byte* data, uint32_t len);

	bool readBool();
	int8_t readInt8();
	byte readByte();
	int16_t readInt16();
	uint16_t readUint16();
	int32_t readInt32();
	uint32_t readUint32();
	int64_t readInt64();
	uint64_t readUint64();
	float32 readFloat32();
	float64 readFloat64();
	fixedPoint readFixedPoint();
	std::string readString();
protected:

	void resize(uint32_t addLen);

	G_FORCEINLINE uint32_t getWriteLimit() 
	{
		G_ASSERT(m_position <= m_capacity);
		return m_capacity - m_position; 
	}

	G_FORCEINLINE uint32_t getReadLimit() 
	{
		G_ASSERT(m_position <= m_size);
		return m_size - m_position; 
	}

	G_FORCEINLINE uint8_t* ptr() 
	{ 
		return m_buffer + m_position; 
	}

	G_SYNTHESIZE_READONLY(uint32_t, m_position, Position);
	G_SYNTHESIZE_READONLY(uint32_t, m_size, Size);
	G_SYNTHESIZE_READONLY(uint32_t, m_capacity, Capacity);
	G_SYNTHESIZE_READONLY(uint8_t*, m_buffer, Buffer);
};

NS_G_END