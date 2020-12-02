-- @Author: fangcheng
-- @Date:   2020-11-07 16:33:58
-- @remark: 场景基类

local ViewBase = cc.load("mvc").ViewBase

local SceneBase = class("SceneBase", ViewBase)

function SceneBase:onCreate()
    self.netRecipient = G_Class.Recipient.new(G_NetEventEmitter)
end

function SceneBase:initWithParameter(args)
end

function SceneBase:onEnter()
end

function SceneBase:onExit()
    self.netRecipient:clear()
end

function SceneBase:onKeyBackReleased()
end

return SceneBase