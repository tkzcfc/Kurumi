-- @Author : fc
-- @Date   : 2022-02-06 10:58:18
-- @remark : 


local M = {}

-- @brief 构造函数
function M:ctor()
	self.pActorComponent = G_GetComponent(self, "GActorComponent")
	self.pActorComponent = G_GetComponent(self, "GActorComponent")
end

-- @brief 触发函数
function M:emit()
	if not self.pActorComponent:isKeyDown(slot.G_KEY_MOVE_MUSTER) then
		return
	end

	if self.pActorComponent:isKeyDown(slot.G_KEY_MOVE_MUSTER) then
	end
end

return M


