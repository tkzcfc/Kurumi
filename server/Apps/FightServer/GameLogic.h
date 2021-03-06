#pragma once

#include "game/GGameWorld.h"
#include "GamePlayer.h"

// 服务器游戏同步逻辑
class GameLogic
{
public:

	GameLogic();

	~GameLogic();

	err::Code init(int32_t mapID, const ::google::protobuf::RepeatedPtrField< ::svr_msg::FightPlayerSpawnInfo >& players);
	
	void update(float dt);

	G_FORCEINLINE int32_t uuid();

	// 判断是否完成
	G_FORCEINLINE bool finish();
	
public:
	
	err::Code join(uint32_t sessionID, const msg::JoinFightReq& req);

	void exitGame(const std::string& playerID);

	err::Code exitGameWithSessionID(uint32_t sessionID);

protected:

	void update_Ready(float dt);

	void update_Run(float dt);

	void update_Wait(float dt);

	GamePlayer* getPlayerBySessionID(uint32_t sessionID);

	// 获取逻辑帧最慢的一个玩家
	GamePlayer* getSlowestPlayer();

	bool containPlayer(const std::string& playerID);

	void sendToAllPlayer(MessageID msgID, const ::google::protobuf::MessageLite& msg);
	
	void onMsg_RunNextFrameReq(uint32_t sessionID, const msg::RunNextFrameReq& req);

private:
	std::unique_ptr<GGameWorld> m_world;
	int32_t m_uuid;
	bool m_isFinish;
	GNetService* m_pNetService;
	GApplication* m_pApplication;
	
	float m_lastRunTime;

	// 本局游戏玩家数量
	int32_t m_playerCount;
	std::unique_ptr<GamePlayer> m_players[G_FIGHT_MAX_PLAYER_COUNT];
	std::set<std::string> m_playerIDSet;
	
	enum RUN_STATE
	{
		READY = 0,	// 准备状态,等待玩家全部准备完毕
		RUN,		// 正常运行状态
		WAIT		// 等待状态,等待逻辑帧最慢的客户端跟上服务器逻辑帧
	};
	RUN_STATE m_state;
	float m_waitTime;

	// 玩家输入记录
	struct Record
	{
		uint32_t frame;
		std::string input;
	};
	// 已经执行过的历史操作记录
	std::list<Record> m_pastRecords;
};

int32_t GameLogic::uuid()
{
	return m_uuid;
}

bool GameLogic::finish()
{
	return m_isFinish;
}
