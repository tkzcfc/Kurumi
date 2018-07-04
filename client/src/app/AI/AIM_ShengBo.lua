local AIBase = require("app.AI.AIBase")
local AIM_ShengBo = class("AIM_ShengBo", AIBase)

function AIM_ShengBo:ctor()
	self.super.ctor(self)
end

function AIM_ShengBo:override_AIUpdate(time)
	if not self.isAIEnable then
		return
	end
	self.curAITime = self.curAITime + time

	if self.enemy == nil then
		self.enemy = getGameWord():getLocalPlayer()
	end
	
	if self.owner:getActorPositionX() > self.enemy:getActorPositionX() then
		self.owner:setOrientation(GAME_ORI_LEFT)
	else
		self.owner:setOrientation(GAME_ORI_RIGHT)
	end
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

return AIM_ShengBo
