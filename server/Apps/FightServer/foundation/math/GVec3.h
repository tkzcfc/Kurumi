#pragma once

#include "GMathCommon.h"


class GVec3
{
public:
	union {
		float32 v[3];
		struct {
			float32 x;
			float32 y;
			float32 z;
		};
	};
	GVec3()
	{
		x = y = z = 0.0f;
	}
};


