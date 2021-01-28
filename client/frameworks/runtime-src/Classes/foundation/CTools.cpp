#include "CTools.h"

#if G_TARGET_CLIENT

bool CTools::isInRect(Node* InNode, float InX, float InY)
{
	CC_ASSERT(InNode != NULL);
	if (InNode == NULL)
		return false;
	Rect rect;
	rect.size = InNode->getContentSize();
	return isScreenPointInRect(Vec2(InX, InY), Camera::getDefaultCamera(), InNode->getWorldToNodeTransform(), rect, NULL);
}

#endif