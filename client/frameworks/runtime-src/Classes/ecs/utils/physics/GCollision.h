/*
    Copyright (c) 2013 Randy Gaul http://RandyGaul.net

    This software is provided 'as-is', without any express or implied
    warranty. In no event will the authors be held liable for any damages
    arising from the use of this software.

    Permission is granted to anyone to use this software for any purpose,
    including commercial applications, and to alter it and redistribute it
    freely, subject to the following restrictions:
      1. The origin of this software must not be misrepresented; you must not
         claim that you wrote the original software. If you use this software
         in a product, an acknowledgment in the product documentation would be
         appreciated but is not required.
      2. Altered source versions must be plainly marked as such, and must not be
         misrepresented as being the original software.
      3. This notice may not be removed or altered from any source distribution.
*/

#ifndef COLLISION_H
#define COLLISION_H

#include "GShape.h"

class GManifold;
class BodyComponent;
typedef void (*CollisionCallback)(GManifold *m, BodyComponent*, BodyComponent*);

class GCollision
{
public:
	static CollisionCallback Dispatch[GShape::eCount][GShape::eCount];

	static void circletoCircle(GManifold *m, BodyComponent* a, BodyComponent* b);
	static void circletoPolygon(GManifold *m, BodyComponent* a, BodyComponent* b);
	static void polygontoCircle(GManifold *m, BodyComponent* a, BodyComponent* b);
	static void polygontoPolygon(GManifold *m, BodyComponent* a, BodyComponent* b);

	// 检测2个矩形是否相交
	static bool isRectIntersect(const GVec2* A, const GVec2* B);
	
};

#endif // COLLISION_H