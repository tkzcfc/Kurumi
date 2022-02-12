-- @Author : fangcheng
-- @Date   : 2019-10-17 21:26:05
-- @remark : UI基类

-- @brief 窗口默认打开动画
local function DefaultOpenAction(this, call)
	if this.pContentView == nil then 
		call()
		return
	end
    this.pContentView:setScale(0.3)

    local action = cc.Sequence:create(
    	cc.ScaleTo:create(0.25, 1.1), 
    	cc.ScaleTo:create(0.1, 1.0), 
    	cc.CallFunc:create(call)
    )
    this.pContentView:runAction(action)
end

-- @brief 窗口默认关闭动画
local function DefaultCloseAction(this, call)
	if this.pContentView == nil then 
		call()
		return
	end
    this.pContentView:setScale(1.0)

    local action = cc.Sequence:create(
    	cc.ScaleTo:create(0.1, 1.1), 
    	cc.ScaleTo:create(0.25, 0.5), 
    	cc.CallFunc:create(call)
    )
    this.pContentView:runAction(action)
end



local EventEmitter = import(".EventEmitter")
local UIPanel = class("UIPanel", function() return ccui.Layout:create() end)

-- @brief 是否可以对本UI优化显示,即在新的UI以独占模式弹出后是否能隐藏本UI
-- @default 默认可以对本UI优化
property(UIPanel, "bCanOptimize", true)

-- @brief 是否执行UI打开动画
property(UIPanel, "bPlayOpenAction", true)

-- @brief 是否执行UI关闭动画
property(UIPanel, "bPlayCloseAction", true)

-- @brief 点击空白处是否自动关闭
property(UIPanel, "bAutoDismiss", false)

-- @brief 是否正在执行UI打开动画
property(UIPanel, "bRunOpeningTag", false)

-- @brief 此UI是否是全屏窗口
property(UIPanel, "bIsFullScreen", false)

-- @brief UI内容节点
property(UIPanel, "pContentView")

-- @brief UI打开动画
property(UIPanel, "fOpenActionCall", DefaultOpenAction)

-- @brief UI关闭动画
property(UIPanel, "fCloseActionCall", DefaultCloseAction)


function UIPanel:ctor()
	self:setContentSize(display.size)
	self:setBackGroundColorType(ccui.LayoutBackGroundColorType.solid)
	self:setBackGroundColor(cc.c3b(0, 0, 0))

	-- 默认显示遮罩层
	self:setShowMask(true)
	self:enableTouchListener()
end

---------------------------------------public---------------------------------------

-- @brief 隐藏遮罩
function UIPanel:hideMask()
	self:setBackGroundColorOpacity(0)
	-- com_log("hideMask----------------->>>", tostring(self))
end

-- @brief 显示遮罩
function UIPanel:showMask()
	self:setBackGroundColorOpacity(130)
	-- com_log("showMask----------------->>>", tostring(self))
end

-- @brief 是否显示遮罩
function UIPanel:isShowMask()
	return self.showMaskTag
end

-- @brief 设置是否显示遮罩
-- @param showMaskTag 是否显示遮罩
function UIPanel:setShowMask(showMaskTag)
	self.showMaskTag = showMaskTag

	if self.showMaskTag then
		self:showMask()
	else
		self:hideMask()
	end
end

-- @brief 显示UI
function UIPanel:show()
	self:iBeforeOpened()
	G_UIManager:pushUI(self)

	if self.bPlayOpenAction then
		self.bRunOpeningTag = true
		self:iRunOpenActionBegin()
	else
		self:iAfterOpened()
	end
end

-- @brief 使本窗口不接受关闭响应，除非调用dismiss函数时参数force为true
function UIPanel:eternal()
	self.bEternalTag = true
end

-- @brief 关闭UI
-- @param force 是否强制关闭
function UIPanel:dismiss(force)
	self:doDismiss(force)
end

-- @brief 关闭UI
-- @param force 是否强制关闭
function UIPanel:doDismiss(force)
	if self.bEternalTag and not force then
		return
	end

	-- 正在执行打开动画,不接受关闭响应
	if self.bRunOpeningTag then
		return
	end

	-- 保证此函数只执行一次
	if self.bExecuteDismissTag then
		return
	end
	self.bExecuteDismissTag = true

	self:iWillClose()
	if self.bPlayCloseAction then
		self:iCloseActionBegin()
	else
		self:iAfterClosed()
	end
end

-- @brief 强制移除UI
function UIPanel:forceRemove()
	self:iWillClose()
	self:iAfterClosed()
end

-- @brief 本窗口事件订阅
function UIPanel:eventOn(...)
	if self.pEventEmitter == nil then
		self.pEventEmitter = EventEmitter.new()
	end
	return self.pEventEmitter:on(...)
end

-- @brief订阅一次本窗口事件订阅
function UIPanel:eventOnce(...)
	if self.pEventEmitter == nil then
		self.pEventEmitter = EventEmitter.new()
	end
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
-- @brief UI界面打开动画
function UIPanel:iRunOpenActionBegin()
	self.fOpenActionCall(self, handler(self, self.iAfterOpened))
end

-- @brief UI界面关闭动画
function UIPanel:iCloseActionBegin()
	self.fCloseActionCall(self, handler(self, self.iAfterClosed))
end

-- @brief UI界面打开之前的回调
function UIPanel:iBeforeOpened()
	-- com_log("iBeforeOpened------------>>")
	self:eventEmit(SysEvent.UI_BEFORE_OPENED)
end

-- @brief UI界面打开后的回调
function UIPanel:iAfterOpened()
	-- com_log("iAfterOpened------------>>")
	self.bRunOpeningTag = false
	G_UIManager:uiShowFinish(self)

	self:eventEmit(SysEvent.UI_AFTER_OPENED)
end

-- @brief UI界面关闭前的回调
function UIPanel:iWillClose()
	self:eventEmit(SysEvent.UI_WILL_CLOSE)
end

-- @brief UI界面关闭后的回调
function UIPanel:iAfterClosed()
	-- com_log("iAfterClosed------------>>")
	self:eventEmit(SysEvent.UI_AFTER_CLOSED)

	if self.pEventEmitter then
		self.pEventEmitter:clear()
		self.pEventEmitter = nil
	end

	G_UIManager:removeUI_(self)
end

---------------------------------------- private ----------------------------------------

function UIPanel:enableTouchListener()
	-- 事件吞没
	local function onTouchBegan(touch, event)
		if self.bRunOpeningTag then
			return true
		end
		return self:onTouchBegan(touch, event)
	end

	local function onTouchEnded(touch, event)
		self:onTouchEnded(touch, event)
	end

	local listener = cc.EventListenerTouchOneByOne:create()
	listener:setSwallowTouches(true)
	listener:registerScriptHandler(onTouchBegan, cc.Handler.EVENT_TOUCH_BEGAN)
	listener:registerScriptHandler(onTouchEnded, cc.Handler.EVENT_TOUCH_ENDED)
	self:getEventDispatcher():addEventListenerWithSceneGraphPriority(listener, self)
end


function UIPanel:onTouchBegan(touch, event)
	if self.bAutoDismiss then
		self.touchContentViewBeginTag = not self:isContainContentView(touch, event)
	end
	return true
end

-- @brief 触摸结束,窗口自动关闭判定逻辑
function UIPanel:onTouchEnded(touch, event)
	if not self.bAutoDismiss then
		return
	end

	if self.touchContentViewBeginTag and not self:isContainContentView(touch, event) then
		self:dismiss()
	else
		self.touchContentViewBeginTag = false
	end
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


return UIPanel
