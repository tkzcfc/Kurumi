#pragma once

#include "cocos2d.h"

using namespace cocos2d;

enum GameMapNodeType
{
	STAGE_NODE,
	FIX_NODE,
	COUNT
};

class GameMap : public Node
{
public:
	GameMap();

	virtual ~GameMap();

	static GameMap * create();

	virtual bool init()override;

public:

	void loadMapFile(const std::string& filepath, const std::string& actorNodeName, const std::string& fixNodeName, float minPosY);

	void setViewPos(float x, float y);

	void setViewSize(float width, float height);

	float getValidWorldX(float inValue, float actorRadius);

	float getValidWorldY(float inValue, float actorRadius);

	void setOpenAreaMinx(float value);

	void setOpenAreaMaxX(float value);

	void setEnableViewPosLimit(bool enable);

public:

	inline Node* getActorNode() { return m_actorNode; }

	inline void lockMapY() { m_lockMapY = true; }

	inline void unlockMapY() { m_lockMapY = false; }

	inline float getMapWidth() { return m_mapSize.width; }

	inline float getMapHeight() { return m_mapSize.height; }

	inline Node* getRootNode() { return m_mapNode[GameMapNodeType::STAGE_NODE]; }

	inline float getMinPosY() {	return m_minPosY; }

	inline bool isEnableViewPosLimit() { return m_enableViewPosLimit; }

	inline float getOpenAreaMinX() { return m_openAreaMinX; }

	inline float getOpenAreaMaxX() { return m_openAreaMaxX; }

#if COCOS2D_DEBUG == 1 
	inline DrawNode* getDrawNode() { return m_drawNode; }
#else
	inline DrawNode* getDrawNode() { return NULL; }
#endif

private:


	Size m_mapNodeSize[GameMapNodeType::COUNT];
	Size m_mapNodeMoveSize[GameMapNodeType::COUNT];

	Node* m_mapNode[GameMapNodeType::COUNT];

	Node* m_actorNode;

	float m_fixNodeBeginX;

	Size m_mapSize;
	Size m_viewSize;
	Size m_halfViewSize;
	bool m_lockMapY;

	float m_save_view_x;
	float m_save_view_y;

	float m_minPosY;

#if COCOS2D_DEBUG == 1 
	DrawNode* m_drawNode;
#endif

	bool m_enableViewPosLimit;
	float m_openAreaMinX;
	float m_openAreaMaxX;
};
