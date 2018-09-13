#pragma once

#include "cocos2d.h"
#include "../lua_function/LuaFunctionBond.h"

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

	void loadMapFile(const std::string& filepath, const std::string& actorNodeName, const std::string& fixNodeName);

	void setViewPos(float x, float y);

	void setViewSize(float width, float height);

	inline Node* getActorNode() { return m_actorNode; }

	inline void lockMapY() { m_lockMapY = true; }

	inline void unlockMapY() { m_lockMapY = false; }

	inline float getMapWidth() { return m_mapSize.width; }

	inline float getMapHeight() { return m_mapSize.height; }

private:


	Size m_mapNodeSize[GameMapNodeType::COUNT];
	Size m_mapNodeMoveSize[GameMapNodeType::COUNT];

	Node* m_mapNode[GameMapNodeType::COUNT];

	Node* m_actorNode;

	float m_fixNodeBeginX;

	Size m_mapSize;
	Size m_viewSize;
	bool m_lockMapY;

	float m_save_view_x;
	float m_save_view_y;
};
