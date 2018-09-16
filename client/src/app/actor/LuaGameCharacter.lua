local LuaGameCharacter = class("LuaGameCharacter", GameCharacter)

function LuaGameCharacter:ctor()

	self:registerLuaHandle("logicUpdate", function(...) return self:override_logicUpdate(...) end)

	self:registerLuaHandle("updateArmatureInfo", function(...) return self:override_updateArmatureInfo(...) end)

	self:registerLuaHandle("loadArmature", function(...) return self:override_loadArmature(...) end)

	self:registerLuaHandle("attLevelTest", function(...) return self:override_attLevelTest(...) end)

	self:registerLuaHandle("AABBCallback", function(...) return self:override_AABBCallback(...) end)

	self:registerLuaHandle("attOtherActorCallback", function(...) return self:override_attOtherActorCallback(...) end)

	self:registerLuaHandle("isRunAABB", function(...) return self:override_isRunAABB(...) end)

	self:registerLuaHandle("loadActorFinish", function(...) return self:override_loadActorFinish(...) end)

	self.FSM = self:getFSM()

	self.totalStateName = {}
	self.stateConfig = {}

    self:registerScriptHandler(function(state)
        if state == "enter" then
            self:onEnter()
        elseif state == "exit" then
            self:onExit()
        end
    end)
end

function LuaGameCharacter:onEnter()
end

function LuaGameCharacter:onExit()
	self:unregisterScriptHandler()
end

function LuaGameCharacter:override_logicUpdate(time)
end

function LuaGameCharacter:override_updateArmatureInfo()
end

function LuaGameCharacter:override_loadArmature(filePath)
	-- if self.yingyingNode == nil then
	-- 	self.yingyingNode = cc.Sprite:create("ui/fragment/yy_ty.png")
	-- 	self.yingyingNode:setPositionY(10)
	-- 	self:addChild(self.yingyingNode, -1)
	-- end
end

function LuaGameCharacter:override_attLevelTest(otherActor)
	return self:getActorType() > otherActor:getActorType()
end

function LuaGameCharacter:override_AABBCallback(otherActor)
end

function LuaGameCharacter:override_attOtherActorCallback(otherActor)
end

--actor受到攻击
-- 参数attackActor ： 攻击者
-- 参数isPickUp ： 是否为上挑攻击
function LuaGameCharacter:override_beAttacked(attackActor, isPickUp)
	if attackActor:getPositionX() > self:getPositionX() then
		self:setOrientation(GAME_ORI_RIGHT)
	elseif attackActor:getPositionX() < self:getPositionX() then
		self:setOrientation(GAME_ORI_LEFT)
	end
end

function LuaGameCharacter:override_movementEventCallFunc(armature, movementType, movementID)

	if movementType == ccs.MovementEventType.complete then

		local curStateName = self.FSM:getCurState():getStateName()

		local data = self.stateConfig[curStateName]
		if data == nil then
			print("ERROR: LuaGameCharacter:override_movementEventCallFunc -> self.stateConfig[curStateName] == nil")
			return
		end

		local index = -1
		for i,v in ipairs(data) do
			if movementID == data[i] then
				index = i
				break
			end
		end
		assert(index ~= -1)

		if index >= #data then
			self:handle(curStateName.."_stop")
			_MyG.PlayerDispatcher:call(curStateName.."_stop", self)
		else
			local armature = self:getArmature()
			armature:getAnimation():play(data[index + 1])
		end
	end
end

function LuaGameCharacter:override_isRunAABB(other)
	return self:getActorType() ~= other:getActorType()
end

function LuaGameCharacter:override_loadActorFinish()
	self.b2Body = self:getB2Body()
end

function LuaGameCharacter:loadConfig(config)
	assert(config ~= nil)

	self.stateConfig = config.StateConfig

	self:clearState()
	for k,v in pairs(self.stateConfig) do
		self:addState(k)
	end

	ccs.ArmatureDataManager:getInstance():addArmatureFileInfo(config.ExportJson)

	self:initCharacterByData(config.Armature, {width = 100, height = 100}, {x = 0, y = 0})

	self:getArmature():getAnimation():setMovementEventCallFunc(function(...) self:override_movementEventCallFunc(...) end)
end

-------------------------------------------------FSM-------------------------------------------------

function LuaGameCharacter:addState(stateName)

	self.totalStateName[stateName] = true

	local enter = function(state, fsm)
		--print("FSM:enter",state:getStateName())
		
		local f = self["enter_"..stateName]
		if type(f) == "function" then
			f(self, state, fsm)
		end
		self:playAnimationByState(state)
	end

	local leave = function(state, fsm)
		--print("FSM:leave",state:getStateName())

		local f = self["leave_"..stateName]
		if type(f) == "function" then
			f(self, state, fsm)
		end
	end

	self.FSM:addState(stateName, enter, leave)
end

function LuaGameCharacter:handle(evenName)
	--print("handle", evenName)
	return self.FSM:handle(evenName)
end

-- 强制切换
function LuaGameCharacter:forceSwitch(stateName)
	self:override_forceSwitchClean()
	return self.FSM:forceSwitch(stateName) 
end

--强制切换清理
function LuaGameCharacter:override_forceSwitchClean()
	self:unLockOrientation()
end

function LuaGameCharacter:clearState()
	self.totalStateName = {}
	self.FSM:clear()
end

function LuaGameCharacter:playAnimationByState(state)
	local m = self.stateConfig[state:getStateName()]
	assert(m ~= nil and #m > 0)

	local armature = self:getArmature()
	armature:getAnimation():play(m[1])
end

function LuaGameCharacter:getVelocityByOrientation(invalue)
	if self:getOrientation() == GAME_ORI_RIGHT then
		return invalue
	else
		return -invalue
	end
end

function LuaGameCharacter:clearForceX()
	local velocity = self.b2Body:GetLinearVelocity()
	if math.abs(velocity.x) < 0.0001 then
		return
	end 
	self.b2Body:SetLinearVelocity({x = 0, y = velocity.y})
	-- local velocity = self.b2Body:GetLinearVelocity()
	-- local impulse_x = -velocity.x * self.b2Body:GetMass()
	-- self.b2Body:ApplyLinearImpulse({ x = impulse_x , y = 0}, self.b2Body:GetWorldCenter(), true)
end

function LuaGameCharacter:clearForceY()
	local velocity = self.b2Body:GetLinearVelocity()
	if math.abs(velocity.y) < 0.0001 then
		return
	end 
	self.b2Body:SetLinearVelocity({x = velocity.x, y = 0})
end

function LuaGameCharacter:clearForceXY()
	self.b2Body:SetLinearVelocity({x = 0, y = 0})
end

function LuaGameCharacter:setVelocityXByImpulse(velo_x)
	local curVelocity = self.b2Body:GetLinearVelocity()
	velo_x = velo_x - curVelocity.x
	velo_x = velo_x * self.b2Body:GetMass()
	self.b2Body:ApplyLinearImpulse({x = velo_x, y = 0}, self.b2Body:GetWorldCenter(), true)
end

function LuaGameCharacter:setVelocityYByImpulse(velo_y)	
	local curVelocity = self.b2Body:GetLinearVelocity()
	velo_y = velo_y - curVelocity.y
	velo_y = velo_y * self.b2Body:GetMass()
	self.b2Body:ApplyLinearImpulse({x = 0, y = velo_y}, self.b2Body:GetWorldCenter(), true)
end

function LuaGameCharacter:setVelocityXYByImpulse(velo_x, velo_y)
	local curVelocity = self.b2Body:GetLinearVelocity()
	velo_x = velo_x - curVelocity.x
	velo_y = velo_y - curVelocity.y
	velo_x = velo_x * self.b2Body:GetMass()
	velo_y = velo_y * self.b2Body:GetMass()
	self.b2Body:ApplyLinearImpulse({x = velo_x, y = velo_y}, self.b2Body:GetWorldCenter(), true)
end

function LuaGameCharacter:keepInAir()	
	self:setVelocityYByImpulse(self.b2Body:GetMass() * -PHYSICS_WORLD_GRAVITY_Y * PHYSICS_WORLD_FPS)
end

return LuaGameCharacter
