local Monster_Base = require("app.actor.monster.Monster_Base")

local Monster_Leiqiu = class("Monster_Leiqiu", Monster_Base)

function Monster_Leiqiu:ctor()
	Monster_Leiqiu.super.ctor(self)
	
	self:setActorType(AT_MONSTER)

	self:loadConfig(require("app.config.monster.LeiQiuConfig"))

	self:initFSM()
	self.FSM:start("State_Leiqiu1")
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

function Monster_Leiqiu:start(height, distance)
	if height < 200 then
		print("Le 200")
		print(height)
	end
	local armature = self:getArmature()
	armature:setPosition({x = 0, y = height})
	armature:stopAllActions()

	local move = cc.MoveBy:create(0.8, {x = distance, y = 0})
	local call = cc.CallFunc:create(function()
		self:getGameWord():removeActor(self)
	end)

	local q1 = cc.Sequence:create(move, call)
	armature:runAction(q1)
end

function Monster_Leiqiu:initFSM()
	self.FSM:addTranslation("State_Leiqiu1", "CMD_LeiQiu2", "State_Leiqiu2")
	self.FSM:addTranslation("State_Leiqiu2", "CMD_LeiQiu1", "State_Leiqiu1")
end

return Monster_Leiqiu
