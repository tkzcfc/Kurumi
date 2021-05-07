-- @Author: fangcheng
-- @Date:   2020-11-07 16:33:58
-- @remark: 场景基类

local ViewBase = cc.load("mvc").ViewBase

local SceneBase = class("SceneBase", ViewBase)

function SceneBase:onCreate()
	self.iFullWindowCount = 0

	G_SysEventEmitter:on("event_WindowShow", function(window, unique)
		if not unique then return end
		if self ~= _MyG.ScenesManager:getRuningView() then return end

		self.iFullWindowCount = self.iFullWindowCount + 1
		if self.iFullWindowCount == 1 then
			self:onHideNodes()
		end
	end, self)
	
	G_SysEventEmitter:on("event_WindowDismiss", function(window, unique)
		if not unique then return end
		if self ~= _MyG.ScenesManager:getRuningView() then return end

		self.iFullWindowCount = self.iFullWindowCount - 1
		if self.iFullWindowCount == 0 then
			self:onShowNodes()
		end
	end, self)
end


function SceneBase:loadUILua(path)
	self.ui = G_Helper.loadStudioFile(path, self)
    self:addChild(self.ui.root)
end

function SceneBase:initWithParameter(args)
end

-- @brief 监听网络消息
-- @param msgID 消息ID
-- @param call 回调
-- @param priority 监听优先级
function SceneBase:onNetMsg(msgID, call, priority)
	G_NetEventEmitter:on(msgID, call, self, priority)
end

function SceneBase:onEnter()
	if type(self.initNetEvent) == "function" then
		self:initNetEvent()
	end
end

function SceneBase:onExit()
	G_NetEventEmitter:offByTag(self)
	G_SysEventEmitter:offByTag(self)
end

-- @brief 返回按键按下
function SceneBase:onKeyBackReleased()
end

-- @brief 优化操作,隐藏场景子节点
function SceneBase:onHideNodes()
	self.ui.root:hide()
end

-- @brief 优化操作,显示场景子节点
function SceneBase:onShowNodes()
	self.ui.root:show()
end

return SceneBase