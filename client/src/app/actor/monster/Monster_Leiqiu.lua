local Monster_Base = require("app.actor.monster.Monster_Base")

local Monster_Leiqiu = class("Monster_Leiqiu", Monster_Base)

function Monster_Leiqiu:ctor()
	Monster_Leiqiu.super.ctor(self)
	
	self:loadConfig(require("app.config.monster.LeiQiuConfig"))

	self:initFSM()
	self.FSM:start("State_Leiqiu1")
	self.durtime = 0.0

	self:enableDefaultPhysics()
end

function Monster_Leiqiu:override_attCollisionCallback(otherActor)
	Monster_Leiqiu.super.override_attCollisionCallback(self, otherActor)
	self.isPickUp = false
end

function Monster_Leiqiu:override_update(delta)
	if self.durtime < 0 then
		self:runAction(cc.RemoveSelf:create())
		return
	end
	self.durtime = self.durtime - delta

	self:setVelocityXByImpulse_Ext(900 / BOX2D_PIXEL_TO_METER)
end

function Monster_Leiqiu:start(posx, posy, durtime)
	self.durtime = durtime
	self:setPositionAndSyncPhysicsTransform({x = posx, y = 0})
	self.armature:setPositionY(posy)
end

function Monster_Leiqiu:initFSM()
	self.FSM:addTranslation("State_Leiqiu1", "CMD_LeiQiu2", "State_Leiqiu2")
	self.FSM:addTranslation("State_Leiqiu2", "CMD_LeiQiu1", "State_Leiqiu1")
end

return Monster_Leiqiu
