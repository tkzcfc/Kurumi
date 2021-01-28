#include "ArmatureRenderSystem.h"
#include "foundation/animator/GAnimCMD.h"
#include "foundation/animator/GAnimData.h"
#include "ecs/components/MapComponent.h"
#include "ecs/utils/CommonUtils.h"

#if  G_TARGET_CLIENT

// 允许误差范围5帧左右
static const int32_t disparityThreshold = 5;

void ArmatureRenderSystem::render()
{
	for (auto& entity : this->getEntities())
	{
		auto& component = entity.getComponent<ArmatureComponent>();
		auto& renderComponent = entity.getComponent<ArmatureRenderComponent>();
		auto render = renderComponent.render;

		if (false == component.roleName.empty())
		{
			if (render == NULL)
			{
				auto& admin = CommonUtils::getAdmin(this->getWorld());
				auto mapComponent = admin.getComponent<MapComponent>();

				render = cocostudio::Armature::create();
				mapComponent.render->getActorNode()->addChild(render);

				renderComponent.render = render;
			}
			if (renderComponent.m_cacheRoleName != component.roleName)
			{
				renderComponent.m_cacheRoleName = component.roleName;

				auto animData = GAnimDataCache::getInstance()->getOrCreate(component.roleName);
				G_ASSERT(animData != NULL);

				auto cmd = GAnimCMDCache::getInstance()->getOrCreate(component.roleName);
				G_ASSERT(cmd != NULL);
				
				if (animData != NULL && cmd != NULL)
				{
					cocostudio::ArmatureDataManager::getInstance()->addArmatureFileInfo(cmd->anime);
					render->init(animData->getArmatureName());
				}
				else
				{
					renderComponent.actionType = kArmatureRenderAction::NONE;
				}
			}
		}
		if (render)
		{
			auto animation = render->getAnimation();
			if (animation)
			{
				switch (renderComponent.actionType)
				{
				case kArmatureRenderAction::NONE:
				{}break;
				case kArmatureRenderAction::PAUSE:
				{
					if (component.playing)
					{
						animation->resume();
						animation->setAnimationScale(component.timeScale * 1.0f);
						animation->play(component.curAniName, component.curFrameIndex);
						renderComponent.actionType = kArmatureRenderAction::RUN;
						//CCLOG("kArmatureRenderAction::RUN_3(PAUSE) %s", component.curAniName.c_str());
					}
				}break;
				// 追赶逻辑帧
				case kArmatureRenderAction::PURSUE:
				// 等待逻辑帧
				case kArmatureRenderAction::AWAIT:
				{
					if (component.playing)
					{
						if (animation->getCurrentMovementID() == component.curAniName)
						{
							int32_t diff = animation->getCurrentFrameIndex() - component.curFrameIndex;
							if (std::labs(diff) <= 2)
							{
								animation->setAnimationScale(component.timeScale * 1.0f);
								renderComponent.actionType = kArmatureRenderAction::RUN;
								//CCLOG("kArmatureRenderAction::RUN_1 %s", component.curAniName.c_str());
							}
						}
						else
						{
							animation->setAnimationScale(component.timeScale * 1.0f);
							animation->play(component.curAniName, component.curFrameIndex);
							renderComponent.actionType = kArmatureRenderAction::RUN;
							//CCLOG("kArmatureRenderAction::RUN_2 %s", component.curAniName.c_str());
						}
					}
					else
						this->pause(animation, component, renderComponent);
				}break;
				case kArmatureRenderAction::RUN:
				{
					if (component.playing)
					{
						if (animation->getCurrentMovementID() == component.curAniName)
						{
							if (animation->getRawDuration() > 20)
							{
								bool isLoop = false;
								do 
								{
									auto animData = GAnimDataCache::getInstance()->getOrCreate(component.roleName);
									if(animData == NULL)
										break;

									auto curAnim = animData->getAniData(component.curAniName);
									if (curAnim == NULL)
										break;
									isLoop = curAnim->isLoop;
								} while (false);

								if (false == isLoop)
								{
									int32_t diff = animation->getCurrentFrameIndex() - component.curFrameIndex;
									if (diff > disparityThreshold)// 减速
									{
										//CCLOG("kArmatureRenderAction::AWAIT %d", diff);
										animation->setAnimationScale(component.timeScale * 0.9f);
										renderComponent.actionType = kArmatureRenderAction::AWAIT;
									}
									else if (diff < -disparityThreshold)// 加速
									{
										//CCLOG("kArmatureRenderAction::PURSUE %d", diff);
										animation->setAnimationScale(component.timeScale * 1.1f);
										renderComponent.actionType = kArmatureRenderAction::PURSUE;
									}
								}
							}
							else
							{
								animation->setAnimationScale(component.timeScale);
							}
						}
						else
						{
							animation->play(component.curAniName, component.curFrameIndex);
							animation->setAnimationScale(component.timeScale);
							//CCLOG("kArmatureRenderAction::RUN_4(RUN) %s", component.curAniName.c_str());
						}
					}
					else
						this->pause(animation, component, renderComponent);
				}break;
				default:
					break;
				}
			}
		}
	}
}

void ArmatureRenderSystem::pause(cocostudio::ArmatureAnimation* animation, ArmatureComponent& component, ArmatureRenderComponent& renderComponent)
{
	//CCLOG("kArmatureRenderAction::pause %s %d-%d", component.curAniName.c_str(), component.curFrameIndex, animation->getCurrentFrameIndex());
	if (animation->getCurrentMovementID() != component.curAniName)
		animation->play(component.curAniName, component.curFrameIndex);
	else
	{
		int32_t diff = animation->getCurrentFrameIndex() - component.curFrameIndex;
		if (std::labs(diff) > disparityThreshold)
			animation->play(component.curAniName, component.curFrameIndex);
	}
	animation->pause();
	renderComponent.actionType = kArmatureRenderAction::PAUSE;
}

#endif
