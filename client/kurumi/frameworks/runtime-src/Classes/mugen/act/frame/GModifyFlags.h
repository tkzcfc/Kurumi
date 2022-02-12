#pragma once

#include "GEventFrame.h"
#include "mugen/GGameDef.h"

NS_G_BEGIN

// 修改标记
class GModifyFlags : public GEventFrame
{
public:

	enum class ModifyFlagsType
	{
		BEGIN,
		ADD_FLAGS,
		REMOVE_FLAGS,
		MAX
	};

	GModifyFlags();

	virtual ~GModifyFlags();
	
	virtual void onEnter(int32_t currentFrameIndex) override;

	virtual void onEmit() override;

public:

	virtual void serialize(GByteBuffer& byteBuffer) override;

	virtual bool deserialize(GByteBuffer& byteBuffer) override;

private:
	G_SYNTHESIZE(ModifyFlagsType, m_modifyType, ModifyFlagsType);
	G_SYNTHESIZE(G_BIT_TYPE, m_flags, Flags);

	GActorComponent* m_actorComponent;
};

NS_G_END
