
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
local PowerName_Collapse = "PowerName_Collapse" --向后倒


--攻击时移动属性
local Attack_Power = {}
Attack_Power[PowerName_Attack1] = {x = 10, y = 0}
Attack_Power[PowerName_Attack2] = {x = 15, y = 0}
Attack_Power[PowerName_Attack3] = {x = 15, y = 0}
Attack_Power[PowerName_Attack4] = {x = 20, y = 0}

--受到攻击时移动属性
local Hit_Power = CommonActorConfig.playerHitBackSpeed

--向后倒
local Collapse_Power = CommonActorConfig.playerCollapseMovePower


--------------------------------------override--------------------------------------

function Hero_dao:ctor()
	self.super.ctor(self)

	self.actionList = {}

	self.gameAttribute:setSpeed(CommonActorConfig.playerMoveSpeed.x, CommonActorConfig.playerMoveSpeed.y)

	self:setActorType(AT_PLAYER)


	self.actorSpeedController:setStopCondition(SC_CD_NONE)
	self.actorSpeedController:setGravityEnable(true)

	self.armatureSpeedController:setStopCondition(SC_CD_NONE)
	self.armatureSpeedController:setGravity(0, -800)
	-- self.armatureSpeedController:setGravityEnable(true)
	self.armatureSpeedController:setMinValue(0, 0)
	self.armatureSpeedController:setMinValueEnable(true)

	self:changeRole("hero_lanse_dao")
end

function Hero_dao:override_attOtherActorCallback(otherActor)

	if self:getMovePower(PowerName_Attack4).enable then
		otherActor:override_beAttacked(self, true)
	else
		otherActor:override_beAttacked(self, false)
	end
end

function Hero_dao:override_beAttacked(attackActor, isPickUp)
	self.super.override_beAttacked(self, attackActor, isPickUp)

	if not isPickUp then
		self:handle("CMD_hit")
	else
		local JumpUpTime = CommonActorConfig.playerCollapseJumpTime
		local JumpHeight = CommonActorConfig.playerCollapseJumpHeight
		if self:handle("CMD_Collapse") then
			local move = cc.MoveBy:create(JumpUpTime, {x = 0, y = JumpHeight})
			local call1 = cc.CallFunc:create(function()
				self:handle("CMD_To_Collapse2")
			end)
			local call2 = cc.CallFunc:create(function()
				self:handle("CMD_To_Collapse3")
			end)
			local q = cc.Sequence:create(move, call1, move:reverse(), call2)
			self:getArmature():runAction(q)
	
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
	self:addMovePower(PowerName_Collapse)

	self:setMovePower(PowerName_ControlMove, {x = 0, y = 0})
	self:setMovePower(PowerName_JumpMove, {x = 0, y = 0})
	self:setMovePower(PowerName_Attack1, {x = 0, y = 0})
	self:setMovePower(PowerName_Attack2, {x = 0, y = 0})
	self:setMovePower(PowerName_Attack3, {x = 0, y = 0})
	self:setMovePower(PowerName_Attack4, {x = 0, y = 0})
	self:setMovePower(PowerName_Hit, Hit_Power)
	self:setMovePower(PowerName_Collapse, Collapse_Power)

	self:setAllMovePowerEnable(false)
end

function Hero_dao:changeValueByOri(x)
	if self.gameAttribute:getCurOrientation() == GAME_ORI_LEFT then
		return -x
	end
	return x
end

function Hero_dao:setMoveStop()
	self:setMovePower(PowerName_ControlMove, {x = 0, y = 0})
	self:setMovePower(PowerName_JumpMove, {x = 0, y = 0})
	self:setMovePower(PowerName_Attack1, {x = 0, y = 0})
	self:setMovePower(PowerName_Attack2, {x = 0, y = 0})
	self:setMovePower(PowerName_Attack3, {x = 0, y = 0})
	self:setMovePower(PowerName_Attack4, {x = 0, y = 0})
end

function Hero_dao:setMove(x, y)
	self:setMovePower(PowerName_ControlMove, {x = x, y = y})
	self:setMovePower(PowerName_JumpMove, {x = x * 0.5, y = 0})


	if x > 0.0 then
		self:setOrientation(GAME_ORI_RIGHT)
	elseif x < 0.0 then
		self:setOrientation(GAME_ORI_LEFT)
	end




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

function Hero_dao:playActionByActionName(actionName, action, target)
	self:stopActionByActionName(actionName)
	self.actionList[actionName] = {target = target, action = action}

	local clearAction = cc.CallFunc:create(function() self:stopActionByActionName(actionName) end)
	target:runAction(cc.Sequence:create(action, clearAction))
end

function Hero_dao:playMoveAction(actionName, target, movepos, time, autoOrientation, actionEaseFunc)

	if autoOrientation then
		if self.gameAttribute:getCurOrientation() == GAME_ORI_LEFT then
			movepos.x = -movepos.x
		end
	end

	local action = cc.MoveBy:create(time, movepos)
	
	if actionEaseFunc ~= nil then
		action = actionEaseFunc(action)
	end
	self:playActionByActionName(actionName, action, target) 
end

function Hero_dao:stopActionByActionName(actionName)
	if self.actionList[actionName] == nil then
		return
	end
	local action = self.actionList[actionName].action
	if action then
		self.actionList[actionName].target:stopAction(action)
		self.actionList[actionName].action = nil
	end
end

function Hero_dao:jump()
	if self:handle("CMD_JumpUpStart") then
		self.armatureSpeedController:setForce(0, 700)
		self.armatureSpeedController:setForceEnable(true)
		self.armatureSpeedController:setFriction(100)
		self.armatureSpeedController:setFrictionEnable(true)

		local tage = 0

		self.armatureSpeedController:resetCallForceZero()
		self.armatureSpeedController:setEventCall(function(eventName)
			if eventName == "forceZero" then
				if tage == 0 then
					self:handle("CMD_JumpDownStart")
					self.armatureSpeedController:setForce(0, -700)
					self.armatureSpeedController:setFriction(-100)
					self.armatureSpeedController:resetCallForceZero()
				else
					self:handle("CMD_JumpDownEnd")
				end
				tage = tage + 1
			end
		end)
	end
end

--------------------------------------FSM--------------------------------------

function Hero_dao:initFSM()

	--站立
	self.FSM:addTranslation("State_Run", "CMD_MoveStand", "State_Stand")
	self.FSM:addTranslation("State_Run2", "CMD_MoveStand", "State_Brak")
	self.FSM:addTranslation("State_Brak", "State_Brak_stop", "State_Stand")

	--移动
	self.FSM:addTranslation("State_Stand", "CMD_MoveStart", "State_Run")
	self.FSM:addTranslation("State_Brak", "CMD_MoveStart", "State_Run")
	self.FSM:addTranslation("State_Run", "State_Run_stop", "State_Run2")

	--跳跃
	self.FSM:addTranslation("State_Stand", "CMD_JumpUpStart", "State_JumpUp")
	self.FSM:addTranslation("State_Run", "CMD_JumpUpStart", "State_JumpUp")
	self.FSM:addTranslation("State_Run2", "CMD_JumpUpStart", "State_JumpUp")
	self.FSM:addTranslation("State_Brak", "CMD_JumpUpStart", "State_JumpUp")
	self.FSM:addTranslation("State_Attack1", "CMD_JumpUpStart", "State_Upcut")
	self.FSM:addTranslation("State_Attack2", "CMD_JumpUpStart", "State_Upcut")
	self.FSM:addTranslation("State_Attack3", "CMD_JumpUpStart", "State_Upcut")
	--self.FSM:addTranslation("State_Attack4", "CMD_JumpUpStart", "State_JumpUp")

	self.FSM:addTranslation("State_Upcut", "CMD_JumpDownStart", "State_JumpDown")
	self.FSM:addTranslation("State_Upcut", "CMD_JumpDownEnd", "State_JumpDownEnd")
	self.FSM:addTranslation("State_Upcut", "CMD_JumpTo_MoveStart", "State_Run")
	self.FSM:addTranslation("State_Upcut", "State_JumpDownEnd_stop", "State_Stand")


	self.FSM:addTranslation("State_JumpUp", "CMD_JumpDownStart", "State_JumpDown")
	self.FSM:addTranslation("State_JumpDown", "CMD_JumpDownEnd", "State_JumpDownEnd")
	self.FSM:addTranslation("State_JumpDown", "CMD_JumpTo_MoveStart", "State_Run")
	self.FSM:addTranslation("State_JumpDownEnd", "State_JumpDownEnd_stop", "State_Stand")

	--换刀
	self.FSM:addTranslation("State_Stand", "CMD_change", "State_Replace")
	self.FSM:addTranslation("State_Run", "CMD_change", "State_Replace")
	self.FSM:addTranslation("State_Run2", "CMD_change", "State_Replace")
	self.FSM:addTranslation("State_Brak", "CMD_change", "State_Replace")
	self.FSM:addTranslation("State_Replace", "State_Replace_stop", "State_Stand")

	--受到攻击
	self.FSM:addTranslation("State_Stand", "CMD_hit", "State_Hit")
	self.FSM:addTranslation("State_Run", "CMD_hit", "State_Hit")
	self.FSM:addTranslation("State_Run2", "CMD_hit", "State_Hit")
	self.FSM:addTranslation("State_Brak", "CMD_hit", "State_Hit")
	self.FSM:addTranslation("State_Hit", "State_Hit_stop", "State_Stand")

	--受到攻击并向后倒
	self.FSM:addTranslation("State_Stand", "CMD_Collapse", "State_Collapse1")
	self.FSM:addTranslation("State_Run", "CMD_Collapse", "State_Collapse1")
	self.FSM:addTranslation("State_Run2", "CMD_Collapse", "State_Collapse1")
	self.FSM:addTranslation("State_Brak", "CMD_Collapse", "State_Collapse1")

	self.FSM:addTranslation("State_Collapse1", "CMD_To_Collapse2", "State_Collapse2")
	self.FSM:addTranslation("State_Collapse2", "CMD_To_Collapse3", "State_Collapse3")
	self.FSM:addTranslation("State_Collapse3", "State_Collapse3_stop", "State_Stand")

	--普通攻击
	self.FSM:addTranslation("State_Stand", "CMD_Attack", "State_Attack1")
	self.FSM:addTranslation("State_Run", "CMD_Attack", "State_Attack1")
	self.FSM:addTranslation("State_Run2", "CMD_Attack", "State_Attack1")
	self.FSM:addTranslation("State_Brak", "CMD_Attack", "State_Attack1")

	self.FSM:addTranslation("State_Stand", "CMD_To_Attack1", "State_Attack1")
	self.FSM:addTranslation("State_Attack1", "State_Attack1_stop", "State_Stand")

	self.FSM:addTranslation("State_Stand", "CMD_To_Attack2", "State_Attack2")
	self.FSM:addTranslation("State_Attack2", "State_Attack2_stop", "State_Stand")

	self.FSM:addTranslation("State_Stand", "CMD_To_Attack3", "State_Attack3")
	self.FSM:addTranslation("State_Attack3", "State_Attack3_stop", "State_Stand")

	self.FSM:addTranslation("State_Stand", "CMD_To_Attack4", "State_Attack4")
	self.FSM:addTranslation("State_Attack4", "State_Attack4_stop", "State_Stand")

	--跳跃攻击
	self.FSM:addTranslation("State_JumpUp", "CMD_To_JumpAttack", "State_JumpAttack3")
	self.FSM:addTranslation("State_JumpAttack3", "State_JumpAttack3_stop", "State_JumpDown")
	self.FSM:addTranslation("State_JumpAttack3", "CMD_JumpTo_MoveStart", "State_Run")
	self.FSM:addTranslation("State_JumpAttack3", "CMD_JumpDownEnd", "State_JumpDownEnd")
end

function Hero_dao:enter_State_Stand()
	self:setAllMovePowerEnable(false)

	-- if self.actorSpeedController:isForceEnable() then

	-- end

	local movePower = self:getMovePower(PowerName_ControlMove)
	if movePower and math.abs(movePower.power.x) > 0.1 then
		local call = cc.CallFunc:create(function()
			self:handle("CMD_MoveStart")
		end)
		self:runAction(call)
	end
end

function Hero_dao:enter_State_Run()
	self.isRun = true

	local x = self:changeValueByOri(CommonActorConfig.playerMoveSpeed.x * 0.9)
	local y = CommonActorConfig.playerMoveSpeed.y
	self.actorSpeedController:setGravity(x, y)
end

function Hero_dao:leave_State_Run()
	self.isRun = false
	self.actorSpeedController:setGravity(0, 0)
end

function Hero_dao:enter_State_Run2()
	self.isRun = true
	local x = self:changeValueByOri(CommonActorConfig.playerMoveSpeed.x)
	local y = CommonActorConfig.playerMoveSpeed.y
	self.actorSpeedController:setGravity(x, y)
end

function Hero_dao:leave_State_Run2()
	self.isRun = false
	self.actorSpeedController:setGravity(0, 0)
end

function Hero_dao:enter_State_Brak()

	local forcex = 800
	if self.gameAttribute:getCurOrientation() == GAME_ORI_LEFT then
		forcex = -forcex
	end
	self.actorSpeedController:setForce(forcex, 0)
	self.actorSpeedController:setForceEnable(true)
	self.actorSpeedController:setForceMinValue(0, 0)
	self.actorSpeedController:setForceMinValueEnable(true)
	self.actorSpeedController:setFriction(700)
	self.actorSpeedController:setFrictionEnable(true)
end

function Hero_dao:leave_State_Brak()
	self.actorSpeedController:setForceEnable(false)
	self.actorSpeedController:setForceMinValueEnable(false)
	self.actorSpeedController:setFrictionEnable(false)
end

function Hero_dao:enter_State_JumpUp()
	self.isJump = true
	self:setMovePowerEnable(PowerName_ControlMove, false)
	self:setMovePowerEnable(PowerName_JumpMove, true)
end

function Hero_dao:enter_State_JumpDownEnd()
	self.isJump = false
	self:setMovePowerEnable(PowerName_ControlMove, false)
	self:setMovePowerEnable(PowerName_JumpMove, false)
end

local attack_move_func_time = 0
local attack_move_func_total_time = 0
local attack_move_x = 0
local function attack_move_func(move, time)
	if attack_move_func_time > attack_move_func_total_time then
		return
	end
	if math.abs(move.x) < 1 then
		return
	end
	if attack_move_func_time == 0 then
		attack_move_x = move.x
	end
	attack_move_func_time = attack_move_func_time + time
	attack_move_x = attack_move_x + attack_move_x * attack_move_func_time
	return {x = attack_move_x, y = 0}
end

function Hero_dao:enter_State_Attack1()

	local power = self:getMovePower(PowerName_Attack1)
	if power then
		power.enable = true
		power.func = attack_move_func
		attack_move_func_time = 0
		attack_move_func_total_time = 0.4
	end

	self.isAttack = true
	self:setMovePowerEnable(PowerName_ControlMove, false)
end

function Hero_dao:leave_State_Attack1()
	self.isAttack = false
	self:setMovePowerEnable(PowerName_ControlMove, true)
	self:setMovePowerEnable(PowerName_Attack1, false, true)

	-- self:setActorPosition(self:getActorPositionX() + 40, self:getActorPositionY())
end

function Hero_dao:enter_State_Attack2()

	local power = self:getMovePower(PowerName_Attack2)
	if power then
		power.enable = true
		power.func = attack_move_func
		attack_move_func_time = 0
		attack_move_func_total_time = 0.3
	end

	self.isAttack = true
	self:setMovePowerEnable(PowerName_ControlMove, false)
end

function Hero_dao:leave_State_Attack2()
	self.isAttack = false
	self:setMovePowerEnable(PowerName_ControlMove, true)
	self:setMovePowerEnable(PowerName_Attack2, false, true)
end

function Hero_dao:enter_State_Attack3()
	local power = self:getMovePower(PowerName_Attack3)
	if power then
		power.enable = true
		power.func = attack_move_func
		attack_move_func_time = 0
		attack_move_func_total_time = 0.3
	end
	self.isAttack = true
	self:setMovePowerEnable(PowerName_ControlMove, false)
end

function Hero_dao:leave_State_Attack3()
	self.isAttack = false
	self:setMovePowerEnable(PowerName_ControlMove, true)
	self:setMovePowerEnable(PowerName_Attack3, false, true)
end

function Hero_dao:enter_State_Attack4()
	local power = self:getMovePower(PowerName_Attack4)
	if power then
		power.enable = true
		power.func = attack_move_func
		attack_move_func_time = 0
		attack_move_func_total_time = 0.4
	end
	self.isAttack = true
	self:setMovePowerEnable(PowerName_ControlMove, false)
end

function Hero_dao:leave_State_Attack4()
	self.isAttack = false
	self:setMovePowerEnable(PowerName_ControlMove, true)
	self:setMovePowerEnable(PowerName_Attack4, false, true)
end

function Hero_dao:enter_State_Replace()
	self:lockOrientation()
end

function Hero_dao:leave_State_Replace()
	self:unLockOrientation()
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

function Hero_dao:enter_State_Collapse1()
	self:setMovePowerEnable(PowerName_Collapse, true)
	self:lockOrientation()
end

function Hero_dao:leave_State_Collapse2()
	self:setMovePowerEnable(PowerName_Collapse, false)
	self:unLockOrientation()
end

function Hero_dao:leave_State_Collapse3()
	self:unLockOrientation()
end


-----------------------------------------------------------------------------
function Hero_dao:override_updateArmatureInfo()
	self.super.override_updateArmatureInfo(self)
	if self.gameAttribute:getCurOrientation() == GAME_ORI_LEFT then
		self:setMovePower(PowerName_Hit, {x = -Hit_Power.x, y = Hit_Power.y})
		self:setMovePower(PowerName_Collapse, {x = -Collapse_Power.x, y = Collapse_Power.y})
	else
		self:setMovePower(PowerName_Hit, Hit_Power)
		self:setMovePower(PowerName_Collapse, Collapse_Power)
	end
end

return Hero_dao