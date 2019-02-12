#pragma once

#include "foundation/Actor.h"


class PhysicsActor : public Actor
{
public:

	PhysicsActor(GameWorldBase* world);

	virtual ~PhysicsActor();

	static PhysicsActor* create(GameWorldBase* world);

	void syncPhysicsTransform(float x, float y, float angle);

protected:

	virtual void killEntity()override;

public:

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

protected:

	const Vec2& getPosFromPhysics() const;

};


