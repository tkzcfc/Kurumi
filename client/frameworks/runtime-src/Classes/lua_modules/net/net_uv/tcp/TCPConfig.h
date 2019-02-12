#pragma once

NS_NET_UV_BEGIN
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// 基础配置
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 是否使用内置消息结构
// 开启此选项以下配置才生效传送消息时使用TCPMsgHead结构
// 关闭此选项后socket的接收发送为原始数据
#define TCP_USE_NET_UV_MSG_STRUCT 1


// 套接字最小接收缓存大小
#define TCP_UV_SOCKET_RECV_BUF_LEN (1024 * 8)
// 套接字最小发送缓存大小
#define TCP_UV_SOCKET_SEND_BUF_LEN (1024 * 8)

// 大消息最大发送大小
// 如果消息头的长度字段大于该值
// 则直接认定为该客户端发送的消息为非法消息
// (4MB)
#define TCP_BIG_MSG_MAX_LEN (1024 * 1024 * 4)

// 单次消息发送最大字节
// 若超过该长度，则进行分片发送
// (4K)
#define TCP_WRITE_MAX_LEN (1024 * 4)

// 最大连接数
#define TCP_MAX_CONNECT (0xFFFF)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// 消息校验 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 消息开启md5校验
#define TCP_UV_OPEN_MD5_CHECK 1
// 校验密码
#define TCP_UV_ENCODE_KEY "net_uv_tcp_md5_key"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// 心跳相关
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 是否开启在UV线程进行心跳校验
// 如果关闭该选项，则需要在应用层自己做心跳校验
#define TCP_OPEN_UV_THREAD_HEARTBEAT 1

#if TCP_USE_NET_UV_MSG_STRUCT == 0
#undef TCP_OPEN_UV_THREAD_HEARTBEAT
#define TCP_OPEN_UV_THREAD_HEARTBEAT 0
#endif


#define TCP_HEARTBEAT_TIMER_DELAY (400)		// 心跳检测定时器间隔
#define TCP_HEARTBEAT_CHECK_DELAY (1200)	// 心跳检测时间
#define TCP_HEARTBEAT_MAX_COUNT_SERVER 3	// 心跳不回复最大次数(服务端)
#define TCP_HEARTBEAT_MAX_COUNT_CLIENT 3	// 心跳不回复最大次数(客户端)

// 心跳次数计数重置值(服务端) 小于0 
// 当服务端该值比客户端小时，心跳请求一般由客户端发送，服务端进行回复
#define TCP_HEARTBEAT_COUNT_RESET_VALUE_SERVER (-2) 
// 心跳次数计数重置值(客户端) 小于0
#define TCP_HEARTBEAT_COUNT_RESET_VALUE_CLIENT (-1)	


NS_NET_UV_END