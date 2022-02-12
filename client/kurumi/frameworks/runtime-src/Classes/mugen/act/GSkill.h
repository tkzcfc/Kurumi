#pragma once

#include "timeline/GTrack.h"
#include "action/GAction.h"
#include "GChannel.h"
#include "mugen/base/GEntity.h"

NS_G_BEGIN


class GActorComponent;
class GSkill : public GObject
{
public:

	GSkill();

	virtual ~GSkill();

	virtual void serialize(GByteBuffer& byteBuffer) override;

	virtual bool deserialize(GByteBuffer& byteBuffer) override;

	void reset();
	
	bool step();

	void addAction(GAction* action);

	void clearAction();

	void addChannel(GChannel* channel);

	void clearChannel();

	// @brief 中断
	void interrupt(GInterruptType type);

	int32_t getChannelIndex(GChannel* channel);

	GEntity* getEntity();

private:

	void onEnter();
	
	void onExit();

public:

	// 轨道
	G_SYNTHESIZE_READONLY(GTrack*, m_track, Track);
	// 技能名
	G_SYNTHESIZE(std::string, m_name, Name);
	// 技能id
	G_SYNTHESIZE(int32_t, m_id, Id);


	// 技能总帧数
	G_SYNTHESIZE(int32_t, m_totalFrame, TotalFrame);
	// 当前帧数
	G_SYNTHESIZE_READONLY(int32_t, m_curFrame, CurFrame);


	// 技能循环次数（小于等于0则为无限循环）
	G_SYNTHESIZE(int32_t, m_totalLoopCount, TotalLoopCount);
	// 当前循环次数
	G_SYNTHESIZE_READONLY(int32_t, m_curLoopCount, CurLoopCount);


	// 当前动作
	G_SYNTHESIZE_READONLY(GAction*, m_curAction, CurAction);
	// 当前动作下标
	G_SYNTHESIZE_READONLY(int32_t, m_curActionIdx, CurActionIdx);
	// 技能动作合集
	G_SYNTHESIZE_READONLY_BY_REF(std::vector<GAction*>, m_actions, Actions);


	// 转换通道
	G_SYNTHESIZE_READONLY_BY_REF(std::vector<GChannel*>, m_channels, Channel);


	G_SYNTHESIZE(GActorComponent*, m_actorComponent, ActorComponent);
	
	// 动作代理
	G_PROPERTY_WRITEONLY(GActionDelegate*, m_actionDelegate, ActionDelegate);

	GInterruptType m_interrupt;
};

NS_G_END
