#include "GPhysicalForceFrame.h"
#include "mugen/component/GRigidBodyComponent.h"
#include "mugen/component/GDataComponent.h"
#include "mugen/component/GActorComponent.h"

NS_G_BEGIN

GPhysicalForceFrame::GPhysicalForceFrame()
{
	m_forceType = GPhysicalForceType::FORCE;
	m_type = GFrameType::PHYSICAL_FORCE_FRAME;
	m_forceOrientation = GForceOrientation::Positive_Direction;
	setTriggerMaxCount(0);
	setTriggerInterval(0);
}

GPhysicalForceFrame::~GPhysicalForceFrame()
{}

void GPhysicalForceFrame::onEnter(int32_t currentFrameIndex)
{
	GEventFrame::onEnter(currentFrameIndex);
	m_pRigidBodyComponent = G_GetComponent(m_pEntity, GRigidBodyComponent);
	m_pDataComponent = G_GetComponent(m_pEntity, GDataComponent);
	m_pActorComponent = G_GetComponent(m_pEntity, GActorComponent);
}

void GPhysicalForceFrame::onEmit()
{
	if (false == m_pActorComponent->isKeyDown(G_KEY_MOVE_MUSTER))
	{
		return;
	}

	auto applyValue = m_value;
	if (m_valueType == GValueType::VALUE_PERCENTAGE)
	{
		switch (m_forceType)
		{
		case ng::GPhysicalForceType::FORCE:
		{
			auto& force = m_pDataComponent->force;
			applyValue.x *= force.x;
			applyValue.y *= force.y;
			applyValue.z *= force.z;
		}
			break;
		case ng::GPhysicalForceType::IMPULSE:
		{
			auto& impulse = m_pDataComponent->impulse;
			applyValue.x *= impulse.x;
			applyValue.y *= impulse.y;
			applyValue.z *= impulse.z;
		}
			break;
		case ng::GPhysicalForceType::MOVEMENT:
		{
			auto& moveSpeed = m_pDataComponent->moveSpeed;
			applyValue.x *= moveSpeed.x;
			applyValue.y *= moveSpeed.y;
		}
			break;
		default:
			break;
		}
	}

	switch (m_forceOrientation)
	{
		// 正方向
	case ng::GForceOrientation::Positive_Direction:
	{
		if (m_pActorComponent->getOrientation() == GActorOrientation::LEFT)
		{
			applyValue.x = -applyValue.x;
		}
	}
	break;
	case ng::GForceOrientation::Negative_Direction:
	{
		if (m_pActorComponent->getOrientation() == GActorOrientation::RIGHT)
		{
			applyValue.x = -applyValue.x;
		}
	}
	break;
	default:
		G_ASSERT(0);
		break;
	}



	switch (m_forceType)
	{
	case ng::GPhysicalForceType::FORCE:
	{
		m_pRigidBodyComponent->applyForce(applyValue);
	}
		break;
	case ng::GPhysicalForceType::IMPULSE:
	{
		m_pRigidBodyComponent->applyImpulse(applyValue);
	}
		break;
	case ng::GPhysicalForceType::MOVEMENT:
	{
		if (m_pActorComponent->isKeyDown(G_KEY_MOVE_Y))
		{
			if (m_pActorComponent->isKeyDown(G_KEY_MOVE_DOWN))
				applyValue.y = -applyValue.y;
		}
		else
		{
			applyValue.y.setZero();
		}

		if (false == m_pActorComponent->isKeyDown(G_KEY_MOVE_X))
		{
			applyValue.x.setZero();
		}
		CCLOG("offset x:%f, y:%f", applyValue.x.to_float(), applyValue.y.to_float());
		m_pRigidBodyComponent->appendOffset(applyValue.x, applyValue.y);
	}
		break;
	default:
		break;
	}
}

void GPhysicalForceFrame::serialize(GByteBuffer& byteBuffer)
{
	GEventFrame::serialize(byteBuffer);
	
	byteBuffer.writeInt32((int32_t)m_forceType);
	byteBuffer.writeInt32((int32_t)m_forceOrientation);
	byteBuffer.writeInt32((int32_t)m_valueType);
	byteBuffer.writeFixedPoint(m_value.x);
	byteBuffer.writeFixedPoint(m_value.y);
	byteBuffer.writeFixedPoint(m_value.z);
}

bool GPhysicalForceFrame::deserialize(GByteBuffer& byteBuffer)
{
	do
	{
		G_BREAK_IF(!GEventFrame::deserialize(byteBuffer));

		m_forceType = (GPhysicalForceType)byteBuffer.readInt32();
		m_forceOrientation = (GForceOrientation)byteBuffer.readInt32();

		auto value = byteBuffer.readInt32();
		if (value < (int32_t)GValueType::VALUE_PERCENTAGE || value >(int32_t)GValueType::VALUE_ABSOLUTE)
		{
			G_ASSERT(0);
			break;
		}
		m_valueType = (GValueType)value;

		G_BREAK_IF(!byteBuffer.getFixedPoint(m_value.x));
		G_BREAK_IF(!byteBuffer.getFixedPoint(m_value.y));
		G_BREAK_IF(!byteBuffer.getFixedPoint(m_value.z));

		return true;
	} while (0);
	return false;
}

NS_G_END