local msgViewBase = class("msgViewBase", cc.load("mvc").ViewBase)

function msgViewBase:onCreate()

	-- local function onNodeEvent(event)
    --     if event == "enter" then
    --         self:onEnter()
    --     elseif event == "exit" then
    --         self:onExit()
    --     end
    -- end
    -- self:registerScriptHandler(onNodeEvent)

    self.msgRegisterMap = {}
end

function msgViewBase:register(msgKey, func, priority)
	_MyG.Net:register(msgKey, func, priority)
	self.msgRegisterMap[msgKey] = func
end

function msgViewBase:unRegisterAll()
    if self.msgRegisterMap == nil then
        print("\n\nERROR:The super class 'onCreate' is not executed\n\n")
    end
	for key,value in pairs(self.msgRegisterMap) do
		_MyG.Net:unRegister(key, value)
	end
	self.msgRegisterMap = {}
end

function msgViewBase:onEnter()
end

function msgViewBase:onExit()
	self:unRegisterAll()
end

return msgViewBase