
local LuaCharacter = require("app.foundation.LuaCharacter")
local Skill_Base = class("Skill_Base", LuaCharacter)


--------------------------------------override--------------------------------------

function Skill_Base:ctor()
	Skill_Base.super.ctor(self)
	self:setFilterData(BOX2D_FILTER_MASK.B2DM_PLAYER)
end

-- 设置宿主
function Skill_Base:setHost(host)
	self.host = host
end

--------------------------------------logic--------------------------------------
function Skill_Base:startWithConfig(config, startState)
	self:loadConfig(config)
	self:override_initFSM()
	self.FSM:start(startState)
	self:enableDefaultPhysics()

	self:changeCategoryBits(BOX2D_FILTER_MASK.B2DM_SKILL)
end

function Skill_Base:override_initFSM()
end

return Skill_Base