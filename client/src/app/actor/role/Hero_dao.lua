
local LuaGameActor = require("app.actor.LuaGameActor")

local Hero_dao = class("Hero_dao", LuaGameActor)


-----------------------------------------------------------------------------------

local RoleConfig = require("app.config.RoleConfig")
local CommonActorConfig = require("app.config.CommonActorConfig")

local PowerName_ControlMove = "PowerName_ControlMove"
local PowerName_JumpMove = "PowerName_JumpMove"
local PowerName_Attack1 = "PowerName_Attack1"
local PowerName_Attack2 = "PowerName_Attack2"
local PowerName_Attack3 = "PowerName_Attack3"
local PowerName_Attack4 = "PowerName_Attack4"
local PowerName_Hit = "PowerName_Hit"

--攻击时移动属性
local Attack_Power = {}
Attack_Power[PowerName_Attack1] = {x = 20, y = 0}
Attack_Power[PowerName_Attack2] = {x = 30, y = 0}
Attack_Power[PowerName_Attack3] = {x = 30, y = 0}
Attack_Power[PowerName_Attack4] = {x = 10, y = 0}

--受到攻击时移动属性
local Hit_Power = {x = 30, y = 0}


--------------------------------------override--------------------------------------

function Hero_dao:ctor()
	self.super.ctor(self)

	self:setActorType(AT_PLAYER)

	self:changeRole("hero_lanse_dao")
end

function Hero_dao:override_attOtherActorCallback(otherActor)
	otherActor:override_beAttacked(self, false)
end

function Hero_dao:override_beAttacked(attackActor, isPickUp)
	self.super.override_beAttacked(self, attackActor, isPickUp)

	-- if not isPickUp then
		--CommonActorConfig.beAttackedAndBackOffSpeedPercent
	-- end
	self:handle("CMD_hit")
end

--------------------------------------logic--------------------------------------

--切换角色
function Hero_dao:changeRole(name)

	if self.roleName == name then
		return
	end
	self.roleName = name

	self:loadConfig(RoleConfig[name])

	ccs.ArmatureDataManager:getInstance():addArmatureFileInfo("uianimation/juhe_texiao.ExportJson")
	local ArmatureNode = ccs.Armature:create()
	ArmatureNode:init("juhe_texiao")
	ArmatureNode:getAnimation():play("juhe_texiao")
	ArmatureNode:setPosition({x = 0, y = 110})
	self:addChild(ArmatureNode)

	self.isRun = false
	self.isJump = false
	self.isAttack = false

	self:initMovePower()
	self:initFSM()

	self.FSM:start("State_Stand")
end

function Hero_dao:initMovePower()
	self:addMovePower(PowerName_ControlMove)
	self:addMovePower(PowerName_JumpMove)
	self:addMovePower(PowerName_Attack1)
	self:addMovePower(PowerName_Attack2)
	self:addMovePower(PowerName_Attack3)
	self:addMovePower(PowerName_Attack4)
	self:addMovePower(PowerName_Hit)

	self:setMovePower(PowerName_ControlMove, {x = 0, y = 0})
	self:setMovePower(PowerName_JumpMove, {x = 0, y = 0})
	self:setMovePower(PowerName_Attack1, Attack_Power[PowerName_Attack1])
	self:setMovePower(PowerName_Attack2, Attack_Power[PowerName_Attack2])
	self:setMovePower(PowerName_Attack3, Attack_Power[PowerName_Attack3])
	self:setMovePower(PowerName_Attack4, Attack_Power[PowerName_Attack4])
	self:setMovePower(PowerName_Hit, Hit_Power)

	self:setAllMovePowerEnable(false)
end

function Hero_dao:setMove(x, y)
	self:setMovePower(PowerName_ControlMove, {x = x, y = y})
	self:setMovePower(PowerName_JumpMove, {x = x * 0.5, y = 0})

	if x < 0 then
		local p_x = -Attack_Power[PowerName_Attack1].x
		local p_y = Attack_Power[PowerName_Attack1].y
		self:setMovePower(PowerName_Attack1, {x = p_x, y = p_y})

		p_x = -Attack_Power[PowerName_Attack2].x
		p_y = Attack_Power[PowerName_Attack2].y
		self:setMovePower(PowerName_Attack2, {x = p_x, y = p_y})

		p_x = -Attack_Power[PowerName_Attack3].x
		p_y = Attack_Power[PowerName_Attack3].y
		self:setMovePower(PowerName_Attack3, {x = p_x, y = p_y})

		p_x = -Attack_Power[PowerName_Attack4].x
		p_y = Attack_Power[PowerName_Attack4].y
		self:setMovePower(PowerName_Attack4, {x = p_x, y = p_y})
	else
		self:setMovePower(PowerName_Attack1, Attack_Power[PowerName_Attack1])
		self:setMovePower(PowerName_Attack2, Attack_Power[PowerName_Attack2])
		self:setMovePower(PowerName_Attack3, Attack_Power[PowerName_Attack3])
		self:setMovePower(PowerName_Attack4, Attack_Power[PowerName_Attack4])
	end
end

--------------------------------------FSM--------------------------------------

function Hero_dao:initFSM()

	--站立
	self.FSM:addTranslation("State_Run", "CMD_MoveStand", "State_Stand")

	--移动
	self.FSM:addTranslation("State_Stand", "CMD_MoveStart", "State_Run")

	--跳跃
	self.FSM:addTranslation("State_Stand", "CMD_JumpUpStart", "State_JumpUp")
	self.FSM:addTranslation("State_Run", "CMD_JumpUpStart", "State_JumpUp")
	self.FSM:addTranslation("State_Attack1", "CMD_JumpUpStart", "State_JumpUp")
	self.FSM:addTranslation("State_Attack2", "CMD_JumpUpStart", "State_JumpUp")
	self.FSM:addTranslation("State_Attack3", "CMD_JumpUpStart", "State_JumpUp")
	--self.FSM:addTranslation("State_Attack4", "CMD_JumpUpStart", "State_JumpUp")

	self.FSM:addTranslation("State_JumpUp", "CMD_JumpDownStart", "State_JumpDown")
	self.FSM:addTranslation("State_JumpDown", "CMD_JumpDownEnd", "State_JumpDownEnd")
	self.FSM:addTranslation("State_JumpDown", "CMD_JumpTo_MoveStart", "State_Run")
	self.FSM:addTranslation("State_JumpDownEnd", "State_JumpDownEnd_stop", "State_Stand")

	--换刀
	self.FSM:addTranslation("State_Stand", "CMD_change", "State_Replace")
	self.FSM:addTranslation("State_Run", "CMD_change", "State_Replace")
	self.FSM:addTranslation("State_Replace", "State_Replace_stop", "State_Stand")

	--受到攻击
	self.FSM:addTranslation("State_Stand", "CMD_hit", "State_Hit")
	self.FSM:addTranslation("State_Run", "CMD_hit", "State_Hit")
	self.FSM:addTranslation("State_Hit", "State_Hit_stop", "State_Stand")

	--受到攻击并倒地

	--普通攻击
	self.FSM:addTranslation("State_Stand", "CMD_Attack", "State_Attack1")
	self.FSM:addTranslation("State_Run", "CMD_Attack", "State_Attack1")
	self.FSM:addTranslation("State_Attack1", "State_Attack1_stop", "State_Stand")

	self.FSM:addTranslation("State_Stand", "CMD_To_Attack2", "State_Attack2")
	self.FSM:addTranslation("State_Attack2", "State_Attack2_stop", "State_Stand")

	self.FSM:addTranslation("State_Stand", "CMD_To_Attack3", "State_Attack3")
	self.FSM:addTranslation("State_Attack3", "State_Attack3_stop", "State_Stand")

	self.FSM:addTranslation("State_Stand", "CMD_To_Attack4", "State_Attack4")
	self.FSM:addTranslation("State_Attack4", "State_Attack4_stop", "State_Stand")

	self.FSM:addTranslation("State_Stand", "CMD_To_Attack1", "State_Attack1")

	--跳跃攻击
	self.FSM:addTranslation("State_JumpUp", "CMD_To_JumpAttack", "State_JumpAttack3")
	self.FSM:addTranslation("State_JumpAttack3", "State_JumpAttack3_stop", "State_JumpDown")
	self.FSM:addTranslation("State_JumpAttack3", "CMD_JumpTo_MoveStart", "State_Run")
	self.FSM:addTranslation("State_JumpAttack3", "CMD_JumpDownEnd", "State_JumpDownEnd")
end

function Hero_dao:enter_State_Stand()
	self:setAllMovePowerEnable(false)
end

function Hero_dao:enter_State_Run()
	self.isRun = true
	self:setAllMovePowerEnable(false)
	self:setMovePowerEnable(PowerName_ControlMove, true)
end

function Hero_dao:leave_State_Run()
	self.isRun = false
	self:setMovePowerEnable(PowerName_ControlMove, false)
end

function Hero_dao:enter_State_JumpUp()
	self.isJump = true
	self:setMovePowerEnable(PowerName_ControlMove, false)
	self:setMovePowerEnable(PowerName_JumpMove, true)
end

function Hero_dao:enter_State_JumpDownEnd()
	self.isJump = false
	self:setMovePowerEnable(PowerName_ControlMove, true)
	self:setMovePowerEnable(PowerName_JumpMove, false)
end

function Hero_dao:enter_State_Attack1()
	self.isAttack = true
	self:setMovePowerEnable(PowerName_ControlMove, false)
	self:setMovePowerEnable(PowerName_Attack1, true)
end

function Hero_dao:leave_State_Attack1()
	self.isAttack = false
	self:setMovePowerEnable(PowerName_ControlMove, true)
	self:setMovePowerEnable(PowerName_Attack1, false)
end

function Hero_dao:enter_State_Attack2()
	self.isAttack = true
	self:setMovePowerEnable(PowerName_ControlMove, false)
	self:setMovePowerEnable(PowerName_Attack2, true)
end

function Hero_dao:leave_State_Attack2()
	self.isAttack = false
	self:setMovePowerEnable(PowerName_ControlMove, true)
	self:setMovePowerEnable(PowerName_Attack2, false)
end

function Hero_dao:enter_State_Attack3()
	self.isAttack = true
	self:setMovePowerEnable(PowerName_ControlMove, false)
	self:setMovePowerEnable(PowerName_Attack3, true)
end

function Hero_dao:leave_State_Attack3()
	self.isAttack = false
	self:setMovePowerEnable(PowerName_ControlMove, true)
	self:setMovePowerEnable(PowerName_Attack3, false)
end

function Hero_dao:enter_State_Attack4()
	self.isAttack = true
	self:setMovePowerEnable(PowerName_ControlMove, false)
	self:setMovePowerEnable(PowerName_Attack4, true)
end

function Hero_dao:leave_State_Attack4()
	self.isAttack = false
	self:setMovePowerEnable(PowerName_ControlMove, true)
	self:setMovePowerEnable(PowerName_Attack4, false)
end

function Hero_dao:enter_State_Replace()
	self.movePowerEnableState = self:getAllMovePowerEnableState()
	self:setAllMovePowerEnable(false)
end

function Hero_dao:leave_State_Replace()
	self:setAllMovePowerEnableState(self.movePowerEnableState)
end

function Hero_dao:enter_State_Hit()
	self.movePowerEnableState = self:getAllMovePowerEnableState()
	self:setAllMovePowerEnable(false)
	self:setMovePowerEnable(PowerName_Hit, true)
	self:lockOrientation()
end

function Hero_dao:leave_State_Hit()
	self:setAllMovePowerEnableState(self.movePowerEnableState)
	self:unLockOrientation()
end

-----------------------------------------------------------------------------
function Hero_dao:override_updateArmatureInfo()
	self.super.override_updateArmatureInfo(self)
	if self.gameAttribute:getCurOrientation() == GAME_ORI_LEFT then
		self:setMovePower(PowerName_Hit, Hit_Power)
	else
		self:setMovePower(PowerName_Hit, {x = -Hit_Power.x, y = Hit_Power.y})
	end
end

return Hero_dao