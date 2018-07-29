local Monster_Base = require("app.actor.monster.Monster_Base")
local Monster_Leizhu = require("app.actor.monster.Monster_Leizhu")
local Monster_Leiqiu = require("app.actor.monster.Monster_Leiqiu")

local Monster_LeiShen = class("Monster_LeiShen", Monster_Base)

function Monster_LeiShen:ctor()
	Monster_LeiShen.super.ctor(self)
	
	self:setActorType(AT_MONSTER)

	self:loadConfig(require("app.config.monster.LeiShenConfig"))

	self:override_forceSwitchClean()

	self:initFSM()
	self.FSM:start("State_Stand")

	self.AI = require("app.AI.AIM_LeiShen"):new()
end

function Monster_LeiShen:onEnter()
	Monster_LeiShen.super.onEnter(self)
	if self.AI then
		self.AI:setOwner(self)
		self.AI:start()
	end
end

function Monster_LeiShen:override_loadArmature(filePath)
	changeParticleSystemPositionType(self:getArmature())
end


function Monster_LeiShen:override_updateArmatureInfo()
end

function Monster_LeiShen:override_attOtherActorCallback(otherActor)

	local stateName = self.FSM:getCurState():getStateName()

	if stateName == "State_Kill" then
		otherActor:override_beAttacked(self, true)
	else
		otherActor:override_beAttacked(self, false)
	end
end

function Monster_LeiShen:override_beAttacked(attackActor, isPickUp)
	
	local curStateName = self.FSM:getCurState():getStateName()
	for k, v in pairs(self.forceStateNameArr) do
		if curStateName == v then
			return
		end
	end

	Monster_LeiShen.super.override_beAttacked(self, attackActor, isPickUp)

	if not isPickUp then
		self:forceSwitch("State_Hit")
	else
		self:forceSwitch("State_Collapase_EndToStand")		
	end
end

--------------------------------------Logic--------------------------------------
function Monster_LeiShen:moveLeft()
	local ret = self:handle("CMD_MoveStart")

	if ret then
		self.actorSpeedController:setGravity(-400, 0)
	end

	return ret
end

function Monster_LeiShen:moveRight()
	local ret = self:handle("CMD_MoveStart")

	if ret then
		self.actorSpeedController:setGravity(400, 0)
	end

	return ret
end

function Monster_LeiShen:moveStop()
	local ret = self:handle("CMD_MoveStand")
	if ret then
		self.actorSpeedController:setGravity(0, 0)
	end
	return ret
end

function Monster_LeiShen:skill1()
	local ret = self:handle("CMD_Skill1")
	if ret then
		self.actorSpeedController:setGravity(0, 0)
	end
	return ret
end

function Monster_LeiShen:skill2()
	local ret = self:handle("CMD_Kill2")
	if ret then
		self.actorSpeedController:setGravity(0, 0)
	end
	return ret
end

function Monster_LeiShen:skill3()
	local ret = self:handle("CMD_Kill3")
	if ret then
		self.actorSpeedController:setGravity(0, 0)

		local call = cc.CallFunc:create(function()
			self:handle("CMD_Kill3_Finish")
		end)

		self:getArmature():stopAllActions()
		local q = cc.Sequence:create(cc.DelayTime:create(2.0), call)
		self:getArmature():runAction(q)
	end
	return ret
end

function Monster_LeiShen:skill5(endPos)
	local ret = self:handle("CMD_Kill5_1")
	if ret then
		self.actorSpeedController:setGravity(0, 0)
		self.skill5EndPos = endPos
	end
	return ret
end

function Monster_LeiShen:skill6()
	local ret = self:handle("CMD_Kill6")
	if ret then
		self.actorSpeedController:setGravity(0, 0)

		local callfunc = cc.CallFunc:create(function()
			self:handle("CMD_Kill6_Finish")
		end)

		local q = cc.Sequence:create(cc.DelayTime:create(0.6), callfunc)
		self:getArmature():stopAllActions()
		self:getArmature():runAction(q)
	end
	return ret
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
	self.FSM:addTranslation("State_Stand", "CMD_Kill2", "State_Kill2")
	self.FSM:addTranslation("State_Run", "CMD_Kill2", "State_Kill2")
	self.FSM:addTranslation("State_Brake", "CMD_Kill2", "State_Kill2")
	self.FSM:addTranslation("State_Kill2", "State_Kill2_stop", "State_Stand")

	--skill3
	self.FSM:addTranslation("State_Stand", "CMD_Kill3", "State_Kill3")
	self.FSM:addTranslation("State_Run", "CMD_Kill3", "State_Kill3")
	self.FSM:addTranslation("State_Brake", "CMD_Kill3", "State_Kill3")
	self.FSM:addTranslation("State_Kill3", "CMD_Kill3_Finish", "State_Stand")

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
	self.FSM:addTranslation("State_Hit", "State_Hit_stop", "State_Stand")

	--受到攻击并被击飞
	self.FSM:addTranslation("State_Collapase_EndToStand", "State_Collapase_EndToStand_stop", "State_Stand")

	self.forceStateNameArr = {}
	table.insert(self.forceStateNameArr, "State_Hit")
	table.insert(self.forceStateNameArr, "State_Collapase_EndToStand")
	table.insert(self.forceStateNameArr, "State_Kill1")
	table.insert(self.forceStateNameArr, "State_Kill2")
	table.insert(self.forceStateNameArr, "State_Kill3")
	table.insert(self.forceStateNameArr, "State_Kill4")
	table.insert(self.forceStateNameArr, "State_Kill5_1")
	table.insert(self.forceStateNameArr, "State_Kill5_2")
	table.insert(self.forceStateNameArr, "State_Kill6_Run")
	table.insert(self.forceStateNameArr, "State_Dead")
	table.insert(self.forceStateNameArr, "State_Collapase_EndToDead")
end

--强制切换清理
function Monster_LeiShen:override_forceSwitchClean()
	Monster_LeiShen.super.override_forceSwitchClean(self)

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

function Monster_LeiShen:enter_State_Hit()
	self.isHit = true
	self.actorSpeedController:setForce(self:changeValueByOri(-100), 0)
	self.actorSpeedController:setFriction(300)
	self.actorSpeedController:setForceEnable(true)
	self.actorSpeedController:setFrictionEnable(true)
	self:lockOrientation()
end

function Monster_LeiShen:leave_State_Hit()
	self.isHit = false
	self.actorSpeedController:setForceEnable(false)
	self.actorSpeedController:setFrictionEnable(false)
	self.actorSpeedController:setForce(0, 0)
	self.actorSpeedController:setFriction(0)
	self:unLockOrientation()
end

function Monster_LeiShen:enter_State_Kill1()
	self:lockOrientation()
end

function Monster_LeiShen:leave_State_Kill1()
	self:unLockOrientation()

	local qiu = Monster_Leiqiu:create()
	getGameWord():addActor(qiu)

	if self:getOrientation() == GAME_ORI_LEFT then
		qiu:start(200, -1200)
		qiu:setActorPosition(self:getActorPositionX() - 20, 0)
	else
		qiu:start(200, 1200)
		qiu:setActorPosition(self:getActorPositionX() + 20, 0)
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

	if self.skill5EndPos == nil then
		local movex = math.random(200, 1000)
		if math.random(1, 2) == 1 then
			movex = -movex
		end
		self.skill5EndPos = movex
	end

	self:setActorPosition(self.skill5EndPos, self:getActorPositionY())
	self.skill5EndPos = nil
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

	local zhu = Monster_Leizhu:create()
	getGameWord():addActor(zhu)

	if self:getOrientation() == GAME_ORI_LEFT then
		zhu:startRun(0.2, -900)
	else
		zhu:startRun(0.2, 900)
	end
	zhu:setActorPosition(self:getActorPositionX(), 0)
end

function Monster_LeiShen:enter_State_Kill6_Run()
	self:lockOrientation()
end

function Monster_LeiShen:leave_State_Kill6_Run()
	self:unLockOrientation()
end

return Monster_LeiShen