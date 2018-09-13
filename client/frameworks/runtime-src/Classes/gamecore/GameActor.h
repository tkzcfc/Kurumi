#pragma once

#include "GameAttribute.h"
#include "FSM.h"
#include "SpeedController.h"
#include "cocostudio/CocoStudio.h"
#include "lua_function/LuaFunctionBond.h"
#include "GamePhysicsNode.h"
#include "Box2D/Box2D.h"

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
class GameActor : public GamePhysicsNode, public LuaFunctionBond
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

	// 逻辑更新
	virtual void logicUpdate(float d);
	
	// 设置角色方向
	virtual void setOrientation(int ori);
	// 获取角色方向
	inline int getOrientation() { return m_curOrientation; }

	// 
	virtual void loadArmature(const std::string& filepath);

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

	inline void lockOrientation() { m_isLockOrientation = true; }

	inline void unLockOrientation() { m_isLockOrientation = false; }

	inline bool isLockOrientation() { return m_isLockOrientation; }

	// 是否启用地图约束
	inline void setMapConstraintEnable(bool InEnable) { m_isMapConstraintEnable = InEnable; }
	inline bool isEnableMapConstraint() { return m_isMapConstraintEnable; }

protected:

	void updateArmatureInfo();

	void createPhysicsBox();

protected:
	friend class GameWord;

	GameWord* m_word;

	QFSM			m_FSM;				// 有限状态机
	GameAttribute	m_gameAttribute;	// 基础属性
	Armature*		m_armature;			// 骨骼动画

	GameActorType	m_actorType;
	
	// 方向锁定？
	bool m_isLockOrientation;

	// 是否受地图约束?
	bool m_isMapConstraintEnable;

	// 当前朝向 -1 左 1 右边
	int	m_curOrientation;
};