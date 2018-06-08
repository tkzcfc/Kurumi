local PlayerController = class("PlayerController")

local CommonActorConfig = require("app.config.CommonActorConfig")

local JumpHeight = CommonActorConfig.playerJumpHeight
local JumpUpTime = CommonActorConfig.playerJumpTime



function PlayerController:ctor()

	self.player = nil

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
	_MyG.PlayerDispatcher:register(key, function(...) 
		if self.player == nil then
			return
		end
		if self["dis_"..key] then
			self["dis_"..key](self, ...)
		end
	end)
end

function PlayerController:dis_control_move(actor, x, y)
	if actor ~= self.player then return end
	if math.abs(x) <= 0.0001 and math.abs(y) <= 0.0001 then
		return
	end

	x = x * self.player.gameAttribute:getSpeedX()
	y = y * self.player.gameAttribute:getSpeedY()
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

	if self.player:handle("CMD_JumpUpStart") then

		self.isJumpAttack = false

		local move = cc.MoveBy:create(JumpUpTime, {x = 0, y = JumpHeight})
		local call1 = cc.CallFunc:create(function()
			if self.isJumpAttack then
				self.player:handle("CMD_To_JumpAttack")
			else
				self.player:handle("CMD_JumpDownStart")
			end
			self.isJumpAttack = false
		end)
		local call2 = cc.CallFunc:create(function()
			local movePower = self.player:getMovePower("PowerName_ControlMove")
			if movePower and math.abs(movePower.power.x) > 0.1 then
				self.player:handle("CMD_JumpTo_MoveStart")
			else
				self.player:handle("CMD_JumpDownEnd")
			end
		end)
		local q = cc.Sequence:create(move, call1, move:reverse(), call2)
		self.player:getArmature():runAction(q)

		local word = getGameWord()
		if word ~= nil then
			local winSize = cc.Director:getInstance():getVisibleSize()
			local subheight = winSize.height - word:getMapSize().height
			subheight = subheight * 0.5
			subheight = math.max(subheight, -JumpHeight)

			local mapMove = cc.MoveBy:create(JumpUpTime, {x = 0, y = subheight})
			word:getRootNode():runAction(cc.Sequence:create(mapMove, mapMove:reverse()))
		end
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

	if not self.player:handle("CMD_Attack") then
		self.toNextAttack = true
		self.isJumpAttack = true
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
		print("CMD_To_Attack4")
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
