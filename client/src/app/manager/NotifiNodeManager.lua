-- @Author: fangcheng
-- @Date:   2020-11-08 21:49:00
-- @remark: 通知节点管理(常驻节点)

local NotifiNodeManager = class("NotifiNodeManager", import(".BaseManager"))

-- @brief 添加子节点
function NotifiNodeManager:add(node, zorder, tag)
	self:changeEventDispatcher(node)
    if tag then
        self.notificationNode:addChild(node, zorder, tag)
    elseif zorder then
        self.notificationNode:addChild(node, zorder)
    else
        self.notificationNode:addChild(node)
    end
end

-- @brief 获取子节点
function NotifiNodeManager:getChildNode(nodeName)
	return self.notificationNode:getChildByName(nodeName)
end

-- @brief 在常驻节点上显示窗口
function NotifiNodeManager:showWindow(window)
	window:setWinManager(self.winContext)
	window:show()

	window:enableTouchListener(false)
	self:changeEventDispatcher(window)
	window:enableTouchListener(true)
end

-- @brief 获取常驻节点
function NotifiNodeManager:getNotificationNode()
	return self.notificationNode
end

-- @brief 获取常驻节点窗口管理器
function NotifiNodeManager:getWinContext()
	return self.winContext
end

-- @brief 更改节点及其子节点的触摸事件派发器
function NotifiNodeManager:changeEventDispatcher(rootNode)
	if rootNode:getEventDispatcher() ~= self.eventDispatcher then
		if rootNode.isTouchEnabled and rootNode:isTouchEnabled() then
			rootNode:setTouchEnabled(false)
			rootNode:setEventDispatcher(self.eventDispatcher)
			rootNode:setTouchEnabled(true)
		else
			rootNode:setEventDispatcher(self.eventDispatcher)
		end
	end

	local children = rootNode:getChildren()
	if #children < 1 then
		return
	end

	for k,v in pairs(children) do
		self:changeEventDispatcher(v)
	end
end

------------------------------------------------------ private ------------------------------------------------------

propertyReadOnly(NotifiNodeManager, "pMaskLayer")


function NotifiNodeManager:override_onInit()
	NotifiNodeManager.super.override_onInit(self)
	self:initNotificationNode()
	self:initWindowManager()

	-- 创建UI mask层
	local maskLayer = ccui.Layout:create()
	maskLayer:setContentSize(display.size)
	maskLayer:setBackGroundColorType(ccui.LayoutBackGroundColorType.solid)
	maskLayer:setBackGroundColor(cc.c3b(0, 0, 0))
	maskLayer:setBackGroundColorOpacity(255)
	maskLayer:hide()
	self:add(maskLayer, Const.WindowZ.UI_MASK)
	maskLayer:setTouchEnabled(true)
	self.pMaskLayer = maskLayer
end

function NotifiNodeManager:initNotificationNode()
	-- 新建一个事件派发器
	local eventDispatcher = cc.EventDispatcher:new()
	eventDispatcher:setEnabled(true)
	eventDispatcher:retain()
	
	-- 是否吞没事件,每次touchbegin事件经过eventDispatcher派发后如果该值为true,则表明
	-- eventDispatcher事件派发器中有节点吞没了事件
	local swallowTouchEnable = false
	
	-- 订阅一个层级很低的事件,如果事件派发到此处了,则说明本次事件派发没有节点吞没事件
	local listener = cc.EventListenerTouchOneByOne:create()
	listener:setSwallowTouches(true)
	listener:registerScriptHandler(function(touch, event)
		swallowTouchEnable = false
	    return true
	end, cc.Handler.EVENT_TOUCH_BEGAN)
	eventDispatcher:addEventListenerWithFixedPriority(listener, 0xffff)

	-- 订阅一个层级很高的事件,然后用新的事件派发器先进行事件派发
	local listener = cc.EventListenerTouchOneByOne:create()
	listener:setSwallowTouches(true)
	listener:registerScriptHandler(function(touch, event)
		swallowTouchEnable = true
		eventDispatcher:dispatchEvent(event)
	    return swallowTouchEnable
	end, cc.Handler.EVENT_TOUCH_BEGAN)
	
	listener:registerScriptHandler(function(touch, event)
		eventDispatcher:dispatchEvent(event)
	end, cc.Handler.EVENT_TOUCH_MOVED )
	
	listener:registerScriptHandler(function(touch, event)
		eventDispatcher:dispatchEvent(event)
	end, cc.Handler.EVENT_TOUCH_ENDED)
	
	listener:registerScriptHandler(function(touch, event)
		eventDispatcher:dispatchEvent(event)
	end, cc.Handler.EVENT_TOUCH_CANCELLED)
	
	-- 常驻节点创建
	local notificationNode = cc.Node:create()
	-- 触摸事件订阅
	cc.Director:getInstance():getEventDispatcher():addEventListenerWithFixedPriority(listener, -0xffff)
	cc.Director:getInstance():setNotificationNode(notificationNode)

	self.notificationNode = notificationNode
	self.eventDispatcher = eventDispatcher
	self.notifiTouchListener = listener
end

function NotifiNodeManager:initWindowManager()
	local winContext = G_Class.WindowContext.new()
	winContext:setDefaultWindowNode(self.notificationNode)
	self.winContext = winContext
end

-- @brief 销毁时调用
function NotifiNodeManager:override_onDestroy()
    NotifiNodeManager.super.override_onDestroy(self)

    cc.Director:getInstance():getEventDispatcher():removeEventListener(self.notifiTouchListener)
    self.notifiTouchListener = nil

    cc.Director:getInstance():setNotificationNode(nil)

	oRoutine(o_once(function()
		o_wait(o_seconds(5))
		if self.eventDispatcher then
			self.eventDispatcher:release()
			self.eventDispatcher = nil
		end
	end))
end


return NotifiNodeManager
