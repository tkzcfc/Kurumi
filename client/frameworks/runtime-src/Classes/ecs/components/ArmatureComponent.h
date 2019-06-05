#pragma once

#include "ecs/anaxHelper.h"
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "lua_function/LuaFunction.h"

struct ArmatureCollisionRect
{
	cocos2d::Vec2 v[4];
};

// 骨骼动画组件
class ArmatureComponent : public anax::Component, public Ref
{
public:
	ArmatureComponent() 
	{
		m_armature = NULL;
	}

	virtual ~ArmatureComponent() 
	{
		//if (m_armature)
		//{
		//	m_armature->removeFromParent();
		//	m_armature = NULL;
		//}
	}

	cocostudio::Armature* m_armature;
	cocos2d::Node* m_owner;
};

// 骨骼动画碰撞组件
class ArmatureCollisionComponent : public anax::Component, public Ref
{
public:
	ArmatureCollisionComponent()
		: m_defCacheDirty(true)
		, m_attCacheDirty(true)
	{
		m_defRectCache.reserve(5);
		m_attRectCache.reserve(5);
	}
	virtual ~ArmatureCollisionComponent() {}

	// 作为攻击者碰撞回调
	LuaFunction m_attCollisionCall;
	// 作为受击者碰撞回调
	LuaFunction m_defCollisionCall;

	bool m_defCacheDirty;
	bool m_attCacheDirty;

	// 碰撞矩形缓存
	std::vector<ArmatureCollisionRect> m_defRectCache;
	std::vector<ArmatureCollisionRect> m_attRectCache;
};

// 骨骼动画碰撞过滤组件
class CollisionFilterComponent : public anax::Component, public Ref
{
public:
	CollisionFilterComponent() 
	{
		m_groupIndex = 0;
		m_collisionEnable = false;
	}
	virtual ~CollisionFilterComponent() {}
	
	int m_groupIndex;
	bool m_collisionEnable;
};

DEFINE_COMPONENT(ArmatureComponent);
DEFINE_COMPONENT(ArmatureCollisionComponent);
DEFINE_COMPONENT(CollisionFilterComponent);

