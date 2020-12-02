#pragma once

#include "anax/anax.hpp"
#include "GMath.h"

#ifdef COCOS2D_DEBUG
	#define G_TARGET_SERVER 0
	#define G_DEBUG COCOS2D_DEBUG
	#define G_LOG CCLOG
#else
	#define G_TARGET_SERVER 1
	#define G_DEBUG _DEBUG
	#define G_LOG(...) do {} while (0)
#endif


#if G_TARGET_SERVER

#else
	#include "cocos2d.h"
	using namespace cocos2d;
#endif
