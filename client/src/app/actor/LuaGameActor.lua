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
	self:unregisterScriptHandler()
end

function LuaGameActor:override_logicUpdate(time)
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
	return self:getActorType() ~= other:getActorType()
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

-------------------------------------------------FSM-------------------------------------------------

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

-- 强制切换
function LuaGameActor:forceSwitch(stateName)
	self:override_forceSwitchClean()
	return self.FSM:forceSwitch(stateName) 
end

--强制切换清理
function LuaGameActor:override_forceSwitchClean()
	self:unLockOrientation()
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

return LuaGameActor
