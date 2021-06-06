#pragma once

#include "game/GGameWorld.h"
#include "GamePlayer.h"
#include "GameProto.h"

// 服务器游戏同步逻辑
class GameLogic
{
public:

	GameLogic();

	~GameLogic();

	err::Code init(const GGameWorldInitArgs &args, const ::google::protobuf::RepeatedPtrField< ::svr_msg::FightRoleSpawnInfo >& roles);
	
	void update(float dt);

	// 获取当前逻辑帧
	uint32_t getGameLogicFrame() const;

	// 获取当前状态
	int32_t getGameStatus() const;
			
public:
	
	err::Code joinCode(uint32_t sessionID, const msg::JoinFightReq& req);

	void doJoin(uint32_t sessionID, const msg::JoinFightReq& req);

	void exitGame(int64_t playerID);

	err::Code exitGameWithSessionID(uint32_t sessionID);

public:

	G_SYNTHESIZE_PASS_BY_REF(GGameWorldInitArgs, m_initArgs, InitArgs);

	G_SYNTHESIZE(bool, m_isFinish, IsFinish);

	G_SYNTHESIZE(int32_t, m_uuid, uuid);

protected:

	void update_WaitConnect(float dt);

	void update_Ready(float dt);

	void update_Run(float dt);

	void update_Wait(float dt);

	GamePlayer* getPlayerBySessionID(uint32_t sessionID);

	// 获取逻辑帧最慢的一个玩家
	GamePlayer* getSlowestPlayer();

	bool containPlayer(int64_t playerID);

	void sendToAllPlayer(MessageID msgID, const ::google::protobuf::MessageLite& msg);

	// 广播所有玩家加载信息
	void sendLoadingPercentToAllPlayer();

	// 向玩家推帧
	void pushFrameInfo(uint32_t startFrame, uint32_t sessionID);

protected:

	void onMsg_RunNextFrameReq(uint32_t sessionID, const msg::RunNextFrameReq& req);

	void onMsg_PlayerLoadingReq(uint32_t sessionID, const msg::PlayerLoadingReq& req);

private:
	std::unique_ptr<GGameWorld> m_world;

	GNetService* m_pNetService;
	GApplication* m_pApplication;

	// 本局游戏玩家数量
	int32_t m_playerCount;
	std::unique_ptr<GamePlayer> m_players[G_FIGHT_MAX_PLAYER_COUNT];
	std::set<int64_t> m_playerIDSet;
	
	enum RUN_STATE
	{
		WAIT_CONNECT = 0, // 等待客户端连接服务器
		READY,	// 准备状态,等待玩家全部准备完毕
		RUN,		// 正常运行状态
		WAIT		// 等待状态,等待逻辑帧最慢的客户端跟上服务器逻辑帧
	};
	RUN_STATE m_state;
	float m_waitTime;

	// 游戏最后一次执行逻辑时间
	float m_lastRunTime;
	// 游戏累计运行时间
	float m_accumilatedTime;

	msg::PlayerRecords m_pastRecords;

	//std::vector<msg::PlayerFrameInput*> m_curFrameInputs;

	msg::RunNextFrameAck m_runNextFrameAckCache;
	msg::PlayerFrameInput* m_pCacheFrameInputs[G_FIGHT_MAX_PLAYER_COUNT];
};
