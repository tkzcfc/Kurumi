-- @Author: fangcheng
-- @Date:   2021-05-07 21:49:27
-- @remark: UI基类

local UIBase = class("UIBase", G_Class.Window)

function UIBase:ctor()
	UIBase.super.ctor(self)
	self:setLocalZOrder(Const.WindowZ.UI)
end

function UIBase:loadUILua(path)
	self.ui = G_Helper.loadStudioFile(path, self)
    self:addChild(self.ui.root)

    self:setContentView(self.ui.Panel_Content)
end

-- @brief 监听网络消息
-- @param msgID 消息ID
-- @param call 回调
-- @param priority 监听优先级
function UIBase:onNetMsg(msgID, call, priority)
	G_NetEventEmitter:on(msgID, call, self, priority)
end

function UIBase:onEnterCallback_()
	if type(self.initNetEvent) == "function" then
		self:initNetEvent()
	end
end

function UIBase:onExitCallback_()
	G_NetEventEmitter:offByTag(self)
end

-- UI界面关闭前的回调
function UIBase:iWillCloseWindow_()
	UIBase.super.iWillCloseWindow_(self)
	G_NetEventEmitter:offByTag(self)
end

return UIBase

