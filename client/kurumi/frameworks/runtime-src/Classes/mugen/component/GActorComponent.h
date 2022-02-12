#pragma once

#include "mugen/base/GComponent.h"
#include "mugen/act/GSkill.h"
#include "mugen/GGameDef.h"

NS_G_BEGIN

class GActorComponent : public GComponent, public GBody, public GActionDelegate
{
public:
	G_DEFINE_COMPONENT(GActorComponent);

	GActorComponent();

	virtual ~GActorComponent();

	/// GObject
	virtual void serialize(GByteBuffer& byteBuffer) override;

	virtual bool deserialize(GByteBuffer& byteBuffer) override;

	// GActionDelegate
	virtual void onPlayAnimation(const std::string& name, int32_t frame) override;

	/// GComponent
	virtual void onUpdate() override;

public:

	void addSkill(GSkill* skill);

	void clearSkill();

	GSkill* getSkill(int32_t id);

	void doSkill(int32_t id);
	
	///////////////////////////// 输入相关 /////////////////////////////

	// 按键按下
	void onKeyDown(G_BIT_TYPE key);
	// 按键持续按下
	void onKeepPress(G_BIT_TYPE key);
	// 按键抬起
	void onKeyUp(G_BIT_TYPE key);

	// 判断按键是否按下
	bool isKeyDown(G_BIT_TYPE key);


	// 设置坐标
	void setPosition(const fixedPoint& posx, const fixedPoint& posy);

private:

	void doSkillEx(int32_t id);

	void updateTransform();

	G_SYNTHESIZE_READONLY_BY_REF(std::vector<GSkill*>, m_skills, Skills);
	G_SYNTHESIZE(int32_t, m_nextSkillId, NextSkillId);
	G_SYNTHESIZE(int32_t, m_defaultSkillId, DefaultSkillId);
	G_SYNTHESIZE_READONLY(GSkill*, m_curSkill, CurSkill);

	G_SYNTHESIZE(G_BIT_TYPE, m_status, Status);
	G_SYNTHESIZE(G_BIT_TYPE, m_flags, Flags);
	G_SYNTHESIZE(GActorOrientation, m_orientation, Orientation);
	G_SYNTHESIZE_READONLY_BY_REF(GFixedVec2, m_logicPos, LogicPos);
	G_SYNTHESIZE_READONLY_BY_REF(fixedPoint, m_jumpHeight, JumpHeight);

public:

	///////////////////////////// 输入相关 /////////////////////////////
	// 上一帧按键状态
	G_BIT_TYPE lastKeyDown;
	// 当前按下的键
	G_BIT_TYPE curKeyDown;
};

NS_G_END
