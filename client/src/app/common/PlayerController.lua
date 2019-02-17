local PlayerController = class("PlayerController")

function PlayerController:ctor()
	self.inputEventList = {}

	for k,v in pairs(_MyG.INPUT_KEY) do
		-- print(k, v)
		self:registerInput(k, v)
	end	
end

function PlayerController:setPlayer(player)
	self.player = player
end

function PlayerController:registerInput(funcName, key)
	local func = function(...) 
		if self.player == nil then
			return
		end
		if self["input_"..funcName] and self.player then
			self["input_"..funcName](self, ...)
		end
	end
	_MyG.InputDispatcher:register(key, func)
	self.inputEventList[key] = func
end

function PlayerController:unRegisterAllInput()
	for k,v in pairs(self.inputEventList) do
		_MyG.InputDispatcher:unRegister(k, v)
	end
	self.inputEventList = {}
end

function PlayerController:enable()
	self:disable()
end

function PlayerController:disable()
	self.controlBegin = false
end

function PlayerController:input_CONTROL_X(value)
	self.controlBegin = true
	self.player:move_x(value)
end

function PlayerController:input_CONTROL_Y(value)
	self.controlBegin = true
end

function PlayerController:input_CONTROL_CANCEL()
	self.controlBegin = false
	self.player:move_stop()
end

function PlayerController:input_CONTROL_ATTACK_NORMAL()
	self.player:attack_normal()
end

function PlayerController:input_CONTROL_JUMP()
	self.player:jump()
end

function PlayerController:input_CONTROL_DOWN_CUT()
	self.player:down_cut()
end

function PlayerController:input_CONTROL_SKILL_1()
	self.player:do_skill_1()
end

function PlayerController:input_CONTROL_SKILL_10()
	self.player:do_skill_10()
end

return PlayerController


