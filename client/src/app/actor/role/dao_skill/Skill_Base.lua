
local LuaGameCharacter = require("app.actor.LuaGameCharacter")

local Skill_Base = class("Skill_Base", LuaGameCharacter)


--------------------------------------override--------------------------------------

function Skill_Base:ctor()
	Skill_Base.super.ctor(self)
	self:setActorType(AT_PLAYER)
end

function Skill_Base:override_attOtherActorCallback(otherActor)
	otherActor:override_beAttacked(self, false)
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
end

function Skill_Base:override_initFSM()
end

return Skill_Base