#pragma once

#include "GameActor.h"
#include "GameMap.h"
#include "Box2D/Box2D.h"
#include "GLES-Render.h"


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

	void initGameWorld(GameMap* map, int minPosY);

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

	b2World* getPhysicsWorld() { return m_world; }

protected:

	void initPhysics();

	Node* findChild(Node* root, const std::string& name);

	void updateMapMoveLogic();

	void collisionTest();

#ifdef ENABLE_GAME_WORD_DEBUG
	void debugDraw();
	virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t flags) override;
	void onDraw();

	DrawNode* m_debugDraw;
	GLESDebugDraw* m_physicsDebugDraw;
	cocos2d::CustomCommand _customCommand;
	cocos2d::Mat4 _modelViewMV;
#endif

private:

	GameMap* m_gameMap;

	Vector<GameActor*> m_allActor;
	GameActor* m_player;

	float m_minPosY;

	std::vector<ActorRect> m_defRectCache;
	std::vector<ActorRect> m_attRectCache;

	Size m_winSize;

	b2World* m_world;
};


extern GameWord* getGameWord();

extern void changeParticleSystemPositionType(Node* root);

