#pragma once

#include "ecs/anaxHelper.h"

// 伤害列表组件
class InjuryListComponent : public BaseComponent
{
public:
	InjuryListComponent()
	{
		attacker.reserve(5);
		victims.reserve(5);
	}

	struct InjuryInfo
	{
		GUUID uuid;
		uint32_t frame;
	};

	// 攻击者
	std::vector<InjuryInfo> attacker;
	// 受击者
	std::vector<InjuryInfo> victims;
};


