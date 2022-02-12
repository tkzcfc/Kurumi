#include "GStaticDataComponent.h"

NS_G_BEGIN


GStaticDataComponent::GStaticDataComponent()
{
	directionLeft = false;
}

GStaticDataComponent::~GStaticDataComponent()
{
}

/// GObject
void GStaticDataComponent::serialize(GByteBuffer& byteBuffer)
{
	GComponent::serialize(byteBuffer);

	byteBuffer.writeBool(directionLeft);
	byteBuffer.writeFixedPoint(mass);

	byteBuffer.writeFixedPoint(size.x);
	byteBuffer.writeFixedPoint(size.y);
	byteBuffer.writeFixedPoint(size.z);

	byteBuffer.writeFixedPoint(moveSpeed.x);
	byteBuffer.writeFixedPoint(moveSpeed.y);

	byteBuffer.writeFixedPoint(force.x);
	byteBuffer.writeFixedPoint(force.y);
	byteBuffer.writeFixedPoint(force.z);

	byteBuffer.writeFixedPoint(impulse.x);
	byteBuffer.writeFixedPoint(impulse.y);
	byteBuffer.writeFixedPoint(impulse.z);

	byteBuffer.writeFixedPoint(radius);
	
	byteBuffer.writeFixedPoint(offset.x);
	byteBuffer.writeFixedPoint(offset.y);

	byteBuffer.writeString(armatureFile);
	byteBuffer.writeString(binaryFileName);
}

bool GStaticDataComponent::deserialize(GByteBuffer& byteBuffer)
{
	do
	{
		G_BREAK_IF(!GComponent::deserialize(byteBuffer));

		G_BREAK_IF(!byteBuffer.getBool(directionLeft));
		G_BREAK_IF(!byteBuffer.getFixedPoint(mass));

		G_BREAK_IF(!byteBuffer.getFixedPoint(size.x));
		G_BREAK_IF(!byteBuffer.getFixedPoint(size.y));
		G_BREAK_IF(!byteBuffer.getFixedPoint(size.z));

		G_BREAK_IF(!byteBuffer.getFixedPoint(moveSpeed.x));
		G_BREAK_IF(!byteBuffer.getFixedPoint(moveSpeed.y));

		G_BREAK_IF(!byteBuffer.getFixedPoint(force.x));
		G_BREAK_IF(!byteBuffer.getFixedPoint(force.y));
		G_BREAK_IF(!byteBuffer.getFixedPoint(force.z));

		G_BREAK_IF(!byteBuffer.getFixedPoint(impulse.x));
		G_BREAK_IF(!byteBuffer.getFixedPoint(impulse.y));
		G_BREAK_IF(!byteBuffer.getFixedPoint(impulse.z));

		G_BREAK_IF(!byteBuffer.getFixedPoint(radius));

		G_BREAK_IF(!byteBuffer.getFixedPoint(offset.x));
		G_BREAK_IF(!byteBuffer.getFixedPoint(offset.y));

		G_BREAK_IF(!byteBuffer.getString(armatureFile));
		G_BREAK_IF(!byteBuffer.getString(binaryFileName));

		return true;
	} while (false);
	return false;
}

NS_G_END

