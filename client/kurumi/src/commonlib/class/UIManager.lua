-- @Author : fangcheng
-- @Date   : 2020-02-29 21:23:48
-- @remark : UI管理

local Vector = require("commonlib.class.Vector")
local UIContext = require("commonlib.class.UIContext")

local UIManager = class("UIManager")

function UIManager:ctor()
	self.contextStack = Vector:new(false)
	self:push()
end

function UIManager:pop()
	self.contextStack:back():removeAllUI()
	self.contextStack:popBack()
end

function UIManager:push()
	self.contextStack:pushBack(UIContext.new())
end

function UIManager:curContext()
	return self.contextStack:back()
end

function UIManager:pushUI(ui)
	self:curContext():pushUI(ui)
end

function UIManager:uiShowFinish(ui)
	return self:curContext():uiShowFinish(ui)
end

function UIManager:getTopUI()
	return self:curContext():getTopUI()
end

function UIManager:popUI()
	return self:curContext():popUI()
end

function UIManager:removeUI_(ui)
	self:curContext():removeUI_(ui)
end

function UIManager:removeAllUI()
	self:curContext():removeAllUI()
end

function UIManager:removeUIByName(...)
	self:curContext():removeUIByName(...)
end

function UIManager:hasUI(...)
	return self:curContext():hasUI(...)
end

function UIManager:pushQueueUI(ui)
	self:curContext():pushQueueUI(ui)
end

function UIManager:clearQueue()
	self:curContext():clearQueue()
end

function UIManager:getUIByName(name)
	return self:curContext():getUIByName(name)
end

function UIManager:getUIByTag(tag)
	return self:curContext():getUIByTag(tag)
end

function UIManager:getUIFromQueueByName(name)
	return self:curContext():getUIFromQueueByName(name)
end

return UIManager