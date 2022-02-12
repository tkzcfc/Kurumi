-- @Author: fangcheng
-- @Date:   2021-05-07 21:49:27
-- @remark: UI基类

local UIBase = class("UIBase", G_Class.UIPanel)

function UIBase:ctor()
	UIBase.super.ctor(self)
	self:setNodeEventEnabled(true)
end

-- override me for setNodeEventEnabled(true)
function UIBase:onEnter()
end

-- override me for setNodeEventEnabled(true)
function UIBase:onExit()
end

-- override me for setNodeEventEnabled(true)
function UIBase:onEnterTransitionFinish()
end

-- override me for setNodeEventEnabled(true)
function UIBase:onExitTransitionStart()
end

-- override me for setNodeEventEnabled(true)
function UIBase:onCleanup()
end

function UIBase:loadUILua(path)
	self.ui = G_Helper.loadStudioFile(path, self)
    self:addChild(self.ui.root)

    self:setContentView(self.ui.Panel_Content)
end

-- @interface
function UIBase:initNetEvent()
end

-- @brief 监听网络消息
-- @param msgID 消息ID
-- @param call 回调
-- @param priority 监听优先级
function UIBase:onNetMsg(msgID, call, priority)
	G_NetEventEmitter:on(msgID, call, self, priority)
end

-- @brief 监听系统事件
-- @param msgID 消息ID
-- @param call 回调
-- @param priority 监听优先级
function UIBase:onSysMsg(msgID, call, priority)
	G_SysEventEmitter:on(msgID, call, self, priority)
end

-- @override UI界面打开之前的回调
function UIBase:iBeforeOpened()
	UIBase.super.iBeforeOpened(self)
	self:initNetEvent()
end

-- @override UI界面关闭前的回调
function UIBase:iWillClose()
	UIBase.super.iWillClose(self)
	G_NetEventEmitter:offByTag(self)
	G_SysEventEmitter:offByTag(self)
end

return UIBase

