#pragma once

#include "GTranslation.h"
#include "GAnimatorCondition.h"

/// 动画状态转换通道
class GAnimatorTranslation : public GTranslation
{
public:

	GAnimatorTranslation();

	GAnimatorTranslation(const FStateKeyType& toState);

	// 添加转换条件
	void addCondition(const GAnimatorCondition& condition);

	// 
	inline void setHasExitTime(bool value);

	inline bool hasExitTime();

protected:

	virtual bool polling(GState* curState)override;

	virtual bool progressEvent(GState* curState, const FEventNameType& evetName)override;

private:

	std::vector<GAnimatorCondition> m_conditions;

	// 为true则表示在该动作完成后才允许切换,但是一般我们要的都是立即切换,所以默认为false
	bool m_hasExitTime;
};

void GAnimatorTranslation::setHasExitTime(bool value)
{
	m_hasExitTime = value;
}

bool GAnimatorTranslation::hasExitTime()
{
	return m_hasExitTime;
}
