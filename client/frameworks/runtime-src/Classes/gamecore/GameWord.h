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

	void loadMapFile(const std::string& filepath, const std::string& actorNodeName = "di1ceng");

	void addActor(GameActor* actor);

	void removeActor(GameActor* actor);

	void setPlayer(GameActor* player);

	inline GameActor* getPlayer() { return m_player; }

	void removeActorByName(const std::string& name);
	
	void logicUpdate(float d);

	void openDebugDraw(bool open);

	bool isOpenDebugDraw();
	
	inline Node* getRootNode() { return m_rootNode; }
	
	inline Node* getActorNode() { return m_actorNode; }

	Node* getChildNode(const std::string& name);

	inline Size getMapSize() { return m_mapSize; }

	inline void setMinPosY(float InMinPosY) { m_minPosY = InMinPosY; }

	inline float getMinPosY() { return m_minPosY; }

protected:

	Node* findChild(Node* root, const std::string& name);

	void updateMapMoveLogic();

	void updateMapCorrectActor();

#ifdef ENABLE_GAME_WORD_DEBUG
	void debugDraw();
#endif

	void collisionTest();

private:
	float m_minPosY;
	Size m_mapSize;

	Vector<GameActor*> m_allActor;
	GameActor* m_player;

	Node* m_actorNode;
	Node* m_rootNode;

#ifdef ENABLE_GAME_WORD_DEBUG
	DrawNode* m_debugDraw;
#endif

	std::vector<ActorRect> m_defRectCache;
	std::vector<ActorRect> m_attRectCache;
};


extern GameWord* getGameWord();

extern void changeParticleSystemPositionType(Node* root);

