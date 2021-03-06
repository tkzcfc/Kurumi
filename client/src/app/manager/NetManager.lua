-- @Author: fangcheng
-- @Date:   2020-11-07 16:34:33
-- @remark: 游戏中所以的网络请求管理

local manifest = require("pb.manifest")
local NetManager = class("NetManager", import(".BaseManager"))

local GAME_SESSION_ID  = 1
local FIGHT_SESSION_ID = 2

local str_len = string.len

-- 要屏蔽输出的消息
local SHIELD_PRING_MSGS = {}

function NetManager:override_onInit()
	NetManager.super.override_onInit(self)

	SHIELD_PRING_MSGS = {
		[MessageID.MSG_RUN_NEXT_FRAME_REQ] = true,
		[MessageID.MSG_RUN_NEXT_FRAME_ACK] = true,
		[MessageID.MSG_PING_REQ] = true,
		[MessageID.MSG_PING_ACK] = true,
	}


	self.sessionInfo = {}

	self:initProtobuf()
	self:initNet()
end

function NetManager:override_onDestroy()
	NetManager.super.override_onDestroy(self)
	self.sessionInfo = {}
	self.client:closeClient()
end


-- @brief 设置游戏服服务器信息
function NetManager:setGameInfo(ip, port)
	self:setSessionInfo(GAME_SESSION_ID, ip, port)
end

-- @brief 设置战斗服服务器信息
function NetManager:setFightInfo(ip, port)
	self:setSessionInfo(FIGHT_SESSION_ID, ip, port)
end

-- @brief 清除所有会话信息
function NetManager:clearAllSessionInfo()
	self:setFightInfo()
	self:setGameInfo()
end

-- @brief 设置会话信息
-- @param 会话id
-- @param 会话ip
-- @param 会话端口
function NetManager:setSessionInfo(sessionID, ip, port)
	if ip == nil then
		self.sessionInfo[sessionID] = nil
		self.client:disconnect(sessionID)
		return
	end

	local t = {}
	t.ip 		= ip
	t.port 		= port
	t.reCount 	= 0
	self.sessionInfo[sessionID] = t

	self:doConnect(sessionID)
end

-- @brief protobuf 初始化
function NetManager:initProtobuf()
	if cc.exports._protobuf_init then return end

	require "app.protobuf.protobuf"

	for k, v in pairs(manifest.pb) do
		local filename = cc.FileUtils:getInstance():fullPathForFilename("/pb/" .. v)
		protobuf.register_file(filename)
	end
	cc.exports._protobuf_init = true
end

-- @brief 网络初始化
function NetManager:initNet()
	self.client = NetClient:create(false)
	self.client:retain()
	self.client:registerLuaHandle("onConnectCallback", handler(self, self.onConnectCallback))
	self.client:registerLuaHandle("onMsgCallback", handler(self, self.onMsgCallback))
	self.client:registerLuaHandle("onRemoveSessionCallback", handler(self, self.onRemoveSessionCallback))
	self.client:registerLuaHandle("onDisconnectCallback", handler(self, self.onDisconnectCallback))
	self.client:registerLuaHandle("onClientCloseCallback", function()
		oRoutine(o_once(function()
			self.client:release()
		end))
	end)
end

-- @brief 向游戏服发送消息
function NetManager:sendToGame(msgID, msg)
	local info = manifest.CMD[msgID]
	if G_MAC.IS_PC and not SHIELD_PRING_MSGS[msgID] then
		print("send msg:", info.name, msgID)
		print_lua_value(msg)
		print("----------------------------")
	end

	local data = protobuf.encode(info.msg, msg)
	self.client:sendMsg(GAME_SESSION_ID, msgID, data, str_len(data))
end

-- @brief 向战斗服发送消息
function NetManager:sendToFight(msgID, msg)
	local info = manifest.CMD[msgID]
	if G_MAC.IS_PC and not SHIELD_PRING_MSGS[msgID] then
		print("send msg:", info.name, msgID)
		print_lua_value(msg)
		print("----------------------------")
	end

	local data = protobuf.encode(info.msg, msg)
	self.client:sendMsg(FIGHT_SESSION_ID, msgID, data, str_len(data))
end

-- @brief 连接结果回调
function NetManager:onConnectCallback(session, status)
	self:log("onConnectCallback", session:getIp(), session:getPort(), session:getSessionID(), status)

	local sessionID = session:getSessionID()
	if self.sessionInfo[sessionID] == nil then
		session:disconnect()
		return
	end

	if status == 1 then
		self.sessionInfo[sessionID].reCount = 0
		G_SysEventEmitter:emit(SysEvent.NET_CONNECT_SUC, sessionID == FIGHT_SESSION_ID)
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
	G_SysEventEmitter:emit(SysEvent.NET_DISCONNECT, sessionID == FIGHT_SESSION_ID, sessionID)
	self:doConnect(session:getSessionID())
end

-- @brief 连接删除回调
function NetManager:onRemoveSessionCallback(session)
	self:log("onRemoveSessionCallback", session:getSessionID())
end

-- @brief 消息接收回调
function NetManager:onMsgCallback(sessionID, msgID, data)
	local info = manifest.CMD[msgID]
	if not info then
		self:log("收到非法消息:", msgID)
		return
	end

	local msg, err = protobuf.decode(info.msg, data)

	if not msg then
		logE("decode msg:", msgID, ",error:", err)
		return
	end
	self:recursiveDecode(msg)

	if G_MAC.IS_PC and not SHIELD_PRING_MSGS[msgID] then
		print("recv msg:", info.name, msgID)
		print_lua_value(msg)
		print("----------------------------")
	end

	G_NetEventEmitter:emit(msgID, msg)
end

--@brief 递归解析protobuf消息
function NetManager:recursiveDecode(tab,opcode)
	for k,v in pairs(tab) do
		if type(v) == "table" then
			if type(v[1]) == "string" and string.find(v[1],"msg.") then
				local ret = protobuf.decode(v[1], v[2])
				if ret then
					tab[k] = ret
				end
			end
			self:recursiveDecode(tab[k])
		end
	end
end

-- @brief 执行连接操作
function NetManager:doConnect(sessionID)
	local info = self.sessionInfo[sessionID]
	if info == nil then
		return
	end

	info.reCount = info.reCount + 1
	if info.reCount > 5 then
		info.reCount = 0
		G_SysEventEmitter:emit(SysEvent.NET_CONNECT_FAIL, sessionID == FIGHT_SESSION_ID, sessionID)
		return false
	end

	self.client:connect(info.ip, info.port, sessionID)
	return true
end

return NetManager