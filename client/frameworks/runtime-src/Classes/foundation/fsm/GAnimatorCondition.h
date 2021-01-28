#pragma once

#include "GState.h"

enum class GLogicType 
{
	EQUAL = 0,
	NOTEQUAL = 1,
	GREATER = 2,
	LESS = 3,
	GREATER_EQUAL = 4,
	LESS_EQUAL = 5,
	NONE
};

class GAnimatorParams;
/// 动画状态机条件
class GAnimatorCondition
{
public:

	GAnimatorCondition();

	GAnimatorCondition(GAnimatorParams* params, const std::string& paramName, int value, float fvalue, GLogicType logicType);

	// 检测条件是否通过
	bool check();

	virtual void clone(GAnimatorCondition* pCondition) const;

private:	
	// 条件所对应的参数名
	std::string m_paramName;
	// 条件判断右值
	int m_value;
	// 
	float m_fvalue;
	// 逻辑类型
	GLogicType m_logicType;
	// 参数指针
	GAnimatorParams* m_params;
};
