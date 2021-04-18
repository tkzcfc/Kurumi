-- @Author: fangcheng
-- @Date:   2020-03-11 21:11:22
-- @remark: UI窗口对象基类

local UIWindow = class("UIWindow", G_Class.Window)

function UIWindow:ctor()
	UIWindow.super.ctor(self)
	self:setLocalZOrder(G_Const.WINDOW_Z.UI)
end

-- @brief 监听网络消息
-- @param msgID 消息ID
-- @param call 回调
-- @param priority 监听优先级
function UIWindow:onNetMsg(msgID, call, priority)
	G_NetEventEmitter:on(msgID, call, self, priority)
end

function UIWindow:onEnterCallback_()
	if type(self.initNetEvent) == "function" then
		self:initNetEvent()
	end
end

function UIWindow:onExitCallback_()
	G_NetEventEmitter:offByTag(self)
end

-- UI界面关闭前的回调
function UIWindow:iWillCloseWindow()
	UIWindow.super.iWillCloseWindow(self)
	G_NetEventEmitter:offByTag(self)
end

return UIWindow
