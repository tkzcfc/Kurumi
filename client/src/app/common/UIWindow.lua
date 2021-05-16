-- @Author: fangcheng
-- @Date:   2020-03-11 21:11:22
-- @remark: UI窗口类型

local UIWindow = class("UIWindow", require("app.common.UIBase"))

local FADE_IN_TIME_1 = 0.5
local FADE_IN_TIME_2 = 0.2
local FADE_OUT_TIME_1 = 0.3
local FADE_OUT_TIME_2 = 0.4

-- @brief 窗口默认打开动画
local function UIWindowOpenAction(window, call)
	if _MyG.NotifiNodeManager == nil then
		call()
		return
	end

	local maskLayer = _MyG.NotifiNodeManager:getMaskLayer()

    window:setVisible(false)
    maskLayer:setVisible(true)
    maskLayer:stopAllActions()
    maskLayer:setOpacity(0)

    local action = cc.Sequence:create(
    	cc.FadeIn:create(FADE_IN_TIME_1),
    	cc.CallFunc:create(function()
    		window:setVisible(true)
    	end),
    	cc.FadeOut:create(FADE_IN_TIME_2),
    	cc.Hide:create(),
    	cc.CallFunc:create(call)
    )
    maskLayer:runAction(action)
end

-- @brief 窗口默认关闭动画
local function UIWindowCloseAction(window, call)
	if _MyG.NotifiNodeManager == nil then
		call()
		return
	end

	local maskLayer = _MyG.NotifiNodeManager:getMaskLayer()

    maskLayer:setVisible(true)
    maskLayer:stopAllActions()
    maskLayer:setOpacity(0)

    local action = cc.Sequence:create(
    	cc.FadeIn:create(FADE_OUT_TIME_1),
    	cc.CallFunc:create(function()
    		call()
    	end),
    	cc.FadeOut:create(FADE_OUT_TIME_2),
    	cc.Hide:create()
    )
    maskLayer:runAction(action)
end


function UIWindow:ctor()
	UIWindow.super.ctor(self)

	self:setAutoDismiss(false)
	self:setPlayOpenAction(true)
	self:setPlayCloseAction(true)
	self:setIsFullScreen(true)

	self:setOpenActionCall(UIWindowOpenAction)
	self:setCloseActionCall(UIWindowCloseAction)
end


return UIWindow
