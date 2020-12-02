-- @Author: fangcheng
-- @Date:   2020-11-07 16:34:33
-- @remark: 游戏中所以的网络请求管理

local NetManager = class("NetManager", import(".BaseManager"))
local Client = require("app.moudels.net.Client")

local SESSIONID_KCP = 1000
local SESSIONID_TCP = 1

-- tcp 最大重连次数
local MAX_CONNECT_COUNT_TCP = 5

function NetManager:override_onInit()
	NetManager.super.override_onInit(self)
	self.tcpIp 		= _MyG.startSvrTcpIP
	self.tcpPort 	= _MyG.startSvrTcpPort

	self:initNet()
	self:initNetEvent()
	self:initUI()
end

function NetManager:destroy()
	self.loadingUI:release()
	self.msgBox:release()
end

function NetManager:initNet()
	local client = Client.new()

	self.dns = client.net:createDnsResolver()
	self.dns:retain()
    self.dns:setCallback(function(addr, ip)
    	print("dns解析回调", addr, ip)
    	self.kcpResolveIp = ip
		if self:isConnect_Kcp() then
			self.client:kcpDisconnect(SESSIONID_KCP)
		else
			self:doKcpReconnect()
		end
    end)

	G_SysEventEmitter:on("event_appWillExit", function()
		if self.dns then
			self.dns:release()
			self.dns = nil
		end
	end)

	client.emitter:on("event_onTcpCconnect", function(sessionID, isConnect)
		local sessionData = self:getSessionData(sessionID)
		
		sessionData.isConnect = isConnect
		
		if isConnect then
			sessionData.curConnectCount = 0
			self:tryHideConnectLoading()
		else
			sessionData.curConnectCount = sessionData.curConnectCount + 1
			if sessionData.curConnectCount > MAX_CONNECT_COUNT_TCP then
				self:showConnectFailMsgBox()
			else
				self:tryShowConnectLoading()
				oRoutine(o_once(function()
					-- 等待一段时间后再继续连 
					o_wait(o_seconds(1))
					self:doTcpReconnect()
				end))
			end
		end
	end)

	client.emitter:on("event_onTcpMsg", function(sessionID, data)
		if string.len(data) <= 0 then
			print("收到0个字节消息!!!!!!!!!!!!!!!!!!!!!!!!!!!")
			return
		end
		local msg = json.decode(data)
		G_NetEventEmitter:emit(msg.__MsgName__, msg)

		print("recv-------------------------------------- begin>>>>")
		print_lua_value(msg)
		print("recv-------------------------------------- end>>>>")
	end)

	client.emitter:on("event_onTcpDisconnect", function(sessionID)
		self:getSessionData(sessionID).isConnect = false
		self:doTcpReconnect()
	end)

	client.emitter:on("event_onKcpConnect", function(sessionID, isConnect)
		self:getSessionData(sessionID).isConnect = isConnect and true or false
		print("kcp连接", isConnect and "成功" or "失败", isConnect)
		if not isConnect then
			oRoutine(o_once(function()
				-- 等待一段时间后再继续连 
				o_wait(o_seconds(2))
				self:doKcpReconnect()
			end))
		end
	end)

	client.emitter:on("event_onKcpMsg", function(sessionID, data)
		if string.len(data) <= 0 then
			print("收到0个字节消息!!!!!!!!!!!!!!!!!!!!!!!!!!!")
			return
		end
		local msg = json.decode(data)
		G_NetEventEmitter:emit(msg.__MsgName__, msg)

		print("recv-------------------------------------- begin>>>>")
		print_lua_value(msg)
		print("recv-------------------------------------- end>>>>")
	end)

	client.emitter:on("event_onKcpDisconnect", function(sessionID)
		print("kcp断开连接")
		self:getSessionData(sessionID).isConnect = false
		self:doKcpReconnect()
	end)

	self.client = client
	self.sessionMng = {}
end

function NetManager:initNetEvent()
	G_NetEventEmitter:on("登录_答复", function(msg)
		-- 登录成功,设置token
		if msg.strError == "" then
			self.client.net:setToken(msg.nToken)
			self.client.net:setDomain(msg.strDomain)
			self.client.net:setReserved(msg.nToken_Reserved)
		end
	end)
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


function NetManager:tryHideConnectLoading()
	if self.showMsgBoxTag then
		self:hideConnectLoading()
		return
	end

	if not self:getSessionData(SESSIONID_TCP).isConnect then
		return
	end

	self:hideConnectLoading()
end

function NetManager:tryShowConnectLoading()
	if self.showMsgBoxTag then
		return
	end

	if not self:getSessionData(SESSIONID_TCP).isConnect then
		self:showConnectLoading()
	end
end

-- 显示连接loading
function NetManager:showConnectLoading()
	self.showLoadingTag = true
	self.loadingUI:showLoading(nil, nil, nil, 0xfffff)
end

function NetManager:hideConnectLoading()
	self.showLoadingTag = false
	self.loadingUI:hideLoding()
end

function NetManager:isShowConnectLoading()
	return self.showLoadingTag
end

-- 显示连接失败弹窗
function NetManager:showConnectFailMsgBox()
	self.showMsgBoxTag = true
	self.msgBox:showBox("连接失败，请稍后再试", function()
		self:hideConnectFailMsgBox()
		self:getSessionData(SESSIONID_TCP).curConnectCount = 0
		self:connect_Tcp()
	end)
end

function NetManager:hideConnectFailMsgBox()
	self.showMsgBoxTag = false
	self.msgBox:hideBox()
end

function NetManager:isShowConnectFailMsgBox()
	return self.showMsgBoxTag
end

--------------------------------------------- tcp ---------------------------------------------

function NetManager:doTcpReconnect()
	local sessionData = self:getSessionData(SESSIONID_TCP)
	print("连接tcp", sessionData.curConnectCount)

	self:tryShowConnectLoading()
	self:connect_Tcp()
end

function NetManager:connect_Tcp()
	self.client:tcpConnect(SESSIONID_TCP, self.tcpIp, self.tcpPort)
end

function NetManager:isConnect_Tcp()
	return self:getSessionData(SESSIONID_TCP).isConnect
end

function NetManager:resetTcpAddress(ip, port)
	self.tcpIp 		= ip
	self.tcpPort 	= port
	if self:isConnect_Tcp() then
		self.client:tcpDisconnect(SESSIONID_TCP)
	else
		self:doTcpReconnect()
	end
end

--------------------------------------------- kcp ---------------------------------------------
function NetManager:doKcpReconnect()
	if not self.kcpResolveIp or not self.kcpPort then
		return
	end
	self:connect_Kcp()
end

function NetManager:connect_Kcp()
	if self:isConnect_Kcp() then
		return
	end
	if self.kcpResolveIp == nil or self.kcpResolveIp == "" then
		print("kcp地址未解析")
		return
	end
	self.client:kcpConnect(SESSIONID_KCP, self.kcpResolveIp, self.kcpPort)
end

function NetManager:isConnect_Kcp()
	return self:getSessionData(SESSIONID_KCP).isConnect
end

function NetManager:setKcpAddress(ip, port)
	self.kcpIp 		= ip
	self.kcpResolveIp = nil
	self.kcpPort 	= port
end

function NetManager:doResolve()
    self.dns:resolve(self.kcpIp)
end

function NetManager:clearKcppAddress()
	self.kcpIp 		= nil
	self.kcpPort 	= nil
	self.self.kcpResolveIp = nil
	if self:isConnect_Kcp() then
		self.client:kcpDisconnect(SESSIONID_KCP)
	end
end

---------------------------------------------  ---------------------------------------------

function NetManager:sendMsg(msg, sendToGame)
	if not G_MSG.check_msg(msg) then
		print("发送消息失败，消息校验失败")
		return
	end
	local data = json.encode(msg)
	-- 游戏中，发送消息时，先判断2条线路，如果都通使用kcp通道，如果kcp不通使用tcp通道。
	if self:isConnect_Kcp() then

		print("kcp send-------------------------------------- begin>>>>")
		print_lua_value(msg)
		print("kcp send-------------------------------------- end>>>>")

		if sendToGame then
			self.client:kcpSend(SESSIONID_KCP, Client.DIR_TYPE_SERVER_GAME, data)
		else
			self.client:kcpSend(SESSIONID_KCP, Client.DIR_TYPE_SERVER, data)
		end
		return true
	elseif self:isConnect_Tcp() then

		print("tcp send-------------------------------------- begin>>>>")
		print_lua_value(msg)
		print("tcp send-------------------------------------- end>>>>")

		if sendToGame then
			self.client:tcpSend(SESSIONID_TCP, Client.DIR_TYPE_SERVER_GAME, data)
		else
			self.client:tcpSend(SESSIONID_TCP, Client.DIR_TYPE_SERVER, data)
		end
		return true
	else
		logI("发送消息失败，未连接到服务器")
	end
end

function NetManager:getSessionData(sessionID)
	local t = self.sessionMng[sessionID]
	if not t then
		t = {}
		t.isConnect = false
		t.curConnectCount = 0
		t.sessionID = sessionID
		self.sessionMng[sessionID] = t
	end
	return t
end

return NetManager
