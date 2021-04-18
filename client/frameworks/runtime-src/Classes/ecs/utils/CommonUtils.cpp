#include "CommonUtils.h"

#include "ecs/components/TransformComponent.h"
#include "ecs/components/PropertyComponent.h"
#include "ecs/components/InputComponent.h"
#include "ecs/system/GlobalSystem.h"
#include "ecs/system/SIMPhysSystem.h"
#include "ecs/system/UUIDSystem.h"
#include "ecs/utils/ArmatureUtils.h"

#include "foundation/file/GFileUtiles.h"

#include "ecs/utils/animator/GActorStateMachine.h"
#include "ecs/utils/animator/dao/DaoStateMachine.h"

namespace CommonUtils
{
	anax::Entity& getAdmin(anax::World& world)
	{
		auto sys = world.getSystem<GlobalSystem>();
		G_ASSERT(sys != NULL);

		return sys->admin;
	}

	GlobalComponent& getGlobalComponent(anax::World& world)
	{
		auto sys = world.getSystem<GlobalSystem>();
		G_ASSERT(sys != NULL);

		return sys->admin.getComponent<GlobalComponent>();
	}

	bool initMapSize(anax::Entity& admin, int mapId)
	{
		char szPath[256] = { 0 };
		sprintf(szPath, "json/map/mi_%d.json", mapId);

		std::string content;
		if (!GFileUtiles::readFileString(szPath, content))
			return false;

		if (content.empty())
			return false;

		rapidjson::Document json;
		rapidjson::StringStream stream(content.c_str());

		json.ParseStream<0>(stream);
		if (json.HasParseError())
		{
			G_LOG_E("initMapSize : GetParseError %d\n", json.GetParseError());
			return false;
		}

		if (json.HasMember("infos") == false)
			return false;

		auto it = json.FindMember("infos");
		auto& arr = it->value;
		if (arr.IsArray() == false)
			return false;

		for (auto i = 0; i < arr.Size(); ++i)
		{
			auto& item = arr[i];
			if (!item.FindMember("ignore")->value.GetBool() && item.HasMember("actor") && item.FindMember("actor")->value.GetBool())
			{
				auto& component = admin.getComponent<GlobalComponent>();
				component.mapWidth = (float)item.FindMember("w")->value.GetDouble();
				component.mapHeight = (float)item.FindMember("h")->value.GetDouble();
				component.minPosy = (float)item.FindMember("miny")->value.GetDouble();
				component.maxPosy = (float)item.FindMember("maxy")->value.GetDouble();
				return true;
			}
		}
		return false;
	}


#if G_TARGET_CLIENT
	DrawNode* getDebugDraw(anax::World& world)
	{
		return getGlobalComponent(world).debugDrawNode;
	}
#endif

	bool spawnActor(anax::World& world, ActorIdentityInfo& info, anax::Entity* outActor)
	{
		// 读取动画状态机文件内容
		std::string fsmContent;
		if (!GFileUtiles::readFileString(info.anifsm, fsmContent) || fsmContent.empty())
			return false;
		
		auto entity = world.createEntity();

		// 添加变换组件
		auto& transform = entity.addComponent<TransformComponent>();
		
		// 添加输入组件
		auto& input = entity.addComponent<InputComponent>();

		// 添加物理组件
		SIMPhysSystem::createBox(entity, info.originPos, info.bodySize, GVec2(0.5f, 0.5f));

		// 添加动画组件
		ArmatureUtils::initAnimationComponent(entity);
		// 动画角色切换
		ArmatureUtils::changeRole(entity, info.roleName);
		// 默认动画播放
		ArmatureUtils::playAnimationCMD(entity, "ANI_NAME_FIGHT_STAND", kArmaturePlayMode::LOOP);
		
		// 添加属性组件
		auto& propertyCom = entity.addComponent<PropertyComponent>();
		propertyCom.uuid = info.uuid;
		propertyCom.moveForce = info.moveForce;
		propertyCom.jumpIm = info.jumpIm;
		propertyCom.moveMaxVelocityX = info.moveMaxVelocityX;
		
		// 创建动画状态机
		std::shared_ptr<GActorStateMachine> stateMachine = NULL;

		//if (info.roleName == "")
		//{
		//	stateMachine = std::make_shared<GActorStateMachine>();
		//}
		//else
			stateMachine = std::make_shared<GActorStateMachine>();

		// 动画状态机初始化
		stateMachine->setEntity(entity);
		if (!stateMachine->initWithJson(fsmContent))
		{
			entity.kill();
			return false;
		}

		propertyCom.stateMachine = stateMachine;

		*outActor = entity;

		return true;
	}

	GUUID genUUID(anax::World& world)
	{
		auto& global = getGlobalComponent(world);
		return global.uuidSeed++;
	}

	bool queryUUID(anax::World& world, GUUID uuid, anax::Entity* pEntity)
	{
		auto pSys = world.getSystem<UUIDSystem>();
		if (pSys)
		{
			return pSys->query(uuid, pEntity);
		}
		return false;
	}
}
