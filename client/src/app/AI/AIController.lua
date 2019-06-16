local BehaviorTree = require("app.AI.BehaviorTree")

local AI_CONTROLLER_UPDATE_INTERVAL = 0.1

local AIController = class("AIController")

function AIController:ctor()
	self.bhTree = BehaviorTree:new()
	self.updateInterval = 0.0
	self.doAttackInterval = 0.0
	self.scriptDirName = ""

	self.onActorDestroyCall = function(actor)
		if self.hatredTarget == actor then
			self.hatredTarget = nil
		end
	end
	_MyG.EventDispatcher:register("onActorDestroy", self.onActorDestroyCall)
end

function AIController:start(pawn, scriptname, dirname, loop)
	if dirname == "" then
		self.scriptDirName = ""
	else
		self.scriptDirName = dirname .. "."
	end
	self.pawn = pawn
	self.updateInterval = 0.0
	self.blackboard = {}

	local node = self:require(scriptname)
	self.bhTree:execute(node, self, loop)
end

function AIController:setBlackboard(key, value)
	self.blackboard[key] = value
	return true
end

function AIController:removeBlackboardKey(key)
	self.blackboard[key] = nil
	return true
end

function AIController:update(delta)

	if self.pawn == nil then
		return false
	end

	if self.doAttackInterval > 0 then
		self.doAttackInterval = self.doAttackInterval - delta
	end
	
	self.updateInterval = self.updateInterval + delta
	if self.updateInterval < AI_CONTROLLER_UPDATE_INTERVAL then
		return false
	end

	if self.bhTree then
		self.bhTree:update(self.updateInterval)
	end

	if self:ai_has_target() then
		if self.hatredTarget:getPositionX() > self.pawn:getPositionX() then
			self.pawn:setOrientation(GAME_ORI_RIGHT)
		else
			self.pawn:setOrientation(GAME_ORI_LEFT)
		end
	end

	self.updateInterval = 0.0
	return true
end

function AIController:onEnter()
end

function AIController:onExit()
	if self.bhTree then
		self.bhTree:doForceStop()
		self.bhTree = nil
	end
	self.pawn = nil
	_MyG.EventDispatcher:unRegister("onActorDestroy", self.onActorDestroyCall)
end

function AIController:require(name)
	local scriptPath = "app.AI.export." ..  self.scriptDirName .. name .. "_export"
	return require(scriptPath)
end

-----------------------------------------------------------------------------------------------------

-- 有目标对象？
function AIController:ai_has_target()
	return self.hatredTarget ~= nil
end

-- 寻找目标对象
function AIController:ai_find_target()
	local filterSystem = self.pawn:getSystem("FilterSystem")
	if filterSystem == nil then
		self.hatredTarget = nil
		return
	end
	self.hatredTarget = filterSystem:randomGetActorByFilterData(BOX2D_FILTER_MASK.B2DM_PLAYER)
	return true
end

-- 朝向左边？
function AIController:ai_is_ori_left()
	return self.pawn.orientationCache == GAME_ORI_LEFT
end

-- 距离目标大于distance？
function AIController:ai_is_dis_too_long(distance)
	if self.hatredTarget == nil then
		return false
	end
	return math.abs(self.hatredTarget:getPositionX() - self.pawn:getPositionX()) > distance
end

-- 检测黑板是否有该值
function AIController:ai_check_value(key)
	if self.blackboard[key] then
		return true
	end
	return false
end

-- 调用黑板函数并始终返回true
function AIController:ai_call_bb_true(funcName, ...)
	local curFunc = self.blackboard[funcName]
	if curFunc then
		curFunc(...)
	end
	return true
end

-- 调用黑板函数并始终返回false
function AIController:ai_call_bb_false(funcName, ...)
	local curFunc = self.blackboard[funcName]
	if curFunc then
		curFunc(...)
	end
	return false
end

-- 调用黑板函数
function AIController:ai_call_bb_false(funcName, ...)
	local curFunc = self.blackboard[funcName]
	if curFunc then
		return curFunc(...)
	end
	return false
end

-- 运行子树
function AIController:ai_run_sub_tree(treeName, loop, result)
	loop = loop or false

	local data = self:require(treeName)

	local newtree = BehaviorTree:new()

	newtree:execute(data, self, false)

	self.bhTree:doPauseUntil(function(delta)
		newtree:update(delta)
		return newtree:isFinish()
	end)
	
	if result == nil then
		return newtree.executionResult
	end

	return result
end

-- 执行状态机切换指令
function AIController:ai_do_handle(cmd, result)
	if result == nil then
		return self.pawn:handle(cmd)
	else
		self.pawn:handle(cmd)
		return result
	end
end

--------------------------------------------------------------------------------------------------------------------

function AIController:ai_can_attack()
	if self.hatredTarget == nil then
		return false
	end
	local rangeValid = math.abs(self.hatredTarget:getPositionX() - self.pawn:getPositionX()) <= self.pawn.config.AI_CONFIG.ATTACK_MIN_RANGE
	return rangeValid and self.doAttackInterval <= 0.0
end

function AIController:ai_reset_atk_interval(interval)
	self.doAttackInterval = interval
	return true
end

function AIController:ai_do_attack()
	self.doAttackInterval = self.pawn.config.AI_CONFIG.ATTACK_INTERVAL
end

function AIController:ai_move_by_time(minTime, maxTime, isMoveToLeft)
	local time = _MyG.randomf(minTime, maxTime)

	if isMoveToLeft == nil then
		isMoveToLeft = math.random(0, 1) == 0
	end

	if not self.pawn:moveStart(isMoveToLeft) then
		return true
	end

	local curTime = 0
	local pre_pos_x = self.pawn:getPositionX()
	local move_dis_zero_count = 0

	self.bhTree:doPauseUntil(function(delta)
		curTime = curTime + delta

		-- 时间判断
		if curTime >= time then
			self:ai_move_stop()
			return true
		end

		-- 判断走到无法前行的地方，停止走动
		local cur_pos_x = self.pawn:getPositionX()
		if math.abs(pre_pos_x - cur_pos_x) < 1.0 then
			move_dis_zero_count = move_dis_zero_count + 1
			pre_pos_x = cur_pos_x
			if move_dis_zero_count >= 5 then
				self:ai_move_stop()
				return true
			end
		else
			move_dis_zero_count = 0
		end

		-- 因受到攻击切换到其他状态时
		if self.pawn.FSM:getCurState():getStateName() ~= "State_Run" then
			self:ai_move_stop()
			return true
		end 
	end)

	return true
end

function AIController:ai_move_stop()
	return self.pawn:moveStop()
end



return AIController