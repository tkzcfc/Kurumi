local GlobalMsgRecipient = class("GlobalMsgRecipient")

function GlobalMsgRecipient:ctor()
    self.msgRegisterMap = {}

    -- self:register("", "")
    self:register("common.S2C_changeToPhase", changePhase)
end

function GlobalMsgRecipient:register(msgKey, funcName, priority)
	local function lamda(...) self[funcName](...) end
	_MyG.Net:register(msgKey, lamda, priority)
	self.msgRegisterMap[msgKey] = lamda
end

function GlobalMsgRecipient:unRegisterAll()
	for key,value in pairs(self.msgRegisterMap) do
		_MyG.Net:unRegister(key, value)
	end
	self.msgRegisterMap = {}
end

function GlobalMsgRecipient:changePhase(data)
	if data.code == 1 then
		--data.phase
	end
end

return GlobalMsgRecipient



