#pragma once

#include "GEventFrame.h"
#include "mugen/GGameDef.h"

NS_G_BEGIN

enum class GPhysicalForceType
{
	// 力
	FORCE,
	// 冲力
	IMPULSE,
	// 匀速移动
	MOVEMENT,
};

// 力施加帧
class GPhysicalForceFrame : public GEventFrame
{
public:

	GPhysicalForceFrame();

	virtual ~GPhysicalForceFrame();

	G_SYNTHESIZE(GPhysicalForceType, m_forceType, ForceType);
	G_SYNTHESIZE(GForceOrientation, m_forceOrientation, ForceOrientation);
	G_SYNTHESIZE(GValueType, m_valueType, ValueType);
	G_SYNTHESIZE(GFixedVec3, m_value, Value);

	virtual void onEnter(int32_t currentFrameIndex) override;

	virtual void onEmit() override;

public:

	virtual void serialize(GByteBuffer& byteBuffer) override;

	virtual bool deserialize(GByteBuffer& byteBuffer) override;

private:
	class GRigidBodyComponent* m_pRigidBodyComponent;
	class GDataComponent* m_pDataComponent;
	class GActorComponent* m_pActorComponent;
};

NS_G_END
