#include "GObject.h"

NS_G_BEGIN

static int32_t kObjectCount = 0;

GObject::GObject() 
{
	kObjectCount++;
}

GObject::~GObject() 
{
	kObjectCount--;
}

void GObject::serialize(GByteBuffer& byteBuffer) 
{}

bool GObject::deserialize(GByteBuffer& byteBuffer)
{ 
	return true; 
}

void GObject::copySpecialProperties(GObject* other) 
{
}

int32_t GObject::getObjectCount()
{
	return kObjectCount;
}

NS_G_END