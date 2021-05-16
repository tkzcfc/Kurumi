-- @Author : fangcheng
-- @Date   : 2020-02-29 21:23:48
-- @remark : 窗口Context


local Vector = require("commonlib.class.Vector")

local WindowContext = class("WindowContext")

property(WindowContext, "pDefaultWindowNode")

function WindowContext:ctor()
	self.tArrWindows = Vector:new()
	self.tWindowQueue = Vector:new(true)
	self.pCurQueueWindow = nil
end

-- @brief 获取当前最顶层窗口
function WindowContext:getTopWindow()
	if self.tArrWindows:size() > 0 then
		return self.tArrWindows:back()
	end
end

-- @brief 关闭当前最顶层窗口
function WindowContext:popWindow()
	local top = self:getTopWindow()
	if top then
		top:dismiss()
		return true
	end
	return false
end

-- @brief 移除所有窗口
function WindowContext:removeAllWindow()
	self:clearQueue()

	for i = self.tArrWindows:size(), 1, -1 do
		local window = self.tArrWindows:at(i)
		window:setPlayCloseAction(false)
		window:dismiss(true)
	end
	self.tArrWindows = Vector:new()
end

-- @brief 通过窗口名称移除窗口
-- @param winName 窗口名称
-- @param force 是否强制移除
function WindowContext:removeWindowByName(winName, force)
	for key, window in ipairs(self.tArrWindows) do
		if window.__cname == winName then
			window:dismiss(force)
			break
		end
	end
end

-- @brief 判断是否存在
-- @param cls 为字符串时,判断是否存在名称为xxx的窗口,为table时则一一判断
function WindowContext:hasWindow(cls)
	if type(cls) == type("") then
		cls = { cls }
	end
	for i = self.tArrWindows:size(), 1, -1 do
		local window = self.tArrWindows:at(i)
		local classname = window.__cname
		if classname and G_Helper.findEleInTab(cls, classname) ~= nil then
			return true
		end
	end
	return false
end

-- @brief 入队窗口缓存,进入此缓存后会自动弹出窗口
function WindowContext:pushQueueWindow(window)
	self.tWindowQueue:pushBack(window)
	self:checkQueueNext()
end

-- @brief 检查窗口队列
function WindowContext:checkQueueNext()
	if not self.pCurQueueWindow and self.tWindowQueue:size() > 0 then
		self.pCurQueueWindow = self.tWindowQueue:front()
		self:addWindow(self.pCurQueueWindow)

		self.tWindowQueue:popFront()
	end
end

-- @brief 清理窗口队列
function WindowContext:clearQueue()
	self.tWindowQueue:clear()
	self.tWindowQueue = Vector:new(true)
	self.pCurQueueWindow = nil
end

-- @brief 通过名称获取窗口
function WindowContext:getWindowByName(name)
	for i, window in ipairs(self.tArrWindows) do
		if window.__cname == name then
			return window
		end
	end
end

-- @brief通过标记获取窗口
function WindowContext:getWindowByTag(tag)
	for i, window in ipairs(self.tArrWindows) do
		if window:getTag() == tag then
			return window
		end
	end
end

-- @brief 通过名称获取在窗口队列的窗口
function WindowContext:getWindowFromQueueByName(name)
	if not self.tWindowQueue then
		return
	end

	for i, window in ipairs(self.tWindowQueue) do
		if window.__cname == name then
			return window
		end
	end
end

------------------------------------------- ------------------  private  ------------------------------------------- ------------------
-- @brief 添加一个window,Window内部调用
-- @param window
-- @param parentNode 父节点,为空则默认取当前场景
function WindowContext:addWindow(window, parentNode)
	local unique = window:getIsFullScreen()
	if parentNode == nil then
		parentNode = self.pDefaultWindowNode or cc.Director:getInstance():getRunningScene()
		if parentNode == nil then
			com_log("[ERROR]: WindowContext parentNode == nil")
			return false
		end
	end

	parentNode:addChild(window)
	window:setAnchorPoint(0.5, 0.5)
	window:setPosition(display.center)
	
	-- 独占模式
	if unique then
		window.__cache_window_tag = true
		local curWindow
		for i = self.tArrWindows:size(), 1, -1 do
			curWindow = self.tArrWindows:at(i)
			-- 判断该窗口可以被优化并且此窗口的Zorder值小于要独占的窗口
			if curWindow:getCanOptimize() and curWindow:getLocalZOrder() <= window:getLocalZOrder() then
				curWindow:setVisible(false)
			end
		end
	end

	-- 获取当前最顶层的窗口并隐藏它的黑色遮罩层
	local topWindow = self:getTopWindow()
	if topWindow and topWindow:isShowMask() then
		topWindow:hideMask()
	end

	-- 窗口入队
	self.tArrWindows:pushBack(window)
	G_SysEventEmitter:emit("event_WindowShowStart", window, unique)

	return true
end

-- @brief 窗口显示完毕
function WindowContext:windowShowFinish(window)
	G_SysEventEmitter:emit("event_WindowShowFinish", window, window.__cache_window_tag)
end

-- @brief 移除某个窗口,Window内部调用,不要手动调用
function WindowContext:removeWindow_(window)
	local bIsQueWindow = window == self.pCurQueueWindow
	local unique = window.__cache_window_tag

	if not self.tArrWindows:eraseObject(window) then
		return
	end

	G_SysEventEmitter:emit("event_WindowDismiss", window, unique)
	window:removeFromParent()

	-- 独占模式
	if unique then
		for i = self.tArrWindows:size(), 1, -1 do
			window = self.tArrWindows:at(i)
			window:setVisible(true)
			if window.__cache_window_tag then
				break
			end
		end
	end

	-- 恢复之前窗口的遮罩显示
	window = self:getTopWindow()
	if window and window:isShowMask() then
		window:showMask()
	end

	if bIsQueWindow then
		self.pCurQueueWindow = nil
		self:checkQueueNext()
	end
end

return WindowContext