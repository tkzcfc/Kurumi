#pragma once

#include "GameActor.h"
#include "GameMap.h"
#include "Box2D/Box2D.h"


#define ENABLE_GAME_WORD_DEBUG

#define PIXEL_TO_METER 30.0f

using namespace cocos2d;

class GameWord : public Node
{
public:
	GameWord();
	virtual ~GameWord();

	static GameWord* create();

	virtual bool init() override;

	void setGameMap(GameMap* map);

	inline GameMap* getGameMap() { return m_gameMap; }

	void addActor(GameActor* actor);

	void removeActor(GameActor* actor);

	void setLocalPlayer(GameActor* player);

	inline GameActor* getLocalPlayer() { return m_player; }

	int getPlayerCount();

	GameActor* getPlayerByIndex(int index);

	virtual void removeActorByName(const std::string& name);

	void logicUpdate(float d);

	void openDebugDraw(bool open);

	bool isOpenDebugDraw();

	inline Node* getActorNode() { return m_gameMap->getActorNode(); }

	Node* getChildNode(const std::string& name);

	void updateActors();

	void setViewPortMinXValue(float InValue);
	inline float getViewPortMinXValue() { return m_viewPortMinX; }

	void setViewPortMaxXValue(float InValue);
	inline float getViewPortMaxXValue() { return m_viewPortMaxX; }

	void setMinPosY(float minPosY) { m_minPosY = minPosY; }

	b2World* getPhysicsWorld() { return m_world; }

protected:

	Node* findChild(Node* root, const std::string& name);

	void updateMapMoveLogic();

	void updateMapCorrectActor();

#ifdef ENABLE_GAME_WORD_DEBUG
	void debugDraw();
#endif

	void collisionTest();
private:

	GameMap* m_gameMap;

	Vector<GameActor*> m_allActor;
	GameActor* m_player;

	float m_viewPortMinX;
	float m_viewPortMaxX;
	float m_minPosY;

#ifdef ENABLE_GAME_WORD_DEBUG
	DrawNode* m_debugDraw;
#endif

	std::vector<ActorRect> m_defRectCache;
	std::vector<ActorRect> m_attRectCache;

	Size m_winSize;

	b2World* m_world;
};


extern GameWord* getGameWord();

extern void changeParticleSystemPositionType(Node* root);

