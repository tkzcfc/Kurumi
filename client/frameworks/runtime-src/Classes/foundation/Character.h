#pragma once

#include "foundation/Actor.h"
#include "foundation/FSM.h"
#include "cocostudio/CocoStudio.h"

class Character : public Actor
{
public:

	Character(GameWorldBase* world);

	virtual ~Character();

	static Character* create(GameWorldBase* world);

	void loadArmature(const std::string& filepath);

	void enableBox2DComponent(const Vec2& bodyPos, const Size& characterSize);

	void setPositionAndSyncPhysicsTransform(const Vec2& inPos);

public:

	virtual bool init()override;

	virtual void killEntity()override;

public:

	inline QFSM* getFSM();

	inline cocostudio::Armature* getArmature();

protected:

	QFSM m_fsm;

	cocostudio::Armature* m_armature;
};

QFSM* Character::getFSM()
{
	return &m_fsm;
}

cocostudio::Armature* Character::getArmature()
{
	return m_armature;
}
