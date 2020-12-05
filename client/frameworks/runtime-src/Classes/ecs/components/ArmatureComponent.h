#pragma once

#include "ecs/anaxHelper.h"
#include "foundation/animator/GAnimData.h"

enum kArmaturePlayMode
{
	ONCE = 0,
	LOOP
};

struct ArmatureCollisionRect
{
	cocos2d::Vec2 v[4];
};

// 骨骼动画组件
class ArmatureComponent : public anax::Component
{
public:
	ArmatureComponent() 
	{}
	// 当前帧
	uint32_t curFrameIndex;
	// 当前动作动画名
	std::string curAniName;
	// 动画文件
	std::string aniFile;
	// 当前动画命令
	std::string curAniCMD;
	// 角色名
	std::string roleName;

	kArmaturePlayMode mode;
	bool playing;
};



//
//// 骨骼动画碰撞组件
//class ArmatureCollisionComponent : public anax::Component, public Ref
//{
//public:
//	ArmatureCollisionComponent()
//		: m_defCacheDirty(true)
//		, m_attCacheDirty(true)
//	{
//		m_defRectCache.reserve(5);
//		m_attRectCache.reserve(5);
//	}
//	virtual ~ArmatureCollisionComponent() {}
//
//	// 作为攻击者碰撞回调
//	LuaFunction m_attCollisionCall;
//	// 作为受击者碰撞回调
//	LuaFunction m_defCollisionCall;
//
//	bool m_defCacheDirty;
//	bool m_attCacheDirty;
//
//	// 碰撞矩形缓存
//	std::vector<ArmatureCollisionRect> m_defRectCache;
//	std::vector<ArmatureCollisionRect> m_attRectCache;
//};
//
//// 骨骼动画碰撞过滤组件
//class CollisionFilterComponent : public anax::Component, public Ref
//{
//public:
//	CollisionFilterComponent() 
//	{
//		m_groupIndex = 0;
//		m_collisionEnable = false;
//	}
//	virtual ~CollisionFilterComponent() {}
//	
//	int m_groupIndex;
//	bool m_collisionEnable;
//};

DEFINE_COMPONENT(ArmatureComponent);
//DEFINE_COMPONENT(ArmatureCollisionComponent);
//DEFINE_COMPONENT(CollisionFilterComponent);

