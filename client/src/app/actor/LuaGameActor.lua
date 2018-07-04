local LuaGameActor = class("LuaGameActor", GameActor)

function LuaGameActor:ctor()

	self:registerLuaHandle("logicUpdate", function(...) return self:override_logicUpdate(...) end)

	self:registerLuaHandle("updateArmatureInfo", function(...) return self:override_updateArmatureInfo(...) end)

	self:registerLuaHandle("loadArmature", function(...) return self:override_loadArmature(...) end)

	self:registerLuaHandle("setActorPosition", function(...) return self:override_setActorPosition(...) end)

	self:registerLuaHandle("attLevelTest", function(...) return self:override_attLevelTest(...) end)

	self:registerLuaHandle("AABBCallback", function(...) return self:override_AABBCallback(...) end)

	self:registerLuaHandle("attOtherActorCallback", function(...) return self:override_attOtherActorCallback(...) end)

	self:registerLuaHandle("isRunAABB", function(...) return self:override_isRunAABB(...) end)

	self.FSM = self:getFSM()
	self.gameAttribute = self:getGameAttribute()

	self.actorSpeedController = self:getActorSpeedController()
	self.armatureSpeedController = self:getArmatureSpeedController()

	self.totalStateName = {}
	self.stateConfig = {}

	self.selfMovePower = {x = 0, y = 0}
	self.allMovePower = {}

    self:registerScriptHandler(function(state)
        if state == "enter" then
            self:onEnter()
        elseif state == "exit" then
            self:onExit()
        end
    end)
end

function LuaGameActor:onEnter()
end

function LuaGameActor:onExit()
end

function LuaGameActor:override_logicUpdate(time)
	self:updateMovePower(time)
end

function LuaGameActor:override_updateArmatureInfo()

	if self:getOrientation() == GAME_ORI_LEFT then
		local x = self.actorSpeedController:getGravityX()
		local y = self.actorSpeedController:getGravityY()
		self.actorSpeedController:setGravity(-math.abs(x), y)
	else
		local x = self.actorSpeedController:getGravityX()
		local y = self.actorSpeedController:getGravityY()
		self.actorSpeedController:setGravity(math.abs(x), y)
	end
end

function LuaGameActor:override_loadArmature(filePath)
	--self:getArmature():setScale(0.9)
end

function LuaGameActor:override_setActorPosition(x, y)
end

function LuaGameActor:override_attLevelTest(otherActor)
	return self:getActorType() > otherActor:getActorType()
end

function LuaGameActor:override_AABBCallback(otherActor)
end

function LuaGameActor:override_attOtherActorCallback(otherActor)
end

--actor受到攻击
-- 参数attackActor ： 攻击者
-- 参数isPickUp ： 是否为上挑攻击
function LuaGameActor:override_beAttacked(attackActor, isPickUp)
	if attackActor:getActorPositionX() > self:getActorPositionX() then
		self:setOrientation(GAME_ORI_RIGHT)
	elseif attackActor:getActorPositionX() < self:getActorPositionX() then
		self:setOrientation(GAME_ORI_LEFT)
	end
end

function LuaGameActor:override_movementEventCallFunc(armature, movementType, movementID)

	if movementType == ccs.MovementEventType.complete then

		local curStateName = self.FSM:getCurState():getStateName()

		local data = self.stateConfig[curStateName]
		if data == nil then
			print("ERROR: LuaGameActor:override_movementEventCallFunc -> self.stateConfig[curStateName] == nil")
			return
		end

		local index = -1
		for i,v in ipairs(data) do
			if movementID == data[i] then
				index = i
				break
			end
		end
		assert(index ~= -1)

		if index >= #data then
			self:handle(curStateName.."_stop")
			_MyG.PlayerDispatcher:call(curStateName.."_stop", self)
		else
			local armature = self:getArmature()
			armature:getAnimation():play(data[index + 1])
		end
	end
end

function LuaGameActor:override_isRunAABB(other)
	return true
end

function LuaGameActor:changeValueByOri(x)
	if self:getOrientation() == GAME_ORI_LEFT then
		return -x
	end
	return x
end

function LuaGameActor:loadConfig(config)
	assert(config ~= nil)

	self.stateConfig = config.StateConfig

	self:clearState()
	for k,v in pairs(self.stateConfig) do
		self:addState(k)
	end

	ccs.ArmatureDataManager:getInstance():addArmatureFileInfo(config.ExportJson)

	self:loadArmature(config.Armature)

	self:getArmature():getAnimation():setMovementEventCallFunc(function(...) self:override_movementEventCallFunc(...) end)
end

function LuaGameActor:addState(stateName)

	self.totalStateName[stateName] = true

	local enter = function(state, fsm)
		--print("FSM:enter",state:getStateName())
		
		local f = self["enter_"..stateName]
		if type(f) == "function" then
			f(self, state, fsm)
		end
		self:playAnimationByState(state)
	end

	local leave = function(state, fsm)
		--print("FSM:leave",state:getStateName())

		local f = self["leave_"..stateName]
		if type(f) == "function" then
			f(self, state, fsm)
		end
	end

	self.FSM:addState(stateName, enter, leave)
end

function LuaGameActor:handle(evenName)
	--print("handle", evenName)
	return self.FSM:handle(evenName)
end

function LuaGameActor:clearState()
	self.totalStateName = {}
	self.FSM:clear()
end

function LuaGameActor:playAnimationByState(state)
	local m = self.stateConfig[state:getStateName()]
	assert(m ~= nil and #m > 0)

	local armature = self:getArmature()
	armature:getAnimation():play(m[1])
end
----------------------move power begin-----------------------------

function LuaGameActor:setMovePower(powerName, power)
	--print(powerName, power.x, power.y)
	local ptab = self.allMovePower[powerName]
	if ptab then
		ptab.power.x = power.x
		ptab.power.y = power.y
	end
end

function LuaGameActor:getMovePower(powerName)
	return self.allMovePower[powerName]
end

function LuaGameActor:addMovePower(powerName, func)
	if self.allMovePower[powerName] == nil then
		self.allMovePower[powerName] = {power = {x = 0, y = 0}, enable = true, func = func}
	end
end

function LuaGameActor:removeMovePower(powerName)
	self.allMovePower[powerName] = nil
end

function LuaGameActor:setMovePowerEnable(powerName, enable, clearfunc)
	if self.allMovePower[powerName] ~= nil then
		self.allMovePower[powerName].enable = enable
		if clearfunc then
			self.allMovePower[powerName].func = nil
		end
	end
end

function LuaGameActor:setAllMovePowerEnable(enable)
	for k,v in pairs(self.allMovePower) do
		if v then
			v.enable = enable
		end
	end
end

function LuaGameActor:getAllMovePowerEnableState()
	local s = {}
	for k,v in pairs(self.allMovePower) do
		if v then 
			s[k] = v.enable
		end
	end
	return s
end

function LuaGameActor:setAllMovePowerEnableState(allEnableState)
	if allEnableState == nil or #allEnableState < 1 then
		return
	end
	
	for k,v in pairs(allEnableState) do
		if self.allMovePower[k] then
			self.allMovePower[k].enable = v
		end
	end
end

function LuaGameActor:updateMovePower(time)
	local power = {x = 0.0, y = 0.0}
	for k,v in pairs(self.allMovePower) do
		if v and v.enable then
			if v.func then
				local p = v.func(v.power, time)
				if p then
					power.x = power.x + p.x
					power.y = power.y + p.y
				end
			else
				power.x = power.x + v.power.x
				power.y = power.y + v.power.y
			end
		end
	end
	self:setSelfMovePower(power)
end

function LuaGameActor:setSelfMovePower(power)
	self:clearSelfMovePower()
	self.selfMovePower = power
end

function LuaGameActor:clearSelfMovePower()
	self.selfMovePower = {x = 0, y = 0}
end

----------------------------move power end---------------------------------

return LuaGameActor
