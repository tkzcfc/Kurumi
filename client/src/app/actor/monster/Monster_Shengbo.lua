local Monster_Base = require("app.actor.monster.Monster_Base")

local Monster_Shengbo = class("Monster_Shengbo", Monster_Base)

function Monster_Shengbo:ctor()
	Monster_Shengbo.super.ctor(self)
	
	self:setActorType(AT_MONSTER)

	self:loadConfig(require("app.config.monster.ShengBoConfig"))

	self:override_forceSwitchClean()

	self:initFSM()
	self.FSM:start("State_Stand")
end

function Monster_Shengbo:onEnter()
	Monster_Shengbo.super.onEnter(self)
	self.AI = require("app.AI.AIM_ShengBo"):new()
	self.AI:setOwner(self)
	self.AI:start()
end

function Monster_Shengbo:override_loadArmature(filePath)
	changeParticleSystemPositionType(self:getArmature())
end

function Monster_Shengbo:override_updateArmatureInfo()
end

function Monster_Shengbo:override_attOtherActorCallback(otherActor)

	local stateName = self.FSM:getCurState():getStateName()

	if stateName == "State_Kill" then
		otherActor:override_beAttacked(self, true)
	else
		otherActor:override_beAttacked(self, false)
	end
end

function Monster_Shengbo:override_beAttacked(attackActor, isPickUp)
	Monster_Shengbo.super.override_beAttacked(self, attackActor, isPickUp)

	local curStateName = self.FSM:getCurState():getStateName()
	if curStateName == "State_Hit" or 
	   curStateName == "State_Collapase_Up" or 
	   curStateName == "State_Collapase_Down" or
	   curStateName == "State_Collapase_EndToStand" or
	   curStateName == "State_Collapase_EndToDead" or
	   curStateName == "State_Dead" then
		return
	end

	if not isPickUp then
		if self:forceSwitch("State_Hit") then
			self.actorSpeedController:setGravity(0, 0)
		end
	else
		local JumpUpTime = 0.3
		local JumpHeight = 200
		if self:forceSwitch("State_Collapase_Up") then
			local move = cc.MoveBy:create(JumpUpTime, {x = 0, y = JumpHeight})
			
			local call1 = cc.CallFunc:create(function()
				self:handle("CMD_Collapase_Down")
			end)
			
			local call2 = cc.CallFunc:create(function()
				self:handle("CMD_Collapase_EndToStand")
			end)
			
			local q = cc.Sequence:create(move, call1, move:reverse(), call2)
			self:getArmature():runAction(q)

			self.actorSpeedController:setGravity(0, 0)
		end
	end
end

--------------------------------------Logic--------------------------------------
function Monster_Shengbo:moveLeft()
	local ret = self:handle("CMD_MoveStart")

	if ret then
		self.actorSpeedController:setGravity(-400, 0)
	end

	return ret
end

function Monster_Shengbo:moveRight()
	local ret = self:handle("CMD_MoveStart")

	if ret then
		self.actorSpeedController:setGravity(400, 0)
	end

	return ret
end

function Monster_Shengbo:moveStop()
	local ret = self:handle("CMD_MoveStand")
	if ret then
		self.actorSpeedController:setGravity(0, 0)
	end
	return ret
end

function Monster_Shengbo:attack1()
	local ret = self:handle("CMD_Attack1")
	if ret then
		self.actorSpeedController:setGravity(0, 0)
	end
	return ret
end

function Monster_Shengbo:attack2()
	local ret = self:handle("CMD_Attack2")
	if ret then
		self.actorSpeedController:setGravity(0, 0)
	end
	return ret
end

function Monster_Shengbo:skill()
	local ret = self:handle("CMD_Skill")
	if ret then
		self.actorSpeedController:setGravity(0, 0)
	end
	return ret
end

--------------------------------------FSM--------------------------------------

function Monster_Shengbo:initFSM()

	--站立
	self.FSM:addTranslation("State_Run", "CMD_MoveStand", "State_Stand")

	--移动
	self.FSM:addTranslation("State_Stand", "CMD_MoveStart", "State_Run")

	--攻击1
	self.FSM:addTranslation("State_Stand", "CMD_Attack1", "State_Attack1")
	self.FSM:addTranslation("State_Run", "CMD_Attack1", "State_Attack1")
	self.FSM:addTranslation("State_Attack1", "State_Attack1_stop", "State_Stand")

	--攻击2
	self.FSM:addTranslation("State_Stand", "CMD_Attack2", "State_Attack2")
	self.FSM:addTranslation("State_Run", "CMD_Attack2", "State_Attack2")
	self.FSM:addTranslation("State_Attack2", "State_Attack2_stop", "State_Stand")

	--kill
	self.FSM:addTranslation("State_Stand", "CMD_Skill", "State_Kill")
	self.FSM:addTranslation("State_Run", "CMD_Skill", "State_Kill")
	self.FSM:addTranslation("State_Kill", "State_Kill_stop", "State_Stand")

	--受到攻击
	self.FSM:addTranslation("State_Hit", "State_Hit_stop", "State_Stand")


	--受到攻击并被击飞
	self.FSM:addTranslation("State_Collapase_Up", "CMD_Collapase_Down", "State_Collapase_Down")
	self.FSM:addTranslation("State_Collapase_Down", "CMD_Collapase_EndToStand", "State_Collapase_EndToStand")
	self.FSM:addTranslation("State_Collapase_Down", "CMD_Collapase_EndToDead", "State_Collapase_EndToDead")

	self.FSM:addTranslation("State_Collapase_EndToStand", "State_Collapase_EndToStand_stop", "State_Stand")


end

--强制切换清理
function Monster_Shengbo:override_forceSwitchClean()
	Monster_Shengbo.super.override_forceSwitchClean(self)

	self.actorSpeedController:defaultValue()
	self.actorSpeedController:setStopUpdate(false)
	self.actorSpeedController:setGravityEnable(true)

	self.armatureSpeedController:defaultValue()

	local armature = self:getArmature()
	if armature then
		armature:setPosition({x = 0, y = 0})
		armature:stopAllActions()
	end
end

function Monster_Shengbo:enter_State_Hit()
	self.actorSpeedController:setForce(self:changeValueByOri(-100), 0)
	self.actorSpeedController:setFriction(300)
	self.actorSpeedController:setForceEnable(true)
	self.actorSpeedController:setFrictionEnable(true)
	self:lockOrientation()
end

function Monster_Shengbo:leave_State_Hit()
	self.actorSpeedController:setForceEnable(false)
	self.actorSpeedController:setFrictionEnable(false)
	self.actorSpeedController:setForce(0, 0)
	self.actorSpeedController:setFriction(0)
	self:unLockOrientation()
end

function Monster_Shengbo:enter_State_Collapase_Up()
	self.actorSpeedController:setForce(self:changeValueByOri(-350), 0)
	self.actorSpeedController:setFriction(150)
	self.actorSpeedController:setForceEnable(true)
	self.actorSpeedController:setFrictionEnable(true)
	self:lockOrientation()
end

function Monster_Shengbo:leave_State_Collapase_Down()
	self.actorSpeedController:setForceEnable(false)
	self.actorSpeedController:setFrictionEnable(false)
	self.actorSpeedController:setForce(0, 0)
	self.actorSpeedController:setFriction(0)
	self:unLockOrientation()
end

function Monster_Shengbo:leave_State_Collapase_EndToStand()
	self:unLockOrientation()
end

function Monster_Shengbo:enter_State_Kill()
	self:lockOrientation()
	self.actorSpeedController:setGravityEnable(false)
	self.actorSpeedController:setGravity(0, 0)
end

function Monster_Shengbo:leave_State_Kill()
	self:unLockOrientation()
	self.actorSpeedController:setGravityEnable(true)
end

function Monster_Shengbo:enter_State_Attack1()
	self:lockOrientation()
	self.actorSpeedController:setGravityEnable(false)
	self.actorSpeedController:setGravity(0, 0)
end

function Monster_Shengbo:leave_State_Attack1()
	self:unLockOrientation()
	self.actorSpeedController:setGravityEnable(true)
end

function Monster_Shengbo:enter_State_Attack2()
	self:lockOrientation()
	self.actorSpeedController:setGravityEnable(false)
	self.actorSpeedController:setGravity(0, 0)
end

function Monster_Shengbo:leave_State_Attack2()
	self:unLockOrientation()
	self.actorSpeedController:setGravityEnable(true)
end

return Monster_Shengbo