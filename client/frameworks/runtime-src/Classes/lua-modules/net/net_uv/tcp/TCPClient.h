#pragma once

#include "TCPSocket.h"
#include "TCPSession.h"

NS_NET_UV_BEGIN

class NET_UV_EXTERN TCPClient : public Client
{
protected:
	enum CONNECTSTATE
	{
		CONNECT,		//已连接
		CONNECTING,		//正在连接
		DISCONNECTING,	//正在断开
		DISCONNECT,		//已断开
	};

	struct clientSessionData
	{
		clientSessionData() {}
		~clientSessionData() {}
		CONNECTSTATE connectState;
		bool removeTag; // 是否被标记移除
		bool reconnect;	// 是否断线重连
		float curtime;
		float totaltime;
		std::string ip;
		unsigned int port;
		TCPSession* session;
	};

	//客户端所处阶段
	enum class clientStage
	{
		START,
		CLEAR_SESSION,//清理会话
		WAIT_EXIT,//即将退出
		STOP
	};
public:

	TCPClient();
	TCPClient(const TCPClient&) = delete;
	virtual ~TCPClient();

	/// Client
	virtual void connect(const char* ip, unsigned int port, unsigned int sessionId)override;

	virtual void disconnect(unsigned int sessionId)override;

	virtual void closeClient()override;
	
	virtual void updateFrame()override;

	virtual void send(unsigned int sessionId, char* data, unsigned int len)override;

	virtual void removeSession(unsigned int sessionId)override;

	/// SessionManager
	virtual void send(Session* session, char* data, unsigned int len)override;

	virtual void disconnect(Session* session)override;

	/// TCPClient
	bool isCloseFinish();

	//是否启用TCP_NODELAY
	bool setSocketNoDelay(bool enable);

	//设置心跳
	bool setSocketKeepAlive(int enable, unsigned int delay);

	//设置所有socket是否自动重连
	void setAutoReconnect(bool isAuto);

	//设置所有socket自动重连时间(单位：S)
	void setAutoReconnectTime(float time);

	//是否自动重连
	void setAutoReconnectBySessionID(unsigned int sessionID, bool isAuto);

	//自动重连时间(单位：S)
	void setAutoReconnectTimeBySessionID(unsigned int sessionID, float time);

protected:

	/// Runnable
	virtual void run()override;

	/// SessionManager
	virtual void executeOperation()override;

	/// Client
	virtual void onIdleRun()override;

	virtual void onSessionUpdateRun()override;

	/// TCPClient
	void onSocketConnect(Socket* socket, int status);

	void onSessionClose(Session* session);

	void onSessionRecvData(Session* session, char* data, unsigned int len);

	void createNewConnect(void* data);

	void clearData();

	clientSessionData* getClientSessionDataBySessionId(unsigned int sessionId);

	clientSessionData* getClientSessionDataBySession(Session* session);

	void onClientUpdate();

protected:
	uv_timer_t m_clientUpdateTimer;

	bool m_reconnect;		// 是否自动断线重连
	float m_totalTime;		// 断线重连时间
	bool m_enableNoDelay;	
	int m_enableKeepAlive; 
	int m_keepAliveDelay;

	// 所有会话
	std::map<unsigned int, clientSessionData*> m_allSessionMap;
	
	clientStage m_clientStage;
	bool m_isStop;
protected:

	static void uv_client_update_timer_run(uv_timer_t* handle);
};
NS_NET_UV_END


