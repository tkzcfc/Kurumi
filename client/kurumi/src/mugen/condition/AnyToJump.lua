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
-- function M:reset()
-- end


function M:canJump()
	local curCount = self.pActorComponent.jumpCount or 0

	if curCount <= 0 then
		return self.pActorComponent:isKeyDown(slot.G_KEY_JUMP)
	else
		if not self.pActorComponent:isKeyDown(slot.G_KEY_JUMP) then
			return false
		end

		-- 跳跃最大次数限制
		if curCount >= 2 then
			return false
		end

		local curSkill = self.pActorComponent:getCurSkill()
		local curSkillName = curSkill:getName()

		if string.find(curSkillName, "JUMPUP") and curSkill:getCurFrame() < 15 then
			return false
		end
	end


	return true
end


-- @brief 检测函数
function M:check()

	if not self:canJump() then
		return false
	end

	local curCount = self.pActorComponent.jumpCount or 0
	self.pActorComponent.jumpCount = curCount + 1

	return true
end

-- @brief 销毁函数
-- function M:destroy()
-- end

return M

