#pragma once

#include "GVirtualCamera.h"

NS_G_BEGIN

class GMapLayer_Custom : public cocos2d::Node
{
public:
	GMapLayer_Custom();

	virtual ~GMapLayer_Custom();

	static GMapLayer_Custom * create(int mapId);

	virtual bool init()override;

private:

	bool initWithMapID(int mapId);

	int getNodeOrder(Node* root, Node* node);

public:

	void setViewSize(const Size& size);

	inline float getMapWidth() { return m_mapSize.width; }

	inline float getMapHeight() { return m_mapSize.height; }


private:

	G_SYNTHESIZE_READONLY(Node*, m_actorNode, ActorNode);
	G_SYNTHESIZE_READONLY(Node*, m_rootNode, RootNode);
	G_SYNTHESIZE_READONLY(DrawNode*, m_drawNode, DrawNode);
	G_SYNTHESIZE_READONLY(GVirtualCamera*, m_camera, VirtualCamera);

	G_SYNTHESIZE_READONLY(fixedPoint, m_minPosY, MinPosY);
	G_SYNTHESIZE_READONLY(fixedPoint, m_maxPosY, MaxPosY);
	
	Size m_mapSize;
	Size m_diffMapViewSize;

	struct SubMapNodeInfo
	{
		bool isActor;
		bool ignore;
		Node* node;
		Size size;
		Size diffSize;
		Vec2 originPos;
	};
	std::vector<SubMapNodeInfo> m_arrSubMapNodeInfo;
};

NS_G_END