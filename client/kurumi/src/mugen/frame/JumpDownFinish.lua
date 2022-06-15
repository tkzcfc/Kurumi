-- @Author : fc
-- @Date   : 2022-05-28 18:47:10
-- @remark : 


local M = {}

-- @brief 构造函数
function M:ctor()
	local entity = self:getEntity()
	self.pActorComponent = G_GetComponent(entity, "GActorComponent")
end

-- @brief 触发函数
function M:emit()
	if not self.pActorComponent:isInAir() then
		self.pActorComponent.jumpCount = 0
		self.pActorComponent:getCurSkill():getCurAction():interrupt(GInterruptType.PROMPTLY)
	end
end

return M


