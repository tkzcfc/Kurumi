require("app.models.net.registerMsg")

local dispatcher = require("app.common.dispatcher")

local gameNet = class("gameNet", dispatcher)


function gameNet:ctor()
	self.super.ctor(self)

    local client = Client:getInstance()
    client:setAutoReconnect(true)
    client:setCallFunc(function(msgtype, data)
        if msgtype == "recv" then
            --print("recvMsg")
			self:recvMsg(data)
        else
            if msgtype == "connecting" then
                _MyG.Loading:showLoading()
            elseif msgtype == "fail" then
                _MyG.Loading:showLoading()
            elseif msgtype == "connect" then
                _MyG.Loading:hideLoding()
            elseif msgtype == "disconnect" then
                _MyG.Loading:showLoading()
            elseif msgtype == "loop exit" then
            end
           	self:call(msgtype, nil) 
        end
    end)

    self.client = client
    self.clientKeyMap = {}
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

    self.client:send(clientKey, encodeMsg)

    if _MyG.OPEN_DEBUG then
        print("send msg", msgKey)
        print(json.encode(msg).."\n")
    end
end

function gameNet:recvMsg(msgdata)
    --print("msgdata len", string.len(msgdata))
    local baseMsg, lastError = protobuf.decode("__msg_base_" , msgdata)

    if type(baseMsg) ~= "table" 
    or baseMsg.msgName == nil 
    or baseMsg.msgData == nil then
        print("net : data is wrongful!!!")
        print("error:", lastError)
        return
    end 
    local msg = protobuf.decode(baseMsg.msgName, baseMsg.msgData)

    if _MyG.OPEN_DEBUG then
        print("recv msg", baseMsg.msgName)
        print(json.encode(msg).."\n")
    end

    self:call(baseMsg.msgName, msg)
end

return gameNet


