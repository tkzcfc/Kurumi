local LuaCharacter = require("app.foundation.LuaCharacter")
local BehaviorTree = require("app.AI.BehaviorTree")

local AICharacter = class("AICharacter", LuaCharacter)

function AICharacter:ctor()
	AICharacter.super.ctor(self)
	self.bhTree = BehaviorTree:new()
	self:enableUpdate()
end

function AICharacter:loadConfig(config)
	AICharacter.super.loadConfig(self, config)
end

function AICharacter:override_update(delta)
	AICharacter.super.override_update(self, delta)
	if self.bhTree then
		self.bhTree:update(delta)
	end
end

function AICharacter:onExit()
	AICharacter.super.onExit(self)
	if self.bhTree then
		self.bhTree:doForceStop()
	end
end

function AICharacter:ai_hasTarget()
	return self.hatredTarget == nil
end

function AICharacter:ai_findTarget()
	local filterSystem = self:getSystem("FilterSystem")
	if filterSystem == nil then
		self.hatredTarget = nil
		return
	end
	self.hatredTarget = filterSystem:randomGetActorByFilterData(BOX2D_FILTER_MASK.B2DM_PLAYER)
	return true
end

-- 空闲
function AICharacter:ai_on_free()
	return true
end

-- 追击
function AICharacter:ai_on_pursuit()
	return true
end

-- 逃跑
function AICharacter:ai_on_escape()
	return true
end

function AICharacter:ai_rand_move(time)
	return self:ai_move_by_time( math.random(0.5, tonumber(time) ) )
end

function AICharacter:ai_move_by_time(time)
	time = tonumber(time)

	if not self:handle("CMD_MoveStart") then
		return true
	end

	local curTime = 0
	self.moveToLeft = math.random(0, 1) == 0
	print("self.moveToLeft", self.moveToLeft)

	self.bhTree:doPauseUntil(function(delta)
		curTime = curTime + delta

		if curTime >= time then
			self:ai_move_stop()
			return true
		end

		if self.FSM:getCurState():getStateName() ~= "State_Run" then
			self:ai_move_stop()
			return true
		end 
	end)

	return true
end

function AICharacter:ai_move_stop()
	self:clearForceX()
	return self:handle("CMD_MoveStand")
end


return AICharacter


