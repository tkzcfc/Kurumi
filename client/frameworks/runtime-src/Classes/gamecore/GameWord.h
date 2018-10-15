#pragma once

#include "GameActor.h"
#include "GameMap.h"
#include "Box2D/Box2D.h"
#include "GLES-Render.h"


#define ENABLE_GAME_WORD_DEBUG

#define PIXEL_TO_METER 30.0f

#define PHYSICS_WORLD_GRAVITY_Y -40.0f
#define PHYSICS_WORLD_GRAVITY_X 0.0f

#define PHYSICS_WORLD_FPS (1.0 / 60.0f)

using namespace cocos2d;

class GameWord : public Node
{
public:
	GameWord();
	virtual ~GameWord();

	static GameWord* create();

	virtual bool init() override;

	void initGameWorld(GameMap* map, float left_offset, float right_offset);

	inline GameMap* getGameMap() { return m_gameMap; }

	// actorÏà¹Ø
	void addActor(GameActor* actor);

	void removeActor(GameActor* actor);

	void setLocalPlayer(GameActor* player);

	inline GameActor* getLocalPlayer() { return m_player; }

	int getPlayerCount();

	GameActor* getPlayerByIndex(int index);

	virtual void removeActorByName(const std::string& name);

	Node* getChildNode(const std::string& name);

	void updateActors();

	inline Node* getActorNode() const { return m_gameMap->getActorNode(); }

	void logicUpdate(float d);

	// debug draw
	void openDebugDraw(bool open);

	bool isOpenDebugDraw();

	//
	inline b2World* getPhysicsWorld() const { return m_world; }

	inline const Rect& getGameWorldValidRect() const { return m_worldValidRect; }

	void addDiscardB2Body(b2Body* body);

protected:

	void initPhysics(float left_offset, float right_offset, float top_offset, float bottom_offset);

	Node* findChild(Node* root, const std::string& name);

	void updateMapMoveLogic();

	void collisionTest();

	void clearDiscardB2BodyList();

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
	std::vector<GameActor*> m_destroyActor;
	GameActor* m_player;

	std::vector<ActorRect> m_defRectCache;
	std::vector<ActorRect> m_attRectCache;

	Size m_winSize;
	Rect m_worldValidRect;

	b2World* m_world;
	std::list<b2Body*> m_discardB2BodyList;
};


extern GameWord* getGameWord();

extern void changeParticleSystemPositionType(Node* root);

