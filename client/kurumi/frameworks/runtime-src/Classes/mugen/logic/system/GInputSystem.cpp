#include "GInputSystem.h"
#include "mugen/component/GActorComponent.h"
#include "mugen/logic/GGameWorld.h"

NS_G_BEGIN

GInputSystem::GInputSystem()
{
}

GInputSystem::~GInputSystem()
{}

void GInputSystem::step()
{
	doFilter("GActorComponent");

	// 当前逻辑帧
	auto logicFrame = GGameWorld::getInstance()->getGameLogicFrame();

	for (auto it : m_cacheComponents)
	{
		auto pActorComponent = (GActorComponent*)it;

		// 保存上一帧输入状态
		pActorComponent->lastKeyDown = pActorComponent->curKeyDown;
		// 清空当前输入
		pActorComponent->curKeyDown = G_KEY_NONE;
	}

	// 按键状态更新
	while (m_inputQue.check(logicFrame))
	{
		auto msg = m_inputQue.popMsg();

		for (auto& it : m_cacheComponents)
		{
			if(it->getEntity()->getId() == msg->uuid)
			{
				auto pActorComponent = (GActorComponent*)it;
				G_BIT_SET(pActorComponent->curKeyDown, msg->keydown);
			}
		}
		m_inputQue.freeMsg(msg);
	}

	// 按键事件派发
	for (auto& it : m_cacheComponents)
	{
		auto pActorComponent = (GActorComponent*)it;
		if (pActorComponent->curKeyDown != G_KEY_NONE || pActorComponent->lastKeyDown != G_KEY_NONE)
		{
			// 优先处理抬起事件
			for (auto i = 1; i <= G_KEY_MAX_COUNT; ++i)
			{
				if (G_BIT_EQUAL(pActorComponent->lastKeyDown, G_FIXED_VALUE << i))
				{
					if (G_BIT_EQUAL(pActorComponent->curKeyDown, G_FIXED_VALUE << i))
					{
						// 按键持续按下
						pActorComponent->onKeepPress(G_FIXED_VALUE << i);
					}
					else
					{
						// 按键抬起
						pActorComponent->onKeyUp(G_FIXED_VALUE << i);
					}
				}
			}

			for (auto i = 1; i <= G_KEY_MAX_COUNT; ++i)
			{
				if (G_BIT_NO_EQUAL(pActorComponent->lastKeyDown, G_FIXED_VALUE << i))
				{
					// 按键按下瞬间
					if (G_BIT_EQUAL(pActorComponent->curKeyDown, G_FIXED_VALUE << i))
					{
						pActorComponent->onKeyDown(G_FIXED_VALUE << i);
					}
				}
			}
		}
	}
}


NS_G_END
