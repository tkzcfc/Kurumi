-- @Author : fangcheng
-- @Date   : 2020-02-29 21:23:48
-- @remark : 窗口管理

local Vector = require("commonlib.class.Vector")
local WindowContext = require("commonlib.class.WindowContext")

local WindowManager = class("WindowManager")

function WindowManager:ctor()
	self.contextStack = Vector:new(false)
	self:push()
end

function WindowManager:pop()
	self.contextStack:back():clear()
	self.contextStack:popBack()
end

function WindowManager:push()
	self.contextStack:pushBack(WindowContext.new())
end

function WindowManager:curContext()
	return self.contextStack:back()
end

function WindowManager:addWindow(window, parentNode, unique)
	return self:curContext():addWindow(window, parentNode, unique)
end

function WindowManager:getTopWindow()
	return self:curContext():getTopWindow()
end

function WindowManager:popWindow()
	return self:curContext():popWindow()
end

function WindowManager:removeWindow(window)
	self:curContext():removeWindow(window)
end

function WindowManager:removeAllWindow(except_cls)
	self:curContext():removeAllWindow(except_cls)
end

function WindowManager:clear()
	self:curContext():clear()
end

function WindowManager:removeWindowByTag(tag)
	self:curContext():removeWindowByTag(tag)
end

function WindowManager:hasWindow(cls)
	return self:curContext():hasWindow(cls)
end

function WindowManager:pushQueueWindow(window)
	self:curContext():pushQueueWindow(window)
end

function WindowManager:clearQueue()
	self:curContext():clearQueue()
end

function WindowManager:getWindowByName(name)
	return self:curContext():getWindowByName(name)
end

function WindowManager:getWindowByTag(tag)
	return self:curContext():getWindowByTag(tag)
end

function WindowManager:getWindowFromQueueByName(name)
	return self:curContext():getWindowFromQueueByName(name)
end

function WindowManager:setDefaultWindowNode(node)
	self:curContext():setDefaultWindowNode(node)
end

function WindowManager:getDefaultWindowNode()
	return self:curContext():getDefaultWindowNode()
end

return WindowManager