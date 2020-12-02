require("app.models.net.registerMsg")

local dispatcher = require("app.common.dispatcher")

local gameNet = class("gameNet", dispatcher)


function gameNet:ctor()
    self.super.ctor(self)

    local client = TCPLuaClient:getInstance()
    client:setAutoReconnect(true)
    client:registerLuaHandle("onClientConnectCall", function(...) self:onClientConnectCall(...) end)
    client:registerLuaHandle("onClientDisconnectCall", function(...) self:onClientDisconnectCall(...) end)
    client:registerLuaHandle("onClientRecvCall", function(...) self:onClientRecvCall(...) end)
    client:registerLuaHandle("onClientCloseCall", function(...) self:onClientCloseCall(...) end)
    client:registerLuaHandle("onClientRemoveSessionCall", function(...) self:onClientRemoveSessionCall(...) end)

    self.client = client
    self.clientKeyMap = {}
end

function gameNet:onClientConnectCall(client, session, status)
    if status == 1 then
        _MyG.Loading:hideLoding()
    else
        _MyG.Loading:showLoading()
    end
    print("client connect status:", status)
end

function gameNet:onClientDisconnectCall(client, session)
    _MyG.Loading:showLoading()
    print("client disconnect")
end

function gameNet:onClientRecvCall(client, session, data, len)
  local function do_protobuf_decode()
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

  xpcall(do_protobuf_decode, function(msg)
      local errormsg = debug.traceback(msg, 3)
      local logmsg = "do_protobuf_decode error:\t"
      logmsg = logmsg..os.date() .. ":"..errormsg
      print(logmsg)

      local targetPlatform = cc.Application:getInstance():getTargetPlatform()
      if targetPlatform == cc.PLATFORM_OS_ANDROID 
      or targetPlatform == cc.PLATFORM_OS_IPHONE
      or targetPlatform == cc.PLATFORM_OS_IPAD then
          local data = {exception = logmsg}
              _MyG.Net:sendMsgToGame("debug.C2S_luaexception", data)
          end
      return errormsg
  end)
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


