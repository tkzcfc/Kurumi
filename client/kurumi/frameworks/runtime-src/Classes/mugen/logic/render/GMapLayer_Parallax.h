#pragma once

#include "GVirtualCamera.h"

NS_G_BEGIN

class GMapLayer_Parallax : public cocos2d::Node
{
public:
	GMapLayer_Parallax();

	virtual ~GMapLayer_Parallax();

	static GMapLayer_Parallax * create(int mapId);

	virtual bool init()override;

private:

	bool initWithMapID(int mapId);

	int getNodeOrder(Node* root, Node* node);

public:

	inline float getMapWidth() { return m_mapSize.width; }

	inline float getMapHeight() { return m_mapSize.height; }


private:

	G_SYNTHESIZE_READONLY(Node*, m_actorNode, ActorNode);
	G_SYNTHESIZE_READONLY(DrawNode*, m_drawNode, DrawNode);
	G_SYNTHESIZE_READONLY(GVirtualCamera*, m_camera, VirtualCamera);
	G_SYNTHESIZE_READONLY(ParallaxNode*, m_parallaxNode, ParallaxNode);

	G_SYNTHESIZE_READONLY(fixedPoint, m_minPosY, MinPosY);
	G_SYNTHESIZE_READONLY(fixedPoint, m_maxPosY, MaxPosY);

	
	Size m_mapSize;
};

NS_G_END