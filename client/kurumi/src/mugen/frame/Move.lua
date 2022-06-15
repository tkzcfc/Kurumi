-- @Author : fc
-- @Date   : 2022-02-06 10:58:18
-- @remark : 


local slot = slot

local M = {}

-- @brief 构造函数
function M:ctor()
	self.pRigidBodyComponent = G_GetComponent(self, "GRigidBodyComponent")
	self.pDataComponent = G_GetComponent(self, "GDataComponent")
	self.pActorComponent = G_GetComponent(self, "GActorComponent")

end

-- @brief 触发函数
function M:emit()
	if not self.pActorComponent:isKeepPress(slot.G_KEY_MOVE_MUSTER) then
		return
	end

	local moveSpeed = self.pDataComponent.moveSpeed

	-- 在空中Y轴不可移动
	if self.pActorComponent:isInAir() then
		moveSpeed.y = 0
	else
		if self.pActorComponent:isKeepPress(slot.G_KEY_MOVE_Y) then
			if self.pActorComponent:isKeepPress(slot.G_KEY_MOVE_DOWN) then
				moveSpeed.y = -moveSpeed.y
			end
		else
			moveSpeed.y = 0
		end
	end



	if self.pActorComponent:isKeepPress(slot.G_KEY_MOVE_X) then
		-- X移动根据朝向计算正负
		if self.pActorComponent:isLeft() then
			moveSpeed.x = -moveSpeed.x
		end
	else
		moveSpeed.x = 0
	end


	--- 速度缩放
	local scalex = 1
	local scaley = 1

	local curSkill = self.pActorComponent:getCurSkill()
	local curSkillName = curSkill:getName()
	local curAction = curSkill:getCurAction()
	local curActName = curAction:getName()

	-- 跑步
	if curSkillName == "ANI_NAME_FIGHT_RUN" then
		if curSkill:getCurActionIdx() == 0 then
			scalex = 0.7
			scaley = 0.7
		end
	-- 跳跃
	elseif string.find(curSkillName, "JUMP") then
		scalex = 0.4
	end



	-- print(curSkillName, moveSpeed.x, moveSpeed.x * scalex)

	self.pRigidBodyComponent:appendOffsetOneSecond(moveSpeed.x * scalex, moveSpeed.y * scaley)
end

return M


