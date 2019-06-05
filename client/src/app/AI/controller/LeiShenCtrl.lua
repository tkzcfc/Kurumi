local AIController = require("app.AI.AIController")

local LeiShenCtrl = class("LeiShenCtrl", AIController)

function LeiShenCtrl:ctor()
	LeiShenCtrl.super.ctor(self)
end

function LeiShenCtrl:ai_can_attack()
	return true
end

-- 向前发出雷球
function LeiShenCtrl:ai_do_skill1()
	self.pawn:handle("CMD_Skill1")
	return true
end

-- 雷拳
function LeiShenCtrl:ai_do_skill2()
	self.pawn:handle("CMD_Skill2")
	return true
end

-- 变成一个光球
function LeiShenCtrl:ai_do_skill3(time)
	if self.pawn:handle("CMD_Skill3") then
		
		local curTime = 0.0
		
		self.bhTree:doPauseUntil(function(delta)
			curTime = curTime + delta
	
			-- 时间判断
			if curTime >= time then
				self.pawn:handle("CMD_Skill3_Finish")
				return true
			end
	
			-- 因受到攻击切换到其他状态时
			if self.pawn.FSM:getCurState():getStateName() ~= "State_Kill3" then
				return true
			end 
		end)
	end
	return true
end


--瞬移
function LeiShenCtrl:ai_do_skill5()
	if not self.pawn:handle("CMD_Kill5_1") then
		return true
	end

	if self.hatredTarget == nil then
		self.pawn.skill5EndPos = nil
	else
		local hatredPosx = self.hatredTarget:getPositionX()
		local pawnPosx = self.pawn:getPositionX()
		local distance = hatredPosx - pawnPosx
		local distance_abs = math.abs(distance)

		local move_distance = distance_abs + math.random(50, 150)

		-- 超过最大移动距离限制
		if distance_abs > 300 then
			move_distance = math.random(250, 300)
		-- 距离太短
		elseif distance_abs < 50 then
			move_distance = math.random(100, 300)
		end

		if distance > 0 then
			self.pawn.skill5EndPos = {x = pawnPosx + move_distance, y = 0}
		else
			self.pawn.skill5EndPos = {x = pawnPosx - move_distance, y = 0}
		end
	end

	local curTime = 0.0
	self.bhTree:doPauseUntil(function(delta)
		curTime = curTime + delta
		if curTime >= 0.6 then
			return true
		end
	end)

	return true
end

-- 向前发出一个雷柱
function LeiShenCtrl:ai_do_skill6()
	if self.pawn:handle("CMD_Kill6") then
		local curTime = 0.0
		
		self.bhTree:doPauseUntil(function(delta)
			curTime = curTime + delta
	
			-- 时间判断
			if curTime >= 0.6 then
				self.pawn:handle("CMD_Kill6_Finish")
				return true
			end
	
			-- 因受到攻击切换到其他状态时
			local stateName = self.pawn.FSM:getCurState():getStateName()
			if stateName == "State_Kill6_Run" or stateName == "State_Kill6_Begin" then
				return false
			end

			return true
		end)

	end
	return true
end

return LeiShenCtrl