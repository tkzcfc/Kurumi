-- @Author : fangcheng
-- @Date   : 2020-02-29 21:23:48
-- @remark : 


local Vector = require("commonlib.class.Vector")

local UIContext = class("UIContext")

property(UIContext, "pDefaultRootNode")

function UIContext:ctor()
	self.tCurrentUIs = Vector:new()
	self.tCacheUIQueue = Vector:new(true)
	self.pCurQueueUI = nil
end

-- @brief 获取当前最顶层UI
function UIContext:getTopUI()
	if self.tCurrentUIs:size() > 0 then
		return self.tCurrentUIs:back()
	end
end

-- @brief 关闭当前最顶层UI
function UIContext:popUI()
	local top = self:getTopUI()
	if top then
		top:dismiss()
		return true
	end
	return false
end

-- @brief 移除所有UI
function UIContext:removeAllUI()
	self:clearQueue()

	for i = self.tCurrentUIs:size(), 1, -1 do
		local ui = self.tCurrentUIs:at(i)
		ui:forceRemove()
	end
	assert(self.tCurrentUIs:size() == 0)
	self.tCurrentUIs = Vector:new()
end

-- @brief 通过UI名称移除UI
-- @param name UI名称
-- @param force 是否强制移除
function UIContext:removeUIByName(name, force)
	for key, ui in ipairs(self.tCurrentUIs) do
		if ui.__cname == name then
			ui:dismiss(force)
			break
		end
	end
end

-- @brief 判断是否存在
-- @param cls 为字符串时,判断是否存在名称为xxx的UI,为table时则一一判断
function UIContext:hasUI(cls)
	if type(cls) == type("") then
		cls = { cls }
	end
	for i = self.tCurrentUIs:size(), 1, -1 do
		local ui = self.tCurrentUIs:at(i)
		local classname = ui.__cname
		if classname and G_Helper.findEleInTab(cls, classname) ~= nil then
			return true
		end
	end
	return false
end

-- @brief 入队UI缓存,进入此缓存后会自动弹出UI
function UIContext:pushQueueUI(ui)
	self.tCacheUIQueue:pushBack(ui)
	self:checkQueueNext()
end

-- @brief 检查UI队列
function UIContext:checkQueueNext()
	if not self.pCurQueueUI and self.tCacheUIQueue:size() > 0 then
		self.pCurQueueUI = self.tCacheUIQueue:front()
		self:pushUI(self.pCurQueueUI)

		self.tCacheUIQueue:popFront()
	end
end

-- @brief 清理UI队列
function UIContext:clearQueue()
	self.tCacheUIQueue:clear()
	self.tCacheUIQueue = Vector:new(true)
	self.pCurQueueUI = nil
end

-- @brief 通过名称获取UI
function UIContext:getUIByName(name)
	for i, ui in ipairs(self.tCurrentUIs) do
		if ui.__cname == name then
			return ui
		end
	end
end

-- @brief通过标记获取UI
function UIContext:getUIByTag(tag)
	for i, ui in ipairs(self.tCurrentUIs) do
		if ui:getTag() == tag then
			return ui
		end
	end
end

-- @brief 通过名称获取在UI队列的UI
function UIContext:getUIFromQueueByName(name)
	if not self.tCacheUIQueue then
		return
	end

	for i, ui in ipairs(self.tCacheUIQueue) do
		if ui.__cname == name then
			return ui
		end
	end
end

------------------------------------------- ------------------  private  ------------------------------------------- ------------------
-- @brief 
function UIContext:pushUI(ui)
	local unique = ui:getIsFullScreen()

	local parentNode = self.pDefaultRootNode
	if parentNode == nil then
		parentNode = cc.Director:getInstance():getRunningScene()
	end
	
	parentNode:addChild(ui)
	ui:setAnchorPoint(0.5, 0.5)
	ui:setPosition(display.cx, display.cy)
	
	-- 独占模式
	if unique then
		ui.__cache_unique_tag = true
		local curWindow
		for i = self.tCurrentUIs:size(), 1, -1 do
			curWindow = self.tCurrentUIs:at(i)
			-- 判断该UI可以被优化并且此UI的Zorder值小于要独占的UI
			if curWindow:getCanOptimize() and curWindow:getLocalZOrder() <= ui:getLocalZOrder() then
				curWindow:setVisible(false)
			end
		end
	end

	-- 获取当前最顶层的UI并隐藏它的黑色遮罩层
	local topWindow = self:getTopUI()
	if topWindow and topWindow:isShowMask() then
		topWindow:hideMask()
	end

	-- UI入队
	self.tCurrentUIs:pushBack(ui)
	G_SysEventEmitter:emit(SysEvent.UI_SHOW_START, ui, unique)
end

-- @brief UI显示完毕
function UIContext:uiShowFinish(ui)
	G_SysEventEmitter:emit(SysEvent.UI_SHOW_FINISH, ui, ui.__cache_unique_tag)
end

-- @brief 移除某个UI,Window内部调用,不要手动调用
function UIContext:removeUI_(ui)
	local bIsQueWindow = ui == self.pCurQueueUI
	local unique = ui.__cache_unique_tag

	if not self.tCurrentUIs:eraseObject(ui) then
		return
	end

	G_SysEventEmitter:emit(SysEvent.UI_DISMISS, ui, unique)
	ui:removeFromParent()

	-- 独占模式
	if unique then
		for i = self.tCurrentUIs:size(), 1, -1 do
			ui = self.tCurrentUIs:at(i)
			ui:setVisible(true)
			if ui.__cache_unique_tag then
				break
			end
		end
	end

	-- 恢复之前UI的遮罩显示
	ui = self:getTopUI()
	if ui and ui:isShowMask() then
		ui:showMask()
	end

	if bIsQueWindow then
		self.pCurQueueUI = nil
		self:checkQueueNext()
	end
end

return UIContext