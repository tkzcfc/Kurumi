#include "GameCharacter.h"
#include "GameWord.h"


bool GameCharacter::isIgnoreBodyRotation() const
{
	return m_ignoreBodyRotation;
}

void GameCharacter::setIgnoreBodyRotation(bool bIgnoreBodyRotation)
{
	m_ignoreBodyRotation = bIgnoreBodyRotation;
}

// Override the setters and getters to always reflect the body's properties.
const Vec2& GameCharacter::getPosition() const
{
	return getPosFromPhysics();
}

void GameCharacter::getPosition(float* x, float* y) const
{
	if (x == nullptr || y == nullptr) {
		return;
	}
	const Vec2& pos = getPosFromPhysics();
	*x = pos.x;
	*y = pos.y;
}

float GameCharacter::getPositionX() const
{
	return getPosFromPhysics().x;
}

float GameCharacter::getPositionY() const
{
	return getPosFromPhysics().y;
}

Vec3 GameCharacter::getPosition3D() const
{
	Vec2 pos = getPosFromPhysics();
	return Vec3(pos.x, pos.y, 0);
}

b2Body* GameCharacter::getB2Body() const
{
	return m_pB2Body;
}

void GameCharacter::setB2Body(b2Body *pBody)
{
	m_pB2Body = pBody;
}

const Vec2& GameCharacter::getPosFromPhysics() const
{
	static Vec2 s_physicPosion;

	b2Vec2 pos = m_pB2Body->GetPosition();
	float x = pos.x * PIXEL_TO_METER;
	float y = pos.y * PIXEL_TO_METER;
	s_physicPosion.set(x, y);

	return s_physicPosion;
}

void GameCharacter::setPosition(float x, float y)
{
	float angle = m_pB2Body->GetAngle();
	m_pB2Body->SetTransform(b2Vec2(x / PIXEL_TO_METER, y / PIXEL_TO_METER), angle);
}

void GameCharacter::setPosition(const Vec2 &pos)
{
	setPosition(pos.x, pos.y);
}

void GameCharacter::setPositionX(float x)
{
	setPosition(x, getPositionY());
}

void GameCharacter::setPositionY(float y)
{
	setPosition(getPositionX(), y);
}

void GameCharacter::setPosition3D(const Vec3& position)
{
	setPosition(position.x, position.y);
}

float GameCharacter::getRotation() const
{
	return ((m_ignoreBodyRotation && m_pB2Body) ? Node::getRotation() :
		CC_RADIANS_TO_DEGREES(m_pB2Body->GetAngle()));
}

void GameCharacter::setRotation(float fRotation)
{
	if (m_ignoreBodyRotation && m_pB2Body)
	{
		Node::setRotation(fRotation);
	}
	else
	{
		b2Vec2 p = m_pB2Body->GetPosition();
		float radians = CC_DEGREES_TO_RADIANS(fRotation);
		m_pB2Body->SetTransform(p, radians);
	}

}

void GameCharacter::syncPhysicsTransform() const
{
	if (m_pB2Body == NULL)
		return;

	b2Vec2 pos = m_pB2Body->GetPosition();

	float x = pos.x * PIXEL_TO_METER;
	float y = pos.y * PIXEL_TO_METER;

	if (_ignoreAnchorPointForPosition)
	{
		x += _anchorPointInPoints.x;
		y += _anchorPointInPoints.y;
	}

	// Make matrix
	float radians = m_pB2Body->GetAngle();
	float c = cosf(radians);
	float s = sinf(radians);

	if (!_anchorPointInPoints.isZero())
	{
		x += ((c * -_anchorPointInPoints.x * _scaleX) + (-s * -_anchorPointInPoints.y * _scaleY));
		y += ((s * -_anchorPointInPoints.x * _scaleX) + (c * -_anchorPointInPoints.y * _scaleY));
	}

	// Rot, Translate Matrix

	float mat[] = { (float)c * _scaleX, (float)s * _scaleX, 0,  0,
		(float)-s * _scaleY, (float)c * _scaleY,  0,  0,
		0,  0,  1,  0,
		x,	y,  0,  1
	};

	_transform.set(mat);
}

void GameCharacter::onEnter()
{
	Node::onEnter();
	m_syncTransform = Director::getInstance()->getEventDispatcher()->addCustomEventListener(Director::EVENT_AFTER_UPDATE, std::bind(&GameCharacter::afterUpdate, this, std::placeholders::_1));
	m_syncTransform->retain();
}

void GameCharacter::onExit()
{
	if (m_syncTransform != nullptr)
	{
		Director::getInstance()->getEventDispatcher()->removeEventListener(m_syncTransform);
		m_syncTransform->release();
	}
	Node::onExit();
}

void GameCharacter::afterUpdate(EventCustom *event)
{
	syncPhysicsTransform();

	_transformDirty = false;
	_transformUpdated = true;
}




