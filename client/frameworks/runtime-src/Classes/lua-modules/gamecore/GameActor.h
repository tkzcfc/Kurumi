﻿#pragma once

#include "GameAttribute.h"
#include "FSM.h"
#include "cocostudio/CocoStudio.h"

using namespace cocostudio;
using namespace cocos2d;

struct ActorRect
{
	Vec2 v[4];
};

enum GameActorType
{
	AT_MONSTER,
	AT_NPC,
	AT_PLAYER,
	AT_NONE
};

class GameWord;
class GameActor : public Node
{
public:
	static GameActor* create();

	GameActor();

	virtual ~GameActor();

	virtual bool init() override;

	inline GameAttribute* getGameAttribute() { return &m_gameAttribute; }

	inline QFSM* getFSM() { return &m_FSM; }

	inline Armature* getArmature() { return m_armature; }

	inline GameWord* getGameWord() { return m_word; }

	virtual void resetMoveSpeed(float x, float y);

	// 附加移动属性
	virtual void appendMoveSpeed(float x, float y);

	// 逻辑更新
	virtual void logicUpdate(float d);

	// 是否可以移动
	virtual bool isCanMove();
	
	// 设置角色方向
	virtual void setOrientation(short ori);

	// 
	virtual void loadArmature(const std::string& filepath);

	virtual GameActorType getActorType();

	virtual void setActorType(GameActorType type);

	/// 位置相关
	virtual const Vec2& getActorPosition();

	virtual float getActorPositionX();

	virtual float getActorPositionY();

	virtual void setActorPosition(float x, float y);

	virtual void setActorPosition(const Vec2& pos);

	/// 碰撞相关
	virtual bool getAllDefRECT(std::vector<ActorRect>& actorRectVec);

	virtual bool getAllAttRECT(std::vector<ActorRect>& actorRectVec);
	
	virtual bool AABBTest(const Rect& r);

	virtual const Rect& getAABB();

	virtual bool isRunAABB(GameActor* other);

	// 攻击等级测试
	/// true 大于传入actor
	virtual bool attLevelTest(GameActor* other);

	virtual void AABBCallback(GameActor* other);

	// 攻击其他角色
	virtual bool attOtherActorCallback(GameActor* other);

	void registerLuaHandle(const std::string& name, const LuaFunction& handle);

	void unregisterLuaHandle(const std::string& name);

	const Vec2& getMapMovePos();

protected:

	void updateMoveLogic(float d);

	void updateArmatureInfo();

	void clearLuaHandle();

	LuaFunction* getLuaHandle(const std::string& name);

protected:
	friend class GameWord;
	GameWord* m_word;

	QFSM			m_FSM;				// 有限状态机
	GameAttribute	m_gameAttribute;	// 基础属性
	Armature*		m_armature;			// 骨骼动画

	GameActorType	m_actorType;

	std::map<std::string, LuaFunction*> m_luaHandleMap;
};