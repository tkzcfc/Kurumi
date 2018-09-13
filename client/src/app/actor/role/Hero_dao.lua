
local LuaGameActor = require("app.actor.LuaGameActor")

local Hero_dao = class("Hero_dao", LuaGameActor)


-----------------------------------------------------------------------------------

local RoleConfig = require("app.config.RoleConfig")
local CommonActorConfig = require("app.config.CommonActorConfig")


--------------------------------------override--------------------------------------

function Hero_dao:ctor()
	Hero_dao.super.ctor(self)

	self:setActorType(AT_PLAYER)
	self:override_forceSwitchClean()

	self:enableMoveCmd(true)
end

function Hero_dao:onEnter()
	Hero_dao.super.onEnter(self)
end

function Hero_dao:onExit()
	Hero_dao.super.onExit(self)
	self:disenableMapYChange()
end

function Hero_dao:override_attOtherActorCallback(otherActor)

	local stateName = self.FSM:getCurState():getStateName()

	if stateName == "State_Attack4" 
	or stateName == "State_Upcut" then
		otherActor:override_beAttacked(self, true)
	else
		otherActor:override_beAttacked(self, false)
	end
end

function Hero_dao:override_beAttacked(attackActor, isPickUp)
	Hero_dao.super.override_beAttacked(self, attackActor, isPickUp)

	if not isPickUp and not self.isJump then
		if self.FSM:getCurState():getStateName() ~= "State_Hit" then
			self:forceSwitch("State_Hit")
		end
	else
		local curStateName = self.FSM:getCurState():getStateName()
		if curStateName == "State_Collapse1" or curStateName == "State_Collapse2" or curStateName == "State_Collapse3" then
			return
		end

		self:enableMapYChange()

		local armature = self:getArmature()
		local armaturePreY = armature:getPositionY()


		local JumpUpTime = CommonActorConfig.playerCollapseJumpTime
		local JumpHeight = CommonActorConfig.playerCollapseJumpHeight
		if self:forceSwitch("State_Collapse1") then

			armature:stopAllActions()
			armature:setPositionY(armaturePreY)

			local move1 = cc.MoveTo:create(JumpUpTime, {x = 0, y = JumpHeight})
			local move2 = cc.MoveTo:create(JumpUpTime, {x = 0, y = 0})
			local q1 = cc.Sequence:create(move1, move2)
			armature:runAction(q1)

			local call1 = cc.CallFunc:create(function()
				self:handle("CMD_To_Collapse2")
			end)
			local call2 = cc.CallFunc:create(function()
				self:handle("CMD_To_Collapse3")
			end)
			local q2 = cc.Sequence:create(cc.DelayTime:create(JumpUpTime),
										  call1, 
										  cc.DelayTime:create(JumpUpTime * 0.7), 
										  call2)
			armature:runAction(q2)
		end
	end
	self.isJump = false
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
	self.isAttack1 = false
	self.isAttack2 = false
	self.isAttack3 = false
	self.isAttack4 = false

	self:initFSM()

	self.FSM:start("State_Stand")
end

function Hero_dao:setMoveStop()
	self.startMoveCMD = false
	-- self.actorSpeedController:setGravityEnable(false)
	-- self.actorSpeedController:setForceEnable(false)
end

function Hero_dao:setMove(x, y)
	self.startMoveCMD = true
	-- self.actorSpeedController:setGravityEnable(self.isEnableRecvMoveCMD)

	local posotiveX = 0
	if x > 0.0 then
		self:setOrientation(GAME_ORI_RIGHT)
		posotiveX = 1
		self:getB2Body():ApplyForceToCenter({x = 200, y = 0}, true)
		print("right")
	elseif x < 0.0 then
		self:setOrientation(GAME_ORI_LEFT)
		posotiveX = -1
		self:getB2Body():ApplyForceToCenter({x = -200, y = 0}, true)
		print("left")
	end

	-- self.actorSpeedController:setGravityPositive(posotiveX, 0)
	-- self.armatureSpeedController:setGravityPositive(posotiveX, 0)
end

function Hero_dao:enableMoveCmd(enable)
	self.isEnableRecvMoveCMD = enable
	-- self.actorSpeedController:setGravityEnable(enable)
end

function Hero_dao:jump()
	-- if self:handle("CMD_JumpUpStart") then
	-- 	self:enableMapYChange()

	-- 	self.armatureSpeedController:setStopUpdate(false)
	-- 	self.armatureSpeedController:setForceEnable(true)
	-- 	self.armatureSpeedController:setFrictionEnable(true)

	-- 	local isUpCut = false

	-- 	if self.FSM:getCurState():getStateName() == "State_Upcut" then
	-- 		self.armatureSpeedController:setForce(0, 10)
	-- 		self.armatureSpeedController:setFriction(-100)
	-- 		isUpCut = true
	-- 	else
	-- 		self.armatureSpeedController:setForce(0, 2000)
	-- 		self.armatureSpeedController:setFriction(2000)
	-- 	end

	-- 	local stage = 0
	-- 	local jumpTime = 0
	-- 	if isUpCut then
	-- 		stage = -2
	-- 	end

	-- 	local function jumpFinishCall()
	-- 		self.armatureSpeedController:setStopUpdate(true)
	-- 		self.armatureSpeedController:clearLuaUpdateCall()
	-- 		self.armatureSpeedController:setForceEnable(false)
	-- 		self.armatureSpeedController:setFrictionEnable(false)

	-- 		--print("stage == 3")
	-- 		if self.actorSpeedController:isGravityEnable() 
	-- 			and math.abs(self.actorSpeedController:getGravityX()) > 0 then
	-- 			self:handle("CMD_JumpTo_MoveStart")
	-- 		else
	-- 			self:handle("CMD_JumpDownEnd")
	-- 		end
	-- 	end

	-- 	self.armatureSpeedController:setLuaUpdateCall(function(x, y, time)

	-- 		jumpTime = jumpTime + time

	-- 		if stage == -2 and jumpTime > 0.15 then
	-- 			self.armatureSpeedController:setForce(0, 0)
	-- 			self.armatureSpeedController:setFriction(0)
	-- 			stage = -1
	-- 		end
	-- 		if stage == -1 and jumpTime > 0.27 then
	-- 			self.armatureSpeedController:setForce(0, 700)
	-- 			self.armatureSpeedController:setFriction(-2000)
	-- 			stage = 0
	-- 		end

	-- 		local curHeight = self.armatureSpeedController:getTarget():getPositionY()

	-- 		if stage == 0 then
	-- 			if not isUpCut then
	-- 				if self.armatureSpeedController:getAppendY() < 0 then
	-- 					self:handle("CMD_JumpDownStart")
	-- 					stage = 1
	-- 				end
	-- 			else
	-- 				if curHeight >= 350 then
	-- 					self.armatureSpeedController:setForce(0, 830)
	-- 					self.armatureSpeedController:setFriction(2000)
	-- 					self:handle("CMD_JumpDownStart")
	-- 					stage = 1
	-- 					--print("stage == 1")
	-- 				end
	-- 			end
	-- 		end
	-- 		if stage == 1 and self.armatureSpeedController:getForceY() <= 400 then
	-- 			self.armatureSpeedController:setForce(0, -10)
	-- 			self.armatureSpeedController:setFriction(-500)
	-- 			stage = 2
	-- 			--print("stage == 2")
	-- 		end
	-- 		if y == 0 then
	-- 			if isUpCut then
	-- 				if stage > 0 then
	-- 					jumpFinishCall()
	-- 				end
	-- 			else
	-- 				jumpFinishCall()
	-- 			end
	-- 		end
	-- 	end)
	-- end
end

function Hero_dao:enableMapYChange()

	local word = getGameWord()
	if word == nil or word:getLocalPlayer() ~= self then
		return
	end

	if self.scriptEntryID_UpdateMapY then
		return
	end

	local scheduler=cc.Director:getInstance():getScheduler()
    self.scriptEntryID_UpdateMapY = scheduler:scheduleScriptFunc(function(...) self:updateMapYPosition(...) end,1 / 40.0,false)

	local percent = 1.0
	local gameword = getGameWord()
	self.mapRootNode = gameword:getGameMap()

	local winSize = cc.Director:getInstance():getVisibleSize()
	local subheight = gameword:getMapSize().height - winSize.height
	
	subheight = subheight * 0.5
	subheight = math.min(subheight, CommonActorConfig.playerMaxHeight)
	self.mapYpercent = subheight / CommonActorConfig.playerMaxHeight
end

function Hero_dao:disenableMapYChange()
	if self.scriptEntryID_UpdateMapY then
		local scheduler=cc.Director:getInstance():getScheduler()
		scheduler:unscheduleScriptEntry(self.scriptEntryID_UpdateMapY)
	end
	self.scriptEntryID_UpdateMapY = nil
end

function Hero_dao:updateMapYPosition()
	if self.mapYpercent == nil then
		self.mapYpercent = 0.0
	end
	local curHeight = -self:getArmature():getPositionY()
	self.mapRootNode:setPositionY(curHeight * self.mapYpercent)
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

	-- self.FSM:addTranslation("State_Stand", "CMD_MoveStart", "State_Run2")
	-- self.FSM:addTranslation("State_Brak", "CMD_MoveStart", "State_Run2")

	--跳跃
	self.FSM:addTranslation("State_Stand", "CMD_JumpUpStart", "State_JumpUp")
	self.FSM:addTranslation("State_Run", "CMD_JumpUpStart", "State_JumpUp")
	self.FSM:addTranslation("State_Run2", "CMD_JumpUpStart", "State_JumpUp")
	self.FSM:addTranslation("State_Brak", "CMD_JumpUpStart", "State_JumpUp")
	-- self.FSM:addTranslation("State_Attack1", "CMD_JumpUpStart", "State_Upcut")
	-- self.FSM:addTranslation("State_Attack2", "CMD_JumpUpStart", "State_Upcut")
	-- self.FSM:addTranslation("State_Attack3", "CMD_JumpUpStart", "State_Upcut")

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
	self.FSM:addTranslation("State_Hit", "State_Hit_stop", "State_Stand")

	--受到攻击并向后倒
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
	self.FSM:addTranslation("State_JumpUp", "CMD_Attack", "State_JumpAttack3")
	self.FSM:addTranslation("State_JumpAttack3", "State_JumpAttack3_stop", "State_JumpDown")
	self.FSM:addTranslation("State_JumpAttack3", "CMD_JumpTo_MoveStart", "State_Run")
	self.FSM:addTranslation("State_JumpAttack3", "CMD_JumpDownEnd", "State_JumpDownEnd")
end

--强制切换清理
function Hero_dao:override_forceSwitchClean()
	Hero_dao.super.override_forceSwitchClean(self)

	-- self.actorSpeedController:defaultValue()
	-- self.actorSpeedController:setStopUpdate(false)
	-- self.actorSpeedController:setGravityEnable(true)

	-- self.armatureSpeedController:defaultValue()
	-- self.armatureSpeedController:setStopUpdate(false)
	-- self.armatureSpeedController:setGravity(0, -800)
	-- self.armatureSpeedController:setGravityEnable(true)
	-- self.armatureSpeedController:setMinValue(0, 0)
	-- self.armatureSpeedController:setMinValueEnable(true)

	local armature = self:getArmature()
	if armature then
		armature:setPosition({x = 0, y = 0})
		armature:stopAllActions()
	end
	
	local word = getGameWord()
	if word then
		word:getGameMap():setPositionY(0)
		word:getGameMap():stopAllActions()
	end
end

function Hero_dao:enter_State_Stand()
	-- if self.actorSpeedController:isGravityEnable() and math.abs(self.actorSpeedController:getGravityX()) > 0 then
	-- if self.startMoveCMD then
	-- 	local call = cc.CallFunc:create(function()
	-- 		self:handle("CMD_MoveStart")
	-- 	end)
	-- 	self:runAction(call)
	-- else
	-- 	self.actorSpeedController:setGravity(0, 0)
	-- end
end

function Hero_dao:enter_State_Run()
	self.isRun = true

	local x = self:changeValueByOri(CommonActorConfig.playerMoveSpeed.x * 0.9)
	local y = CommonActorConfig.playerMoveSpeed.y
	-- self.actorSpeedController:setGravity(x, y)
end

function Hero_dao:leave_State_Run()
	self.isRun = false
	-- self.actorSpeedController:setGravity(0, 0)
end

function Hero_dao:enter_State_Run2()
	self.isRun = true
	local x = self:changeValueByOri(CommonActorConfig.playerMoveSpeed.x)
	local y = CommonActorConfig.playerMoveSpeed.y
	-- self.actorSpeedController:setGravity(x, y)
end

function Hero_dao:leave_State_Run2()
	self.isRun = false
	-- self.actorSpeedController:setGravity(0, 0)
end

function Hero_dao:enter_State_Brak()
	-- self.actorSpeedController:setForce(self:changeValueByOri(800), 0)
	-- self.actorSpeedController:setForceEnable(true)
	-- self.actorSpeedController:setFriction(700)
end

function Hero_dao:leave_State_Brak()
	-- self.actorSpeedController:setForce(0, 0)
	-- self.actorSpeedController:setFriction(0)
	-- self.actorSpeedController:setForceEnable(false)
end

function Hero_dao:enter_State_JumpUp()
	self.isJump = true
	local x = self:changeValueByOri(CommonActorConfig.playerMoveSpeed.x * 0.5)
	local y = CommonActorConfig.playerMoveSpeed.y
	-- self.actorSpeedController:setGravity(x, y)
end

function Hero_dao:enter_State_JumpDownEnd()
	self.isJump = false
end

function Hero_dao:com_enter_attack()
	self:enableMoveCmd(false)
	-- self.actorSpeedController:setForceEnable(true)
end

function Hero_dao:com_leave_attack()
	self:enableMoveCmd(true)
	-- self.actorSpeedController:setForceEnable(false)
	-- self.actorSpeedController:setForce(0, 0)
	-- self.actorSpeedController:setFriction(0)
	-- self.actorSpeedController:clearLuaUpdateCall()
end

function Hero_dao:enter_State_Attack1()
	self.isAttack1 = true
	self:com_enter_attack()
end

function Hero_dao:leave_State_Attack1()
	self.isAttack1 = false
	self:com_leave_attack()
end

function Hero_dao:enter_State_Attack2()
	self.isAttack2 = true
	self:com_enter_attack()
end

function Hero_dao:leave_State_Attack2()
	self.isAttack2 = false
	self:com_leave_attack()
end

function Hero_dao:enter_State_Attack3()
	self.isAttack3 = true
	self:com_enter_attack()
end

function Hero_dao:leave_State_Attack3()
	self.isAttack3 = false
	self:com_leave_attack()
end

function Hero_dao:enter_State_Attack4()
	self.isAttack4 = true
	self:lockOrientation()
	self:com_enter_attack()
	-- self.actorSpeedController:setForce(self:changeValueByOri(120), 0)
	-- self.actorSpeedController:setFriction(-1500)
	-- self.actorSpeedController:setLuaUpdateCall(function(x, y, time)
	-- 	local tmp = self.actorSpeedController:getAppendX()
	-- 	if math.abs(tmp) >= 3 then
	-- 		self.actorSpeedController:clearLuaUpdateCall()
	-- 		self.actorSpeedController:setForce(0, 0)
	-- 		self.actorSpeedController:setFriction(0)
	-- 	end
	-- end)
end

function Hero_dao:leave_State_Attack4()
	self.isAttack4 = false
	self:unLockOrientation()
	self:com_leave_attack()
end

function Hero_dao:enter_State_Replace()
	self:lockOrientation()
end

function Hero_dao:leave_State_Replace()
	self:unLockOrientation()
end

-- function Hero_dao:enter_State_Hit()
-- 	self.actorSpeedController:setGravityEnable(false)
-- 	self.actorSpeedController:setForceEnable(true)
-- 	self.actorSpeedController:setFrictionEnable(true)
-- 	self.actorSpeedController:setForce(self:changeValueByOri(-100), 0)
-- 	self.actorSpeedController:setFriction(300)
-- 	self:lockOrientation()
-- end

-- function Hero_dao:leave_State_Hit()
-- 	self.actorSpeedController:setGravityEnable(true)
-- 	self.actorSpeedController:setForceEnable(false)
-- 	self.actorSpeedController:setFrictionEnable(false)
-- 	self.actorSpeedController:setForce(0, 0)
-- 	self.actorSpeedController:setFriction(0)
-- 	self:unLockOrientation()
-- end

-- function Hero_dao:enter_State_Collapse1()
-- 	self.actorSpeedController:setGravityEnable(false)
-- 	self.actorSpeedController:setForceEnable(true)
-- 	self.actorSpeedController:setFrictionEnable(true)
-- 	self.actorSpeedController:setForce(self:changeValueByOri(-200), 0)
-- 	self.actorSpeedController:setFriction(150)
-- 	self:lockOrientation()
-- end

-- function Hero_dao:leave_State_Collapse2()
-- 	self.actorSpeedController:setGravityEnable(true)
-- 	self.actorSpeedController:setForceEnable(false)
-- 	self.actorSpeedController:setFrictionEnable(false)
-- 	self.actorSpeedController:setForce(0, 0)
-- 	self.actorSpeedController:setFriction(0)
-- 	self:unLockOrientation()
-- end

-- function Hero_dao:leave_State_Collapse3()
-- 	self.actorSpeedController:setGravityEnable(true)
-- 	self:unLockOrientation()
-- end

return Hero_dao