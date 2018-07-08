local Monster_Base = require("app.actor.monster.Monster_Base")

local Monster_Leizhu = class("Monster_Leizhu", Monster_Base)

function Monster_Leizhu:ctor()
	Monster_Leizhu.super.ctor(self)
	
	self:setActorType(AT_MONSTER)

	self:loadConfig(require("app.config.monster.LeiZhuConfig"))

	self.FSM:start("State_Skill")
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

function Monster_Leizhu:startRun(delayTime, distance)
	local armature = self:getArmature()
	armature:setPosition({x = 0, y = 0})
	armature:stopAllActions()

	local move = cc.MoveBy:create(1.1, {x = distance, y = 0})
	local call = cc.CallFunc:create(function()
		self:getGameWord():removeActor(self)
	end)

	local q1 = cc.Sequence:create(cc.DelayTime:create(delayTime), move, call)
	armature:runAction(q1)
end

return Monster_Leizhu
