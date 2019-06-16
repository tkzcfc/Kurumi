local Monster_Base = require("app.actor.monster.Monster_Base")
local Monster_Leizhu = require("app.actor.monster.Monster_Leizhu")
local Monster_Leiqiu = require("app.actor.monster.Monster_Leiqiu")
local LeiShenCtrl = require("app.AI.controller.LeiShenCtrl")

local Monster_LeiShen = class("Monster_LeiShen", Monster_Base)


local LeiShenConfig = require("app.config.monster.LeiShenConfig")

function Monster_LeiShen:ctor()
	Monster_LeiShen.super.ctor(self)
	
	self:loadConfig(LeiShenConfig)

	self:initFSM()
	self.FSM:start("State_Stand")

	self:initAI()

	self:enableDefaultPhysics()
	changeParticleSystemPositionType(self.armature, 2)
end

function Monster_LeiShen:initAI()
	self.aiController = LeiShenCtrl:new()
	self.aiController:start(self, "base", "leishen", true)
end

function Monster_LeiShen:override_attCollisionCallback(otherActor)
	Monster_LeiShen.super.override_attCollisionCallback(self, otherActor)

	local stateName = self.FSM:getCurState():getStateName()

	if stateName == "State_Kill" then
		self.isPickUp = true
	else
		self.isPickUp = false
	end
end

function Monster_LeiShen:override_defCollisionCallback(otherActor)
	Monster_LeiShen.super.override_defCollisionCallback(self, otherActor)

	if not otherActor.isPickUp then
		self:handle("CMD_Hit")
	else
		self:handle("CMD_Collapase_EndToStand")
	end
end

function Monster_LeiShen:override_update(delta)
	Monster_LeiShen.super.override_update(self, delta)
	local curStateName = self.FSM:getCurState():getStateName()
	-- 奔跑状态
	if curStateName == "State_Run" then
		self:setVelocityXByImpulse(self:getVelocityByMoveOrientation(self.config.BaseConfig.MoveVelocity))
	end
end

--------------------------------------------FSM--------------------------------

function Monster_LeiShen:initFSM()

	--站立
	self.FSM:addTranslation("State_Run", "CMD_MoveStand", "State_Brake")

	self.FSM:addTranslation("State_Brake", "State_Brake_stop", "State_Stand")

	--移动
	self.FSM:addTranslation("State_Stand", "CMD_MoveStart", "State_Run")
	self.FSM:addTranslation("State_Brake", "CMD_MoveStart", "State_Run")

	--skill1
	self.FSM:addTranslation("State_Stand", "CMD_Skill1", "State_Kill1")
	self.FSM:addTranslation("State_Run", "CMD_Skill1", "State_Kill1")
	self.FSM:addTranslation("State_Brake", "CMD_Skill1", "State_Kill1")
	self.FSM:addTranslation("State_Kill1", "State_Kill1_stop", "State_Stand")

	--skill2
	self.FSM:addTranslation("State_Stand", "CMD_Skill2", "State_Kill2")
	self.FSM:addTranslation("State_Run", "CMD_Skill2", "State_Kill2")
	self.FSM:addTranslation("State_Brake", "CMD_Skill2", "State_Kill2")
	self.FSM:addTranslation("State_Kill2", "State_Kill2_stop", "State_Stand")

	--skill3
	self.FSM:addTranslation("State_Stand", "CMD_Skill3", "State_Kill3")
	self.FSM:addTranslation("State_Run", "CMD_Skill3", "State_Kill3")
	self.FSM:addTranslation("State_Brake", "CMD_Skill3", "State_Kill3")
	self.FSM:addTranslation("State_Kill3", "CMD_Skill3_Finish", "State_Stand")

	--skill5
	self.FSM:addTranslation("State_Stand", "CMD_Kill5_1", "State_Kill5_1")
	self.FSM:addTranslation("State_Run", "CMD_Kill5_1", "State_Kill5_1")
	self.FSM:addTranslation("State_Brake", "CMD_Kill5_1", "State_Kill5_1")
	self.FSM:addTranslation("State_Hit", "CMD_Kill5_1", "State_Kill5_1")
	self.FSM:addTranslation("State_Kill5_1", "State_Kill5_1_stop", "State_Kill5_2")
	self.FSM:addTranslation("State_Kill5_2", "State_Kill5_2_stop", "State_Stand")

	--skill6
	self.FSM:addTranslation("State_Stand", "CMD_Kill6", "State_Kill6_Begin")
	self.FSM:addTranslation("State_Run", "CMD_Kill6", "State_Kill6_Begin")
	self.FSM:addTranslation("State_Brake", "CMD_Kill6", "State_Kill6_Begin")
	self.FSM:addTranslation("State_Hit", "CMD_Kill6", "State_Kill6_Begin")
	self.FSM:addTranslation("State_Kill6_Begin", "State_Kill6_Begin_stop", "State_Kill6_Run")
	self.FSM:addTranslation("State_Kill6_Begin", "CMD_Kill6_Finish", "State_Kill6_Finish")
	self.FSM:addTranslation("State_Kill6_Run", "CMD_Kill6_Finish", "State_Kill6_Finish")
	self.FSM:addTranslation("State_Kill6_Finish", "State_Kill6_Finish_stop", "State_Stand")

	--受到攻击
	self.FSM:addTranslation("State_Stand", "CMD_Hit", "State_Hit")
	self.FSM:addTranslation("State_Run", "CMD_Hit", "State_Hit")
	self.FSM:addTranslation("State_Brake", "CMD_Hit", "State_Hit")
	self.FSM:addTranslation("State_Kill6_Begin", "CMD_Hit", "State_Hit")
	self.FSM:addTranslation("State_Kill6_Finish", "CMD_Hit", "State_Hit")
	self.FSM:addTranslation("State_Turn", "CMD_Hit", "State_Hit")
	self.FSM:addTranslation("State_Hit", "State_Hit_stop", "State_Stand")

	--受到攻击并被击飞
	self.FSM:addTranslation("State_Stand", "CMD_Collapase_EndToStand", "State_Collapase_EndToStand")
	self.FSM:addTranslation("State_Run", "CMD_Collapase_EndToStand", "State_Collapase_EndToStand")
	self.FSM:addTranslation("State_Brake", "CMD_Collapase_EndToStand", "State_Collapase_EndToStand")
	self.FSM:addTranslation("State_Kill6_Begin", "CMD_Collapase_EndToStand", "State_Collapase_EndToStand")
	self.FSM:addTranslation("State_Kill6_Finish", "CMD_Collapase_EndToStand", "State_Collapase_EndToStand")
	self.FSM:addTranslation("State_Turn", "CMD_Collapase_EndToStand", "State_Collapase_EndToStand")

	self.FSM:addTranslation("State_Collapase_EndToStand", "State_Collapase_EndToStand_stop", "State_Stand")
end

function Monster_LeiShen:enter_State_Stand()
	self:clearForceX()
end

function Monster_LeiShen:enter_State_Run()
	self:clearForceX()
end

function Monster_LeiShen:leave_State_Run()
	self:clearForceX()
end

function Monster_LeiShen:enter_State_Hit()
	self:lockOrientation()
	self:clearForceX()
	--
	local impluse = LeiShenConfig.BaseConfig.HitImpluse
	self:setVelocityXByImpulse_Ext(impluse)
end

function Monster_LeiShen:leave_State_Hit()
	self:unLockOrientation()
	self:clearForceX()
end

function Monster_LeiShen:enter_State_Kill1()
	self:lockOrientation()
end

function Monster_LeiShen:leave_State_Kill1()
	self:unLockOrientation()

	local gameWord = self:getGameWorld()

	local qiu = Monster_Leiqiu:create(gameWord)
	gameWord.mapActorNode:addChild(qiu)

	if self:getOrientation() == GAME_ORI_LEFT then
		qiu:setOrientation(GAME_ORI_LEFT)
		qiu:start(self:getPositionX() - 20, 200, 0.8)
	else
		qiu:setOrientation(GAME_ORI_RIGHT)
		qiu:start(self:getPositionX() + 20, 200, 0.8)
	end
end

function Monster_LeiShen:enter_State_Kill2()
	self:lockOrientation()
end

function Monster_LeiShen:leave_State_Kill2()
	self:unLockOrientation()
end

function Monster_LeiShen:enter_State_Kill3()
	self:lockOrientation()
end

function Monster_LeiShen:leave_State_Kill3()
	self:unLockOrientation()
end

function Monster_LeiShen:enter_State_Kill4()
	self:lockOrientation()
end

function Monster_LeiShen:leave_State_Kill4()
	self:unLockOrientation()
end

function Monster_LeiShen:enter_State_Kill5_1()
	self:lockOrientation()
end

function Monster_LeiShen:leave_State_Kill5_1()
	self:unLockOrientation()

	if self.skill5EndPosX == nil then
		local movex = math.random(200, 600)
		if math.random(1, 2) == 1 then
			movex = -movex
		end
		self.skill5EndPosX = self:getPositionX() + movex
	end
	
	self:setValidWorldPositionX(self.skill5EndPosX)
	self.skill5EndPosX = nil
end

function Monster_LeiShen:enter_State_Kill5_2()
	self:lockOrientation()
end

function Monster_LeiShen:leave_State_Kill5_2()
	self:unLockOrientation()
end

function Monster_LeiShen:enter_State_Kill6_Begin()
	self:lockOrientation()
end

function Monster_LeiShen:leave_State_Kill6_Begin()
	self:unLockOrientation()

	local gameWord = self:getGameWorld()

	local zhu = Monster_Leizhu:create(gameWord)
	zhu:setOrientation(self:getOrientation())
	zhu:start(self:getPositionX(), 1.5)
	gameWord.mapActorNode:addChild(zhu)
end

function Monster_LeiShen:enter_State_Kill6_Run()
	self:lockOrientation()
end

function Monster_LeiShen:leave_State_Kill6_Run()
	self:unLockOrientation()
end

return Monster_LeiShen