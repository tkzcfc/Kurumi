#include "ArmatureUtils.h"
#include "ecs/system/CollisionSystem.h"
#include "foundation/animator/GAnimCMD.h"


void ArmatureUtils::getAllAnimationData(anax::World& world, std::vector<GAnimationData*>& outDatas)
{
	CollisionSystem* system = world.getSystem<CollisionSystem>();
	if (system == NULL)
	{
		G_ASSERT(false);
		return;
	}

	outDatas.reserve(system->getEntities().size());

	GAnimationData* data = NULL;
	for (auto& it : system->getEntities())
	{
		data = system->getAnimData(it.getComponent<ArmatureComponent>());
		if (data != NULL)
		{
			outDatas.push_back(data);
		}
	}
}

void ArmatureUtils::initAnimationComponent(anax::Entity& entity)
{
	G_ASSERT(!entity.hasComponent<ArmatureComponent>());

	auto& component = entity.addComponent<ArmatureComponent>();
	component.curFrameIndex = 0;
	component.curAniName = "";
	component.curAniCMD = "";
	component.roleName = "";
	component.playing = false;
	component.mode = kArmaturePlayMode::ONCE;


	G_ASSERT(!entity.hasComponent<ArmatureRenderComponent>());

	auto& renderComponent = entity.addComponent<ArmatureRenderComponent>();
	renderComponent.actionType = kArmatureRenderAction::NONE;
	renderComponent.render = NULL;
}

void ArmatureUtils::changeRole(anax::Entity& entity, const std::string& roleName)
{
	G_ASSERT(entity.hasComponent<ArmatureComponent>());
	auto& component = entity.getComponent<ArmatureComponent>();
	component.curFrameIndex = 0;
	component.curAniName = "";
	component.curAniCMD = "";
	component.roleName = roleName;
	component.playing = false;
	component.mode = kArmaturePlayMode::ONCE;

	auto& renderComponent = entity.getComponent<ArmatureRenderComponent>();
	renderComponent.actionType = kArmatureRenderAction::NONE;
}

void ArmatureUtils::playAnimationCMD(anax::Entity& entity, const std::string& cmdName, kArmaturePlayMode mode)
{
	G_ASSERT(entity.hasComponent<ArmatureComponent>());

	auto& component = entity.getComponent<ArmatureComponent>();

	auto cmd = GAnimCMDCache::getInstance()->getOrCreate(component.roleName);
	G_ASSERT(cmd != NULL);
	if (cmd == NULL) return;

	auto cmdData = cmd->get(cmdName);
	G_ASSERT(cmdData != NULL);
	if (cmdData == NULL) return;

	G_ASSERT(cmdData->actions.empty() == false);
	if (cmdData->actions.empty()) return;

	component.curFrameIndex = 0;
	component.curAniName = cmdData->actions[0];
	component.curAniCMD = cmdName;
	component.playing = true;
	component.mode = mode;

	G_ASSERT(entity.hasComponent<ArmatureRenderComponent>());
	auto& renderComponent = entity.getComponent<ArmatureRenderComponent>();
	renderComponent.actionType = kArmatureRenderAction::RUN;
}

