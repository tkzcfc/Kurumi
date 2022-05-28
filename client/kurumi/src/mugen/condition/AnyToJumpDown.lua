-- @Author : fc
-- @Date   : 2022-05-28 16:32:20
-- @remark : 其他状态->跳跃下落



local M = {}

-- @brief 构造函数
function M:ctor()
	local entity = self:getEntity()
	self.pRigidBodyComponent = G_GetComponent(entity, "GRigidBodyComponent")
end

-- @brief 重置函数
-- function M:rest()
-- end

-- @brief 检测函数
function M:check()
	return self.pRigidBodyComponent.linearVelocity.y <= 0
end

-- @brief 销毁函数
-- function M:destroy()
-- end

return M