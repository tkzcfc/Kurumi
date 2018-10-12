#pragma once


#include "KCPSocket.h"
#include "KCPSession.h"

NS_NET_UV_BEGIN

class NET_UV_EXTERN KCPServer : public Server
{
	//服务器所处阶段
	enum class ServerStage
	{
		START,		//启动中
		RUN,		//运行中
		WAIT_CLOSE_SERVER_SOCKET,// 等待服务器套接字关闭
		CLEAR,		//清理会话
		WAIT_SESSION_CLOSE,// 等待会话关闭
		STOP		//退出
	};

	struct serverSessionData
	{
		serverSessionData()
		{
			isInvalid = false;
			session = NULL;
		}
		KCPSession* session;
		bool isInvalid;
	};

public:

	KCPServer();
	KCPServer(const KCPServer&) = delete;

	virtual ~KCPServer();

	/// Server
	virtual void startServer(const char* ip, unsigned int port, bool isIPV6)override;

	virtual bool stopServer()override;

	virtual void updateFrame()override;

	/// SessionManager
	virtual void send(Session* session, char* data, unsigned int len)override;

	virtual void disconnect(Session* session)override;

	/// KCPServer
	bool isCloseFinish();

protected:

	/// Runnable
	virtual void run()override;

	/// SessionManager
	virtual void executeOperation()override;

	/// KCPServer
	void onNewConnect(Socket* socket);

	void onServerSocketClose(Socket* svr);

	bool onServerSocketConnectFilter(const struct sockaddr* addr);

	void onSessionRecvData(Session* session, char* data, unsigned int len);

	/// Server
	virtual void onIdleRun()override;

	virtual void onSessionUpdateRun()override;

protected:

	void addNewSession(KCPSession* session);

	void onSessionClose(Session* session);

	void clearData();

protected:
	bool m_start;

	KCPSocket* m_server;

	// 服务器所处阶段
	ServerStage m_serverStage;

	// 会话管理
	std::map<unsigned int, serverSessionData> m_allSession;
};



NS_NET_UV_END
