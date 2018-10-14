
local LuaGameCharacter = require("app.actor.LuaGameCharacter")

local Hero_dao = class("Hero_dao", LuaGameCharacter)


-----------------------------------------------------------------------------------

local RoleConfig = require("app.config.RoleConfig")
local CommonActorConfig = require("app.config.CommonActorConfig")


--------------------------------------override--------------------------------------

function Hero_dao:ctor()
	Hero_dao.super.ctor(self)

	self:setActorType(AT_PLAYER)
	self:override_forceSwitchClean()
end

function Hero_dao:onEnter()
	Hero_dao.super.onEnter(self)
end

function Hero_dao:onExit()
	Hero_dao.super.onExit(self)
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

	if not isPickUp then
		if self:handle("CMD_Hit") then
			self:clearStateData()
		end
	else
		if self:handle("CMD_Collapse") then
			self:clearStateData()
		end
	end
end

function Hero_dao:override_logicUpdate(time)
	Hero_dao.super.override_logicUpdate(self, time)

	local curStateName = self.FSM:getCurState():getStateName()
	-- 奔跑状态
	if curStateName == "State_Run" or curStateName == "State_Run2" then
		self:setVelocityXInStartMoveCMD(CommonActorConfig.MoveVelocity)
	else
		if self.isJump then
			if self.isJumpAttack then
				local impulse_y = self.b2Body:GetMass() * CommonActorConfig.AttackInAirDescentVelocity * PHYSICS_WORLD_FPS
				if self.startMoveCMD then
					self:setVelocityXYByImpulse(self:getVelocityByOrientation(CommonActorConfig.AttackInAirMoveVelocity), impulse_y)
				else
					self:setVelocityYByImpulse(impulse_y)
					self:clearForceX()
				end
			else
				if curStateName == "State_JumpUp" or curStateName == "State_JumpUp_2" then
					if self.b2Body:GetLinearVelocity().y <= 0 then
						self:handle("CMD_JumpDownStart")
					end
				elseif curStateName == "State_JumpDown" and not self:isInAir() then
					self.isJump = false
					self.jumpCountInAir = 0
					self.jumAttackCount = 0
					if self.startMoveCMD then
						self:handle("CMD_JumpTo_MoveStart")
					else
						self:handle("CMD_JumpDownEnd")
					end
				end
				self:setVelocityXInStartMoveCMD(CommonActorConfig.JumMoveVelocity)
			end
		elseif self.isAttack2 then
			self:setVelocityXInStartMoveCMD(CommonActorConfig.Attacl_2_MoveImpulse)
		elseif self.isAttack3 then
			self:setVelocityXInStartMoveCMD(CommonActorConfig.Attacl_3_MoveImpulse)
		elseif self.isUpcut then
			self:setVelocityYByImpulse(CommonActorConfig.Upcut_Impulse)
		end
		if self.isCollapse then
			if not self:isInAir() then
				self:handle("CMD_To_Collapse3")
			end
		end
	end
end

function Hero_dao:setVelocityXInStartMoveCMD(impulse)				
	if self.startMoveCMD then
		self:setVelocityXByImpulse(self:getVelocityByOrientation(impulse))
	else
		self:clearForceX()
	end
end
--------------------------------------logic--------------------------------------

function Hero_dao:clearStateData()
	self.isRun = false
	self.isJump = false
	self.isJumpAttack = false
	self.isAttack1 = false
	self.isAttack2 = false
	self.isAttack3 = false
	self.isAttack4 = false
	self.isUpcut = false
	self.isCollapse = false
	-- 跳跃次数
	self.jumpCountInAir = 0
	-- 跳跃攻击次数
	self.jumAttackCount = 0
end

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

	self:clearStateData()

	self:initFSM()

	self.FSM:start("State_Stand")
end

function Hero_dao:control_cancel()
	self.startMoveCMD = false
	self:clearForceX()
	self:handle("CMD_MoveStand")
end

function Hero_dao:control_left()
	self.startMoveCMD = true
	self:setOrientation(GAME_ORI_LEFT)
	self:handle("CMD_MoveStart")
end

function Hero_dao:control_right()
	self.startMoveCMD = true
	self:setOrientation(GAME_ORI_RIGHT)
	self:handle("CMD_MoveStart")
end

function Hero_dao:control_up()
	if self.jumpCountInAir >= CommonActorConfig.MAX_JUMP_COUNT_IN_AIR then
		return
	end
	if self:handle("CMD_JumpUpStart") then
		self.jumpCountInAir = self.jumpCountInAir + 1
	end
end

function Hero_dao:control_down()
	self:handle("CMD_DownCut")
end

function Hero_dao:attack()
	if self.isJump and not self.isJumpAttack then
		if self.jumAttackCount >= CommonActorConfig.MAX_ATTACK_COUNT_IN_AIR then
			return false
		end
	end
	return self:handle("CMD_Attack")
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
	self.FSM:addTranslation("State_JumpUp", "CMD_JumpUpStart", "State_JumpUp")
	self.FSM:addTranslation("State_JumpUp_2", "CMD_JumpUpStart", "State_JumpUp")
	self.FSM:addTranslation("State_JumpDown", "CMD_JumpUpStart", "State_JumpUp")
	
	self.FSM:addTranslation("State_Attack1", "CMD_JumpUpStart", "State_Upcut")
	self.FSM:addTranslation("State_Attack2", "CMD_JumpUpStart", "State_Upcut")
	self.FSM:addTranslation("State_Attack3", "CMD_JumpUpStart", "State_Upcut")
	self.FSM:addTranslation("State_Upcut", "State_Upcut_stop", "State_JumpUp_2")

	self.FSM:addTranslation("State_Attack1", "CMD_DownCut", "State_DownCut")
	self.FSM:addTranslation("State_Attack2", "CMD_DownCut", "State_DownCut")
	self.FSM:addTranslation("State_Attack3", "CMD_DownCut", "State_DownCut")
	self.FSM:addTranslation("State_DownCut", "State_DownCut_stop", "State_Stand")


	self.FSM:addTranslation("State_JumpUp", "CMD_JumpDownStart", "State_JumpDown")
	self.FSM:addTranslation("State_JumpUp_2", "CMD_JumpDownStart", "State_JumpDown")
	self.FSM:addTranslation("State_JumpDown", "CMD_JumpDownEnd", "State_JumpDownEnd")
	self.FSM:addTranslation("State_JumpDown", "CMD_JumpTo_MoveStart", "State_Run")
	self.FSM:addTranslation("State_JumpDownEnd", "State_JumpDownEnd_stop", "State_Stand")

	--换刀
	self.FSM:addTranslation("State_Stand", "CMD_change", "State_Replace")
	self.FSM:addTranslation("State_Run", "CMD_change", "State_Replace")
	self.FSM:addTranslation("State_Run2", "CMD_change", "State_Replace")
	self.FSM:addTranslation("State_Brak", "CMD_change", "State_Replace")
	self.FSM:addTranslation("State_Replace", "State_Replace_stop", "State_Stand")

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
	self.FSM:addTranslation("State_JumpDown", "CMD_Attack", "State_JumpAttack3")
	self.FSM:addTranslation("State_JumpAttack3", "State_JumpAttack3_stop", "State_JumpDown")

	--受到攻击
	self.FSM:addTranslation("State_Stand", "CMD_Hit", "State_Hit")
	self.FSM:addTranslation("State_Run", "CMD_Hit", "State_Hit")
	self.FSM:addTranslation("State_Run2", "CMD_Hit", "State_Hit")
	self.FSM:addTranslation("State_Brak", "CMD_Hit", "State_Hit")
	self.FSM:addTranslation("State_JumpUp", "CMD_Hit", "State_Collapse1")
	self.FSM:addTranslation("State_JumpDown", "CMD_Hit", "State_Collapse1")
	self.FSM:addTranslation("State_JumpDownEnd", "CMD_Hit", "State_Hit")
	self.FSM:addTranslation("State_JumpUp_2", "CMD_Hit", "State_Collapse1")
	self.FSM:addTranslation("State_Attack1", "CMD_Hit", "State_Hit")
	self.FSM:addTranslation("State_Attack2", "CMD_Hit", "State_Hit")
	self.FSM:addTranslation("State_Attack3", "CMD_Hit", "State_Hit")
	self.FSM:addTranslation("State_Attack4", "CMD_Hit", "State_Hit")

	self.FSM:addTranslation("State_Hit", "State_Hit_stop", "State_Stand")

	--受到攻击并向后倒
	self.FSM:addTranslation("State_Stand", "CMD_Collapse", "State_Collapse1")
	self.FSM:addTranslation("State_Run", "CMD_Collapse", "State_Collapse1")
	self.FSM:addTranslation("State_Run2", "CMD_Collapse", "State_Collapse1")
	self.FSM:addTranslation("State_Brak", "CMD_Collapse", "State_Collapse1")
	self.FSM:addTranslation("State_JumpUp", "CMD_Collapse", "State_Collapse1")
	self.FSM:addTranslation("State_JumpDown", "CMD_Collapse", "State_Collapse1")
	self.FSM:addTranslation("State_JumpDownEnd", "CMD_Collapse", "State_Collapse1")
	self.FSM:addTranslation("State_JumpUp_2", "CMD_Collapse", "State_Collapse1")
	self.FSM:addTranslation("State_Attack1", "CMD_Collapse", "State_Collapse1")
	self.FSM:addTranslation("State_Attack2", "CMD_Collapse", "State_Collapse1")
	self.FSM:addTranslation("State_Attack3", "CMD_Collapse", "State_Collapse1")
	self.FSM:addTranslation("State_Attack4", "CMD_Collapse", "State_Collapse1")

	self.FSM:addTranslation("State_Collapse1", "State_Collapse1_stop", "State_Collapse2")
	self.FSM:addTranslation("State_Collapse2", "CMD_To_Collapse3", "State_Collapse3")
	self.FSM:addTranslation("State_Collapse3", "State_Collapse3_stop", "State_Stand")

	--Skill_01
	self.FSM:addTranslation("State_Stand", "CMD_To_Skill_01", "State_KAttack4_Begin")
	self.FSM:addTranslation("State_Run", "CMD_To_Skill_01", "State_KAttack4_Begin")
	self.FSM:addTranslation("State_Run2", "CMD_To_Skill_01", "State_KAttack4_Begin")
	self.FSM:addTranslation("State_Brak", "CMD_To_Skill_01", "State_KAttack4_Begin")
	self.FSM:addTranslation("State_Attack1", "CMD_To_Skill_01", "State_KAttack4_Begin")
	self.FSM:addTranslation("State_Attack2", "CMD_To_Skill_01", "State_KAttack4_Begin")
	self.FSM:addTranslation("State_Attack2", "CMD_To_Skill_01", "State_KAttack4_Begin")
	self.FSM:addTranslation("State_KAttack4_Begin", "CMD_To_Skill_01_Stop", "State_KAttack4_End")
	self.FSM:addTranslation("State_KAttack4_End", "State_KAttack4_End_stop", "State_Stand")
end

function Hero_dao:startTimer(time, callback)
	if self.timerNode == nil then
		self.timerNode = cc.Node:create()
		self.timerNode:setVisible(false)
		self:addChild(self.timerNode)
	end
	self:stopTimer()

	local delay = cc.DelayTime:create(time)
    local sequence = cc.Sequence:create(delay, cc.CallFunc:create(callback))
    self.timerNode:runAction(sequence)
end

function Hero_dao:stopTimer()
	if self.timerNode then
		self.timerNode:stopAllActions()
	end
end

--强制切换清理
function Hero_dao:override_forceSwitchClean()
	Hero_dao.super.override_forceSwitchClean(self)

	self:clearStateData()
	if self.b2Body then
		self:clearForceXY()
		local _x = self:getPositionX()
		self:setActorPositionInValidRect({x = _x, y = 0})
	end
	local armature = self:getArmature()
	if armature then
		armature:setPosition({x = 0, y = 0})
		armature:stopAllActions()
	end
	self:stopAllActions()
end

function Hero_dao:enter_State_Stand()
	if self.startMoveCMD then
		local call = cc.CallFunc:create(function()
			self:handle("CMD_MoveStart")
		end)
		self:runAction(call)
	end
end

function Hero_dao:enter_State_Run()
	self.isRun = true
end

function Hero_dao:leave_State_Run()
	self.isRun = false
	self:clearForceX()
end

function Hero_dao:enter_State_Run2()
	self.isRun = true
end

function Hero_dao:leave_State_Run2()
	self.isRun = false
	self:clearForceX()
end

function Hero_dao:enter_State_Brak()
	self:clearForceX()
	self:setVelocityXInStartMoveCMD(CommonActorConfig.BrakVelocity)
end

function Hero_dao:leave_State_Brak()
	self:clearForceX()
end

function Hero_dao:enter_State_JumpUp()
	self.isJump = true
	self:clearForceXY()
	if self.jumpCountInAir == 0 then
		self:setVelocityYByImpulse(CommonActorConfig.JumpImpulse)
	else
		self:setVelocityYByImpulse(CommonActorConfig.AirHikeImpulse)
	end
end

function Hero_dao:enter_State_JumpDownEnd()
	self.isJump = false
	self.jumpCountInAir = 0
	self.jumAttackCount = 0
end

function Hero_dao:enter_State_JumpAttack3()
	self.isJumpAttack = true
	self.jumAttackCount = self.jumAttackCount + 1
end

function Hero_dao:leave_State_JumpAttack3()
	self.isJumpAttack = false
end

function Hero_dao:com_enter_attack()
	self:clearForceX()
end

function Hero_dao:com_leave_attack()
	self:clearForceX()
end

function Hero_dao:enter_State_Attack1()
	self.isAttack1 = true
	self:com_enter_attack()
	self:setVelocityXInStartMoveCMD(CommonActorConfig.Attacl_1_MoveImpulse)
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
	self:setVelocityXInStartMoveCMD(CommonActorConfig.Attacl_4_MoveImpulse)
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

function Hero_dao:enter_State_Hit()
	self:lockOrientation()
	self:clearForceX()
	self:setVelocityXByImpulse(self:getVelocityByOrientation(CommonActorConfig.HitImpluse))
end

function Hero_dao:leave_State_Hit()
	self:unLockOrientation()
	self:clearForceX()
end

function Hero_dao:enter_State_Collapse1()
	self.isCollapse = true
	self:lockOrientation()
	self:clearForceXY()
	self:setVelocityXYByImpulse(self:getVelocityByOrientation(CommonActorConfig.CollapseXImpluse), CommonActorConfig.CollapseYImpluse)
end

function Hero_dao:enter_State_Collapse2()
	self:lockOrientation()
	self.isCollapse = true
end

function Hero_dao:leave_State_Collapse3()
	self:unLockOrientation()
	self.isCollapse = false
end

function Hero_dao:enter_State_Upcut()
	self.isUpcut = true
	self:unLockOrientation()
	self:clearForceY()
end

function Hero_dao:leave_State_Upcut()
	self.isUpcut = false
	self:unLockOrientation()
	self.isJump = true
	self:clearForceY()
	self:setVelocityYByImpulse(CommonActorConfig.Upcut_JumpImpulse)
end

function Hero_dao:enter_State_DownCut()
	self:clearForceX()
	self:setVelocityXByImpulse(self:getVelocityByOrientation(CommonActorConfig.DownCutImpluse))
end

function Hero_dao:leave_State_DownCut()
	self:clearForceX()
end

function Hero_dao:enter_State_KAttack4_Begin()
	self:startTimer(1.5, function() self:handle("CMD_To_Skill_01_Stop") end)
end

return Hero_dao