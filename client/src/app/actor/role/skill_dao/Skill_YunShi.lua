
local Skill_Base = require("app.actor.role.skill_dao.Skill_Base")

local Skill_YunShi = class("Skill_YunShi", Skill_Base)


-- 技能表现：向下掉落陨石

function Skill_YunShi:ctor()
	Skill_YunShi.super.ctor(self)
	self.duration = 0
end

function Skill_YunShi:startSkill(callFunc, rotation)
	self.rotation = rotation
	self.endCallFunc = callFunc

	local config = require("app.config.dao_skill.Skill_YunShi")
	self:startWithConfig(config, "State_Run")
end

function Skill_YunShi:override_initFSM()
	self.FSM:addTranslation("State_Run", "CMD_Stop", "State_Stop")

	self:enableUpdate()
	changeParticleSystemPositionType(self.armature, 2)
	if self.rotation then
		self.armature:setRotation(self.rotation)
	end
end

function Skill_YunShi:override_onStateRunStop(stateName)
	Skill_YunShi.super.override_onStateRunStop(self, stateName)

	if stateName == "State_Stop" then
		if self.endCallFunc then
			self.endCallFunc(self)
		end
		self:destroy()
	end
end

function Skill_YunShi:override_update(time)
	Skill_YunShi.super.override_update(self, time)

	if self.beginContact and  not self.isInAir then
		local curStateName = self.FSM:getCurStateName()
		if curStateName == "State_Run" then
			self:clearForceX()
			self.duration = self.duration + time
			if self.duration > 0.3 then
				self:handle("CMD_Stop")
			end
		end
	end
end

function Skill_YunShi:leave_State_Run()
	self.armature:setRotation(0)
end

function Skill_YunShi:enter_State_Stop()
	self:clearForceX()
end

return Skill_YunShi