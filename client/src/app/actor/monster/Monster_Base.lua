local LuaCharacter = require("app.foundation.LuaCharacter")

local Monster_Base = class("Monster_Base", LuaCharacter)

function Monster_Base:ctor()
	Monster_Base.super.ctor(self)
	
	self:enableUpdate()
	
	self:setFilterData(BOX2D_FILTER_MASK.B2DM_MONSTER)
end

function Monster_Base:onEnter()
	Monster_Base.super.onEnter(self)

	if self.aiController then
		self.aiController:onEnter()
	end
end

function Monster_Base:onExit()
	if self.aiController then
		self.aiController:onExit()
		self.aiController = nil
	end

	Monster_Base.super.onExit(self)
end

function Monster_Base:moveStart(isLeft)
	self.moveToLeft = isLeft
	return self:handle("CMD_MoveStart")
end

function Monster_Base:moveStop()
	self:clearForceX()
	return self:handle("CMD_MoveStand")
end

function Monster_Base:getVelocityByMoveOrientation(value)
	if self.moveToLeft then
		return -value
	end
	return value
end

function Monster_Base:override_update(delta)
	Monster_Base.super.override_update(self, delta)
	self.aiController:update(delta)
end

return Monster_Base


