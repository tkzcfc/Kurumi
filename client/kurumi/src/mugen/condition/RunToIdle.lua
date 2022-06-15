-- @Author : fc
-- @Date   : 2022-02-04 19:59:10
-- @remark : 


local M = {}

-- @brief 构造函数
function M:ctor()
	local entity = self:getEntity()
	self.pActorComponent = G_GetComponent(entity, "GActorComponent")
end

-- @brief 重置函数
-- function M:reset()
-- end

-- @brief 检测函数
function M:check()
	return not self.pActorComponent:isKeepPress(slot.G_KEY_MOVE_MUSTER)
end

-- @brief 销毁函数
-- function M:destroy()
-- end

return M
