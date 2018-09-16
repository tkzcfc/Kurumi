local Monster_Base = require("app.actor.monster.Monster_Base")

local Monster_Leiqiu = class("Monster_Leiqiu", Monster_Base)

function Monster_Leiqiu:ctor()
	Monster_Leiqiu.super.ctor(self)
	
	self:setActorType(AT_MONSTER)

	self:loadConfig(require("app.config.monster.LeiQiuConfig"))

	self:initFSM()
	self.FSM:start("State_Leiqiu1")
	self.runTime = 0.0
end

function Monster_Leiqiu:onEnter()
	Monster_Leiqiu.super.onEnter(self)
end

function Monster_Leiqiu:override_attOtherActorCallback(otherActor)
	otherActor:override_beAttacked(self, false)
end

function Monster_Leiqiu:override_loadArmature(filePath)
	--changeParticleSystemPositionType(self:getArmature())
end

function Monster_Leiqiu:override_logicUpdate(time)
	Monster_Leiqiu.super.override_logicUpdate(self, time)

	if self.runTime > 0.8 then
		getGameWord():removeActor(self)
		return
	end
	self.runTime = self.runTime + time

	self:setVelocityXByImpulse(self:getVelocityByOrientation(900 / PIXEL_TO_METER))
end

function Monster_Leiqiu:start(height)
	local armature = self:getArmature()
	armature:setPosition({x = 0, y = height})
	armature:stopAllActions()
	self.runTime = 0.0
end

function Monster_Leiqiu:initFSM()
	self.FSM:addTranslation("State_Leiqiu1", "CMD_LeiQiu2", "State_Leiqiu2")
	self.FSM:addTranslation("State_Leiqiu2", "CMD_LeiQiu1", "State_Leiqiu1")
end

return Monster_Leiqiu
