-- @Author : fc
-- @Date   : 2022-07-24 17:26:50
-- @remark : 是否按下普通攻击

local M = {}

-- @brief 构造函数
function M:ctor(slotName)
	self.slotName = slotName
	
	local entity = self:getEntity()
	self.pActorComponent = G_GetComponent(entity, "GActorComponent")
end

-- @brief 重置函数
-- function M:reset()
-- end

-- @brief 检测函数
function M:check()
	return self.pActorComponent:isKeepPress(slot[self.slotName])
end

-- @brief 销毁函数
-- function M:destroy()
-- end

return M
