
local Skill_Base = require("app.actor.role.dao_skill.Skill_Base")

local Skill_YunShi = class("Skill_YunShi", Skill_Base)


-- 技能表现：切换刀时候闪现斩字

function Skill_YunShi:ctor()
	Skill_YunShi.super.ctor(self)
	self.noMoveCount = 0
	self.stopTag = false
end

function Skill_YunShi:startSkill(callFunc, rotation)
	self.rotation = rotation
	self.endCallFunc = callFunc

	local config = require("app.config.dao_skill.Skill_YunShi")
	self:startWithConfig(config, "State_Run")
end

function Skill_YunShi:override_loadArmature(filePath)
	changeParticleSystemPositionType(self:getArmature())
	if self.rotation then
		self:getArmature():setRotation(self.rotation)
	end
end

function Skill_YunShi:override_initFSM()
	self.FSM:addTranslation("State_Run", "CMD_Stop", "State_Stop")
end

function Skill_YunShi:override_onStateRunStop(stateName)
	Skill_YunShi.super.override_onStateRunStop(self, stateName)

	if stateName == "State_Stop" then
		if self.endCallFunc then
			self.endCallFunc(self)
		end
		getGameWord():removeActor(self)
	end
end

function Skill_YunShi:override_logicUpdate(time)
	Skill_YunShi.super.override_logicUpdate(self, time)

	if self.stopTag then
		return
	end

	local curY = self:getPositionY()

	if self.lastUpdateYPos then
		local sub = math.abs(self.lastUpdateYPos - curY)
		if sub <= 0.5 then
			self.noMoveCount = self.noMoveCount + 1
			if self.noMoveCount > 5 then
				self.stopTag = true
				self:handle("CMD_Stop")
			end
		end
	end
	self.lastUpdateYPos = curY
end

function Skill_YunShi:leave_State_Run()
	self:getArmature():setRotation(0)
end

return Skill_YunShi