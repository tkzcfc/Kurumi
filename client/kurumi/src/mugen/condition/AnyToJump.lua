-- @Author : fc
-- @Date   : 2022-05-28 16:23:07
-- @remark : 其他状态->跳跃


local M = {}

-- @brief 构造函数
function M:ctor()
	local entity = self:getEntity()
	self.pActorComponent = G_GetComponent(entity, "GActorComponent")
end

-- @brief 重置函数
-- function M:rest()
-- end

-- @brief 检测函数
function M:check()
	return self.pActorComponent:isKeyDown(slot.G_KEY_JUMP)
end

-- @brief 销毁函数
-- function M:destroy()
-- end

return M

