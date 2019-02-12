local LuaCharacter = myClass("LuaCharacter", Character)


function LuaCharacter:ctor()

	self:registerLuaHandle("beginContactCall", function(...) return self:override_beginContact(...) end)
	self:registerLuaHandle("endContactCall", function(...) return self:override_endContact(...) end)

	self.FSM = self:getFSM()

	self.totalStateName = {}
	self.stateConfig = {}
	self.soundConfig = {}

    self:registerScriptHandler(function(state)
        if state == "enter" then
            self:onEnter()
        elseif state == "exit" then
            self:onExit()
        end
    end)

    -- 是否在空中
    self.isInAir = true
    -- 站在地面时Y坐标
    self.groundPositionY = 0
    -- 是否已经和地面接触过
    self.beginContact = false
    -- 
end

function LuaCharacter:enableUpdate()
	if self.updateComponent == nil then
		self.updateComponent = self:addAnaxComponent("UpdateComponent")
		self.updateComponent = tolua.cast(self.updateComponent, "UpdateComponent")
		self:getEntity():activate()
	end
	if self.updateComponent ~= nil then
		self.updateComponent.m_updateCall = function(delta) self:override_update(delta) end
	end
end

function LuaCharacter:enableLastUpdate()
	if self.updateComponent == nil then
		self.updateComponent = self:addAnaxComponent("UpdateComponent")
		self.updateComponent = tolua.cast(self.updateComponent, "UpdateComponent")
		self:getEntity():activate()
	end
	if self.updateComponent ~= nil then
		self.updateComponent.m_lastUpdateCall = function(delta) self:override_lastUpdate(delta) end
	end
end

function LuaCharacter:enableDefaultPhysics()
	self:enablePhysics({x = 1200, y = 700}, {width = 100, height = 150})

	if self.box2DComponent == nil then
		return
	end
	-- 重力*5
	self.box2DComponent.m_body:SetGravityScale(5.0)
end

-----------------------------------------override-----------------------------------------

function LuaCharacter:onEnter()
end

function LuaCharacter:onExit()
	self:unregisterScriptHandler()
end

function LuaCharacter:override_update(delta)
end

function LuaCharacter:override_lastUpdate(delta)

end

function LuaCharacter:override_movementEventCallFunc(armature, movementType, movementID)
	if movementType == ccs.MovementEventType.complete then

		local curStateName = self.FSM:getCurState():getStateName()

		local data = self.stateConfig[curStateName]
		if data == nil then
			print("ERROR: LuaCharacter:override_movementEventCallFunc -> self.stateConfig[curStateName] == nil")
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
			self:override_onStateRunStop(curStateName)
			self:handle(curStateName.."_stop")
			_MyG.PlayerDispatcher:call(curStateName.."_stop", self)
		else
			self.armature:getAnimation():play(data[index + 1])
		end
	end
end

function LuaCharacter:override_attCollisionCallback()
end

function LuaCharacter:override_defCollisionCallback()
end

function LuaCharacter:override_syncArmaturePhysicsTransform(_x, _y, _a)
	self:setPosition(_x, _y)
	-- self:setRotation(_a)
end

-- 在地面
function LuaCharacter:override_beginContact()
	if self.shadowNode then
		self.shadowNode:setVisible(true)
	end
	self.groundPositionY = self:getPositionY()
	self.isInAir = false
	self.beginContact = true
end

-- 离开地面
function LuaCharacter:override_endContact()
	self.isInAir = true
end

function LuaCharacter:override_orientationTurn(orientation)
	self.armature:setScaleX(orientation)
end

function LuaCharacter:override_onStateRunStop(stateName)
end

-----------------------------------------logic-----------------------------------------

function LuaCharacter:loadConfig(config)
	assert(config ~= nil)

	self.stateConfig = config.StateConfig or {}
	self.soundConfig = config.SoundConfig or {}

	self:clearState()
	for k,v in pairs(self.stateConfig) do
		self:addState(k)
	end

	-- 资源加载，预防该资源未加载
	ccs.ArmatureDataManager:getInstance():addArmatureFileInfo(config.ExportJson)

	-- 动画加载
	self:loadArmature(config.Armature)
	self.armature = self:getArmature()
	self.armature:getAnimation():setMovementEventCallFunc(function(...) self:override_movementEventCallFunc(...) end)

	-- 朝向
	local orientationComponent = self:addAnaxComponent("OrientationComponent")
	orientationComponent = tolua.cast(orientationComponent, "OrientationComponent")
	orientationComponent.m_orientation = 1
	orientationComponent.m_orientationTurnCall = function(...)
		self:override_orientationTurn(...)
	end
	self.orientationComponent = orientationComponent
	self.orientationCache = self.orientationComponent.m_orientation
end

function LuaCharacter:enablePhysics(position, size)
	-- 启用刚体
	self:enableBox2DComponent(position, size)

	local box2DComponent = self:getAnaxComponent("Box2DComponent")
	if box2DComponent == nil then
		print("getAnaxComponent Box2DComponent fail")
		return
	end

	box2DComponent = tolua.cast(box2DComponent, "Box2DComponent")
	if box2DComponent == nil then
		print("cast to Box2DComponent fail")
		return
	end

	box2DComponent.m_syncPhysicsTransformCall = function(...)
		self:override_syncArmaturePhysicsTransform(...)
	end
	self.box2DComponent = box2DComponent
	self.b2Body = box2DComponent.m_body

	-- 设置碰撞回调
	local armatureCollisionComponent = self:getAnaxComponent("ArmatureCollisionComponent")
	armatureCollisionComponent = tolua.cast(armatureCollisionComponent, "ArmatureCollisionComponent")
	armatureCollisionComponent.m_attCollisionCall = function(...) self:override_attCollisionCallback(...) end
	armatureCollisionComponent.m_defCollisionCall = function(...) self:override_defCollisionCallback(...) end
	self.armatureCollisionComponent = armatureCollisionComponent

	-- 碰撞过滤器
	local collisionFilterComponent = self:getAnaxComponent("CollisionFilterComponent")
	collisionFilterComponent = tolua.cast(collisionFilterComponent, "CollisionFilterComponent")
	self.collisionFilterComponent = collisionFilterComponent
end

function LuaCharacter:changeCategoryBits(bit)
	if self.b2Body then
		local fixtureList = self.b2Body:GetFixtureList()
		if fixtureList then
			local filterData = fixtureList:GetFilterData()
			filterData.categoryBits = bit
			repeat
				fixtureList:SetFilterData(filterData)
				fixtureList = fixtureList:GetNext()
			until(fixtureList == nil)
		end
	end
end

function LuaCharacter:loadShadow()
	if self.shadowNode == nil then
		self.shadowNode = cc.Sprite:create("ui/fragment/yy_ty.png")
		self.shadowNode:setPositionY(10)
		self:addChild(self.shadowNode, -1)
		self.shadowNode:setVisible(false)
	end
end

function LuaCharacter:setOrientation(orientation)
	if self.orientationComponent:setOrientation(orientation) then
		self.orientationCache = orientation
	end
end

function LuaCharacter:getOrientation()
	return self.orientationComponent.m_orientation
end

function LuaCharacter:lockOrientation()
	self.orientationComponent.m_lockOrientation = true
end

function LuaCharacter:unLockOrientation()
	self.orientationComponent.m_lockOrientation = false
end

function LuaCharacter:isLockOrientation()
	return self.orientationComponent.m_lockOrientation
end

function LuaCharacter:startTimer(time, callback)
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

function LuaCharacter:stopTimer()
	if self.timerNode then
		self.timerNode:stopAllActions()
	end
end

function LuaCharacter:doSomeAtNextFrame(callback)
	if self.doSomeNode == nil then
		self.doSomeNode = cc.Node:create()
		self.doSomeNode:setVisible(false)
		self:addChild(self.doSomeNode)
	end
	self.doSomeNode:runAction(cc.CallFunc:create(callback))
end

function LuaCharacter:setIsLocalPlayer(islocal)
	if islocal then
		self.mapFollowComponent = self:addAnaxComponent("MapFollowComponent")
		self.mapFollowComponent = tolua.cast(self.mapFollowComponent, "MapFollowComponent")
		self.mapFollowComponent.m_owner = self
	else
		if self.mapFollowComponent then
			self:removeAnaxComponent("MapFollowComponent")
		end
		self.mapFollowComponent = nil
	end
end

function LuaCharacter:stopSound()
	if self.curSoundID then
		_MyG.AudioManager:stopSound(self.curSoundID)
		self.curSoundID = nil
	end
end

function LuaCharacter:changePlaySound(soundName, stateName)
	if soundName == nil or soundName == "" then
		self:stopSound()
	else
		if self.curSoundName == soundName then
			if self.curSound_StateName == stateName then
				self:stopSound()
				self.curSoundID = _MyG.AudioManager:playSound(soundName)
			end
		else
			self:stopSound()
			self.curSoundID = _MyG.AudioManager:playSound(soundName)
		end
	end
	self.curSoundName = soundName
	self.curSound_StateName = stateName
end

function LuaCharacter:addState(stateName)

	self.totalStateName[stateName] = true

	local enter = function(state, fsm)
		-- print("FSM:enter",state:getStateName())
		self:changePlaySound(self.soundConfig[stateName], stateName)

		local f = self["enter_"..stateName]
		if type(f) == "function" then
			f(self, state, fsm)
		end
		self:playAnimationByState(state)
	end

	local leave = function(state, fsm)
		-- print("FSM:leave",state:getStateName())

		local f = self["leave_"..stateName]
		if type(f) == "function" then
			f(self, state, fsm)
		end
	end

	self.FSM:addState(stateName, enter, leave)
end

function LuaCharacter:clearState()
	self.totalStateName = {}
	self.FSM:clear()
end

function LuaCharacter:handle(evenName)
	-- print("handle", evenName)
	return self.FSM:handle(evenName)
end

function LuaCharacter:playAnimationByState(state)
	local m = self.stateConfig[state:getStateName()]
	-- print("play animation", m[1])
	assert(m ~= nil and #m > 0)
	self.armature:getAnimation():play(m[1])
end



function LuaCharacter:getVelocityByOrientation(invalue)
	return invalue * self.orientationCache
end

function LuaCharacter:clearForceX()
	if self.b2Body == nil then
		return
	end
	local velocity = self.b2Body:GetLinearVelocity()
	if math.abs(velocity.x) < 0.0001 then
		return
	end 
	self.b2Body:SetLinearVelocity({x = 0, y = velocity.y})
	-- local velocity = self.b2Body:GetLinearVelocity()
	-- local impulse_x = -velocity.x * self.b2Body:GetMass()
	-- self.b2Body:ApplyLinearImpulse({ x = impulse_x , y = 0}, self.b2Body:GetWorldCenter(), true)
end

function LuaCharacter:clearForceY()
	if self.b2Body == nil then
		return
	end
	local velocity = self.b2Body:GetLinearVelocity()
	if math.abs(velocity.y) < 0.0001 then
		return
	end 
	self.b2Body:SetLinearVelocity({x = velocity.x, y = 0})
end

function LuaCharacter:getVelocityYValue()
	if self.b2Body == nil then
		return 0
	end
	return self.b2Body:GetLinearVelocity().y
end

function LuaCharacter:clearForceXY()
	if self.b2Body == nil then
		return
	end
	self.b2Body:SetLinearVelocity({x = 0, y = 0})
end

function LuaCharacter:setVelocityXByImpulse(velo_x)
	if self.b2Body == nil then
		return
	end
	local curVelocity = self.b2Body:GetLinearVelocity()
	velo_x = self:getVelocityByOrientation(velo_x)
	velo_x = velo_x - curVelocity.x
	velo_x = velo_x * self.b2Body:GetMass()
	self.b2Body:ApplyLinearImpulse({x = velo_x, y = 0}, self.b2Body:GetWorldCenter(), true)
end

function LuaCharacter:setVelocityYByImpulse(velo_y)	
	if self.b2Body == nil then
		return
	end
	local curVelocity = self.b2Body:GetLinearVelocity()
	velo_y = velo_y - curVelocity.y
	velo_y = velo_y * self.b2Body:GetMass()
	self.b2Body:ApplyLinearImpulse({x = 0, y = velo_y}, self.b2Body:GetWorldCenter(), true)
end

function LuaCharacter:setVelocityXYByImpulse(velo_x, velo_y)
	if self.b2Body == nil then
		return
	end
	local curVelocity = self.b2Body:GetLinearVelocity()
	velo_x = velo_x - curVelocity.x
	velo_y = velo_y - curVelocity.y
	velo_x = velo_x * self.b2Body:GetMass()
	velo_y = velo_y * self.b2Body:GetMass()
	self.b2Body:ApplyLinearImpulse({x = velo_x, y = velo_y}, self.b2Body:GetWorldCenter(), true)
end

function LuaCharacter:keepInAir()	
	if self.b2Body == nil then
		return
	end
	self:setVelocityYByImpulse(self.b2Body:GetMass() * -PHYSICS_WORLD_GRAVITY_Y * PHYSICS_WORLD_FPS)
end

return LuaCharacter
