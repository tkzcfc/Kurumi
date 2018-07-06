local AIM_Follow = require("app.AI.AIM_Follow")
local AIM_LeiShen = class("AIM_LeiShen", AIM_Follow)


--状态权重
local AttackWeight = 
{
	SKILL_2 = 3,
	SKILL_3 = 3,
	SKILL_5 = 0
}


function AIM_LeiShen:ctor()
	AIM_LeiShen.super.ctor(self)
end

function AIM_LeiShen:start()
	if AIM_LeiShen.super.start(self) then
		local config = require("app.config.monster.LeiShenConfig")
		self:loadFollowConfig(config.FOLLOW_CONFIG)
		return true
	end
	return false
end

function AIM_LeiShen:override_AIUpdate(time)
	AIM_LeiShen.super.override_AIUpdate(self, time)
	if self.enemy == nil and getGameWord() then
		self.enemy = getGameWord():getLocalPlayer()
	end
end

--左移
function AIM_LeiShen:dis_control_4()
	self.owner:moveLeft()
end

--右移
function AIM_LeiShen:dis_control_6()
	self.owner:moveRight()
end

function AIM_LeiShen:dis_control_5()
	self.owner:moveStop()
end

function AIM_LeiShen:dis_control_7()

end

function AIM_LeiShen:dis_control_8()
	self.owner:skill2()
end

function AIM_LeiShen:dis_control_9()
	self.owner:skill3()
end

function AIM_LeiShen:dis_control_1()
	self.owner:skill5()
end

function AIM_LeiShen:override_MoveLeft()
	self.owner:moveLeft()
end

function AIM_LeiShen:override_MoveRight()
	self.owner:moveRight()
end

function AIM_LeiShen:override_Sleep()
	self.owner:moveStop()
end

function AIM_LeiShen:override_Other()

	local value = self:getValueByWigetData(AttackWeight)
	if value == "SKILL_2" then
		self.owner:skill2()
	elseif value == "SKILL_3" then
		self.owner:skill3()
	elseif value == "SKILL_5" then
		self.owner:skill5()
	end
end


return AIM_LeiShen
