#pragma once

#include "mugen/base/GObject.h"
#include "../../geometry/GGeometry.h"
#include "../../collision/GShape.h"
#include "mugen/base/GEntity.h"

NS_G_BEGIN

enum GFrameType
{
	ATT_COLLISION_FRAME,
	DEF_COLLISION_FRAME,
	PHYSICAL_FORCE_FRAME,
	EVENT_FRAME,
	AUDIO_FRAME,
	SCRIPT_FRAME,
	MODIFY_FLAGS_FRAME,
	UNKNOWN_FRAME
};

class GTimeline;
class GSkill;
class GActorComponent;
class GFrame : public GObject
{
public:
	GFrame();

	virtual ~GFrame();

	G_SYNTHESIZE(int32_t, m_startFrame, StartFrame);
	G_SYNTHESIZE(int32_t, m_frameLen, FrameLen);
	G_SYNTHESIZE(int32_t, m_type, Type);
	G_SYNTHESIZE(GTimeline*, m_timeline, Timeline);
	G_SYNTHESIZE_READONLY(GEntity*, m_pEntity, Entity);

	GComponent* getComponent(const std::string& name);

	GSkill* getSkill();

	virtual void onEnter(int32_t currentFrameIndex);

	virtual void onUpdate(int32_t currentFrameIndex);

	virtual void onExit(int32_t currentFrameIndex);

public:

	virtual void serialize(GByteBuffer& byteBuffer) override;

	virtual bool deserialize(GByteBuffer& byteBuffer) override;

public:

	virtual bool contain(int32_t frame);
	
};

NS_G_END
