local Client = class("Client")

Client.DIR_TYPE_CLIENT 				= 1
Client.DIR_TYPE_SERVER 				= 2
Client.DIR_TYPE_SERVER_GAME 		= 3
Client.DIR_TYPE_TRANSFER 			= 4
Client.DIR_TYPE_CENTER 				= 5

local log = function() end
if G_MAC.DEBUG then
	-- log = print
end

function Client:ctor()
	self.emitter = G_Class.EventEmitter.new()
	self.kcpSessionInfoMap = {}

	self:initNet()

	-- self.net:connect(1, "www.baidu.com", 80)
end

------------------------------------------------public begin------------------------------------------------

function Client:tcpConnect(sessionID, ip, port)
	return self.net:connect(sessionID, ip, port)
end

function Client:tcpDisconnect(sessionID)
	return self.net:disconnect(sessionID)
end

function Client:tcpSend(sessionID, dirType, data)
	self.net:send(sessionID, dirType, data, string.len(data))
end

function Client:kcpConnect(sessionID, ip, port)
	local tmp = self.kcpSessionInfoMap[sessionID]
	if tmp then
		return false
	end
	tmp = {}
	tmp.isConnect = false
	tmp.userKey = string.format('kcp_uk_%d', sessionID)
	tmp.fd = -1
	self.kcpSessionInfoMap[sessionID] = tmp
	return self.net:kcp_connect(tmp.userKey, ip, port)
end

function Client:kcpDisconnect(sessionID)
	local tmp = self.kcpSessionInfoMap[sessionID]
	if tmp and tmp.isConnect then
		self.net:kcp_disconnect(tmp.fd)
	end
end

function Client:kcpSend(sessionID, dirType, data)
	local tmp = self.kcpSessionInfoMap[sessionID]
	if tmp and tmp.isConnect then
		self.net:kcp_send(tmp.fd, dirType, data, string.len(data))
	end
end
------------------------------------------------public end------------------------------------------------

function Client:initNet()
	self.net = cc.Net:create()

	G_SysEventEmitter:on("event_appWillExit", function()
		if self.net then
			self.net:release()
			self.net = nil
		end
	end)

	self.net:registerLuaHandle("onTcpCconnect", handler(self, self.onTcpCconnect))
	self.net:registerLuaHandle("onTcpMsg", handler(self, self.onTcpMsg))
	self.net:registerLuaHandle("onTcpDisconnect", handler(self, self.onTcpDisconnect))

	self.net:registerLuaHandle("onKcpMsg", handler(self, self.onKcpMsg))
	self.net:registerLuaHandle("onKcpConnect", handler(self, self.onKcpConnect))
	self.net:registerLuaHandle("onKcpDisconnect", handler(self, self.onKcpDisconnect))
end


-- "ERR_CONNECT_NONE",
-- "ERR_CONNECT_DNS_FAIL",
-- "ERR_CONNECT_TIMEOUT",
-- "ERR_CONNECT_READ_FAIL",
-- "ERR_CONNECT_OTHER",
function Client:onTcpCconnect(sessionID, isConnect, err)
	log("onTcpCconnect", sessionID, isConnect, err)
	self.emitter:emit("event_onTcpCconnect", sessionID, isConnect, err)
end
function Client:onTcpMsg(sessionID, data)
	log("onTcpMsg", sessionID, string.len(data), data)
	self.emitter:emit("event_onTcpMsg", sessionID, data)
end

function Client:onTcpDisconnect(sessionID)
	log("onTcpDisconnect", sessionID)
	self.emitter:emit("event_onTcpDisconnect", sessionID)
end

function Client:onKcpMsg(sessionID, data)
	local logicSessionID = nil
	for k,v in pairs(self.kcpSessionInfoMap) do
		if v.fd == sessionID then
			logicSessionID = k
			break
		end
	end

	log("onKcpMsg", logicSessionID)

	if logicSessionID then
		self.emitter:emit("event_onKcpMsg", logicSessionID, data)
	end
end

function Client:onKcpConnect(sessionID, isOK, userKey)
	local logicSessionID = nil
	for k,v in pairs(self.kcpSessionInfoMap) do
		if v.userKey == userKey then
			v.fd = sessionID
			if isOK then
				v.isConnect = true
			else
				self.kcpSessionInfoMap[k] = nil
			end
			logicSessionID = k
			break
		end
	end

	log("onKcpMsg", logicSessionID, isOK, userKey)

	if logicSessionID then
		self.emitter:emit("event_onKcpConnect", logicSessionID, isOK)
	end
end

function Client:onKcpDisconnect(sessionID, userKey)
	local logicSessionID = nil
	for k,v in pairs(self.kcpSessionInfoMap) do
		if v.userKey == userKey then
			self.kcpSessionInfoMap[k] = nil
			logicSessionID = k
			break
		end
	end

	log("onKcpDisconnect", logicSessionID, userKey)

	if logicSessionID then
		self.emitter:emit("event_onKcpDisconnect", logicSessionID)
	end
end

return Client
