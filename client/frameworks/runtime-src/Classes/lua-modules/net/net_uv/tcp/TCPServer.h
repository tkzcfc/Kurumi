#pragma once


#include "TCPSocket.h"
#include "TCPSession.h"

NS_NET_UV_BEGIN

class NET_UV_EXTERN TCPServer : public Server
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
		TCPSession* session;
		bool isInvalid;
	};

public:

	TCPServer();
	TCPServer(const TCPServer&) = delete;

	virtual ~TCPServer();

	/// Server
	virtual void startServer(const char* ip, unsigned int port, bool isIPV6)override;

	virtual bool stopServer()override;

	virtual void updateFrame()override;

	/// SessionManager
	virtual void send(Session* session, char* data, unsigned int len)override;

	virtual void disconnect(Session* session)override;

	/// TCPServer
	bool isCloseFinish();

protected:

	/// Runnable
	virtual void run()override;

	/// SessionManager
	virtual void executeOperation()override;

	/// TCPServer
	void onNewConnect(uv_stream_t* server, int status);

	void onServerSocketClose(Socket* svr);
	
	void onSessionRecvData(Session* session, char* data, unsigned int len);

	/// Server
	virtual void onIdleRun()override;

	virtual void onSessionUpdateRun()override;
	
protected:

	void addNewSession(TCPSession* session);

	void onSessionClose(Session* session);

	void clearData();

protected:
	bool m_start;

	TCPSocket* m_server;
		
	// 服务器所处阶段
	ServerStage m_serverStage;

	// 会话管理
	std::map<unsigned int, serverSessionData> m_allSession;

	unsigned int m_sessionID;
};



NS_NET_UV_END
