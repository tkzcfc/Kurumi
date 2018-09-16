local Monster_Base = require("app.actor.monster.Monster_Base")

local Monster_Leizhu = class("Monster_Leizhu", Monster_Base)

function Monster_Leizhu:ctor()
	Monster_Leizhu.super.ctor(self)
	
	self:setActorType(AT_MONSTER)

	self:loadConfig(require("app.config.monster.LeiZhuConfig"))

	self.FSM:start("State_Skill")
	self.runTime = 0
end

function Monster_Leizhu:onEnter()
	Monster_Leizhu.super.onEnter(self)
end

function Monster_Leizhu:override_attOtherActorCallback(otherActor)
	otherActor:override_beAttacked(self, false)
end

function Monster_Leizhu:override_loadArmature(filePath)
	--changeParticleSystemPositionType(self:getArmature())
end

function Monster_Leizhu:override_logicUpdate(time)
	Monster_Leizhu.super.override_logicUpdate(self, time)

	if self.runTime > 1.1 then
		getGameWord():removeActor(self)
		return
	end
	self.runTime = self.runTime + time

	self:setVelocityXByImpulse(self:getVelocityByOrientation(800 / PIXEL_TO_METER))
end

function Monster_Leizhu:startRun()
	self.runTime = 0
end

return Monster_Leizhu
