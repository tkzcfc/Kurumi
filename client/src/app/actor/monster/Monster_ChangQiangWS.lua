local Monster_Base = require("app.actor.monster.Monster_Base")

local Monster_ChangQiangWS = class("Monster_ChangQiangWS", Monster_Base)

function Monster_ChangQiangWS:ctor()
	Monster_ChangQiangWS.super.ctor(self)
	
	self:setActorType(AT_MONSTER)

	self:loadConfig(require("app.config.monster.ChangQiangWSConfig"))

	self.actorSpeedController:setGravityEnable(true)

	self.armatureSpeedController:setGravity(0, -800)
	self.armatureSpeedController:setGravityEnable(true)
	self.armatureSpeedController:setMinValue(0, 0)
	self.armatureSpeedController:setMinValueEnable(true)
	self.armatureSpeedController:setStopUpdate(true)

	self.actorSpeedController:setFrictionEnable(true)

	self:initFSM()
	self.FSM:start("State_Run")
end

function Monster_ChangQiangWS:onEnter()
	Monster_ChangQiangWS.super.onEnter(self)
	self.AI = require("app.AI.AIM_ChangQiangWS"):new()
	self.AI:setOwner(self)
	self.AI:start()
end

function Monster_ChangQiangWS:override_attOtherActorCallback(otherActor)

	-- local stateName = self.FSM:getCurState():getStateName()
end

function Monster_ChangQiangWS:override_beAttacked(attackActor, isPickUp)

end

--------------------------------------Logic--------------------------------------
function Monster_ChangQiangWS:moveLeft()
	local ret = self:handle("CMD_MoveStart")

	if ret then
		self.actorSpeedController:setGravity(-200, 0)
	end

	return ret
end

function Monster_ChangQiangWS:moveRight()
	local ret = self:handle("CMD_MoveStart")

	if ret then
		self.actorSpeedController:setGravity(200, 0)
	end

	return ret
end

function Monster_ChangQiangWS:moveStop()
	self.actorSpeedController:setGravity(0, 0)
	return self:handle("CMD_MoveStand")
end

function Monster_ChangQiangWS:jump(isAttack)
	if self:handle("CMD_JumpUpStart") then
		self.armatureSpeedController:setStopUpdate(false)
		self.armatureSpeedController:setForceEnable(true)
		self.armatureSpeedController:setFrictionEnable(true)

		self.armatureSpeedController:setForce(0, 2000)
		self.armatureSpeedController:setFriction(2000)
		

		local function jumpFinishCall()
			self.armatureSpeedController:setStopUpdate(true)
			self.armatureSpeedController:clearLuaUpdateCall()
			self.armatureSpeedController:setForceEnable(false)
			self.armatureSpeedController:setFrictionEnable(false)

			self:handle("CMD_JumpDownEnd")
		end
		local stage = 0
		self.armatureSpeedController:setLuaUpdateCall(function(x, y, time)

			local curHeight = self.armatureSpeedController:getTarget():getPositionY()

			if stage == 0 then
				if self.armatureSpeedController:getAppendY() < 0 then
					if isAttack then
						self:handle("CMD_JumpDownStart")
					else
						self:handle("CMD_JumpAttack")
					end
					stage = 1
				end
			end
			if stage == 1 and self.armatureSpeedController:getForceY() <= 400 then
				self.armatureSpeedController:setForce(0, -10)
				self.armatureSpeedController:setFriction(-500)
				stage = 2
			end
			if y == 0 then
				jumpFinishCall()
			end
		end)
		return true
	end
	return false
end

function Monster_ChangQiangWS:attack()
	return self:handle("CMD_Attack")
end

function Monster_ChangQiangWS:skill()
	return self:handle("CMD_Skill")
end

--------------------------------------FSM--------------------------------------

function Monster_ChangQiangWS:initFSM()

	--站立
	self.FSM:addTranslation("State_Run", "CMD_MoveStand", "State_Stand")

	--移动
	self.FSM:addTranslation("State_Stand", "CMD_MoveStart", "State_Run")

	--跳跃
	self.FSM:addTranslation("State_Stand", "CMD_JumpUpStart", "State_JumpUp")
	self.FSM:addTranslation("State_Run", "CMD_JumpUpStart", "State_JumpUp")
	self.FSM:addTranslation("State_Run2", "CMD_JumpUpStart", "State_JumpUp")
	self.FSM:addTranslation("State_JumpUp", "CMD_JumpDownStart", "State_JumpDown")
	self.FSM:addTranslation("State_JumpDown", "CMD_JumpDownEnd", "State_JumpDownEnd")

	--攻击
	self.FSM:addTranslation("State_Stand", "CMD_Attack", "State_Attack")
	self.FSM:addTranslation("State_Run", "CMD_Attack", "State_Attack")
	self.FSM:addTranslation("State_Attack", "State_Attack_stop", "State_Stand")

	--跳跃攻击
	self.FSM:addTranslation("State_JumpUp", "CMD_JumpAttack", "State_Kill2")
	self.FSM:addTranslation("State_Kill2", "CMD_JumpDownStart", "State_JumpDown")

	--kill
	self.FSM:addTranslation("State_Stand", "CMD_Skill", "State_Kill1")
	self.FSM:addTranslation("State_Run", "CMD_Skill", "State_Kill1")
	self.FSM:addTranslation("State_Kill1", "State_Kill1_stop", "State_Stand")
end

function Monster_ChangQiangWS:enter_State_Kill2()
	self.actorSpeedController:setStopUpdate(true)
	self.armatureSpeedController:setStopUpdate(true)
end

function Monster_ChangQiangWS:leave_State_Kill2()
	self.actorSpeedController:setStopUpdate(false)
	self.armatureSpeedController:setStopUpdate(false)
end

function Monster_ChangQiangWS:State_Kill2_stop(actor)
	if self ~= actor then
		return
	end
	self:handle("CMD_JumpDownStart")
end

return Monster_ChangQiangWS

