#pragma once

#include "FSM.h"
#include "cocostudio/CocoStudio.h"
#include "lua_function/LuaFunctionBond.h"
#include "Box2D/Box2D.h"

#define GAME_ORI_LEFT (-1)
#define GAME_ORI_RIGHT (1)

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
class GameActor : public Node, public LuaFunctionBond
{
public:
	static GameActor* create();

	GameActor();

	virtual ~GameActor();

	virtual bool init() override;

public:

	// 逻辑更新
	virtual void logicUpdate(float d);

	virtual GameActorType getActorType();

	virtual void setActorType(GameActorType type);

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

	inline bool isEnableCollision() { return m_collisionEnable; }

	inline void setCollisionEnable(bool enable) { m_collisionEnable = enable; }
	
protected:
	friend class GameWord;
	GameActorType	m_actorType;
	bool m_collisionEnable;
};