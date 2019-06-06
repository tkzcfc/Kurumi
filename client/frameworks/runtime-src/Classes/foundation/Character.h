#pragma once

#include "foundation/Actor.h"
#include "foundation/FSM.h"
#include "cocostudio/CocoStudio.h"

class Character : public Actor
{
public:

	Character(GameWorld* world);

	virtual ~Character();

	static Character* create(GameWorld* world);

	void loadArmature(const std::string& filepath);

	void enableBox2DComponent(const Vec2& bodyPos, const Size& characterSize);

	void setPositionAndSyncPhysicsTransform(const Vec2& inPos);

	void setCategoryBits(unsigned short categoryBits);

	unsigned short getCategoryBits();

public:

	virtual bool init()override;

	virtual void killEntity()override;

public:

	inline QFSM* getFSM();

	inline cocostudio::Armature* getArmature();

	inline float getCharacterWidth();

	inline float getCharacterHeight();

protected:

	QFSM m_fsm;

	cocostudio::Armature* m_armature;

	unsigned short m_categoryBits;

	Size m_characterSize;
};

QFSM* Character::getFSM()
{
	return &m_fsm;
}

cocostudio::Armature* Character::getArmature()
{
	return m_armature;
}

float Character::getCharacterWidth()
{
	return m_characterSize.width;
}

float Character::getCharacterHeight()
{
	return m_characterSize.height;
}
