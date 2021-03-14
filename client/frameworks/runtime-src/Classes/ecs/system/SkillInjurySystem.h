#pragma once

#include "ecs/components/InjuryListComponent.h"
#include "ecs/components/PropertyComponent.h"

// 技能伤害系统
class SkillInjurySystem : public anax::System< anax::Requires<InjuryListComponent, PropertyComponent> >
{
public:

	void update();
	
public:

	static bool contain(const std::vector<InjuryListComponent::InjuryInfo>& list, GUUID uuid);

	static void remove(std::vector<InjuryListComponent::InjuryInfo>& list, GUUID uuid);

	static void add(std::vector<InjuryListComponent::InjuryInfo>& list, GUUID uuid, uint32_t frame);
};

