#pragma once

#include "foundation/GameMacro.h"

#if G_TARGET_CLIENT

#include "cocos2d.h"
#include <string>
USING_NS_CC;


class CTools
{
public:
	static bool isInRect(Node* InNode, float InX, float InY);
};
#endif