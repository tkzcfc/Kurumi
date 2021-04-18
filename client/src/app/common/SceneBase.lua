-- @Author: fangcheng
-- @Date:   2020-11-07 16:33:58
-- @remark: 场景基类

local ViewBase = cc.load("mvc").ViewBase

local SceneBase = class("SceneBase", ViewBase)

function SceneBase:onCreate()
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
end

function SceneBase:onKeyBackReleased()
end

return SceneBase