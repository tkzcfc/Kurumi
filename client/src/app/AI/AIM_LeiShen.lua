local AIM_Follow = require("app.AI.AIM_Follow")
local AIM_LeiShen = class("AIM_LeiShen", AIM_Follow)


--
--最大移动值
local Skill5_MoveX_Max = 1200
--玩家左边最小值
local Slill5_Left_Random_Range_Min = -150
--玩家左边最大值
local Slill5_Left_Random_Range_Max = -800
--玩家右边最小值
local Slill5_Right_Random_Range_Min = -150
--玩家右边最大值
local Slill5_Right_Random_Range_Max = -800
--随机移动最小值
local Skill5_Random_Range_Min = 300
--随机移动最大值
local Skill5_Random_Range_Max = 1200
local Skill5Weight = 
{
	PLAYER_POS = 3,
	PLAYER_LEFT = 2,
	PLAYER_RIGHT = 2,
	RANDOM = 1
}

--状态权重
local AttackWeight = 
{
	SKILL_1 = 0,
	SKILL_2 = 12,
	SKILL_3 = 20,
	SKILL_5 = 1,
	SKILL_6 = 6,
}

local AttackRange = 
{
	SKILL_1 = 800,
	SKILL_2 = 400,
	SKILL_3 = 200,
	SKILL_5 = 10000,
	SKILL_6 = 800,
}



function AIM_LeiShen:ctor()
	AIM_LeiShen.super.ctor(self)
	--self:setAIEnable(false)
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
	self.owner:skill1()
end

function AIM_LeiShen:dis_control_8()
	self.owner:skill2()
end

function AIM_LeiShen:dis_control_9()
	self.owner:skill3()
end

function AIM_LeiShen:dis_control_1()
	self:runSkill5()
end

function AIM_LeiShen:dis_control_2()
	self.owner:skill6()
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
	local curAttackArr = {}
	if self.enemy then
		local subx = self.enemy:getActorPositionX() - self.owner:getActorPositionX()
		subx = math.abs(subx)
		for k,v in pairs(AttackRange) do
			if subx <= v then
				table.insert(curAttackArr, k)
			end
		end
	end
	if #curAttackArr < 1 then
		table.insert(curAttackArr, "SKILL_5")
	end

	local curAttackWeight = {}
	for k,v in pairs(curAttackArr) do
		curAttackWeight[v] = AttackWeight[v]
	end

	local value = self:getValueByWigetData(curAttackWeight)

	if value == "SKILL_1" then
		self:updateOrientation()
		if not self.owner:skill1() and self.owner.isHit then
			self:runSkill5(true)
		end
	elseif value == "SKILL_2" then
		self:updateOrientation()
		if not self.owner:skill2() and self.owner.isHit then
			self:runSkill5(true)
		end
	elseif value == "SKILL_3" then
		self:updateOrientation()
		if not self.owner:skill3() and self.owner.isHit then
			self:runSkill5(true)
		end
	elseif value == "SKILL_5" then
		self:runSkill5()
	elseif value == "SKILL_6" then
		self:updateOrientation()
		if not self.owner:skill6() and self.owner.isHit then
			self:runSkill5(true)
		end
	end
end

function AIM_LeiShen:runSkill5(isHit)
	local endPosx = nil 
	local value = "RANDOM"
	if not isHit and self.enemy then
		value = self:getValueByWigetData(Skill5Weight)
	end

	if value == "PLAYER_POS" then
		local randomValue = math.random(Slill5_Left_Random_Range_Min, Slill5_Right_Random_Range_Min)
		endPosx = self.enemy:getActorPositionX() + randomValue
	elseif value == "PLAYER_LEFT" then
		local randomValue = math.random(Slill5_Left_Random_Range_Min, Slill5_Left_Random_Range_Max)
		endPosx = self.enemy:getActorPositionX() + randomValue
	elseif value == "PLAYER_RIGHT" then
		local randomValue = math.random(Slill5_Right_Random_Range_Min, Slill5_Right_Random_Range_Max)
		endPosx = self.enemy:getActorPositionX() + randomValue
	elseif value == "RANDOM" then
		local randomValue = math.random(Skill5_Random_Range_Min, Skill5_Random_Range_Max)
		if self.enemy then
			if self.enemy:getActorPositionX() < self.owner:getActorPositionX() then
				randomValue = -randomValue
			end
		else
			if math.random(1,2) == 1 then
				randomValue = -randomValue
			end
		end
		endPosx = self.owner:getActorPositionX() + randomValue
	end
	endPosx = self:Skill5MoveCheck(endPosx)
	self.owner:skill5(endPosx)
end

function AIM_LeiShen:Skill5MoveCheck(endPosx)
	if endPosx == nil then
		return endPosx
	end

	local value = self.owner:getActorPositionX() - endPosx
	local absvalue = math.abs(value)
	if absvalue > Skill5_MoveX_Max then
		absvalue = Skill5_MoveX_Max
		if value < 0 then
			absvalue = -absvalue
		end
		return self.owner:getActorPositionX() - absvalue
	end
	return endPosx
end


return AIM_LeiShen
