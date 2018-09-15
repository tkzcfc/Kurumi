local PlayerController = class("PlayerController")


function PlayerController:ctor()

	self.player = nil

	self.disEventList = {}

	self:register("control_move")
	self:register("control_stop")
	self:register("control_jump")
	self:register("control_changeWeapon")
	self:register("control_attack")

	self:register("State_Attack1_stop")
	self:register("State_Attack2_stop")
	self:register("State_Attack3_stop")
	self:register("State_Attack4_stop")

	self.isJumpAttack = false
end

function PlayerController:setPlayer(player)
	self.player = player

	self.player:handle("CMD_MoveStand")
end

function PlayerController:getPlayer()
	return self.player
end

function PlayerController:register(key)
	local func = function(...) 
		if self.player == nil then
			return
		end
		if self["dis_"..key] then
			self["dis_"..key](self, ...)
		end
	end
	_MyG.PlayerDispatcher:register(key, func)
	self.disEventList[key] = func
end

function PlayerController:unRegisterAll()
	for k,v in pairs(self.disEventList) do
		_MyG.PlayerDispatcher:unRegister(k, v)
	end	
	self.disEventList = {}
end

function PlayerController:dis_control_move(actor, x, y)
	if actor ~= self.player then return end
	if math.abs(x) <= 0.0001 and math.abs(y) <= 0.0001 then
		return
	end
	self.player:setMove(x, y)
	self.player:handle("CMD_MoveStart")
end

function PlayerController:dis_control_stop(actor)
	if actor ~= self.player then return end
	self.player:setMoveStop()
	self.player:handle("CMD_MoveStand")
end

function PlayerController:dis_control_jump(actor)
	if actor ~= self.player then return end

	if not self.player:jump() then
		return
	end
end

-- 切换武器
function PlayerController:dis_control_changeWeapon(actor)
	if actor ~= self.player then return end
	self.player:handle("CMD_change")
end

--攻击
function PlayerController:dis_control_attack(actor)
	if actor ~= self.player then return end

	if not self.player:attack() then
		self.toNextAttack = true
	else
		self.toNextAttack = false
	end
end

-----------------------------------状态切换-----------------------------------

function PlayerController:dis_State_Attack1_stop(actor)
	if actor ~= self.player then return end
	if self.toNextAttack then
		self.toNextAttack = false
		self.player:handle("CMD_To_Attack2")
	end
end

function PlayerController:dis_State_Attack2_stop(actor)
	if actor ~= self.player then return end
	if self.toNextAttack then
		self.toNextAttack = false
		self.player:handle("CMD_To_Attack3")
	end
end

function PlayerController:dis_State_Attack3_stop(actor)
	if actor ~= self.player then return end
	if self.toNextAttack then
		self.toNextAttack = false
		self.player:handle("CMD_To_Attack4")
	end
end

function PlayerController:dis_State_Attack4_stop(actor)
	if actor ~= self.player then return end
	if self.toNextAttack then
		self.toNextAttack = false
		self.player:handle("CMD_To_Attack1")
	end
end

return PlayerController
