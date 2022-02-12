#pragma once

#include "GFixedVec2.h"

NS_G_BEGIN

struct GFixedRect
{
	GFixedRect() {}
	   
	bool intersectsRect(const GFixedRect& rect) const
	{
		return !(maxx < rect.minx ||
			rect.maxx < minx ||
			maxy < rect.miny ||
			rect.maxy < miny);
	}

	bool containsPoint(const GFixedVec2& point) const
	{
		return (minx <= point.x &&
			point.x <= maxx &&
			miny <= point.y &&
			point.y <= maxy);
	}

	fixedPoint minx;
	fixedPoint miny;
	fixedPoint maxx;
	fixedPoint maxy;
};

NS_G_END
