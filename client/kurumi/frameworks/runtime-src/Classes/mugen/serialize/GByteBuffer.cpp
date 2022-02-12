#include "GByteBuffer.h"

NS_G_BEGIN

#define USE_ENDIAN 0

#if USE_ENDIAN
#include "endian.h"
#define G_USE_BIG_ENDIAN 1
#endif

#define READ_CHECK_RETURN_FALSE(len) if (getReadLimit() < (len)) return false
#define WRITE_CHECK_AND_RESIZE(len) if (getWriteLimit() < (len)) this->resize(len)


GByteBuffer::GByteBuffer()
: m_buffer(nullptr)
, m_capacity(0)
, m_size(0)
, m_position(0U)
{
	resize(0);
}

GByteBuffer::GByteBuffer(uint32_t capacity)
{
	m_capacity = capacity;
	m_buffer = new byte[m_capacity];
	m_position = 0U;
	m_size = 0U;
}

GByteBuffer::GByteBuffer(uint8_t* buffer, uint32_t capacity)
{
	m_size = capacity;
	m_capacity = capacity;
	m_position = 0U;

	if (m_capacity > 0)
	{
		m_buffer = new byte[m_capacity];
		::memcpy(m_buffer, buffer, m_capacity);
	}
}

GByteBuffer::~GByteBuffer()
{
	if (m_buffer)
	{
		delete[] m_buffer;
		m_buffer = nullptr;
	}
}

void GByteBuffer::resetPosition(uint32_t pos)
{
	G_ASSERT(pos < m_capacity);
	m_position = pos;
}

void GByteBuffer::readFinish()
{
	resetPosition(0U);
}

void GByteBuffer::writeFinish()
{
	m_size = m_position;
	resetPosition();
}

uint8_t* GByteBuffer::data()
{
	return m_buffer;
}

uint32_t GByteBuffer::len()
{
	return m_size;
}

void GByteBuffer::resize(uint32_t addLen)
{
	auto oldCapacity = m_capacity;

	m_capacity *= 2;
	m_capacity = MAX(m_capacity, 128);

	if (m_capacity < oldCapacity + addLen)
	{
		m_capacity += addLen;
	}

	if (m_buffer == nullptr)
	{
		m_buffer = new byte[m_capacity];
	}
	else
	{
		auto oldBuf = m_buffer;
		m_buffer = new byte[m_capacity];

		::memcpy(m_buffer, oldBuf, m_position);

		delete[] oldBuf;
	}
}

bool GByteBuffer::getBool(bool& value)
{
	byte bval;
	if (getByte(bval))
	{
		value = bval != 0;
		return true;
	}
	return false;
}

void GByteBuffer::writeBool(const bool& value)
{
	writeByte(value ? 1 : 0);
}

bool GByteBuffer::getInt8(int8_t& value)
{
	byte tmp;
	if (getByte(tmp))
	{
		value = (int8_t)tmp;
		return true;
	}
	return false;
}

void GByteBuffer::writeInt8(const int8_t& value)
{
	writeByte((byte)value);
}

bool GByteBuffer::getByte(byte& value)
{
	READ_CHECK_RETURN_FALSE(sizeof(byte));

	auto p = (byte*)ptr();
	value = *p;

	m_position += sizeof(byte);
	return true;
}

void GByteBuffer::writeByte(const byte& value)
{
	WRITE_CHECK_AND_RESIZE(sizeof(byte));

	(*(byte*)ptr()) = value;
	m_position += sizeof(byte);
}

bool GByteBuffer::getInt16(int16_t& value)
{
	uint16_t tmp;
	if (getUint16(tmp))
	{
		value = (int16_t)tmp;
		return true;
	}
	return false;
}

void GByteBuffer::writeInt16(const int16_t& value)
{
	writeUint16((uint16_t)value);
}

bool GByteBuffer::getUint16(uint16_t& value)
{
	READ_CHECK_RETURN_FALSE(sizeof(uint16_t));

#if USE_ENDIAN
#if G_USE_BIG_ENDIAN
	value = readUint16InBigEndian(ptr());
#else
	value = readUint16InLittleEndian(ptr());
#endif
#else
	auto p = (uint16_t*)ptr();
	value = *p;
#endif

	m_position += sizeof(uint16_t);
	return true;
}

void GByteBuffer::writeUint16(const uint16_t& value)
{
	WRITE_CHECK_AND_RESIZE(sizeof(uint16_t));

#if USE_ENDIAN
#if G_USE_BIG_ENDIAN
	writeUint16InBigEndian(ptr(), value);
#else
	writeUint16InLittleEndian(ptr(), value);
#endif
#else
	(*(uint16_t*)ptr()) = value;
#endif

	m_position += sizeof(uint16_t);
}

bool GByteBuffer::getInt32(int32_t& value)
{
	uint32_t tmp;
	if (getUint32(tmp))
	{
		value = (int32_t)tmp;
		return true;
	}
	return false;
}

void GByteBuffer::writeInt32(const int32_t& value)
{
	writeUint32((uint32_t)value);
}

bool GByteBuffer::getUint32(uint32_t& value)
{
	READ_CHECK_RETURN_FALSE(sizeof(uint32_t));

#if USE_ENDIAN
#if G_USE_BIG_ENDIAN
	value = readUint32InBigEndian(ptr());
#else
	value = readUint32InLittleEndian(ptr());
#endif
#else
	auto p = (uint32_t*)ptr();
	value = *p;
#endif

	m_position += sizeof(uint32_t);
	return true;
}
void GByteBuffer::writeUint32(const uint32_t& value)
{
	WRITE_CHECK_AND_RESIZE(sizeof(uint32_t));

#if USE_ENDIAN
#if G_USE_BIG_ENDIAN
	writeUint32InBigEndian(ptr(), value);
#else
	writeUint32InLittleEndian(ptr(), value);
#endif
#else
	(*(uint32_t*)ptr()) = value;
#endif

	m_position += sizeof(uint32_t);
}



bool GByteBuffer::getInt64(int64_t& value)
{
	uint64_t tmp;
	if (getUint64(tmp))
	{
		value = (int64_t)tmp;
		return true;
	}
	return false;
}

void GByteBuffer::writeInt64(const int64_t & value)
{
	writeUint64((uint64_t)value);
}

bool GByteBuffer::getUint64(uint64_t& value)
{
	READ_CHECK_RETURN_FALSE(sizeof(uint64_t));

#if USE_ENDIAN
#if G_USE_BIG_ENDIAN
	value = readUint64InBigEndian(ptr());
#else
	value = readUint64InLittleEndian(ptr());
#endif
#else
	auto p = (uint64_t*)ptr();
	value = *p;
#endif

	m_position += sizeof(uint64_t);
	return true;
}

void GByteBuffer::writeUint64(const uint64_t& value)
{
	WRITE_CHECK_AND_RESIZE(sizeof(uint64_t));

#if USE_ENDIAN
#if G_USE_BIG_ENDIAN
	writeUint64InBigEndian(ptr(), value);
#else
	writeUint64InLittleEndian(ptr(), value);
#endif
#else
	(*(uint64_t*)ptr()) = value;
#endif

	m_position += sizeof(uint64_t);
}



bool GByteBuffer::getFloat32(float32& value)
{
	READ_CHECK_RETURN_FALSE(sizeof(float32));

#if USE_ENDIAN
#if G_USE_BIG_ENDIAN
	value = readFloatInBigEndian(ptr());
#else
	value = readFloatInLittleEndian(ptr());
#endif
#else
	auto p = (float32*)ptr();
	value = *p;
#endif

	m_position += sizeof(float32);
	return true;
}

void GByteBuffer::writeFloat32(const float32& value)
{
	WRITE_CHECK_AND_RESIZE(sizeof(float32));
	
#if USE_ENDIAN
#if G_USE_BIG_ENDIAN
	writeFloatInBigEndian(ptr(), value);
#else
	writeFloatInLittleEndian(ptr(), value);
#endif
#else
	(*(float32*)ptr()) = value;
#endif

	m_position += sizeof(float32);
}

bool GByteBuffer::getFloat64(float64& value)
{
	READ_CHECK_RETURN_FALSE(sizeof(float64));

#if USE_ENDIAN
#if G_USE_BIG_ENDIAN
	value = readDoubleInBigEndian(ptr());
#else
	value = readDoubleInLittleEndian(ptr());
#endif
#else
	auto p = (float64*)ptr();
	value = *p;
#endif

	m_position += sizeof(float64);
	return true;
}

void GByteBuffer::writeFloat64(const float64& value)
{
	WRITE_CHECK_AND_RESIZE(sizeof(float64));

#if USE_ENDIAN
#if G_USE_BIG_ENDIAN
	writeDoubleInBigEndian(ptr(), value);
#else
	writeDoubleInLittleEndian(ptr(), value);
#endif
#else
	(*(float64*)ptr()) = value;
#endif

	m_position += sizeof(float64);
}

bool GByteBuffer::getFixedPoint(fixedPoint& value)
{
#if USE_FIXPOINT_32_BIT
	int32_t ival;
	if (getInt32(ival))
	{
		value = fixedPoint::make((Fixed32::FP_INT)ival);
		return true;
	}
#else
	int64_t ival;
	if (getInt64(ival))
	{
		value = fixedPoint::make((Fixed64::FP_LONG)ival);
		return true;
	}
#endif
	return false;
}

void GByteBuffer::writeFixedPoint(const fixedPoint& value)
{
#if USE_FIXPOINT_32_BIT
	writeInt32(value.data());
#else
	writeInt64(value.data());
#endif
}

bool GByteBuffer::getString(std::string& value)
{
	uint32_t length = 0;
	if (!getUint32(length))
	{
		return false;
	}

	if (length > 0)
	{
		READ_CHECK_RETURN_FALSE(length);
		value.append((char*)ptr(), length);
		m_position += length;
	}
	else
	{
		value = "";
	}
	return true;
}

void GByteBuffer::writeString(const std::string& value)
{
	writeBinary((byte*)value.c_str(), value.size());
}

void GByteBuffer::writeBinary(byte* data, uint32_t length)
{
	WRITE_CHECK_AND_RESIZE(length + 4);
	writeUint32(length);

	if(length > 0)
		::memcpy(ptr(), data, length);

	m_position += length;
}

bool GByteBuffer::readBool()
{
	bool value = false;
	getBool(value);
	return value;
}

int8_t GByteBuffer::readInt8()
{
	int8_t value = 0;
	getInt8(value);
	return value;
}

byte GByteBuffer::readByte()
{
	byte value = 0;
	getByte(value);
	return value;
}

int16_t GByteBuffer::readInt16()
{
	int16_t value = 0;
	getInt16(value);
	return value;
}

uint16_t GByteBuffer::readUint16()
{
	uint16_t value = 0;
	getUint16(value);
	return value;
}

int32_t GByteBuffer::readInt32()
{
	int32_t value = 0;
	getInt32(value);
	return value;
}

uint32_t GByteBuffer::readUint32()
{
	uint32_t value = 0;
	getUint32(value);
	return value;
}

int64_t GByteBuffer::readInt64()
{
	int64_t value = 0;
	getInt64(value);
	return value;
}

uint64_t GByteBuffer::readUint64()
{
	uint64_t value = 0;
	getUint64(value);
	return value;
}

float32 GByteBuffer::readFloat32()
{
	float32 value = 0.0f;
	getFloat32(value);
	return value;
}

float64 GByteBuffer::readFloat64()
{
	float64 value = 0.0;
	getFloat64(value);
	return value;
}

fixedPoint GByteBuffer::readFixedPoint()
{
	fixedPoint value;
	getFixedPoint(value);
	return value;
}

std::string GByteBuffer::readString()
{
	std::string value = "";
	getString(value);
	return value;
}

NS_G_END
