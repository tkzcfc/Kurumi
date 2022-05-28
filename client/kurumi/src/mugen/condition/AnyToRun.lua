-- @Author : fc
-- @Date   : 2022-2-4 14:56:55
-- @remark : 

local IdleToRun = {}
require("mugen.init")

function IdleToRun:ctor()
	local entity = self:getEntity()
	self.pActorComponent = G_GetComponent(entity, "GActorComponent")


	-- print("slot.G_KEY_MOVE_LEFT", slot.G_KEY_MOVE_LEFT)
	-- print("slot.G_KEY_MOVE_RIGH", slot.G_KEY_MOVE_RIGHT)
	-- print("slot.G_KEY_MOVE_UP", slot.G_KEY_MOVE_UP)
	-- print("slot.G_KEY_MOVE_DOWN", slot.G_KEY_MOVE_DOWN)
	-- print("slot.G_KEY_JUMP", slot.G_KEY_JUMP)
	-- print("slot.G_KEY_SKILL_1", slot.G_KEY_SKILL_1)
	-- print("slot.G_KEY_SKILL_2", slot.G_KEY_SKILL_2)
	-- print("slot.G_KEY_SKILL_3", slot.G_KEY_SKILL_3)
	-- print("slot.G_KEY_SKILL_4", slot.G_KEY_SKILL_4)
	-- print("slot.G_KEY_SKILL_5", slot.G_KEY_SKILL_5)
	-- print("slot.G_KEY_SKILL_6", slot.G_KEY_SKILL_6)
	-- print("slot.G_KEY_SKILL_7", slot.G_KEY_SKILL_7)
end

-- function IdleToRun:rest()
-- end

function IdleToRun:check()
	return self.pActorComponent:isKeyDown(slot.G_KEY_MOVE_MUSTER)
end

-- function IdleToRun:destroy()
-- end

return IdleToRun
