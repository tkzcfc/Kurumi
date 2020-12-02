-- @Author: fangcheng
-- @Date:   2020-03-11 21:11:22
-- @remark: UI窗口对象基类

local UIWindow = class("UIWindow", G_Class.Window)

function UIWindow:ctor()
	UIWindow.super.ctor(self)
	self:setLocalZOrder(G_Const.WINDOW_Z.UI)
end

function UIWindow:enableNetRecipient()
	if self.netRecipient then
		return
	end
    self.netRecipient = G_Class.Recipient.new(G_NetEventEmitter)
end

function UIWindow:onEnterCallback_()
	if type(self.initNetEvent) == "function" then
		self:enableNetRecipient()
		self:initNetEvent()
	end
end

function UIWindow:onExitCallback_()
	if self.netRecipient then
    	self.netRecipient:clear()
    	self.netRecipient = nil
	end
end

-- UI界面关闭前的回调
function UIWindow:iWillCloseWindow()
	UIWindow.super.iWillCloseWindow(self)
	if self.netRecipient then
    	self.netRecipient:clear()
    	self.netRecipient = nil
	end
end

return UIWindow
