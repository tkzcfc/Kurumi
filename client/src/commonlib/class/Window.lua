-- @Author : fangcheng
-- @Date   : 2019-10-17 21:26:05
-- @remark : 窗口基类

local EventEmitter = import(".EventEmitter")
local Window = class("Window", function() return ccui.Layout:create() end)

function Window:ctor()
	-- 是否可以对本UI优化显示,即在新的UI以独占模式弹出后是否能隐藏本窗口
	-- 默认可以对本UI优化
	self.canOptimizeTag = true

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

function Window:onTouchBegan(touch, event)
	if self.autoDismissTag then
		if self.contentView then
			self.touchContentViewBeginTag = not self:isContainContentView(touch, event)
		else
			self.touchContentViewBeginTag = true
		end
	end
	return true
end

-- @brief 触摸结束,窗口自动关闭判定逻辑
function Window:onTouchEnded(touch, event)
	if not self.autoDismissTag then
		return
	end

	if self.touchContentViewBeginTag and not self:isContainContentView(touch, event) then
		self:dismiss()
	end

	self.touchContentViewBeginTag = false
end

-- @brief 隐藏遮罩
function Window:hideMask()
	self:setBackGroundColorOpacity(0)
	com_log("hideMask----------------->>>", tostring(self))
end

-- @brief 显示遮罩
function Window:showMask()
	self:setBackGroundColorOpacity(130)
	com_log("showMask----------------->>>", tostring(self))
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

-- @brief 是否点击到contentView
function Window:isContainContentView(touch, event)
	if self.contentView == nil then
		return false
	end

	-- local parent = self.contentView:getParent()
	-- if parent == nil then return false end
	-- local location = parent:convertToNodeSpace(touch:getLocation())
	-- return cc.rectContainsPoint(self.contentView:getBoundingBox(), location)

	-- 调用C++的区域判断更准确
	local location = touch:getLocation()
	return CTools:isInRect(self.contentView, location.x, location.y)
end


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
		if self.runOpenActionTag then
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

---------------------------------------public---------------------------------------
-- 获取窗口管理器
function Window:getWinManager()
	if self.winManager == nil then
		self.winManager = G_WindowManager
	end
	return self.winManager
end

-- @brief 设置窗口管理器
function Window:setWinManager(manager)
	self.winManager = manager
end

-- @brief 设置UI内容显示节点
function Window:setContentView(contentView)
	self.contentView = contentView
end

-- @brief 显示UI
-- @param runAction 是否执行动画
-- @param parentNode 父节点，为空则父节点为当前场景
-- @param unique 是否为独占模式
function Window:show(runAction, parentNode, unique)
	self:iBeforeOpenedWindow()
	self:getWinManager():addWindow(self, parentNode, unique)
	if runAction ~= false then
		self:iRunOpenActionBegin()
	else
		self:iAfterOpenedWindow()
	end


end

-- @brief 是否启用关闭动画
function Window:setEnableCloseAnimation(enable)
	self.enableCloseAnimationTag = enable
end

-- @brief 使本窗口不接受关闭响应，除非调用dismiss函数时参数force为true
function Window:eternal()
	self.eternalTag = true
end

-- @brief 关闭UI
-- @param force 是否强制关闭
function Window:dismiss(force)
	self:doDismiss(force)
end

-- @brief 关闭UI
-- @param force 是否强制关闭
function Window:doDismiss(force)
	if self.eternalTag and not force then
		return
	end

	-- 正在执行打开窗口动画
	if self.runOpenActionTag then
		return
	end

	-- 保证此函数只执行一次
	if self.executeDismissTag then
		return
	end
	self.executeDismissTag = true

	self:iWillCloseWindow()
	if self.enableCloseAnimationTag then
		self:iCloseActionBegin()
	else
		self:iAfterClosedWindow()
	end
end

-- @brief 设置UI点击空白处自动关闭
function Window:setAutoDismiss()
	self.autoDismissTag = true
end

-- @brief 取消UI点击空白处自动关闭
function Window:disEnableAutoDismiss()
	self.autoDismissTag = false
end

-- @brief 禁止对本UI优化显示
function Window:keepOutOptimize()
	self.canOptimizeTag = false
end

-- @brief 是否可以对本UI优化显示
function Window:canOptimize()
	return self.canOptimizeTag
end

-- @brief 本窗口事件订阅
function Window:on(...)
	if self.eventEmitter == nil then
		self.eventEmitter = EventEmitter.new()
	end
	return self.eventEmitter:on(...)
end

-- @brief订阅一次本窗口事件订阅
function EventEmitter:once(...)
	if self.eventEmitter == nil then
		self.eventEmitter = EventEmitter.new()
	end
	return self.eventEmitter:once(...)
end

-- @brief 取消本窗口事件订阅
function Window:off(...)
	if self.eventEmitter then
		self.eventEmitter:off(...)
	end
end

-- @brief 派发本窗口事件
function Window:emit(event, ...)
	if self.eventEmitter then
		self.eventEmitter:off(event, ...)
	end
end


----------------------------------------interface----------------------------------------
-- @brief UI界面打开动画
function Window:iRunOpenActionBegin()
	if not self.contentView then
		self:iAfterOpenedWindow()
		return
	end

	self.runOpenActionTag = true
	
    self.contentView:setScale(0.3)
    local actionEnd = function()
		self:iAfterOpenedWindow()
    end
    local q = cc.Sequence:create(cc.ScaleTo:create(0.25, 1.1), cc.ScaleTo:create(0.1, 1.0), cc.CallFunc:create(actionEnd))
    self.contentView:runAction(q)

    -- 启用关闭动画
    self:setEnableCloseAnimation(true)
end

-- @brief UI界面关闭动画
function Window:iCloseActionBegin()
	if not self.contentView then
		self:iAfterClosedWindow()
		return
	end

    self.contentView:setScale(1.0)
    local actionEnd = function()
        self:iAfterClosedWindow() 
    end
    local q = cc.Sequence:create(cc.ScaleTo:create(0.1, 1.1), cc.ScaleTo:create(0.25, 0.5), cc.CallFunc:create(actionEnd))
    self.contentView:runAction(q)
end

-- @brief UI界面打开之前的回调
function Window:iBeforeOpenedWindow()
	com_log("iBeforeOpenedWindow------------>>")
	self:emit("onBeforeOpenedWindow")
end

-- @brief UI界面打开后的回调
function Window:iAfterOpenedWindow()
	com_log("iAfterOpenedWindow------------>>")
	self.runOpenActionTag = false
	self:emit("onAfterOpenedWindow")
	G_SysEventEmitter:emit("event_WindowShowFinish", self)
end

-- @brief UI界面关闭前的回调
function Window:iWillCloseWindow()
	com_log("iWillCloseWindow------------>>")
	self:emit("onWillCloseWindow")
end

-- @brief UI界面关闭后的回调
function Window:iAfterClosedWindow()
	com_log("iAfterClosedWindow------------>>")
	self:emit("onAfterClosedWindow")
	self:getWinManager():removeWindow(self)
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
	if self.eventEmitter then
		self.eventEmitter:clear()
	end
	self.winManager = nil
	collectgarbage("collect")
end

return Window
