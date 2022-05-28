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
	self.contextStack:back():destroyAllUI()
	self.contextStack:popBack()
end

function UIManager:push()
	self.contextStack:pushBack(UIContext.new())
end

function UIManager:curContext()
	return self.contextStack:back()
end

function UIManager:pushUI(ui, unique, zorder)
	self:curContext():pushUI(ui, unique, zorder)
end

function UIManager:popTopUI(ui)
	self:curContext():popTopUI(ui)
end

function UIManager:popUI(ui)
	return self:curContext():popUI(ui)
end

function UIManager:hasUI(ui)
	return self:curContext():hasUI(ui)
end

function UIManager:destroyUI(ui)
	self:curContext():destroyUI(ui)
end

function UIManager:destroyAllUI()
	self:curContext():destroyAllUI()
end

function UIManager:getCurUISize()
	return self:curContext():getCurUISize()
end

return UIManager