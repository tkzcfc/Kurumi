#pragma once

#include "mugen/platform/GStdC.h"
#include "mugen/serialize/GByteBuffer.h"
#include <functional>
#include <memory>

#ifndef RUNTIME_IN_COOCS
#define RUNTIME_IN_COOCS 1
#endif

#if RUNTIME_IN_COOCS == 1
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
USING_NS_CC;
#define G_LOG CCLOG
#else
#define G_LOG(...)       do {} while (0)
#endif


NS_G_BEGIN

class GObject
{
public:

	GObject();

	virtual ~GObject();

	virtual void serialize(GByteBuffer& byteBuffer);

	virtual bool deserialize(GByteBuffer& byteBuffer);

	virtual void copySpecialProperties(GObject* other);

	static int32_t getObjectCount();
};

template <typename T>
static T* clone(T& other)
{
	GByteBuffer buffer(sizeof(T));
	other.serialize(buffer);

	buffer.writeFinish();

	T* ptr = new(std::nothrow) T();
	if (ptr == NULL)
		return NULL;

	if (!ptr->deserialize(buffer))
	{
		delete ptr;
		return NULL;
	}
	ptr->copySpecialProperties(&other);
	return ptr;
}

NS_G_END