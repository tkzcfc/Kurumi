require("app.models.net.registerMsg")

local dispatcher = require("app.common.dispatcher")

local gameNet = class("gameNet", dispatcher)


function gameNet:ctor()
	self.super.ctor(self)

    local client = TCPLuaClient:getInstance()
    client:setAutoReconnect(true)
   --  client:setCallFunc(function(msgtype, data)
   --      if msgtype == "recv" then
   --          --print("recvMsg")
			-- self:recvMsg(data)
   --      else
   --          if msgtype == "connecting" then
   --              _MyG.Loading:showLoading()
   --          elseif msgtype == "fail" then
   --              _MyG.Loading:showLoading()
   --          elseif msgtype == "connect" then
   --              _MyG.Loading:hideLoding()
   --          elseif msgtype == "disconnect" then
   --              _MyG.Loading:showLoading()
   --          elseif msgtype == "loop exit" then
   --          end
   --         	self:call(msgtype, nil) 
   --      end
   --  end)
   client:registerLuaHandle("onClientConnectCall", function(...) self:onClientConnectCall(...) end)
   client:registerLuaHandle("onClientDisconnectCall", function(...) self:onClientDisconnectCall(...) end)
   client:registerLuaHandle("onClientRecvCall", function(...) self:onClientRecvCall(...) end)
   client:registerLuaHandle("onClientCloseCall", function(...) self:onClientCloseCall(...) end)
   client:registerLuaHandle("onClientRemoveSessionCall", function(...) self:onClientRemoveSessionCall(...) end)

    self.client = client
    self.clientKeyMap = {}
end

function gameNet:onClientConnectCall(client, session, status)
    print(tolua.type(client), tolua.type(session), tolua.type(status))
    if status == 1 then
        _MyG.Loading:hideLoding()
    else
        _MyG.Loading:showLoading()
    end
    -- print("client connect status:", status)
end

function gameNet:onClientDisconnectCall(client, session)
    _MyG.Loading:showLoading()
    print("client disconnect")
end

function gameNet:onClientRecvCall(client, session, data, len)
    local baseMsg, lastError = protobuf.decode("__msg_base_" , data)

    if type(baseMsg) ~= "table" 
    or baseMsg.msgName == nil 
    or baseMsg.msgData == nil then
        print("net : data is wrongful!!!")
        print("error:", lastError)
        return
    end 
    local msg = protobuf.decode(baseMsg.msgName, baseMsg.msgData)

    if _MyG.DEBUG then
        print("recv msg", baseMsg.msgName)
        print(json.encode(msg).."\n")
    end

    self:call(baseMsg.msgName, msg)
end

function gameNet:onClientCloseCall(client)
end

function gameNet:onClientRemoveSessionCall(client, session)
end


function gameNet:connect(ip, port)
	local k = ip..tostring(port)

	if self.clientKeyMap[k] == nil then
		self.clientKeyMap[k] = #self.clientKeyMap
	end

	return self.client:connect(ip, port, self.clientKeyMap[k])
end

function gameNet:sendMsg(msgKey, msg, ip, port)
	local s = ip..tostring(port)
	self:sendMsgToGame(msgKey, msg, self.clientKeyMap[s])
end

function gameNet:sendMsgToGame(msgKey, msg, clientKey)
	
	clientKey = clientKey or 0

	local baseMsg = { msgName = msgKey }
    baseMsg.msgData = protobuf.encode(msgKey, msg)
    local encodeMsg = protobuf.encode("__msg_base_", baseMsg)

    self.client:send(clientKey, encodeMsg, #encodeMsg)

    if _MyG.DEBUG then
        print("send msg", msgKey)
        print(json.encode(msg).."\n")
    end
end

return gameNet


