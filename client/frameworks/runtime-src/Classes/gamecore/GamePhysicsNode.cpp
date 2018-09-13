#include "GamePhysicsNode.h"
#include "Box2D/Box2D.h"



GamePhysicsNode::GamePhysicsNode()
	: m_ignoreBodyRotation(false)
	, m_pB2Body(nullptr)
	, m_PTMRatio(0.0f)
	, m_syncTransform(nullptr)
{}


bool GamePhysicsNode::isIgnoreBodyRotation() const
{
	return m_ignoreBodyRotation;
}

void GamePhysicsNode::setIgnoreBodyRotation(bool bIgnoreBodyRotation)
{
	m_ignoreBodyRotation = bIgnoreBodyRotation;
}

// Override the setters and getters to always reflect the body's properties.
const Vec2& GamePhysicsNode::getPosition() const
{
	return getPosFromPhysics();
}

void GamePhysicsNode::getPosition(float* x, float* y) const
{
	if (x == nullptr || y == nullptr) {
		return;
	}
	const Vec2& pos = getPosFromPhysics();
	*x = pos.x;
	*y = pos.y;
}

float GamePhysicsNode::getPositionX() const
{
	return getPosFromPhysics().x;
}

float GamePhysicsNode::getPositionY() const
{
	return getPosFromPhysics().y;
}

Vec3 GamePhysicsNode::getPosition3D() const
{
	Vec2 pos = getPosFromPhysics();
	return Vec3(pos.x, pos.y, 0);
}

b2Body* GamePhysicsNode::getB2Body() const
{
	return m_pB2Body;
}

void GamePhysicsNode::setB2Body(b2Body *pBody)
{
	m_pB2Body = pBody;
}

float GamePhysicsNode::getPTMRatio() const
{
	return m_PTMRatio;
}

void GamePhysicsNode::setPTMRatio(float fRatio)
{
	m_PTMRatio = fRatio;
}

const Vec2& GamePhysicsNode::getPosFromPhysics() const
{
	static Vec2 s_physicPosion;

	b2Vec2 pos = m_pB2Body->GetPosition();
	float x = pos.x * m_PTMRatio;
	float y = pos.y * m_PTMRatio;
	s_physicPosion.set(x, y);

	return s_physicPosion;
}

void GamePhysicsNode::setPosition(float x, float y)
{
	float angle = m_pB2Body->GetAngle();
	m_pB2Body->SetTransform(b2Vec2(x / m_PTMRatio, y / m_PTMRatio), angle);
}

void GamePhysicsNode::setPosition(const Vec2 &pos)
{
	setPosition(pos.x, pos.y);
}

void GamePhysicsNode::setPositionX(float x)
{
	setPosition(x, getPositionY());
}

void GamePhysicsNode::setPositionY(float y)
{
	setPosition(getPositionX(), y);
}

void GamePhysicsNode::setPosition3D(const Vec3& position)
{
	setPosition(position.x, position.y);
}

float GamePhysicsNode::getRotation() const
{
	return ((m_ignoreBodyRotation && m_pB2Body) ? Node::getRotation() :
		CC_RADIANS_TO_DEGREES(m_pB2Body->GetAngle()));
}

void GamePhysicsNode::setRotation(float fRotation)
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

void GamePhysicsNode::syncPhysicsTransform() const
{
	if (m_pB2Body == NULL)
		return;

	b2Vec2 pos = m_pB2Body->GetPosition();

	float x = pos.x * m_PTMRatio;
	float y = pos.y * m_PTMRatio;

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

void GamePhysicsNode::onEnter()
{
	Node::onEnter();
	m_syncTransform = Director::getInstance()->getEventDispatcher()->addCustomEventListener(Director::EVENT_AFTER_UPDATE, std::bind(&GamePhysicsNode::afterUpdate, this, std::placeholders::_1));
	m_syncTransform->retain();
}

void GamePhysicsNode::onExit()
{
	if (m_syncTransform != nullptr)
	{
		Director::getInstance()->getEventDispatcher()->removeEventListener(m_syncTransform);
		m_syncTransform->release();
	}
	Node::onExit();
}

void GamePhysicsNode::afterUpdate(EventCustom *event)
{
	syncPhysicsTransform();

	_transformDirty = false;
	_transformUpdated = true;
}

