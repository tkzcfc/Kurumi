-- @Author: fangcheng
-- @Date:   2020-11-07 16:34:33
-- @remark: 游戏中所以的网络请求管理

local NetManager = class("NetManager", import(".BaseManager"))


function NetManager:override_onInit()
	NetManager.super.override_onInit(self)

	self:initNet()
	-- self:initUI()
end

function NetManager:override_onDestroy()
	NetManager.super.override_onDestroy(self)
	self.client:closeClient()
end

function NetManager:initNet()
	self.client = NetClient:create(false)
	self.client:registerLuaHandle("onConnectCallback", handler(self, self.onConnectCallback))
	self.client:registerLuaHandle("onMsgCallback", function(sessionID, msgID, data) end)
	self.client:registerLuaHandle("onRemoveSessionCallback", function(session)

	end)
	self.client:registerLuaHandle("onDisconnectCallback", function(session)

	end)
	self.client:registerLuaHandle("onClientCloseCallback", function()
		oRoutine(o_once(function()
			self.client:release()
		end))
	end)


	

	-- local client = Client.new()
	-- self.dns = client.net:createDnsResolver()
	-- self.dns:retain()
 --    self.dns:setCallback(function(addr, ip)
 --    	print("dns解析回调", addr, ip)
 --    	self.kcpResolveIp = ip
	-- 	if self:isConnect_Kcp() then
	-- 		self.client:kcpDisconnect(SESSIONID_KCP)
	-- 	else
	-- 		self:doKcpReconnect()
	-- 	end
 --    end)

	-- G_SysEventEmitter:on("event_appWillExit", function()
	-- 	if self.dns then
	-- 		self.dns:release()
	-- 		self.dns = nil
	-- 	end
	-- end)

	-- client.emitter:on("event_onTcpCconnect", function(sessionID, isConnect)
	-- 	local sessionData = self:getSessionData(sessionID)
		
	-- 	sessionData.isConnect = isConnect
		
	-- 	if isConnect then
	-- 		sessionData.curConnectCount = 0
	-- 		self:tryHideConnectLoading()
	-- 	else
	-- 		sessionData.curConnectCount = sessionData.curConnectCount + 1
	-- 		if sessionData.curConnectCount > MAX_CONNECT_COUNT_TCP then
	-- 			self:showConnectFailMsgBox()
	-- 		else
	-- 			self:tryShowConnectLoading()
	-- 			oRoutine(o_once(function()
	-- 				-- 等待一段时间后再继续连 
	-- 				o_wait(o_seconds(1))
	-- 				self:doTcpReconnect()
	-- 			end))
	-- 		end
	-- 	end
	-- end)

	-- client.emitter:on("event_onTcpMsg", function(sessionID, data)
	-- 	if string.len(data) <= 0 then
	-- 		print("收到0个字节消息!!!!!!!!!!!!!!!!!!!!!!!!!!!")
	-- 		return
	-- 	end
	-- 	local msg = json.decode(data)
	-- 	G_NetEventEmitter:emit(msg.__MsgName__, msg)

	-- 	print("recv-------------------------------------- begin>>>>")
	-- 	print_lua_value(msg)
	-- 	print("recv-------------------------------------- end>>>>")
	-- end)

	-- client.emitter:on("event_onTcpDisconnect", function(sessionID)
	-- 	self:getSessionData(sessionID).isConnect = false
	-- 	self:doTcpReconnect()
	-- end)

	-- client.emitter:on("event_onKcpConnect", function(sessionID, isConnect)
	-- 	self:getSessionData(sessionID).isConnect = isConnect and true or false
	-- 	print("kcp连接", isConnect and "成功" or "失败", isConnect)
	-- 	if not isConnect then
	-- 		oRoutine(o_once(function()
	-- 			-- 等待一段时间后再继续连 
	-- 			o_wait(o_seconds(2))
	-- 			self:doKcpReconnect()
	-- 		end))
	-- 	end
	-- end)

	-- client.emitter:on("event_onKcpMsg", function(sessionID, data)
	-- 	if string.len(data) <= 0 then
	-- 		print("收到0个字节消息!!!!!!!!!!!!!!!!!!!!!!!!!!!")
	-- 		return
	-- 	end
	-- 	local msg = json.decode(data)
	-- 	G_NetEventEmitter:emit(msg.__MsgName__, msg)

	-- 	print("recv-------------------------------------- begin>>>>")
	-- 	print_lua_value(msg)
	-- 	print("recv-------------------------------------- end>>>>")
	-- end)

	-- client.emitter:on("event_onKcpDisconnect", function(sessionID)
	-- 	print("kcp断开连接")
	-- 	self:getSessionData(sessionID).isConnect = false
	-- 	self:doKcpReconnect()
	-- end)

	-- self.client = client
	-- self.sessionMng = {}
end

function NetManager:onConnectCallback(session, status)
	if status == 1 then
	else
		oRoutine(o_once(function()
			-- 等待一段时间后再继续连 
			o_wait(o_seconds(1))
			self.client:connect(_MyG.startSvrTcpIP, _MyG.startSvrTcpPort, 0)
		end))
	end
	-- 	if isConnect then
	-- 		sessionData.curConnectCount = 0
	-- 		self:tryHideConnectLoading()
	-- 	else
	-- 		sessionData.curConnectCount = sessionData.curConnectCount + 1
	-- 		if sessionData.curConnectCount > MAX_CONNECT_COUNT_TCP then
	-- 			self:showConnectFailMsgBox()
	-- 		else
	-- 			self:tryShowConnectLoading()
	-- 			oRoutine(o_once(function()
	-- 				-- 等待一段时间后再继续连 
	-- 				o_wait(o_seconds(1))
	-- 				self:doTcpReconnect()
	-- 			end))
	-- 		end
	-- 	end
end

function NetManager:initUI()
	self.loadingUI = require("app.ui.general.LoadingUI"):new()
	self.loadingUI:setLocalZOrder(G_Const.WINDOW_Z.NET_LOADING)
	self.loadingUI:retain()

	self.msgBox = require("app.ui.general.NetMessageBoxUI"):new()
	self.msgBox:retain()

	self.showLoadingTag = false
	self.showMsgBoxTag = false

	-- 场景切换之前,移除loading或msgBox
	G_NetEventEmitter:on("event_willEnterScene", function() 
		self.loadingUI:hideLoding()
		self.msgBox:hideBox()
	end)
	-- 场景切换之后，恢复相应的ui
	G_NetEventEmitter:on("event_enterSceneFinish", function() 
		if self.showLoadingTag then
			self:showConnectLoading()
		end
		if self.showMsgBoxTag then
			self:showConnectFailMsgBox()
		end
	end)
end

return NetManager
