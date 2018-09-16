local Monster_Base = require("app.actor.monster.Monster_Base")

local Monster_Shengbo = class("Monster_Shengbo", Monster_Base)

local ShengBoConfig = require("app.config.monster.ShengBoConfig")

function Monster_Shengbo:ctor()
	Monster_Shengbo.super.ctor(self)
	
	self:setActorType(AT_MONSTER)

	self:loadConfig(ShengBoConfig)

	self:override_forceSwitchClean()

	self:initFSM()
	self.FSM:start("State_Stand")
	self.AI = require("app.AI.AIM_ShengBo"):new()
end

function Monster_Shengbo:onEnter()
	Monster_Shengbo.super.onEnter(self)
	if self.AI then
		self.AI:setOwner(self)
		self.AI:start()
	end
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

	if not isPickUp then
		self:handle("CMD_Hit")
	else
		self:handle("CMD_Collapase")
	end
end

function Monster_Shengbo:override_logicUpdate(time)
	Monster_Shengbo.super.override_logicUpdate(self, time)
	local curStateName = self.FSM:getCurState():getStateName()
	-- 奔跑状态
	if curStateName == "State_Run" then
		if self.startMoveCMD then
			self:setVelocityXByImpulse(self:getVelocityByMoveOrientation(ShengBoConfig.BaseConfig.MoveVelocity))
		else
			self:clearForceX()
		end
	else
		if self.isCollapse then
			if not self:isInAir() then
				self:handle("CMD_Collapase_EndToStand")
			end
		end
	end
end

--------------------------------------Logic--------------------------------------
function Monster_Shengbo:getVelocityByMoveOrientation(value)
	if self.moveToLeft then
		return -value
	end
	return value
end

function Monster_Shengbo:moveLeft()
	self.startMoveCMD = true
	self.moveToLeft = true
	local ret = self:handle("CMD_MoveStart")
	return ret
end

function Monster_Shengbo:moveRight()
	self.startMoveCMD = true
	self.moveToLeft = false
	local ret = self:handle("CMD_MoveStart")
	return ret
end

function Monster_Shengbo:moveStop()
	self.startMoveCMD = false
	self:clearForceX()
	local ret = self:handle("CMD_MoveStand")
	return ret
end

function Monster_Shengbo:attack1()
	local ret = self:handle("CMD_Attack1")
	return ret
end

function Monster_Shengbo:attack2()
	local ret = self:handle("CMD_Attack2")
	return ret
end

function Monster_Shengbo:skill()
	local ret = self:handle("CMD_Skill")
	return ret
end

--------------------------------------FSM--------------------------------------

function Monster_Shengbo:initFSM()

	self.isCollapse = false

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
	self.FSM:addTranslation("State_Stand", "CMD_Hit", "State_Hit")
	self.FSM:addTranslation("State_Run", "CMD_Hit", "State_Hit")
	self.FSM:addTranslation("State_Attack1", "CMD_Hit", "State_Hit")
	self.FSM:addTranslation("State_Attack2", "CMD_Hit", "State_Hit")
	self.FSM:addTranslation("State_Hit", "State_Hit_stop", "State_Stand")


	--受到攻击并被击飞
	self.FSM:addTranslation("State_Stand", "CMD_Collapase", "State_Collapase_Up")
	self.FSM:addTranslation("State_Run", "CMD_Collapase", "State_Collapase_Up")
	self.FSM:addTranslation("State_Attack1", "CMD_Collapase", "State_Collapase_Up")
	self.FSM:addTranslation("State_Attack2", "CMD_Collapase", "State_Collapase_Up")
	self.FSM:addTranslation("State_Hit", "CMD_Collapase", "State_Collapase_Up")

	self.FSM:addTranslation("State_Collapase_Up", "State_Collapase_Up_stop", "State_Collapase_Down")
	self.FSM:addTranslation("State_Collapase_Down", "CMD_Collapase_EndToStand", "State_Collapase_EndToStand")
	self.FSM:addTranslation("State_Collapase_Down", "CMD_Collapase_EndToDead", "State_Collapase_EndToDead")

	self.FSM:addTranslation("State_Collapase_EndToStand", "State_Collapase_EndToStand_stop", "State_Stand")


end

--强制切换清理
function Monster_Shengbo:override_forceSwitchClean()
	Monster_Shengbo.super.override_forceSwitchClean(self)
	
	if self.b2Body then
		self:clearForceXY()
	end
	local armature = self:getArmature()
	if armature then
		armature:setPosition({x = 0, y = 0})
		armature:stopAllActions()
	end
end

function Monster_Shengbo:enter_State_Stand()
	self:clearForceX()
end

function Monster_Shengbo:enter_State_Run()
	self:clearForceX()
end

function Monster_Shengbo:leave_State_Run()
	self:clearForceX()
end

function Monster_Shengbo:enter_State_Hit()
	self:lockOrientation()
	self:clearForceX()
	--
	local impluse = self:getVelocityByOrientation(ShengBoConfig.BaseConfig.HitImpluse)
	self:setVelocityXByImpulse(impluse)
end

function Monster_Shengbo:leave_State_Hit()
	self:unLockOrientation()
	self:clearForceX()
end

function Monster_Shengbo:enter_State_Collapase_Up()
	self:lockOrientation()
	self.isCollapse = true

	local implusex = self:getVelocityByOrientation(ShengBoConfig.BaseConfig.CollapseXImpluse)
	self:setVelocityXYByImpulse(implusex, ShengBoConfig.BaseConfig.CollapseYImpluse)
end

function Monster_Shengbo:leave_State_Collapase_Down()
	self:unLockOrientation()
	self.isCollapse = false
end

function Monster_Shengbo:leave_State_Collapase_EndToStand()
	self:unLockOrientation()
	self.isCollapse = false
end

function Monster_Shengbo:enter_State_Kill()
	self:lockOrientation()
end

function Monster_Shengbo:leave_State_Kill()
	self:unLockOrientation()
end

function Monster_Shengbo:enter_State_Attack1()
	self:lockOrientation()
end

function Monster_Shengbo:leave_State_Attack1()
	self:unLockOrientation()
end

function Monster_Shengbo:enter_State_Attack2()
	self:lockOrientation()
end

function Monster_Shengbo:leave_State_Attack2()
	self:unLockOrientation()
end

return Monster_Shengbo