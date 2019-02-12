#include "ComLuaFunctionUtil.h"


void ArmatureCollisionComponentUtil::bindAttCallback(ArmatureCollisionComponent* component, const LuaFunction& handle)
{
	component->m_attCollisionCall = std::move(handle);
}

void ArmatureCollisionComponentUtil::bindDefCallback(ArmatureCollisionComponent* component, const LuaFunction& handle)
{
	component->m_defCollisionCall = std::move(handle);
}

void ArmatureCollisionComponentUtil::clearAttCallback(ArmatureCollisionComponent* component)
{
	component->m_attCollisionCall.invalid();
}

void ArmatureCollisionComponentUtil::clearDefCallback(ArmatureCollisionComponent* component)
{
	component->m_defCollisionCall.invalid();
}


//////////////////////////////////////////////////////////////////////////

void Box2DComponentUtil::bindSyncPhysicsTransformCallback(Box2DComponent* component, const LuaFunction& handle)
{
	component->m_syncPhysicsTransformCall = std::move(handle);
}

void Box2DComponentUtil::clearSyncPhysicsTransformCallback(Box2DComponent* component)
{
	component->m_syncPhysicsTransformCall.invalid();
}








