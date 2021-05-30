#include "anaxHelper.h"
#include "ECSDefine.h"

std::unordered_map<std::string, SystemHelper*> AnaxHelper::GSystemHelperMap;
std::unordered_map<std::string, ComponentHelper*> AnaxHelper::GComponentHelperMap;

void AnaxHelper::implementation()
{
	// IMPLEMENT_BEGIN
	//! Generated by the "autoCode.lua".  DO NOT EDIT!
	IMPLEMENTATION_COMPONENT(ArmatureComponent);
	IMPLEMENTATION_COMPONENT(ArmatureRenderComponent);
	IMPLEMENTATION_COMPONENT(BodyComponent);
	IMPLEMENTATION_COMPONENT(BuffComponent);
	IMPLEMENTATION_COMPONENT(FilterBitsComponent);
	IMPLEMENTATION_COMPONENT(GlobalComponent);
	IMPLEMENTATION_COMPONENT(InjuryListComponent);
	IMPLEMENTATION_COMPONENT(InputComponent);
	IMPLEMENTATION_COMPONENT(PropertyComponent);
	IMPLEMENTATION_COMPONENT(SIMPhysComponent);
	IMPLEMENTATION_COMPONENT(TransformComponent);
	IMPLEMENTATION_SYSTEM(ArmatureDebugSystem);
	#if G_TARGET_CLIENT
	IMPLEMENTATION_SYSTEM(ArmatureRenderSystem);
	#endif
	IMPLEMENTATION_SYSTEM(ArmatureSystem);
	IMPLEMENTATION_SYSTEM(BuffSystem);
	IMPLEMENTATION_SYSTEM(CollisionSystem);
	IMPLEMENTATION_SYSTEM(GlobalSystem);
	IMPLEMENTATION_SYSTEM(InputSystem);
	IMPLEMENTATION_SYSTEM(PhysicsSystem);
	IMPLEMENTATION_SYSTEM(SIMPhysSystem);
	IMPLEMENTATION_SYSTEM(SkillInjurySystem);
	IMPLEMENTATION_SYSTEM(TransformSyncSystem);
	IMPLEMENTATION_SYSTEM(UpdateSystem);
	IMPLEMENTATION_SYSTEM(UUIDSystem);
	// IMPLEMENT_END



}

