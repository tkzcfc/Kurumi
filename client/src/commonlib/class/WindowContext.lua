-- @Author : fangcheng
-- @Date   : 2020-02-29 21:23:48
-- @remark : 窗口Context


local Vector = require("commonlib.class.Vector")

local WindowContext = class("WindowContext")

property(WindowContext, "pDefaultWindowNode")

function WindowContext:ctor()
	self.arrWindows = Vector:new()
end

-- @brief 获取当前最顶层窗口
function WindowContext:getTopWindow()
	if self.arrWindows:size() > 0 then
		return self.arrWindows:back()
	end
end

-- @brief 关闭当前最顶层窗口
function WindowContext:popWindow()
	local pop = self:getTopWindow()
	if pop then
		pop:dismiss()
		return true
	end
	return false
end

-- @brief 移除所有窗口
-- except_cls 除了这个之外
function WindowContext:removeAllWindow(except_cls)
	except_cls = except_cls or ""
	for i = self.arrWindows:size(), 1, -1 do
		local window = self.arrWindows:at(i)
		if window.__cname ~= except_cls then
			window:dismiss()
		end
	end

	self:clearQueue()
end

-- @brief 清除所有数据
function WindowContext:clear()
	self.arrWindows:clear()
	self:clearQueue()
end

-- @brief 通过窗口tag移除窗口
function WindowContext:removeWindowByTag(tag)
	for key, window in ipairs(self.arrWindows) do
		if window:getTag() == tag then
			window:dismiss()
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
	for i = self.arrWindows:size(), 1, -1 do
		local window = self.arrWindows:at(i)
		local classname = window.__cname
		if classname and G_Helper.findEleInTab(cls, classname) ~= nil then
			return true
		end
	end
	return false
end

-- @brief 入队窗口缓存,进入此缓存后会自动弹出窗口
function WindowContext:pushQueueWindow(window)
	if not self.windowQueue then
		self.windowQueue = { }
	end

	window:retain()
	table.insert(self.windowQueue, window)

	self:checkQueueNext()
end

-- @brief 检查窗口队列
function WindowContext:checkQueueNext()
	if not self.curQueueWindow and #self.windowQueue > 0 then
		self.curQueueWindow = self.windowQueue[1]
		table.remove(self.windowQueue, 1)

		self:addWindow(self.curQueueWindow)
		self.curQueueWindow:release()
	end
end

-- @brief 清理窗口队列
function WindowContext:clearQueue()
	if self.windowQueue then
		for key, var in ipairs(self.windowQueue) do
			var:release()
		end
		self.windowQueue = nil
	end
	self.curQueueWindow = nil
end

-- @brief 通过名称获取窗口
function WindowContext:getWindowByName(name)
	for i, window in ipairs(self.arrWindows) do
		if window.__cname == name then
			return window
		end
	end
end

-- @brief通过标记获取窗口
function WindowContext:getWindowByTag(tag)
	for i, window in ipairs(self.arrWindows) do
		if window:getTag() == tag then
			return window
		end
	end
end

-- @brief 通过名称获取在窗口队列的窗口
function WindowContext:getWindowFromQueueByName(name)
	if not self.windowQueue then
		return
	end

	for i, window in ipairs(self.windowQueue) do
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
		for i = self.arrWindows:size(), 1, -1 do
			curWindow = self.arrWindows:at(i)
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
	self.arrWindows:pushBack(window)
	G_SysEventEmitter:emit("event_WindowShow", window, unique)

	return true
end

-- @brief 移除某个窗口,Window内部调用,不要手动调用
function WindowContext:removeWindow(window)
	local bIsQueWindow = window == self.curQueueWindow
	local unique = window.__cache_window_tag

	if not self.arrWindows:eraseObject(window) then
		return
	end

	G_SysEventEmitter:emit("event_WindowDismiss", window, unique)

	window:removeFromParent()

	-- 独占模式
	if unique then
		for i = self.arrWindows:size(), 1, -1 do
			window = self.arrWindows:at(i)
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
		self.curQueueWindow = nil
		self:checkQueueNext()
	end
end

return WindowContext