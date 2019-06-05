local Monster_Base = require("app.actor.monster.Monster_Base")

local Monster_Leizhu = class("Monster_Leizhu", Monster_Base)

function Monster_Leizhu:ctor()
	Monster_Leizhu.super.ctor(self)
	
	self:loadConfig(require("app.config.monster.LeiQiuConfig"))

	self.FSM:start("State_Skill")
	self.durtime = 0.0
	self:enableDefaultPhysics()
end

function Monster_Leizhu:override_attCollisionCallback(otherActor)
	Monster_Leizhu.super.override_attCollisionCallback(self, otherActor)
	self.isPickUp = false
end

function Monster_Leizhu:override_update(delta)
	if self.durtime < 0 then
		self:destroy()
		return
	end
	self.durtime = self.durtime - delta

	self:setVelocityXByImpulse_Ext(800 / BOX2D_PIXEL_TO_METER)
end

function Monster_Leizhu:start(posx, durtime)
	self.durtime = durtime
	self:setPositionAndSyncPhysicsTransform({x = posx, y = 0})
end

return Monster_Leizhu
