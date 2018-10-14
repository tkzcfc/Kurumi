local ControlUI = class("ControlUI", cc.Node)

local ControlUI_Left 	= 0
local ControlUI_Right 	= 1
local ControlUI_Up 		= 2
local ControlUI_Down 	= 3

function ControlUI:ctor()
    local function onNodeEvent(event)
        if event == "enter" then
            self:onEnter()
        elseif event == "exit" then
            self:onExit()
        end
    end
    self:registerScriptHandler(onNodeEvent)

    self.ui = _MyG.loadStudioFile("playerControlUI", self)

    self:addChild(self.ui.root)

    self:initTouch()
    self:initKeyboard()

    self:onClickOpenDebug(nil)
end

function ControlUI:onEnter()
end

function ControlUI:onExit()
end

function ControlUI:initTouch()

	self.history_Key_Y = nil
	self.history_Key_X = nil

	local beginPos = {x = self.ui.sprite_BG:getPositionX(), y = self.ui.sprite_BG:getPositionY()}
	local touchBox = self.ui.sprite_BG:getBoundingBox()

	local size = self.ui.sprite_BG:getContentSize()

	local touchR = self.ui.sprite_Red:getContentSize().width * 0.5
	local centerPos = {x = 0, y = 0}

	local touchLayer = self

	local function normal()
		self.ui.sprite_BG:setPosition(beginPos)
		self.ui.sprite_Move:setPosition({x = 0, y = 0})
		self.ui.sprite_Move:setVisible(false)
		self.ui.sprite_Red:setVisible(false)
		self.ui.sprite_Ori:setOpacity(180)
		self.history_Key_Y = nil
		self.history_Key_X = nil
	end
	normal()

	local function onTouchBegin(touch,event)
		local curPos = touchLayer:convertToNodeSpace(touch:getLocation())
		if cc.rectContainsPoint(touchBox, curPos) then
			self.ui.sprite_BG:setPosition(curPos)
			self.ui.sprite_Move:setPosition(curPos)
			self.ui.sprite_Move:setVisible(true)
			self.ui.sprite_Ori:setOpacity(255)
			centerPos = curPos
			return true
		end
		return false
	end

	local function onTouchMove(touch,event)
		local curPos = touchLayer:convertToNodeSpace(touch:getLocation())

		local V_R = { x = curPos.x - centerPos.x, y = curPos.y - centerPos.y }
		local length = cc.pGetLength(V_R)
		if length < 5 then
			return
		end

		local angle = cc.pToAngleSelf(V_R)
		local radian = -angle * 57.29577951

		local moveR = touchR - 36
		if length <= moveR then
			self.ui.sprite_Move:setPosition(curPos)
		else
			angle = angle
			local x = math.cos(angle) * moveR + centerPos.x
			local y = math.sin(angle) * moveR + centerPos.y
			self.ui.sprite_Move:setPosition({x = x, y = y})
		end

		self.ui.sprite_Red:setVisible(true)
		self.ui.sprite_Red:setRotation(radian)

		if length <= 25 then
			self.history_Key_X = nil
			self.history_Key_Y = nil
			return
		end

		-- 上
		if radian < -30 and radian > -150 then
			self:up()
		-- 下
		elseif radian >= 60 and radian < 120 then
			self:down()
		end
		if math.abs(V_R.x) < 0.001 then
			return
		end

		-- 右
		if V_R.x > 0 then
			self:right()
		-- 左
		else
			self:left()
		end
	end

	local function onTouchEnd(touch,event)
		normal()
		self:cancel()
	end

	local listener = cc.EventListenerTouchOneByOne:create();
	listener:registerScriptHandler(onTouchBegin,cc.Handler.EVENT_TOUCH_BEGAN);
	listener:registerScriptHandler(onTouchMove,cc.Handler.EVENT_TOUCH_MOVED);
	listener:registerScriptHandler(onTouchEnd,cc.Handler.EVENT_TOUCH_ENDED);
	listener:registerScriptHandler(onTouchEnd,cc.Handler.EVENT_TOUCH_CANCELLED);
	cc.Director:getInstance():getEventDispatcher():addEventListenerWithSceneGraphPriority(listener, touchLayer)
end

function ControlUI:left()
	local player = getGameWord():getLocalPlayer()
	if self.history_Key_X ~= ControlUI_Left then
		_MyG.PlayerDispatcher:call("control_left", player)
		self.history_Key_X = ControlUI_Left
		-- print("left")
	end
end

function ControlUI:right()
	local player = getGameWord():getLocalPlayer()
	if self.history_Key_X ~= ControlUI_Right then
		_MyG.PlayerDispatcher:call("control_right", player)
		self.history_Key_X = ControlUI_Right
		-- print("right")
	end
end

function ControlUI:up()
	local player = getGameWord():getLocalPlayer()
	if self.history_Key_Y ~= ControlUI_Up then
		_MyG.PlayerDispatcher:call("control_up", player)
		self.history_Key_Y = ControlUI_Up
		-- print("up")
	end
end

function ControlUI:down()
	local player = getGameWord():getLocalPlayer()
	if self.history_Key_Y ~= ControlUI_Down then
		_MyG.PlayerDispatcher:call("control_down", player)
		self.history_Key_Y = ControlUI_Down
		-- print("down")
	end
end

function ControlUI:cancel()
	local player = getGameWord():getLocalPlayer()
	_MyG.PlayerDispatcher:call("control_cancel", player)
	-- print("cancel")
end

function ControlUI:initKeyboard()
	local LEFT = 26
    local RIGHT = 27
    local TOP = 28
    local BOTTOM = 29

    local KEY_Z = 149
    local KEY_X = 147
    local KEY_C = 126

    local curOri = 0

	 --键盘事件  
    local function onKeyPressed(keyCode, event)
    	local player = _MyG.PlayerController:getPlayer()

        if keyCode == LEFT then
        	curOri = LEFT
        	self:left()
        elseif keyCode == RIGHT then
        	curOri = RIGHT
        	self:right()
        elseif keyCode == TOP then
        	self:up()
        elseif keyCode == BOTTOM then
        	self:down()
        elseif keyCode == KEY_C then
        	_MyG.PlayerDispatcher:call("control_changeWeapon", player)
		elseif keyCode == KEY_X then
        	_MyG.PlayerDispatcher:call("control_attack", player)
        end
        -- print("code", keyCode)

        if keyCode >= 77 and keyCode <= 85 then
        	local controlcode = keyCode-76
        	_MyG.PlayerDispatcher:call("control_"..controlcode)
        	-- print(controlcode)
        end
    end  
  
    local function onKeyReleased(keyCode, event)
    	local player = _MyG.PlayerController:getPlayer()
    	if keyCode == curOri then
    		self:cancel()
    	end
    end  
  
    local listener = cc.EventListenerKeyboard:create()  
    listener:registerScriptHandler(onKeyPressed, cc.Handler.EVENT_KEYBOARD_PRESSED)  
    listener:registerScriptHandler(onKeyReleased, cc.Handler.EVENT_KEYBOARD_RELEASED)  
  
    cc.Director:getInstance():getEventDispatcher():addEventListenerWithSceneGraphPriority(listener, self) 
end



function ControlUI:onClickChangeWeapon(sender)
	local player = _MyG.PlayerController:getPlayer()
	_MyG.PlayerDispatcher:call("control_changeWeapon", player)
end

function ControlUI:onClickAttack(sender)
	local player = _MyG.PlayerController:getPlayer()
	_MyG.PlayerDispatcher:call("control_attack", player) 
end

function ControlUI:onClickSkill(sender)
	local player = _MyG.PlayerController:getPlayer()
	_MyG.PlayerDispatcher:call("control_to_Skill_01", player) 
end

function ControlUI:onClickOpenDebug(sender)
	local gameword = getGameWord()
	if gameword ~= nil then
		gameword:openDebugDraw(not gameword:isOpenDebugDraw())
	end
end


return ControlUI