#pragma once

#include "GFixedVec2.h"

NS_G_BEGIN

struct GFixedTransform
{
	GFixedTransform() 
	{
		s.x = 1.0f;
		s.y = 1.0f;
	}

	GFixedVec2 p; // position
	GFixedVec2 s; // scale
};


G_FORCEINLINE GFixedVec2 mulT(const GFixedTransform& T, const GFixedVec2& v)
{
	GFixedVec2 out;

	out.x = v.x * T.s.x + T.p.x;
	out.y = v.y * T.s.y + T.p.y;

	return out;
}

G_FORCEINLINE void mulT_quick(const GFixedTransform& T, const GFixedVec2& v, GFixedVec2& out)
{
	out.x = v.x * T.s.x + T.p.x;
	out.y = v.y * T.s.y + T.p.y;
}

NS_G_END
