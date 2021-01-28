#pragma once

#include "foundation/GameMacro.h"

#if G_TARGET_CLIENT

#include "foundation/render/GVirtualCamera.h"

class GMapLayer : public Node
{
public:
	GMapLayer();

	virtual ~GMapLayer();

	static GMapLayer * create(int mapId);

	virtual bool init()override;

private:

	bool initWithMapID(int mapId);

public:

	void setViewSize(const Size& size);

	inline float getMapWidth() { return m_mapSize.width; }

	inline float getMapHeight() { return m_mapSize.height; }

	inline Node* getActorNode() { return m_actorNode; }

	inline DrawNode* getDrawNode() { return m_drawNode; }

	inline GVirtualCamera* getVirtualCamera() { return m_camera; }

private:

	Node* m_actorNode;
	DrawNode* m_drawNode;
	Node* m_rootNode;
	GVirtualCamera* m_camera;

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

#endif