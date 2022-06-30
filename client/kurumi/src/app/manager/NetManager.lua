-- @Author: fangcheng
-- @Date:   2020-11-07 16:34:33
-- @remark: 游戏中所有的网络请求管理

-- 网络类型定义
local NET_TYPE = enum {
	1,
	"TCP",
	"KCP",
}
global.NET_TYPE = NET_TYPE

-- 回话ID定义
local SESSION_ID = enum {
	1,
	"GAME",
	"FIGHT"
}
global.SESSION_ID = SESSION_ID


-- 要屏蔽输出的消息
local SHIELD_PRING_MSGS = {
	["msg.RunNextFrameReq"] = true,
	["msg.RunNextFrameAck"] = true,
	["msg.Ping"] = true,
	["msg.Pong"] = true,
	["msg.PushPingInfo"] = true,
}

local str_len = string.len


local pb = require "luapb"
local NetManager = class("NetManager", import(".BaseManager"))

function NetManager:override_onInit()
	NetManager.super.override_onInit(self)

	self.tArrClient = {}
	self.tSessionInfo = {}

	self.pbLoader = require("app.common.PBLoader").new()
	self.pbLoader:initialize()

	self:initNet()
end

function NetManager:override_onDestroy()
	NetManager.super.override_onDestroy(self)
	self.tSessionInfo = {}

	for k, v in pairs(self.tArrClient) do
		v:closeClient()
	end
	self.tArrClient = {}
end


-- @brief 设置游戏服服务器信息
function NetManager:setGameInfo(ip, port, netType)
	self:setSessionInfo(SESSION_ID.GAME, ip, port, netType)
end

-- @brief 设置战斗服服务器信息
function NetManager:setFightInfo(ip, port, netType)
	self:setSessionInfo(SESSION_ID.FIGHT, ip, port, netType)
end

-- @brief 清除所有会话信息
function NetManager:clearAllSessionInfo()
	self:setFightInfo()
	self:setGameInfo()
end

-- @brief 设置会话信息
-- @param sessionID 会话id
-- @param ip 会话ip
-- @param port 会话端口
-- @param netType 连接类型,默认为TCP连接
function NetManager:setSessionInfo(sessionID, ip, port, netType)
	netType = netType or NET_TYPE.TCP

	assert(self.tArrClient[netType])

	if ip == nil then
		local info = self.tSessionInfo[sessionID]
		if info then
			self.tArrClient[info.net]:disconnect(sessionID)
		end
		self.tSessionInfo[sessionID] = nil
		return
	end

	local t = {}
	t.ip 		= ip
	t.port 		= port
	t.reCount 	= 0
	t.net 		= netType
	self.tSessionInfo[sessionID] = t

	self:doConnect(sessionID)
end

-- @brief 网络初始化
function NetManager:initNet()
	local function createClient(isKcp)
		local client = NetClient:create(isKcp)
		client:retain()
		client:registerLuaHandle("onConnectCallback", handler(self, self.onConnectCallback))
		client:registerLuaHandle("onMsgCallback", handler(self, self.onMsgCallback))
		client:registerLuaHandle("onRemoveSessionCallback", handler(self, self.onRemoveSessionCallback))
		client:registerLuaHandle("onDisconnectCallback", handler(self, self.onDisconnectCallback))
		client:registerLuaHandle("onClientCloseCallback", function()
			oRoutine(o_once(function()
				client:release()
			end))
		end)
		return client
	end

	self.tArrClient = {}
	self.tArrClient[NET_TYPE.TCP] = createClient(false)
	self.tArrClient[NET_TYPE.KCP] = createClient(true)
end

-- @brief 向游戏服发送消息
function NetManager:sendToGame(msgName, msg)
	self:sendMessage(SESSION_ID.GAME, msgName, msg)
end

-- @brief 向战斗服发送消息
function NetManager:sendToFight(msgName, msg)
	self:sendMessage(SESSION_ID.FIGHT, msgName, msg)
end

function NetManager:sendMessage(sessionID, msgName, msg)
	local msgId = self.pbLoader:getMsgId(msgName)
	assert(msgId)

	if G_MACROS.IS_PC and not SHIELD_PRING_MSGS[msgName] then
		print("send msg:", msgName, msgId)
		print_lua_value(msg)
		print("----------------------------")
	end
	local info = self.tSessionInfo[sessionID]
	if info then
		local data = pb.encode(msgName, msg)
		self.tArrClient[info.net]:sendMsg(sessionID, msgId, data, str_len(data))
	else
		error("Illegal session")
	end
end

-- @brief 连接结果回调
function NetManager:onConnectCallback(session, status)
	self:log("onConnectCallback", session:getIp(), session:getPort(), session:getSessionID(), status)

	local sessionID = session:getSessionID()
	if self.tSessionInfo[sessionID] == nil then
		session:disconnect()
		return
	end

	if status == 1 then
		self.tSessionInfo[sessionID].reCount = 0
		G_SysEventEmitter:emit(SysEvent.NET_CONNECT_SUC, sessionID)
	else
		-- 等待一段时间后再继续连 
		oRoutine(o_once(function()
			o_wait(o_seconds(0.5))
			self:doConnect(sessionID)
		end))
	end
end

-- @brief 连接断开回调
function NetManager:onDisconnectCallback(session)
	self:log("onDisconnectCallback", session:getIp(), session:getPort(), session:getSessionID())
	G_SysEventEmitter:emit(SysEvent.NET_DISCONNECT, sessionID)
	self:doConnect(session:getSessionID())
end

-- @brief 连接删除回调
function NetManager:onRemoveSessionCallback(session)
	self:log("onRemoveSessionCallback", session:getSessionID())
end

-- @brief 消息接收回调
function NetManager:onMsgCallback(sessionID, msgID, data)
	local msgName = self.pbLoader:getMsgName(msgID)

	if not msgName then
		logE("收到非法消息:", msgID)
		return
	end

	local msg, err = pb.decode(msgName, data)

	if not msg then
		logE("decode msg:", msgID, ",error:", err)
		return
	end

	-- 云风的pbc需要递归解析,luapb自动递归解析了,这儿不需要
	-- self:recursiveDecode(msg)

	if G_MACROS.IS_PC and not SHIELD_PRING_MSGS[msgName] then
		print("recv msg:", msgName, msgID)
		print_lua_value(msg)
		print("----------------------------")
	end

	G_NetEventEmitter:emit(msgName, msg)
end

-- --@brief 递归解析protobuf消息
-- function NetManager:recursiveDecode(tab,opcode)
-- 	for k,v in pairs(tab) do
-- 		if type(v) == "table" then
-- 			if type(v[1]) == "string" and string.find(v[1],"msg.") then
-- 				local ret = pb.decode(v[1], v[2])
-- 				if ret then
-- 					tab[k] = ret
-- 				end
-- 			end
-- 			self:recursiveDecode(tab[k])
-- 		end
-- 	end
-- end

-- @brief 执行连接操作
function NetManager:doConnect(sessionID)
	local info = self.tSessionInfo[sessionID]
	if info == nil then
		return
	end

	info.reCount = info.reCount + 1
	if info.reCount > 5 then
		info.reCount = 0
		G_SysEventEmitter:emit(SysEvent.NET_CONNECT_FAIL, sessionID)
		return false
	end

	self.tArrClient[info.net]:connect(info.ip, info.port, sessionID)
	return true
end

return NetManager