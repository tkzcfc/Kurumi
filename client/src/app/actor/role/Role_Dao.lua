local LuaCharacter = require("app.foundation.LuaCharacter")
local Role_Dao = myClass("Role_Dao", LuaCharacter)

local RoleConfig = require("app.config.RoleConfig")
local CommonActorConfig = require("app.config.CommonActorConfig")


function Role_Dao:ctor()
	Role_Dao.super.ctor(self)
	-- 角色名
	self.roleName = ""
	--空中连跳次数
	self.continueJumpCount=0

	self.skill_01_durationTime = 0

	self.skill_10_durationTime = 0

	self:setFilterData(BOX2D_FILTER_MASK.B2DM_PLAYER)
end

function Role_Dao:onEnter()
	Role_Dao.super.onEnter(self)
end

function Role_Dao:onExit()
	Role_Dao.super.onExit(self)
end

function Role_Dao:override_update(delta)
	Role_Dao.super.override_update(self, delta)

	if self.beginContact and self.isInAir then
		local opacity = self.groundPositionY - self:getPositionY()
		if opacity > 0 then
			return
		end
		opacity = 255 + opacity
		if opacity <= 0 then
			opacity = 0
		end
		self.shadowNode:setOpacity(opacity)
	end

	-- 连续点击攻击键切换不同攻击逻辑
	if self.isLeaveNormalAttack then
		self.isLeaveNormalAttack = false
		if self.attack_normal_continue then

			self.attack_normal_continue = false
			local preStateName = self.FSM:getPreStateName()

			if preStateName == "State_Attack1" then
				self:handle("CMD_To_Attack2")
			elseif preStateName == "State_Attack2" then
				self:handle("CMD_To_Attack3")
			elseif preStateName == "State_Attack3" then
				self:handle("CMD_To_Attack4")
			elseif preStateName == "State_Attack4" then
				self:handle("CMD_Attack")
			end
		end
	end

	self:runMoveLogic(delta)
end

function Role_Dao:runMoveLogic(delta)
	local curStateName = self.FSM:getCurStateName()
	-- 奔跑状态
	if curStateName == "State_Run" or curStateName == "State_Run2" then
		if self.startMoveCMD then
			self:setVelocityXByImpulse(CommonActorConfig.MoveImpulse)
		end
	-- 普通攻击
	elseif curStateName == "State_Attack1" then
		if self.startMoveCMD then
			self:setVelocityXByImpulse(CommonActorConfig.Attacl_1_MoveImpulse)
		else
			self:setVelocityXByImpulse(CommonActorConfig.Attacl_1_MoveImpulse * 0.4)
		end
	elseif curStateName == "State_Attack4" then
		if self.startMoveCMD then
			self:setVelocityXByImpulse(CommonActorConfig.Attacl_4_MoveImpulse)
		else
			self:setVelocityXByImpulse(CommonActorConfig.Attacl_4_MoveImpulse * 0.3)
		end
	-- 跳跃相关逻辑
	elseif curStateName == "State_JumpUp" then
		if self:getVelocityYValue() <= 0 then
			self:handle("CMD_JumpDownStart")
		end
		if self.startMoveCMD then
			self:setVelocityXByImpulse(CommonActorConfig.JumMoveImpulse)
		end
	elseif curStateName == "State_JumpDown" then
		if not self.isInAir then
			self.continueJumpCount = 0
			if self.startMoveCMD then
				self:handle("CMD_JumpTo_MoveStart")
			else
				self:handle("CMD_JumpDownEnd")
			end
		end
		if self.startMoveCMD then
			self:setVelocityXByImpulse(CommonActorConfig.JumMoveImpulse)
		end
	elseif curStateName == "State_DownCut" then
		if self.startMoveCMD then
			self:setVelocityXByImpulse(CommonActorConfig.DownCutImpulse)
		end
	elseif curStateName == "State_KAttack4_Begin" then
		self.skill_01_durationTime = self.skill_01_durationTime + delta
		if self.skill_01_durationTime > CommonActorConfig.SKill_01_DurationTime then
			self.skill_01_durationTime = 0
			self:handle("CMD_To_Skill_01_Stop")
		else
			if self.startMoveCMD then
				self:setVelocityXByImpulse(CommonActorConfig.SKill_01_Impulse)
			else
				self:setVelocityXByImpulse(CommonActorConfig.SKill_01_Impulse * 0.3)
			end
		end
	elseif curStateName == "State_KAttack4_End" then
		self:clearForceX()
	elseif curStateName == "State_Skill_10_Begin" then
		self:clearForceX()
		self.skill_10_durationTime = self.skill_10_durationTime + delta
		if self.skill_10_durationTime > CommonActorConfig.SKill_10_DurationTime then
			self.skill_10_durationTime = 0
			self:handle("CMD_To_Skill_10_Stop")
		end
	end

	if self.startMoveCMD and curStateName == "State_Stand" then
		self:handle("CMD_MoveStart")
	end
end

--切换角色
function Role_Dao:changeRole(name)

	if self.roleName == name then
		return
	end
	self.roleName = name

	self:loadConfig(RoleConfig[name])
	self:loadShadow()

	ccs.ArmatureDataManager:getInstance():addArmatureFileInfo("uianimation/juhe_texiao.ExportJson")
	local ArmatureNode = ccs.Armature:create()
	ArmatureNode:init("juhe_texiao")
	ArmatureNode:getAnimation():play("juhe_texiao")
	ArmatureNode:setPosition({x = 0, y = 110})
	self:addChild(ArmatureNode)

	self:initFSM()

	self.FSM:start("State_Stand")

	self:enableDefaultPhysics()
	self:enableUpdate()
end

function Role_Dao:setVelocityXInStartMoveCMD(impulse)				
	if self.startMoveCMD then
		self:setVelocityXByImpulse(self:getVelocityByOrientation(impulse))
	else
		self:clearForceX()
	end
end

function Role_Dao:move_x(value)
	if value > 0 then
		self:setOrientation(1)
	else
		self:setOrientation(-1)
	end
	self:handle("CMD_MoveStart")
	self.startMoveCMD = true
end

function Role_Dao:move_stop()	
	self:handle("CMD_MoveStand")
	self.startMoveCMD = false
	self:clearForceX()
end

function Role_Dao:attack_normal()
	if self.isInAir then
	else
		if not self:handle("CMD_Attack") then
			self.attack_normal_continue = true
		end
	end
end

function Role_Dao:jump()
	if self.isInAir then
		if self.continueJumpCount >= CommonActorConfig.MAX_JUMP_COUNT_IN_AIR then
			return
		end
	else
		self.continueJumpCount = 0
	end
	if self:handle("CMD_JumpUpStart") then
		self.continueJumpCount = self.continueJumpCount + 1
	end
end

function Role_Dao:down_cut()
	self:handle("CMD_DownCut")
end

function Role_Dao:do_skill_1()
	if self:handle("CMD_To_Skill_01") then
		self.skill_01_durationTime = 0.0
	end
end

function Role_Dao:do_skill_10()
	if self:handle("CMD_To_Skill_10") then
		self.skill_10_durationTime = 0.0
		self:clearForceX()
	end
end

--------------------------------------FSM--------------------------------------

function Role_Dao:initFSM()

	--站立
	self.FSM:addTranslation("State_Run", "CMD_MoveStand", "State_Stand")
	-- self.FSM:addTranslation("State_Run2", "CMD_MoveStand", "State_Brak")
	-- self.FSM:addTranslation("State_Brak", "State_Brak_stop", "State_Stand")
	self.FSM:addTranslation("State_Run2", "CMD_MoveStand", "State_Stand")

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
	

	-- self.FSM:addTranslation("State_Attack1", "CMD_JumpUpStart", "State_Upcut")
	-- self.FSM:addTranslation("State_Attack2", "CMD_JumpUpStart", "State_Upcut")
	-- self.FSM:addTranslation("State_Attack3", "CMD_JumpUpStart", "State_Upcut")
	self.FSM:addTranslation("State_Upcut", "State_Upcut_stop", "State_JumpUp_2")

	self.FSM:addTranslation("State_Stand", "CMD_DownCut", "State_DownCut")
	self.FSM:addTranslation("State_Run", "CMD_DownCut", "State_DownCut")
	self.FSM:addTranslation("State_Run2", "CMD_DownCut", "State_DownCut")

	self.FSM:addTranslation("State_Attack1", "CMD_DownCut", "State_DownCut")
	self.FSM:addTranslation("State_Attack2", "CMD_DownCut", "State_DownCut")
	self.FSM:addTranslation("State_Attack3", "CMD_DownCut", "State_DownCut")
	self.FSM:addTranslation("State_KAttack4_End", "CMD_DownCut", "State_DownCut")
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
	self.FSM:addTranslation("State_Attack3", "CMD_To_Skill_01", "State_KAttack4_Begin")
	self.FSM:addTranslation("State_JumpDown", "CMD_To_Skill_01", "State_KAttack4_Begin")
	self.FSM:addTranslation("State_JumpDownEnd", "CMD_To_Skill_01", "State_KAttack4_Begin")
	self.FSM:addTranslation("State_JumpUp", "CMD_To_Skill_01", "State_KAttack4_Begin")
	self.FSM:addTranslation("State_KAttack4_Begin", "CMD_To_Skill_01_Stop", "State_KAttack4_End")
	self.FSM:addTranslation("State_KAttack4_End", "State_KAttack4_End_stop", "State_Stand")

	-- Skill_10 召唤陨石下落
	self.FSM:addTranslation("State_Stand", "CMD_To_Skill_10", "State_Skill_10_Begin")
	self.FSM:addTranslation("State_Run", "CMD_To_Skill_10", "State_Skill_10_Begin")
	self.FSM:addTranslation("State_Run2", "CMD_To_Skill_10", "State_Skill_10_Begin")
	self.FSM:addTranslation("State_Brak", "CMD_To_Skill_10", "State_Skill_10_Begin")
	self.FSM:addTranslation("State_Attack1", "CMD_To_Skill_10", "State_Skill_10_Begin")
	self.FSM:addTranslation("State_Attack2", "CMD_To_Skill_10", "State_Skill_10_Begin")
	self.FSM:addTranslation("State_Attack3", "CMD_To_Skill_10", "State_Skill_10_Begin")
	self.FSM:addTranslation("State_Skill_10_Begin", "CMD_To_Skill_10_Stop", "State_Skill_10_End")
	self.FSM:addTranslation("State_Skill_10_End", "State_Skill_10_End_stop", "State_Stand")
	--
end

function Role_Dao:enter_State_Stand()
	self:clearForceX()
end

function Role_Dao:enter_State_Run()

end

function Role_Dao:leave_State_Run()
end

function Role_Dao:enter_State_Run2()
	-- self.brakeSoundID = _MyG.AudioManager:playSound("audio/brake.ogg", true)
end

function Role_Dao:leave_State_Run2()
	-- if self.brakeSoundID then
	-- 	_MyG.AudioManager:stopSound(self.brakeSoundID)
	-- 	self.brakeSoundID = nil
	-- end
end

function Role_Dao:enter_State_JumpUp()
	self:setVelocityYByImpulse(CommonActorConfig.JumpImpulse)
end

function Role_Dao:leave_State_Attack1()
	self.isLeaveNormalAttack = true
end

function Role_Dao:leave_State_Attack2()
	self.isLeaveNormalAttack = true
end

function Role_Dao:leave_State_Attack3()
	self.isLeaveNormalAttack = true
end

function Role_Dao:enter_State_Attack4()
	self:lockOrientation()
end

function Role_Dao:leave_State_Attack4()
	self:unLockOrientation()
	self.isLeaveNormalAttack = true
end

function Role_Dao:enter_State_DownCut()
	self:lockOrientation()
end

function Role_Dao:leave_State_DownCut()
	self:unLockOrientation()
end

function Role_Dao:enter_State_Skill_10_Begin()
	self:lockOrientation()

	local count = 3

	local space_role = self:getVelocityByOrientation(-200)
	local space_skill = self:getVelocityByOrientation(200)
	local move_velocity = self:getVelocityByOrientation(250 / BOX2D_PIXEL_TO_METER)
	local skill_rotation = self:getVelocityByOrientation(-30)

	local curIndex = 0
	local function do_skill_10_func()
		curIndex = curIndex + 1
		if curIndex >= count then
			self:handle("CMD_To_Skill_10_Stop")
		end

		local skill = require("app.actor.role.skill_dao.Skill_YunShi"):create(self:getGameWorld())
		skill:startSkill(nil, skill_rotation)

		local pos = {x = self:getPositionX() + space_role + curIndex * space_skill, y = self:getPositionY() + 600}
		-- print("pos.x"..tostring(pos.x), "pos.y"..tostring(pos.y))
		-- print("self.x"..tostring(self:getPositionX()), "self.y"..tostring(self:getPositionY()).."\n")

		skill:setPositionAndSyncPhysicsTransform(pos)
		-- skill:setActorPositionInValidRect({x = self:getPositionX() + space_role + curIndex * space_skill, y = self:getPositionY() + 500})
		skill:setVelocityXByImpulse(move_velocity)
		self:getParent():addChild(skill)
	end
	local delay = cc.DelayTime:create(0.3)
    local sequence = cc.Sequence:create(cc.CallFunc:create(do_skill_10_func), delay)
    self:runAction(cc.RepeatForever:create(sequence))
end

function Role_Dao:leave_State_Skill_10_Begin()
	self:unLockOrientation()
	self:stopAllActions()
end

return Role_Dao

