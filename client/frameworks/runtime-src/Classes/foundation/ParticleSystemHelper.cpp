#include "ParticleSystemHelper.h"
#include "cocostudio/CocoStudio.h"


// ParticleSystem::PositionType::GROUPED

void __changeParticleSystemPositionType(Node* root, int type)
{
	if (root == NULL)
		return;

	auto particleSys = dynamic_cast<ParticleSystem*>(root);
	if (particleSys)
	{
		particleSys->setPositionType((ParticleSystem::PositionType)type);
	}

	auto& child = root->getChildren();
	for (auto& it : child)
	{
		__changeParticleSystemPositionType(it, type);
	}
}

void changeParticleSystemPositionType(Node* root, int type)
{
	CC_ASSERT(type >= (int)ParticleSystem::PositionType::FREE || type <= (int)ParticleSystem::PositionType::GROUPED);
	if (root == NULL)
		return;

	auto armature = dynamic_cast<cocostudio::Armature*>(root);
	if (armature)
	{
		auto& boneDic = armature->getBoneDic();
		for (auto& it : boneDic)
		{
			__changeParticleSystemPositionType(it.second->getDisplayRenderNode(), type);
		}
	}

	auto& child = root->getChildren();
	for (auto& it : child)
	{
		changeParticleSystemPositionType(it, type);
	}
}