-- @Author: fangcheng
-- @Date:   2020-11-07 16:34:33
-- @remark: 游戏中所以的网络请求管理

local manifest = require("pb.manifest")
local NetManager = class("NetManager", import(".BaseManager"))

local GAME_SESSION_ID  = 1
local FIGHT_SESSION_ID = 2

function NetManager:override_onInit()
	NetManager.super.override_onInit(self)

	self.sessionInfo = {}

	self:initProtobuf()
	self:initNet()
	-- self:initUI()
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

	require "app.modules.protobuf.protobuf"

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

-- @brief 连接结果回调
function NetManager:onConnectCallback(session, status)
	self:log("onConnectCallback", session:getSessionID(), status)

	local sessionID = session:getSessionID()
	if self.sessionInfo[sessionID] == nil then
		session:disconnect()
		return
	end

	if status == 1 then
		self.sessionInfo[sessionID].reCount = 0
	else
		-- 等待一段时间后再继续连 
		oRoutine(o_once(function()
			o_wait(o_seconds(1))
			self:doConnect(sessionID)
		end))
	end
end

-- @brief 连接断开回调
function NetManager:onDisconnectCallback(session)
	self:log("onDisconnectCallback", session:getSessionID())
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

	G_NetEventEmitter:emit(msgID, msg)
end

-- @brief 执行连接操作
function NetManager:doConnect(sessionID)
	local info = self.sessionInfo[sessionID]
	if info == nil then
		return
	end

	info.reCount = info.reCount + 1
	if info.reCount > 3 then
		return false
	end

	self.client:connect(info.ip, info.port, sessionID)
	return true
end

function NetManager:initUI()
	-- self.loadingUI = require("app.ui.general.LoadingUI"):new()
	-- self.loadingUI:setLocalZOrder(G_Const.WINDOW_Z.NET_LOADING)
	-- self.loadingUI:retain()

	-- self.msgBox = require("app.ui.general.NetMessageBoxUI"):new()
	-- self.msgBox:retain()

	-- self.showLoadingTag = false
	-- self.showMsgBoxTag = false

	-- -- 场景切换之前,移除loading或msgBox
	-- G_NetEventEmitter:on("event_willEnterScene", function() 
	-- 	self.loadingUI:hideLoding()
	-- 	self.msgBox:hideBox()
	-- end)
	-- -- 场景切换之后，恢复相应的ui
	-- G_NetEventEmitter:on("event_enterSceneFinish", function() 
	-- 	if self.showLoadingTag then
	-- 		self:showConnectLoading()
	-- 	end
	-- 	if self.showMsgBoxTag then
	-- 		self:showConnectFailMsgBox()
	-- 	end
	-- end)
end

return NetManager
