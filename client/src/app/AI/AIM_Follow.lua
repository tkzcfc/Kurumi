local AIBase = require("app.AI.AIBase")
local AIM_Follow = class("AIM_Follow", AIBase)




function AIM_Follow:ctor()
	AIM_Follow.super.ctor(self)

	self.moveDirUpdateTime = 0.0
	self.curMoveDirUpdateTime = 0.0
end

function AIM_Follow:loadFollowConfig(config)

	self.STATE_CHAGE_MIN_TIME = config.STATE_CHAGE_MIN_TIME
	self.STATE_CHAGE_MAX_TIME = config.STATE_CHAGE_MAX_TIME
	self.FOLLOW_L_MIN = config.FOLLOW_L_MIN
	self.FOLLOW_G_MAX = config.FOLLOW_G_MAX
	self.FOLLOW_E_RANGE = config.FOLLOW_E_RANGE	
	self.FOLLOW_MAX = config.FOLLOW_MAX
	self.FOLLOW_MIN = config.FOLLOW_MIN

	self.Follow_StateWeight = self.FOLLOW_G_MAX.STATE_WEIGHT

	if  self.STATE_CHAGE_MIN_TIME == nil or
		self.STATE_CHAGE_MAX_TIME == nil or
		self.FOLLOW_L_MIN == nil or
		self.FOLLOW_G_MAX == nil or
		self.FOLLOW_E_RANGE == nil or
		self.FOLLOW_MAX == nil or
		self.FOLLOW_MIN == nil then
		print("\n\n")
		print("[ERROR] loadFollowConfig fail")
		print("self.STATE_CHAGE_MIN_TIME", "=", self.STATE_CHAGE_MIN_TIME)
		print("self.STATE_CHAGE_MAX_TIME", "=", self.STATE_CHAGE_MAX_TIME)
		print("self.FOLLOW_L_MIN        ", "=", self.FOLLOW_L_MIN        )
		print("self.FOLLOW_G_MAX        ", "=", self.FOLLOW_G_MAX        )
		print("self.FOLLOW_E_RANGE      ", "=", self.FOLLOW_E_RANGE      )
		print("self.FOLLOW_MAX          ", "=", self.FOLLOW_MAX          )
		print("self.FOLLOW_MIN          ", "=", self.FOLLOW_MIN          )
		print("\n\n")
	end

	self.Follow_CurStateTime = 0.0
	self.Follow_NextChangeTime = 0.0

	self.Follow_CurChangeOriTime = 0.0
	self.Follow_NextChangeOriTime = 0.0

	self.Follow_CurState = nil
	self.Follow_CurRange = "FOLLOW_G_MAX"

	self:randState()
end

function AIM_Follow:override_AIUpdate(time)
	AIM_Follow.super.override_AIUpdate(self)
	if not self.isAIEnable then
		return
	end

	self.Follow_CurStateTime = self.Follow_CurStateTime + time
	if self.Follow_CurStateTime > self.Follow_NextChangeTime then
		self.Follow_CurStateTime = 0.0
		self:randState()
	end

	self.Follow_CurChangeOriTime = self.Follow_CurChangeOriTime + time
	if self.Follow_CurChangeOriTime >= self.Follow_NextChangeOriTime then
		if self.enemy then
			local subx = self.owner:getActorPositionX() - self.enemy:getActorPositionX()
			subx = math.abs(subx)
			if subx <= self.FOLLOW_MIN then
				self:doChangeOriConfig(self.FOLLOW_L_MIN)
				self.Follow_CurRange = "FOLLOW_L_MIN"
				-- print("self.FOLLOW_L_MIN")
			elseif subx > self.FOLLOW_MAX then
				self:doChangeOriConfig(self.FOLLOW_G_MAX)
				self.Follow_CurRange = "FOLLOW_G_MAX"
				-- print("self.FOLLOW_G_MAX")
			else
				self:doChangeOriConfig(self.FOLLOW_E_RANGE)
				self.Follow_CurRange = "FOLLOW_E_RANGE"
				-- print("self.FOLLOW_E_RANGE")
			end
		else
			self:doChangeOriConfig(self.FOLLOW_G_MAX)
		end
	end
end

function AIM_Follow:updateOrientation()
	local Orientation = 0
	if self.enemy then
		if self.owner:getActorPositionX() > self.enemy:getActorPositionX() then
			self.owner:setOrientation(GAME_ORI_LEFT)
			Orientation = GAME_ORI_LEFT
		else
			self.owner:setOrientation(GAME_ORI_RIGHT)
			Orientation = GAME_ORI_RIGHT
		end
	end
	return Orientation
end

function AIM_Follow:doChangeOriConfig(config)

	self.Follow_StateWeight = config.STATE_WEIGHT
	self.Follow_CurChangeOriTime = 0.0
	self.Follow_NextChangeOriTime = math.random(config.updateOriMinTime, config.updateOriMaxTime)

	local ori = self:updateOrientation()

	-- print("self.Follow_CurState = ", self.Follow_CurState)
	if self.Follow_CurState ~= "MOVE" then
		return
	end

	if ori == 0 then
		self:randomMove()
		-- print("Move random1")
		return
	end

	local value = self:getValueByWigetData(config.changeOriWidget)
	if value == "FOLLOW" then
		if ori == GAME_ORI_LEFT then
			self:override_MoveLeft()
		else
			self:override_MoveRight()
		end
	elseif value == "BACK" then
		if ori == GAME_ORI_LEFT then
			self:override_MoveRight()
		else
			self:override_MoveLeft()
		end
	elseif value == "NONE" then
		self:override_Sleep()
	end
end

function AIM_Follow:randomMove()
	if math.random(1, 2) == 1 then
		self:override_MoveLeft()
	else
		self:override_MoveRight()
	end
end

function AIM_Follow:randState()
	self.Follow_CurStateTime = 0
	self.Follow_NextChangeTime = math.random(self.STATE_CHAGE_MIN_TIME, self.STATE_CHAGE_MAX_TIME)

	local state = self:getValueByWigetData(self.Follow_StateWeight)

	if state == "SLEEP" then
		self:override_Sleep()
	elseif state == "MOVE" then
		self.Follow_NextChangeOriTime = 0.0
		self.Follow_NextChangeTime = math.random(self.STATE_CHAGE_MIN_TIME, self.STATE_CHAGE_MIN_TIME + 0.3)
	else
		self:override_Other()
	end

	self.Follow_CurState = state
end

function AIM_Follow:override_MoveLeft()
end

function AIM_Follow:override_MoveRight()
end

function AIM_Follow:override_Sleep()
end

function AIM_Follow:override_Other()
end


return AIM_Follow
