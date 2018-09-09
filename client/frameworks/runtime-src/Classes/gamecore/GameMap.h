#pragma once

#include "cocos2d.h"
#include "../lua_function/LuaFunctionBond.h"

using namespace cocos2d;

enum GameMapNodeType
{
	BACKGROUND_NODE,
	STAGE_NODE,
	FOREGROUND_NODE,
	COUNT
};

class GameMap : public Node, public LuaFunctionBond
{
public:
	GameMap();

	virtual ~GameMap();

	static GameMap * create();

	virtual bool init()override;

public:

	Node* getMapNode(GameMapNodeType type);

	void setMapNodeSize(GameMapNodeType type, float width, float height);

	void addMapWidgetData(GameMapNodeType type, int widgetKey, float begin_x, float end_x);

	void setViewPos(float x, float y);

	void setViewSize(float width, float height);

	inline void lockMapY() { m_lockMapY = true; }

	inline void unlockMapY() { m_lockMapY = false; }

	inline float getMapWidth() { return m_mapSize.width; }

	inline float getMapHeight() { return m_mapSize.height; }

protected:

	virtual void initMap();

private:

	struct MapWidgetInfo
	{
		bool isload;
		int widgetKey;
		Node* node;
		float begin_x;
		float end_x;
	};

	Size m_mapNodeSize[GameMapNodeType::COUNT];
	Size m_mapNodeMoveSize[GameMapNodeType::COUNT];

	Node* m_rootNode;

	Size m_mapSize;
	Size m_viewSize;
	bool m_lockMapY;

	float m_save_view_x;
	float m_save_view_y;
};
