-- @Author : fangcheng
-- @Date   : 2019-10-17 21:26:05
-- @remark : UI基类

local UIAction = require("commonlib.class.UIAction")
local EventEmitter = import(".EventEmitter")

local UIPanel = class("UIPanel", function() return cc.Node:create() end)

-- @brief 是否可以对本UI优化显示,即在新的UI以独占模式弹出后是否能隐藏本UI
-- @default 默认可以对本UI优化
property(UIPanel, "bCanOptimize", true)

-- @brief 点击空白处是否自动关闭
property(UIPanel, "bAutoDismiss", false)

-- @brief 点击内容节点是否可以拖动
property(UIPanel, "bEnableDrag", false)

-- @brief 此UI是否是全屏窗口
property(UIPanel, "bIsFullScreen", false)

-- @brief UI内容节点
property(UIPanel, "pContentView")

-- @brief UI打开动画
property(UIPanel, "fOpenActionCall")

-- @brief UI关闭动画
property(UIPanel, "fCloseActionCall")

-- @brief UI关闭条件
property(UIPanel, "fUICloseCondition")

-- @brief 是否显示遮罩
property(UIPanel, "bHasMask", true)

-- @brief UI所属Context
propertyReadOnly(UIPanel, "pUICtx")


function UIPanel:ctor()
	self.pEventEmitter = EventEmitter.new()
	self:enableTouchListener()
	self:setOpenActionType(UIActionType.SCALE_TO)
	self:setCloseActionType(UIActionType.SCALE_TO)
end

---------------------------------------public---------------------------------------

-- @brief 显示UI
function UIPanel:show(...)
	G_UIManager:pushUI(self, ...)
	return self
end

-- @brief 使本窗口不接受关闭响应
function UIPanel:eternal()
	self:setUICloseCondition(function() return false end)
	return self
end

-- @brief 关闭此UI
function UIPanel:dismiss()
	if self.pUICtx then
		self.pUICtx:popUI(self)
	end
end

-- @brief 销毁此UI
function UIPanel:destroy()
	if self.pUICtx then
		self.pUICtx:destroyUI(self)
	end
end

-- @brief 设置UI打开动画类型
function UIPanel:setOpenActionType(actType)
	self.fOpenActionCall = UIAction.openActions[actType]
end

-- @brief 设置UI关闭动画类型
function UIPanel:setCloseActionType(actType)
	self.fCloseActionCall = UIAction.closeActions[actType]
end

-- @brief 本窗口事件订阅
function UIPanel:eventOn(...)
	return self.pEventEmitter:on(...)
end

-- @brief订阅一次本窗口事件订阅
function UIPanel:eventOnce(...)
	return self.pEventEmitter:once(...)
end

-- @brief 取消本窗口事件订阅
function UIPanel:eventOff(...)
	if self.pEventEmitter then
		self.pEventEmitter:off(...)
	end
end

-- @brief 派发本窗口事件
function UIPanel:eventEmit(event, ...)
	if self.pEventEmitter then
		self.pEventEmitter:emit(event, ...)
	end
end

----------------------------------------interface----------------------------------------

-- @brief 界面被销毁时的回调
function UIPanel:onDestroy()
	self:eventEmit(SysEvent.UI_WILL_DESTROY)
	G_SysEventEmitter:emit(SysEvent.UI_WILL_DESTROY, self)
end

---------------------------------------- private ----------------------------------------

function UIPanel:enableTouchListener()
	-- 事件吞没
	local function onTouchBegan(touch, event)
		return self:onTouchBegan(touch, event)
	end

	local listener = cc.EventListenerTouchOneByOne:create()
	listener:setSwallowTouches(true)
	listener:registerScriptHandler(onTouchBegan, cc.Handler.EVENT_TOUCH_BEGAN)
	listener:registerScriptHandler(handler(self, self.onTouchMoved), cc.Handler.EVENT_TOUCH_MOVED)
	listener:registerScriptHandler(handler(self, self.onTouchEnded), cc.Handler.EVENT_TOUCH_ENDED)
	self:getEventDispatcher():addEventListenerWithSceneGraphPriority(listener, self)
end


function UIPanel:onTouchBegan(touch, event)
	self.touchContentViewBeginTag = self:isContainContentView(touch, event)
	return true
end

function UIPanel:onTouchMoved(touch, event)
	if self.touchContentViewBeginTag and self.bEnableDrag and self.pContentView then
		local delta = touch:getDelta()
		local x, y = self.pContentView:getPosition()
		self.pContentView:setPosition(delta.x + x, delta.y + y)
	end
end

-- @brief 触摸结束,窗口自动关闭判定逻辑
function UIPanel:onTouchEnded(touch, event)
	if self.bAutoDismiss and not self.touchContentViewBeginTag and not self:isContainContentView(touch, event) then
		self:dismiss()
	end
	self.touchContentViewBeginTag = false
end

-- @brief 是否点击到contentView
function UIPanel:isContainContentView(touch, event)
	if self.pContentView == nil then
		return false
	end

	-- local parent = self.pContentView:getParent()
	-- if parent == nil then return false end
	-- local location = parent:convertToNodeSpace(touch:getLocation())
	-- return cc.rectContainsPoint(self.pContentView:getBoundingBox(), location)

	-- 调用C++的区域判断更准确
	local location = touch:getLocation()
	return GTools:isInRect(self.pContentView, location.x, location.y)
end

function UIPanel:_doUIOpen(callback)
	self:eventEmit(SysEvent.UI_BEFORE_OPENED)
	G_SysEventEmitter:emit(SysEvent.UI_BEFORE_OPENED, self)

	self.fOpenActionCall(self, function()
		callback()
		self:eventEmit(SysEvent.UI_AFTER_OPENED)
		G_SysEventEmitter:emit(SysEvent.UI_AFTER_OPENED, self)
	end)
end

function UIPanel:_doUIClose(callback)
	self:eventEmit(SysEvent.UI_WILL_CLOSE)
	G_SysEventEmitter:emit(SysEvent.UI_WILL_CLOSE, self)

	self.fCloseActionCall(self, function()
		self:eventEmit(SysEvent.UI_AFTER_CLOSED)
		G_SysEventEmitter:emit(SysEvent.UI_AFTER_CLOSED, self)
		callback()
	end)

	return true
end

function UIPanel:_canCloseUI()
	if self.fUICloseCondition and not self.fUICloseCondition() then
		return false
	end
	return true	
end

return UIPanel
