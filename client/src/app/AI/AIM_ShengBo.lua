local AIM_Follow = require("app.AI.AIM_Follow")
local AIM_ShengBo = class("AIM_ShengBo", AIM_Follow)


--状态权重
local AttackWeight = 
{
	ATTACK1 = 3,
	ATTACK2 = 3,
	SKILL = 1
}


function AIM_ShengBo:ctor()
	AIM_ShengBo.super.ctor(self)
end

function AIM_ShengBo:override_AIPreInit()
	AIM_ShengBo.super.override_AIPreInit(self)
	local config = require("app.config.monster.ShengBoConfig")
	self:loadFollowConfig(config.FOLLOW_CONFIG)
end

function AIM_ShengBo:override_AIUpdate(time)
	AIM_ShengBo.super.override_AIUpdate(self, time)
	-- if self.enemy == nil then

	-- 	local world = self.owner:getGameWorld()
	-- 	self.enemy = world.
	-- end
end

--左移
function AIM_ShengBo:dis_control_4()
	self.owner:moveLeft()
end

--右移
function AIM_ShengBo:dis_control_6()
	self.owner:moveRight()
end

function AIM_ShengBo:dis_control_5()
	self.owner:moveStop()
end

function AIM_ShengBo:dis_control_7()
	self.owner:attack1()
end

function AIM_ShengBo:dis_control_8()
	self.owner:attack2()
end

function AIM_ShengBo:dis_control_9()
	self.owner:skill()
end

function AIM_ShengBo:override_MoveLeft()
	self.owner:moveLeft()
end

function AIM_ShengBo:override_MoveRight()
	self.owner:moveRight()
end

function AIM_ShengBo:override_Sleep()
	self.owner:moveStop()
end

function AIM_ShengBo:override_Other()

	if self.Follow_CurRange == "FOLLOW_E_RANGE" then
		self.owner:skill()
		return
	end

	local value = self:getValueByWigetData(AttackWeight)
	if value == "ATTACK1" then
		self:updateOrientation()
		self.owner:attack1()
	elseif value == "ATTACK2" then
		self:updateOrientation()
		self.owner:attack2()
	elseif value == "SKILL" then
		self:updateOrientation()
		self.owner:skill()
	end
end


return AIM_ShengBo
