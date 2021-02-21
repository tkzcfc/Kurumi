#include "CommonUtils.h"

#include "ecs/components/TransformComponent.h"
#include "ecs/components/PropertyComponent.h"
#include "ecs/components/InputComponent.h"
#include "ecs/system/GlobalSystem.h"
#include "ecs/system/SIMPhysSystem.h"
#include "ecs/utils/ArmatureUtils.h"

#include "foundation/file/GFileUtiles.h"

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
		auto entity = world.createEntity();

		// 位置信息
		auto& transform = entity.addComponent<TransformComponent>();
		
		auto& input = entity.addComponent<InputComponent>();

		// 物理信息
		SIMPhysSystem::createBox(entity, info.originPos, info.bodySize, GVec2(0.5f, 0.5f));

		// 动画信息
		ArmatureUtils::initAnimationComponent(entity);
		ArmatureUtils::changeRole(entity, info.roleName);
		ArmatureUtils::playAnimationCMD(entity, "ANI_NAME_FIGHT_STAND", kArmaturePlayMode::LOOP);


		std::string content;
		GFileUtiles::readFileString("json/runtimeData.json", content);
		//
		auto& propertyCom = entity.addComponent<PropertyComponent>();
		propertyCom.uuid = info.uuid;
		propertyCom.moveForce = GVec2(100.0f, 10.0f);
		propertyCom.jumpIm = GVec2(0.0f, 300.0f);
		propertyCom.stateMachine->init(entity);
		propertyCom.stateMachine->initWithJson(content);

		*outActor = entity;

		return true;
	}
}
