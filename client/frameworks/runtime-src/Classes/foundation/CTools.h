#pragma once

#include "foundation/GameMacro.h"
#include "cocos2d.h"
USING_NS_CC;


class CTools
{
public:
	static bool isInRect(Node* InNode, float InX, float InY);
};