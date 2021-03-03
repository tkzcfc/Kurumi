#pragma once

#include "ecs/anaxHelper.h"

class Buff
{
public:

	// @param creator buff创建者uuid
	Buff(anax::World* world, GUUID creator = INVALID_UUID);

	Buff() = delete;

	virtual ~Buff();

public:

	// 判断buff是否可以移除
	virtual bool canRemove();

	// buff执行实现
	virtual void execute(const anax::Entity& entity) = 0;

	// 设置Buff即将移除
	void remove();

	G_FORCEINLINE GUUID getCreator();
	
public:
	anax::World* m_pWorld;
	bool m_removeTag;
	GUUID m_creator;
};


GUUID Buff::getCreator()
{
	return m_creator;
}
