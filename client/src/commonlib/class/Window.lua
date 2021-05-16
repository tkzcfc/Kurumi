-- @Author : fangcheng
-- @Date   : 2019-10-17 21:26:05
-- @remark : 窗口基类

-- @brief 窗口默认打开动画
local function DefaultOpenAction(window, call)
    window.pContentView:setScale(0.3)

    local action = cc.Sequence:create(
    	cc.ScaleTo:create(0.25, 1.1), 
    	cc.ScaleTo:create(0.1, 1.0), 
    	cc.CallFunc:create(call)
    )
    window.pContentView:runAction(action)
end

-- @brief 窗口默认关闭动画
local function DefaultCloseAction(window, call)
    window.pContentView:setScale(1.0)

    local action = cc.Sequence:create(
    	cc.ScaleTo:create(0.1, 1.1), 
    	cc.ScaleTo:create(0.25, 0.5), 
    	cc.CallFunc:create(call)
    )
    window.pContentView:runAction(action)
end



local EventEmitter = import(".EventEmitter")
local Window = class("Window", function() return ccui.Layout:create() end)

-- @brief 是否可以对本UI优化显示,即在新的UI以独占模式弹出后是否能隐藏本窗口
-- @default 默认可以对本UI优化
property(Window, "bCanOptimize", true)

-- @brief 是否执行窗口打开动画
property(Window, "bPlayOpenAction", true)

-- @brief 是否执行窗口关闭动画
property(Window, "bPlayCloseAction", true)

-- @brief 点击空白处是否自动关闭
property(Window, "bAutoDismiss", false)

-- @brief 是否正在执行窗口打开动画
property(Window, "bRunOpeningTag", false)

-- @brief 此窗口是否是全屏窗口
property(Window, "bIsFullScreen", false)

-- @brief 窗口内容节点
property(Window, "pContentView")

-- @brief 窗口打开动画
property(Window, "fOpenActionCall", DefaultOpenAction)

-- @brief 窗口关闭动画
property(Window, "fCloseActionCall", DefaultCloseAction)

-- @brief 窗口管理器
property(Window, "iWinManager")


function Window:ctor()
	-- 窗口管理器,默认为全局窗口管理器
	self:setWinManager(G_WindowManager)

	self:setContentSize(display.size)
	self:setBackGroundColorType(ccui.LayoutBackGroundColorType.solid)
	self:setBackGroundColor(cc.c3b(0, 0, 0))

	-- 默认显示遮罩层
	self:setShowMask(true)
	self:enableTouchListener(true)

	self:enableNodeEvents()
end

---------------------------------------public---------------------------------------

-- @brief 隐藏遮罩
function Window:hideMask()
	self:setBackGroundColorOpacity(0)
	-- com_log("hideMask----------------->>>", tostring(self))
end

-- @brief 显示遮罩
function Window:showMask()
	self:setBackGroundColorOpacity(130)
	-- com_log("showMask----------------->>>", tostring(self))
end

-- @brief 是否显示遮罩
function Window:isShowMask()
	return self.showMaskTag
end

-- @brief 设置是否显示遮罩
-- @param showMaskTag 是否显示遮罩
function Window:setShowMask(showMaskTag)
	self.showMaskTag = showMaskTag

	if self.showMaskTag then
		self:showMask()
	else
		self:hideMask()
	end
end

-- 获取窗口管理器
function Window:getWinManager()
	if self.iWinManager == nil then
		self.iWinManager = G_WindowManager
	end
	return self.iWinManager
end

-- @brief 设置窗口管理器
function Window:setWinManager(manager)
	self.iWinManager = manager
end

-- @brief 显示UI
-- @param parentNode 父节点，为空则父节点为当前场景
function Window:show(parentNode)
	self:iBeforeOpenedWindow_()
	self:getWinManager():addWindow(self, parentNode)

	if self.bPlayOpenAction and self.pContentView then
		self.bRunOpeningTag = true
		self:iRunOpenActionBegin()
	else
		self:iAfterOpenedWindow_()
	end
end

-- @brief 使本窗口不接受关闭响应，除非调用dismiss函数时参数force为true
function Window:eternal()
	self.bEternalTag = true
end

-- @brief 关闭UI
-- @param force 是否强制关闭
function Window:dismiss(force)
	self:doDismiss(force)
end

-- @brief 关闭UI
-- @param force 是否强制关闭
function Window:doDismiss(force)
	if self.bEternalTag and not force then
		return
	end

	-- 正在执行打开窗口动画
	if self.bRunOpeningTag then
		return
	end

	-- 保证此函数只执行一次
	if self.bExecuteDismissTag then
		return
	end
	self.bExecuteDismissTag = true

	self:iWillCloseWindow_()
	if self.bPlayCloseAction and self.pContentView then
		self:iCloseActionBegin()
	else
		self:iAfterClosedWindow_()
	end
end

-- @brief 本窗口事件订阅
function Window:on(...)
	if self.pEventEmitter == nil then
		self.pEventEmitter = EventEmitter.new()
	end
	return self.pEventEmitter:on(...)
end

-- @brief订阅一次本窗口事件订阅
function Window:once(...)
	if self.pEventEmitter == nil then
		self.pEventEmitter = EventEmitter.new()
	end
	return self.pEventEmitter:once(...)
end

-- @brief 取消本窗口事件订阅
function Window:off(...)
	if self.pEventEmitter then
		self.pEventEmitter:off(...)
	end
end

-- @brief 派发本窗口事件
function Window:emit(event, ...)
	if self.pEventEmitter then
		self.pEventEmitter:emit(event, ...)
	end
end

----------------------------------------interface----------------------------------------
-- @brief UI界面打开动画
function Window:iRunOpenActionBegin()
	self.fOpenActionCall(self, handler(self, self.iAfterOpenedWindow_))
end

-- @brief UI界面关闭动画
function Window:iCloseActionBegin()
	self.fCloseActionCall(self, handler(self, self.iAfterClosedWindow_))
end

-- @brief UI界面打开之前的回调
function Window:iBeforeOpenedWindow_()
	-- com_log("iBeforeOpenedWindow_------------>>")
	self:emit("onBeforeOpenedWindow")

	if self.iBeforeOpenedWindow then
		self.iBeforeOpenedWindow(self)
	end
end

-- @brief UI界面打开后的回调
function Window:iAfterOpenedWindow_()
	-- com_log("iAfterOpenedWindow_------------>>")
	self.bRunOpeningTag = false
	self:getWinManager():windowShowFinish(self)

	self:emit("onAfterOpenedWindow")

	if self.iAfterOpenedWindow then
		self.iAfterOpenedWindow(self)
	end
end

-- @brief UI界面关闭前的回调
function Window:iWillCloseWindow_()
	-- com_log("iWillCloseWindow_------------>>")
	self:emit("onWillCloseWindow")

	if self.iWillCloseWindow then
		self.iWillCloseWindow(self)
	end
end

-- @brief UI界面关闭后的回调
function Window:iAfterClosedWindow_()
	-- com_log("iAfterClosedWindow_------------>>")
	self:emit("onAfterClosedWindow")

	if self.iAfterClosedWindow then
		self.iAfterClosedWindow(self)
	end

	self:getWinManager():removeWindow_(self)
end

----------------------------------------override----------------------------------------
function Window:onEnter()
end

function Window:onExit()
end

function Window:onEnterTransitionFinish()
end

function Window:onExitTransitionStart()
end

function Window:onCleanup()
	if self.pEventEmitter then
		self.pEventEmitter:clear()
		self.pEventEmitter = nil
	end
	self.iWinManager = nil
	collectgarbage("collect")
end


---------------------------------------- private ----------------------------------------

function Window:enableTouchListener(enable)
	if enable then
		if self.windowTouchListener then return end
	else
		if self.windowTouchListener then
			self:getEventDispatcher():removeEventListener(self.windowTouchListener)
		end
		self.windowTouchListener = nil
		return
	end

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


function Window:onTouchBegan(touch, event)
	if self.bAutoDismiss then
		if self.pContentView then
			self.touchContentViewBeginTag = not self:isContainContentView(touch, event)
		else
			self.touchContentViewBeginTag = true
		end
	end
	return true
end

-- @brief 触摸结束,窗口自动关闭判定逻辑
function Window:onTouchEnded(touch, event)
	if not self.bAutoDismiss then
		return
	end

	if self.touchContentViewBeginTag and not self:isContainContentView(touch, event) then
		self:dismiss()
	end

	self.touchContentViewBeginTag = false
end

-- @brief 是否点击到contentView
function Window:isContainContentView(touch, event)
	if self.pContentView == nil then
		return false
	end

	-- local parent = self.pContentView:getParent()
	-- if parent == nil then return false end
	-- local location = parent:convertToNodeSpace(touch:getLocation())
	-- return cc.rectContainsPoint(self.pContentView:getBoundingBox(), location)

	-- 调用C++的区域判断更准确
	local location = touch:getLocation()
	return CTools:isInRect(self.pContentView, location.x, location.y)
end


return Window
