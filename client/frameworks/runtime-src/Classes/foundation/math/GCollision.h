#pragma once

#include "GVec2.h"

class GCollision
{
public:

	// 检测2个矩形是否相交
	static bool isRectIntersect(const GVec2* A, const GVec2* B);
};
