#include "CommonUtils.h"

#include "ecs/system/GlobalSystem.h"
#include "ecs/system/SIMPhysSystem.h"
#include "ecs/components/DebugComponent.h"
#include "ecs/utils/ArmatureUtils.h"

#include "foundation/file/GFileUtiles.h"
#include "json/document.h"
#include "json/stringbuffer.h"

anax::Entity& CommonUtils::getAdmin(anax::World& world)
{
	auto sys = world.getSystem<GlobalSystem>();
	G_ASSERT(sys != NULL);

	return sys->admin;
}

bool CommonUtils::initMapSize(anax::Entity& admin, int mapId)
{
	char szPath[256] = { 0 };
	sprintf(szPath, "map_export/mi_%d.json", mapId);

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
		CCLOG("GetParseError %d\n", json.GetParseError());
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
			auto& component = admin.getComponent<MapComponent>();
			component.mapWidth = item.FindMember("w")->value.GetDouble();
			component.mapHeight = item.FindMember("h")->value.GetDouble();
			component.minPosy = (float)item.FindMember("miny")->value.GetDouble();
			component.maxPosy = (float)item.FindMember("maxy")->value.GetDouble();
			return true;
		}
	}
	return false;
}


#if G_TARGET_CLIENT
DrawNode* CommonUtils::getDebugDraw(anax::World& world)
{
	auto& admin = CommonUtils::getAdmin(world);
	auto& component = admin.getComponent<DebugComponent>();
	return component.debugDrawNode;
}
#endif

bool CommonUtils::spawnActor(anax::World& world, ActorIdentityInfo& info, anax::Entity* outActor)
{
	auto entity = world.createEntity();

	// 物理信息
	SIMPhysSystem::createBox(entity, info.originPos, info.bodySize, GVec2(0.5f, 0.5f));

	// 动画信息
	ArmatureUtils::initAnimationComponent(entity);
	ArmatureUtils::changeRole(entity, info.roleName);

	*outActor = entity;

	return true;
}