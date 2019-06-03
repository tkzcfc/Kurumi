local LuaCharacter = require("app.foundation.LuaCharacter")
local BehaviorTree = require("app.AI.BehaviorTree")

local AICharacter = class("AICharacter", LuaCharacter)

function AICharacter:ctor()
	AICharacter.super.ctor(self)
	self.bhTree = BehaviorTree:new()
	self:enableUpdate()

	self:setFilterData(BOX2D_FILTER_MASK.B2DM_MONSTER)
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

function AICharacter:ai_has_target()
	return self.hatredTarget ~= nil
end

function AICharacter:ai_find_target()
	local filterSystem = self:getSystem("FilterSystem")
	if filterSystem == nil then
		self.hatredTarget = nil
		return
	end
	self.hatredTarget = filterSystem:randomGetActorByFilterData(BOX2D_FILTER_MASK.B2DM_PLAYER)
	return true
end

function AICharacter:ai_is_free()
	return true
end

function AICharacter:ai_is_escape()
	return true
end

function AICharacter:ai_is_attack()
	return true
end

-- 空闲
function AICharacter:ai_do_free_tree()
	local data = require("app.AI.export.free_export")

	local newtree = BehaviorTree:new()

	newtree:execute(data, self, false)

	self.bhTree:doPauseUntil(function(delta)
		newtree:update(delta)
		return newtree:isFinish()
	end)
	return true
end

-- 逃跑
function AICharacter:ai_do_escape_tree()
	return true
end

-- 攻击
function AICharacter:ai_do_attack_tree()
	return true
end

function AICharacter:ai_rand_move(time)
end

function AICharacter:ai_can_attack()
	return false
end

function AICharacter:ai_move_by_time(minTime, maxTime)
	local time = math.random(minTime, maxTime)

	if not self:handle("CMD_MoveStart") then
		return true
	end

	local curTime = 0
	self.moveToLeft = math.random(0, 1) == 0
	
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


