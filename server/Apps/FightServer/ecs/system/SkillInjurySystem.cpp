
#include "SkillInjurySystem.h"
#include "ecs/utils/CommonUtils.h"

// 技能攻击间隔
static const int SKILL_ATTACK_DELAY = 10;


//  攻防差 = 攻击-防御
// ·结果范围：[攻击*0.1, 攻击]
inline int32_t ADdiff(int32_t att, int32_t def)
{
	return clampi32(att * 0.1f, att, att - def);
}




void SkillInjurySystem::update()
{
	GlobalComponent* pGlobal = NULL;
	anax::Entity* pEntity = NULL;

	auto& entities = this->getEntities();
	for (auto it : entities)
	{
		auto injuryListCom = it.getComponent<InjuryListComponent>();
		if (!injuryListCom.attacker.empty())
		{
			auto& defPro = it.getComponent<PropertyComponent>();
			// 不是死亡状态
			if (G_BIT_NO_EQUAL(defPro.status, G_PS_IS_DEATH))
			{
				if (pGlobal == NULL)
				{
					pGlobal = &CommonUtils::getGlobalComponent(this->getWorld());
				}

				for (auto att_it = injuryListCom.attacker.begin(); att_it != injuryListCom.attacker.end(); ++att_it)
				{
#if G_DEBUG
					if (false == CommonUtils::queryUUID(this->getWorld(), att_it->uuid, pEntity))
					{
						G_ASSERT(0);
					}
#endif
					if (pGlobal->gameLogicFrame - att_it->frame >= SKILL_ATTACK_DELAY)
					{
						// 通过uuid找到攻击者
						if (CommonUtils::queryUUID(this->getWorld(), att_it->uuid, pEntity))
						{
							auto& attPro = pEntity->getComponent<PropertyComponent>();

							// 技能伤害配置值
							const int32_t skillCfgAttack = 100;

							// 技能伤害值 = 技能配置值 * 攻防差
							auto value = ADdiff(attPro.attack, defPro.armor) * skillCfgAttack;
							defPro.HP -= value;
							if (defPro.HP <= 0)
							{
								defPro.HP = 0;
								G_BIT_SET(defPro.status, G_PS_IS_DEATH);
							}
						}
					}
				}
			}
		}
	}
}


bool SkillInjurySystem::contain(const std::vector<InjuryListComponent::InjuryInfo>& list, GUUID uuid)
{
	if (list.empty())
		return false;

	for (auto& it : list)
	{
		if (it.uuid == uuid)
			return true;
	}
	return false;
}

void SkillInjurySystem::remove(std::vector<InjuryListComponent::InjuryInfo>& list, GUUID uuid)
{
	if (list.empty())
		return;
	for (auto it = list.begin(); it != list.end(); )
	{
		if (it->uuid == uuid)
		{
			it = list.erase(it);
		}
		else
			++it;
	}
}

void SkillInjurySystem::add(std::vector<InjuryListComponent::InjuryInfo>& list, GUUID uuid, uint32_t frame)
{
	for (auto& it : list)
	{
		if (it.uuid == uuid)
		{
			it.frame = frame;
			return;
		}
	}
	InjuryListComponent::InjuryInfo info;
	info.uuid = uuid;
	info.frame = frame;
	list.emplace_back(info);
}
