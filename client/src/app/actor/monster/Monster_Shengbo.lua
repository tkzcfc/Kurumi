local Monster_Base = require("app.actor.monster.Monster_Base")

local Monster_Shengbo = class("Monster_Shengbo", Monster_Base)

function Monster_Shengbo:ctor()
	Monster_Shengbo.super.ctor(self)
	
	self:setActorType(AT_MONSTER)

	self:loadConfig(require("app.config.monster.ShengBoConfig"))

	self.actorSpeedController:setGravityEnable(true)

	self.armatureSpeedController:setGravity(0, -800)
	self.armatureSpeedController:setGravityEnable(true)
	self.armatureSpeedController:setMinValue(0, 0)
	self.armatureSpeedController:setMinValueEnable(true)
	self.armatureSpeedController:setStopUpdate(true)

	self.actorSpeedController:setFrictionEnable(true)

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
	self.super.override_beAttacked(self, attackActor, isPickUp)

	if not isPickUp then
		if self:handle("CMD_hit") then
			self.actorSpeedController:setGravity(0, 0)
		end
	else
		local JumpUpTime = 0.3
		local JumpHeight = 200
		if self:handle("CMD_Collapase_Up") then
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
	self.FSM:addTranslation("State_Stand", "CMD_hit", "State_Hit")
	self.FSM:addTranslation("State_Run", "CMD_hit", "State_Hit")
	self.FSM:addTranslation("State_Turn", "CMD_hit", "State_Hit")
	self.FSM:addTranslation("State_Attack1", "CMD_hit", "State_Hit")
	self.FSM:addTranslation("State_Attack2", "CMD_hit", "State_Hit")
	self.FSM:addTranslation("State_Kill", "CMD_hit", "State_Hit")
	self.FSM:addTranslation("State_Hit", "State_Hit_stop", "State_Stand")

	--受到攻击并被击飞
	self.FSM:addTranslation("State_Stand", "CMD_Collapase_Up", "State_Collapase_Up")
	self.FSM:addTranslation("State_Run", "CMD_Collapase_Up", "State_Collapase_Up")
	self.FSM:addTranslation("State_Turn", "CMD_Collapase_Up", "State_Collapase_Up")
	self.FSM:addTranslation("State_Attack1", "CMD_Collapase_Up", "State_Collapase_Up")
	self.FSM:addTranslation("State_Attack2", "CMD_Collapase_Up", "State_Collapase_Up")
	self.FSM:addTranslation("State_Kill", "CMD_Collapase_Up", "State_Collapase_Up")

	self.FSM:addTranslation("State_Collapase_Up", "CMD_Collapase_Down", "State_Collapase_Down")
	self.FSM:addTranslation("State_Collapase_Down", "CMD_Collapase_EndToStand", "State_Collapase_EndToStand")
	self.FSM:addTranslation("State_Collapase_Down", "CMD_Collapase_EndToDead", "State_Collapase_EndToDead")

	self.FSM:addTranslation("State_Collapase_EndToStand", "State_Collapase_EndToStand_stop", "State_Stand")


end

function Monster_Shengbo:enter_State_Hit()
	self.actorSpeedController:setForce(self:changeValueByOri(-100), 0)
	self.actorSpeedController:setFriction(300)
	self.actorSpeedController:setForceEnable(true)
	self.actorSpeedController:setFrictionEnable(true)
	-- self.actorSpeedController:setGravityEnable(false)
	self:lockOrientation()
end

function Monster_Shengbo:leave_State_Hit()
	self.actorSpeedController:setForceEnable(false)
	self.actorSpeedController:setFrictionEnable(false)
	self.actorSpeedController:setForce(0, 0)
	self.actorSpeedController:setFriction(0)
	-- self.actorSpeedController:setGravityEnable(true)
	self:unLockOrientation()
end

function Monster_Shengbo:enter_State_Collapase_Up()
	self.actorSpeedController:setForce(self:changeValueByOri(-350), 0)
	self.actorSpeedController:setFriction(150)
	self.actorSpeedController:setForceEnable(true)
	self.actorSpeedController:setFrictionEnable(true)
	-- self.actorSpeedController:setGravityEnable(false)
	self:lockOrientation()
end

function Monster_Shengbo:leave_State_Collapase_Down()
	self.actorSpeedController:setForceEnable(false)
	self.actorSpeedController:setFrictionEnable(false)
	self.actorSpeedController:setForce(0, 0)
	self.actorSpeedController:setFriction(0)
	-- self.actorSpeedController:setGravityEnable(true)
	self:unLockOrientation()
end

function Monster_Shengbo:leave_State_Collapase_EndToStand()
	self:unLockOrientation()
	-- self.actorSpeedController:setGravityEnable(true)
end

-- function Monster_Shengbo:leave_State_Collapase_EndToDead()
-- 	self:unLockOrientation()
-- end

-- function Monster_Shengbo:enter_State_Attack1()
-- 	self.actorSpeedController:setGravityEnable(false)
-- end

-- function Monster_Shengbo:leave_State_Attack1()
-- 	self.actorSpeedController:setGravityEnable(true)
-- end

-- function Monster_Shengbo:enter_State_Attack2()
-- 	self.actorSpeedController:setGravityEnable(false)
-- end

-- function Monster_Shengbo:leave_State_Attack2()
-- 	self.actorSpeedController:setGravityEnable(true)
-- end

-- function Monster_Shengbo:enter_State_Kill()
-- 	self.actorSpeedController:setGravityEnable(false)
-- end

-- function Monster_Shengbo:leave_State_Kill()
-- 	self.actorSpeedController:setGravityEnable(true)
-- end

return Monster_Shengbo