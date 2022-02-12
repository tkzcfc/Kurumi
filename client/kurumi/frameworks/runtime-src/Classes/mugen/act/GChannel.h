#pragma once

#include "condition/GCondition.h"
#include "action/GAction.h"

NS_G_BEGIN

class GSkill;

enum CheckType
{
	Continuous,	// 持续检测
	Once // 触发之后不再检测
};

/// 转换通道
class GChannel : public GObject
{
public:

	GChannel();
	
	virtual ~GChannel();

	virtual bool check();

	void addCondition(GCondition* pCondition);

	void clear();

	void reset();

	int32_t getConditionIndex(GCondition* condition);

public:

	virtual void serialize(GByteBuffer& byteBuffer);

	virtual bool deserialize(GByteBuffer& byteBuffer);

private:
	std::vector<GCondition*> m_conditions;

	G_SYNTHESIZE(GSkill*, m_skill, Skill);
	G_SYNTHESIZE(int32_t, m_nextSkillId, NextSkillId);
	G_SYNTHESIZE(GInterruptType, m_interruptType, InterruptType);
	// 检测类型
	G_SYNTHESIZE(CheckType, m_checkType, CheckType);
	// 是否触发过
	bool m_triggerTag;
};

NS_G_END