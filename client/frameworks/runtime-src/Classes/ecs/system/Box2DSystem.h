#pragma once

#include "ecs/components/Box2DComponent.h"
#include "foundation/GameMacro.h"


class Box2DSystem : public anax::System<anax::Requires<Box2DComponent>>, public Ref, public b2ContactListener
{
public:

	Box2DSystem();

	virtual ~Box2DSystem();
	
	/*************************************************************************
	* @Method  :  initPhysics
	* @brief   :  
	* @inparam :  gravity ÖØÁ¦
	* @outparam:  
	* @author  :  FC
	* @date    :  2018/12/13 21:56
	* @version :  ver 1.0
	*************************************************************************/
	bool initPhysics(const Vec2& gravity, const Size& worldSize, float left_offset, float right_offset, float top_offset, float bottom_offset);

	void updateWorld(float delta);

	void addDiscardB2Body(b2Body* body);

	inline b2World* getBox2DWorld();

protected:

	void initWall(const Size& worldSize, float letf_offset, float right_offset);

	void clearDiscardB2BodyList();

	void syncPhysicsTransform();

public:
	///////////////////////////////////b2ContactListener///////////////////////////////////////
	/// Called when two fixtures begin to touch.
	virtual void BeginContact(b2Contact* contact)override;

	/// Called when two fixtures cease to touch.
	virtual void EndContact(b2Contact* contact)override;

protected:

	b2World* m_box2DWorld;

	std::list<b2Body*> m_discardB2BodyList;
};

b2World* Box2DSystem::getBox2DWorld()
{
	CC_ASSERT(m_box2DWorld != NULL);
	return m_box2DWorld;
}


DEFINE_SYSTEM(Box2DSystem);

