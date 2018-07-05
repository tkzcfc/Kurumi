local AIBase = require("app.AI.AIBase")
local AIM_ChangQiangWS = class("AIM_ChangQiangWS", AIBase)

function AIM_ChangQiangWS:ctor()
	self.super.ctor(self)
end

function AIM_ChangQiangWS:override_AIUpdate(time)
	if not self.isAIEnable then
		return
	end
	self.curAITime = self.curAITime + time
end

--左移
function AIM_ChangQiangWS:dis_control_4()
	self.owner:moveLeft()
end

--右移
function AIM_ChangQiangWS:dis_control_6()
	self.owner:moveRight()
end

function AIM_ChangQiangWS:dis_control_5()
	self.owner:attack(true)
end

function AIM_ChangQiangWS:dis_control_7()
	self.owner:attack(false)
end

function AIM_ChangQiangWS:dis_control_8()
	self.owner:jump()
end

function AIM_ChangQiangWS:dis_control_9()
	self.owner:skill()
end

return AIM_ChangQiangWS
