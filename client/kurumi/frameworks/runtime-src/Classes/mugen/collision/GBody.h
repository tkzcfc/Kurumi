#pragma once

#include "../geometry/GGeometry.h"

NS_G_BEGIN

class GBody
{
public:
	GBody() {}

	virtual ~GBody() {}

	GFixedTransform transform;
};

NS_G_END

