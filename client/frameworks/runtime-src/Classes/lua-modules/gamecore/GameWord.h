#pragma once

#include "GameActor.h"


#define ENABLE_GAME_WORD_DEBUG

using namespace cocos2d;

class GameWord : public Node
{
public:
	GameWord();
	virtual ~GameWord();

	static GameWord* create();

	virtual bool init() override;

	void addBackgroundMap(Node* map);

	void addForegroundMap(Node* map);

	void addActor(GameActor* actor);

	void removeActor(GameActor* actor);

	void setPlayer(GameActor* player);

	inline GameActor* getPlayer() { return m_player; }

	void removeActorByName(const std::string& name);
	
	void logicUpdate(float d);

	void openDebugDraw(bool open);

	bool isOpenDebugDraw();
	
	inline Node* getRootNode() { return m_rootNode; }
	
	inline Node* getBackgroundMap() { return m_backgroundMap; }
	
	inline Node* getForegroundMap() { return m_foregroundMap; }
	
	inline Node* getActorNode() { return m_actorNode; }

	Node* getChildNode(const std::string& name);

	inline Size getMapSize() { return m_mapSize; }

protected:

	Node* findChild(Node* root, const std::string& name);

	void updateMapMoveLogic();

	void updateMapCorrectActor();

#ifdef ENABLE_GAME_WORD_DEBUG
	void debugDraw();
#endif

	void collisionTest();

private:
	//地图中可以移动的区域
	Rect m_enableRectMap;

	Size m_mapSize;

	Vector<GameActor*> m_allActor;
	GameActor* m_player;

	Node* m_backgroundMap;
	Node* m_foregroundMap;
	Node* m_actorNode;
	Node* m_rootNode;

#ifdef ENABLE_GAME_WORD_DEBUG
	DrawNode* m_debugDraw;
#endif

	std::vector<ActorRect> m_defRectCache;
	std::vector<ActorRect> m_attRectCache;
};


extern GameWord* getGameWord();
