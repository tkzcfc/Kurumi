
local Skill_Base = require("app.actor.role.dao_skill.Skill_Base")

local Skill_BaDaoZhan = class("Skill_BaDaoZhan", Skill_Base)


-- 技能表现：切换刀时候闪现斩字

function Skill_BaDaoZhan:ctor()
	Skill_BaDaoZhan.super.ctor(self)
end

function Skill_BaDaoZhan:startSkill(callFunc)
	self.endCallFunc = callFunc
	
	local config = require("app.config.dao_skill.Skill_BaDaoZhan")
	self:startWithConfig(config, "State_Run")
end

function Skill_BaDaoZhan:override_initFSM()
end

function Skill_BaDaoZhan:override_onStateRunStop(stateName)
	Skill_BaDaoZhan.super.override_onStateRunStop(self, stateName)

	if self.endCallFunc then
		self.endCallFunc(self)
	end

	getGameWord():removeActor(self)
end

return Skill_BaDaoZhan