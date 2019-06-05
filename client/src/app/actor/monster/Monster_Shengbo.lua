local Monster_Base = require("app.actor.monster.Monster_Base")
local AIController = require("app.AI.AIController")
local ShengBoConfig = require("app.config.monster.ShengBoConfig")

local Monster_Shengbo = class("Monster_Shengbo", Monster_Base)


function Monster_Shengbo:ctor()
	Monster_Shengbo.super.ctor(self)

	self:loadConfig(ShengBoConfig)

	self:initFSM()
	self.FSM:start("State_Stand")

	self:initAI()

	self:enableDefaultPhysics()
	changeParticleSystemPositionType(self.armature, 2)
end

function Monster_Shengbo:initAI()
	self.aiController = AIController:new()
	self.aiController:start(self, "base", "shengbo", true)
end

function Monster_Shengbo:override_attCollisionCallback(otherActor)
	Monster_Shengbo.super.override_attCollisionCallback(self, otherActor)

	local stateName = self.FSM:getCurState():getStateName()

	if stateName == "State_Kill" then
		self.isPickUp = true
	else
		self.isPickUp = false
	end
end

function Monster_Shengbo:override_defCollisionCallback(otherActor)
	Monster_Shengbo.super.override_defCollisionCallback(self, otherActor)

	if not otherActor.isPickUp then
		self:handle("CMD_Hit")
	else
		self:handle("CMD_Collapase")
	end
end

function Monster_Shengbo:override_update(delta)
	Monster_Shengbo.super.override_update(self, delta)
	local curStateName = self.FSM:getCurState():getStateName()
	-- 奔跑状态
	if curStateName == "State_Run" then
		self:setVelocityXByImpulse(self:getVelocityByMoveOrientation(self.config.BaseConfig.MoveVelocity))
	else
		if self.isCollapse then
			if not self.isInAir then
				self:handle("CMD_Collapase_EndToStand")
			end
		end
	end
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
	local impluse = ShengBoConfig.BaseConfig.HitImpluse
	self:setVelocityXByImpulse_Ext(impluse)
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