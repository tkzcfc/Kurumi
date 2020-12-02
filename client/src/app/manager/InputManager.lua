-- @Author: fangcheng
-- @Date:   2020-11-08 14:44:09
-- @remark: 输入管理


local InputManager = class("InputManager", import(".BaseManager"))


function InputManager:override_onInit()
    InputManager.super.override_onInit(self)
    self:enableTouch()
    self:initialize()
end

-- @brief 屏蔽触摸
function InputManager:disableTouch()
	self.isEnableTouchTag = false
end

-- @brief 启用触摸
function InputManager:enableTouch()
	self.isEnableTouchTag = true
end

function InputManager:initialize()
	self.arrListeners = {}
	local eventDispatcher = cc.Director:getInstance():getEventDispatcher()

	-- 返回按键
    local function onKeyReleased(keyCode, event)
        if _MyG.initFinishTag and keyCode == cc.KeyCode.KEY_BACK then
        	G_SysEventEmitter:emit("event_onKeyBackReleased")
        end
    end
  
    local listener = cc.EventListenerKeyboard:create()  
    listener:registerScriptHandler(onKeyReleased, cc.Handler.EVENT_KEYBOARD_RELEASED)  
    eventDispatcher:addEventListenerWithFixedPriority(listener, 1)
    table.insert(self.arrListeners, listener)


	-- 订阅一个层级很高的触摸事件，在需要屏蔽所有触摸时截断触摸事件
	local listener = cc.EventListenerTouchOneByOne:create()
    listener:setSwallowTouches(true)
    listener:registerScriptHandler(function(touch, event)
        return not self.isEnableTouchTag
    end, cc.Handler.EVENT_TOUCH_BEGAN)
    eventDispatcher:addEventListenerWithFixedPriority(listener, -0xff)
    table.insert(self.arrListeners, listener)
end

-- @brief 销毁时调用
function InputManager:override_onDestroy()
    InputManager.super.override_onDestroy(self)

    for k,v in pairs(self.arrListeners) do
        cc.Director:getInstance():getEventDispatcher():removeEventListener(v)
    end
    self.arrListeners = {}
end

return InputManager
