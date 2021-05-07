-- @Author: fangcheng
-- @Date:   2020-03-11 21:11:22
-- @remark: UI窗口类型

local UIWindow = class("UIWindow", require("app.common.UIBase"))

local FADE_IN_TIME = 0.5
local FADE_OUT_TIME = 0.5

function UIWindow:ctor()
	UIWindow.super.ctor(self)

	self:setAutoDismiss(false)
	self:setPlayOpenAction(true)
	self:setPlayCloseAction(true)
	self:setIsFullScreen(true)
end

-- @brief UI界面打开动画
function UIWindow:iRunOpenActionBegin()
	if not self.pContentView then
		self:iAfterOpenedWindow()
		return
	end

	self.bRunOpeningTag = true
	
    self.pContentView:setOpacity(0)
    local actionEnd = function()
		self:iAfterOpenedWindow()
    end
    local q = cc.Sequence:create(
    	cc.FadeIn:create(FADE_IN_TIME),
    	cc.CallFunc:create(actionEnd)
    )
    self.pContentView:runAction(q)
end

-- @brief UI界面关闭动画
function UIWindow:iCloseActionBegin()
	if not self.pContentView then
		self:iAfterClosedWindow()
		return
	end

    self.pContentView:setOpacity(255)
    local actionEnd = function()
        self:iAfterClosedWindow() 
    end
    local q = cc.Sequence:create(
    	cc.FadeOut:create(FADE_OUT_TIME),
    	cc.CallFunc:create(actionEnd)
    )
    self.pContentView:runAction(q)
end

return UIWindow
