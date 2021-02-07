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

	GAnimatorCondition(GAnimatorParams* params, const std::string& paramName);

	bool initConditionI(int value, GLogicType logicType);

	bool initConditionB(bool value, GLogicType logicType);

	bool initConditionF(float value, GLogicType logicType);

	bool initConditionP(const std::string param, GLogicType logicType);

	bool initConditionT();

	// 检测条件是否通过
	bool check();

	virtual void clone(GAnimatorCondition* pCondition) const;

private:

	// 右值类型
	enum class GRightValueType
	{
		INT,	// int值
		FLOAT,	// float值
		BOOL,	// bool值
		PARAM	// 动态参数
	};

private:
	// 参数hash值
	int m_paramHash;

	// 条件判断右值
	union
	{
		float fvalue;
		int ivalue;
		bool bvalue;
		int hash;
	}m_value;
	bool m_compareWithParam;

	// 逻辑类型
	GLogicType m_logicType;
	// 参数指针
	GAnimatorParams* m_params;
};
