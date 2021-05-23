-- @Author: fangcheng
-- @Date:   2019-06-06 22:08:04
-- @remark: 

local UIControl = class("UIControl", cc.Node)

local UIControl_Left 	= 0
local UIControl_Right 	= 1
local UIControl_Up 		= 2
local UIControl_Down 	= 3

function UIControl:ctor()
    local function onNodeEvent(event)
        if event == "enter" then
            self:onEnter()
        elseif event == "exit" then
            self:onExit()
        end
    end
    self:registerScriptHandler(onNodeEvent)

    self.ui = G_Helper.loadStudioFile("ui.playerUIControl", self)
    self:addChild(self.ui.root)

    self:initTouch()
    self:initKeyboard()
end

function UIControl:onEnter()
end

function UIControl:onExit()
end

function UIControl:initTouch()

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

		if length < 35 then
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

function UIControl:left()
	G_InputEventEmitter:emit(_MyG.INPUT_KEY.CONTROL_X, -1)
end

function UIControl:right()
	G_InputEventEmitter:emit(_MyG.INPUT_KEY.CONTROL_X, 1)
end

function UIControl:up()
	G_InputEventEmitter:emit(_MyG.INPUT_KEY.CONTROL_Y, 1)
end

function UIControl:down()
	G_InputEventEmitter:emit(_MyG.INPUT_KEY.CONTROL_Y, -1)
end

function UIControl:cancel()
	G_InputEventEmitter:emit(_MyG.INPUT_KEY.CONTROL_CANCEL)
end

function UIControl:initKeyboard()
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
		elseif keyCode == KEY_X then
        end
        -- print("code", keyCode)

        if keyCode >= 77 and keyCode <= 85 then
        	local controlcode = keyCode-76
        	_MyG.PlayerDispatcher:call("control_"..controlcode)
        	-- print(controlcode)
        end
    end  
  
    local function onKeyReleased(keyCode, event)
    	if keyCode == curOri then
    		self:cancel()
    	end
    end  
  
    local listener = cc.EventListenerKeyboard:create()  
    listener:registerScriptHandler(onKeyPressed, cc.Handler.EVENT_KEYBOARD_PRESSED)  
    listener:registerScriptHandler(onKeyReleased, cc.Handler.EVENT_KEYBOARD_RELEASED)  
  
    cc.Director:getInstance():getEventDispatcher():addEventListenerWithSceneGraphPriority(listener, self) 
end



function UIControl:onClickChangeWeapon(sender)
	-- local player = _MyG.PlayerController:getPlayer()
	-- _MyG.PlayerDispatcher:call("control_changeWeapon", player)
end

function UIControl:onClickAttack(sender)
	-- G_InputEventEmitter:emit(_MyG.INPUT_KEY.CONTROL_ATTACK_NORMAL)
end

function UIControl:onClickSkill(sender)
	-- local userData = tonumber(sender.UserData[1])
	-- if userData == 1 then
	-- 	G_InputEventEmitter:emit(_MyG.INPUT_KEY.CONTROL_JUMP)
	-- elseif userData == 2 then
	-- 	G_InputEventEmitter:emit(_MyG.INPUT_KEY.CONTROL_DOWN_CUT)
	-- elseif userData == 3 then
	-- 	G_InputEventEmitter:emit(_MyG.INPUT_KEY.CONTROL_SKILL_1)
	-- elseif userData == 4 then
	-- 	G_InputEventEmitter:emit(_MyG.INPUT_KEY.CONTROL_SKILL_10)
	-- end
end


return UIControl