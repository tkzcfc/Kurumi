#pragma once

#include "cocos2d.h"
#include "Box2D/Box2D.h"

struct cpBody;
class b2Body;

using namespace cocos2d;

class GamePhysicsNode : public Node
{
public:

	GamePhysicsNode();
	
	/** Keep the sprite's rotation separate from the body. */
	bool isIgnoreBodyRotation() const;
	void setIgnoreBodyRotation(bool bIgnoreBodyRotation);

	b2Body* getB2Body() const;
	void setB2Body(b2Body *pBody);

	float getPTMRatio() const;
	void setPTMRatio(float fPTMRatio);
	virtual void syncPhysicsTransform() const;

	// overrides
	virtual const Vec2& getPosition() const override;
	virtual void getPosition(float* x, float* y) const override;
	virtual float getPositionX() const override;
	virtual float getPositionY() const override;
	virtual Vec3 getPosition3D() const override;
	virtual void setPosition(const Vec2 &position) override;
	virtual void setPosition(float x, float y) override;
	virtual void setPositionX(float x) override;
	virtual void setPositionY(float y) override;
	virtual void setPosition3D(const Vec3& position) override;
	virtual float getRotation() const override;
	virtual void setRotation(float fRotation) override;

	virtual void onEnter() override;
	virtual void onExit() override;

protected:
	const Vec2& getPosFromPhysics() const;
	void afterUpdate(EventCustom *event);

protected:
	bool    m_ignoreBodyRotation;

	
	// box2d specific
	b2Body  *m_pB2Body;
	float   m_PTMRatio;

	// Event for update synchronise physic transform
	cocos2d::EventListenerCustom* m_syncTransform;
};

