-- @Author : fangcheng
-- @Date   : 2020-02-29 21:23:48
-- @remark : 


local Vector = require("commonlib.class.Vector")


local UIState = enum {
	-- 等待打开
	"WAIT",
	-- 正在打开
	"OPENING",
	-- 正在运行
	"RUNNING",
	-- 正在关闭
	"CLOSING",
	-- 已关闭
	"CLOSED",
	-- 已销毁
	"DESTROYED"
}


------------------------------------------  UIInfo  ------------------------------------------

local UIInfo  = class("UIInfo")

function UIInfo:ctor(ui, parent, unique, zorder)
	local node = ccui.Layout:create()
	node:setContentSize(display.size)
	node:setBackGroundColorType(ccui.LayoutBackGroundColorType.solid)
	node:setBackGroundColor(cc.c3b(0, 0, 0))
	node:setAnchorPoint(0.5, 0.5)
	node:setPosition(display.cx, display.cy)
	node:setLocalZOrder(zorder)
	parent:addChild(node)

	node:addChild(ui)

	self.state = UIState.WAIT
	self.ui = ui
	self.node = node
	self.zorder = zorder
	self.unique = unique

	self:hide()
end

function UIInfo:equal(ui)
	if type(ui) == "string" then
		return self.ui.__cname == ui		
	end
	return self.ui == ui
end

function UIInfo:show()
	self.node:setVisible(true)
end

function UIInfo:hide()
	self.node:setVisible(false)
end

function UIInfo:showMask(show)
	if show then
		self.node:setBackGroundColorOpacity(130)
	else
		self.node:setBackGroundColorOpacity(0)
	end
end

function UIInfo:doOpen(callback)
	assert(self.state == UIState.WAIT);
	self.state = UIState.OPENING
	self:show()
	
	self.ui:_doUIOpen(function()
		if self.state == UIState.DESTROYED then
			return
		end 
		self.state = UIState.RUNNING
		callback()
	end)
end

function UIInfo:canClose()
	if self.state == UIState.RUNNING then
		return self.ui:_canCloseUI()
	end
	return false
end

function UIInfo:doClose(callback)
	assert(self.state == UIState.RUNNING)
	self.state = UIState.CLOSING
	self.ui:_doUIClose(function()
		if self.state == UIState.DESTROYED then 
			return
		end 
		self.state = UIState.CLOSED
		callback()
	end)
end

function UIInfo:doDestroy()
	if self.state == UIState.DESTROYED then
		return
	end
	self.ui:onDestroy()
	self.ui.pUICtx = nil
	self.node:removeFromParent()

	self.node = nil
	self.ui = nil
	self.state = UIState.DESTROYED
end







------------------------------------------  UIContext  ------------------------------------------

local UIContext = class("UIContext")

property(UIContext, "pDefaultRootNode")

function UIContext:ctor()
	self.tWaitOpenUIs = Vector:new()
	self.tCurrentUIs = Vector:new()
end

-- @brief pushUI
-- @param ui
-- @param unique 是否为独占模式
-- @param zorder 层级
function UIContext:pushUI(ui, unique, zorder)
	local parentNode = self.pDefaultRootNode
	if parentNode == nil then
		self.pDefaultRootNode = cc.Director:getInstance():getRunningScene()
		parentNode = self.pDefaultRootNode
	end
	
	ui.pUICtx = self
	self.tWaitOpenUIs:pushBack(UIInfo.new(ui, parentNode, unique, zorder or 0))
	self:_doOpenUI()
end

-- @brief 弹出顶层UI
function UIContext:popTopUI()
	if self.tCurrentUIs:empty() then return end

	return self:popUI(self.tCurrentUIs:back().ui)
end

-- @brief 弹出UI
-- @param ui ui实例或ui的名称
function UIContext:popUI(ui)
	local info = self:_getUIInfo(ui)
	if info and info:canClose() then
		self:_updateUIVisible(info)
		self:_updateViewVisible(info)

		info:doClose(function()
			self:_destroyUIByInfo(info)
		end)
		return true
	end
end

-- @brief 判断是否存在
-- @param ui
function UIContext:hasUI(ui)
	return self:_getUIInfo(ui) ~= nil
end

-- @brief 销毁UI
function UIContext:destroyUI(ui)
	self:_destroyUIByInfo(self:_getUIInfo(ui))
end

-- @brief 销毁所有UI
function UIContext:destroyAllUI()
	local tmpVec = {}
	for i = self.tCurrentUIs:size(), 1, -1 do
		table.insert(tmpVec, self.tCurrentUIs:at(i))
	end
	for i = self.tWaitOpenUIs:size(), 1, -1 do
		table.insert(tmpVec, self.tWaitOpenUIs:at(i))
	end

	self.tCurrentUIs = Vector:new()
	self.tWaitOpenUIs = Vector:new()

	for k, v in pairs(tmpVec) do
		v:doDestroy()
	end
	self:_updateViewVisible()
end

function UIContext:getCurUISize()
	return self.tCurrentUIs:size()
end

-------------------------------------------------------------  private  ------------------------------------------- ------------------


function UIContext:_doOpenUI()
	if self.tWaitOpenUIs:empty() then
		return
	end

	-- 当前有UI正在打开
	local size = self.tCurrentUIs:size()
	if size > 0 and self.tCurrentUIs:back().state == UIState.OPENING then
		return
	end

	local curInfo = self.tWaitOpenUIs:popFront()
	local index = size + 1
	for i = 1, size do
		if self.tCurrentUIs:at(i).zorder > curInfo.zorder then
			index = i
			break
		end
	end
	self.tCurrentUIs:insert(index, curInfo)

	self:_updateUIMask()

	curInfo:doOpen(function()
		self:_updateUIVisible()
		self:_updateViewVisible()
		self:_doOpenUI()
	end)
end

function UIContext:_destroyUIByInfo(uiInfo)
	if uiInfo == nil then return end

	uiInfo:doDestroy()

	if self.tWaitOpenUIs:eraseObject(uiInfo) then
		return
	end

	self.tCurrentUIs:eraseObject(uiInfo)
	
	self:_updateUIMask()
	self:_updateUIVisible()
	self:_updateViewVisible()

	self:_doOpenUI()		
end

function UIContext:_getUIInfo(ui)
	for key, info in ipairs(self.tCurrentUIs) do
		if info:equal(ui) then
			return info
		end
	end

	for key, info in ipairs(self.tWaitOpenUIs) do
		if info:equal(ui) then
			return info
		end
	end
end

function UIContext:_ignore(curUIInfo, willCloseUIInfo)
	return curUIInfo == willCloseUIInfo or curUIInfo.state >= UIState.CLOSING
end

function UIContext:_updateUIMask()
	local size = self.tCurrentUIs:size()
	if size <= 0 then return end

	local hasMask = false
	for i = size, 1, -1 do
		local uiInfo = self.tCurrentUIs:at(i)

		if uiInfo.state ~= UIState.DESTROYED then
			if hasMask then
				uiInfo:showMask(false)
			else
				if uiInfo.ui:getHasMask() then
					uiInfo:showMask(true)
					hasMask = true
				else
					uiInfo:showMask(false)
				end
			end
		end
	end
end

function UIContext:_updateUIVisible(willCloseUIInfo)
	local size = self.tCurrentUIs:size()
	if size <= 0 then return end

	for i = size, 1, -1 do
		local uiInfo = self.tCurrentUIs:at(i)

		if self:_ignore(uiInfo, willCloseUIInfo) then
			-- ignore
		else
			uiInfo:show()

			-- 隐藏全屏UI之下的其他UI
			if uiInfo.ui:getIsFullScreen() then
				for j = i - 1, 1, -1  do
					self.tCurrentUIs:at(j):hide()
				end
				break
			elseif uiInfo.unique then
				for j = i - 1, 1, -1  do
					uiInfo = self.tCurrentUIs:at(j)
					if uiInfo.ui:getIsFullScreen() then
						if self:_ignore(uiInfo, willCloseUIInfo) then
							-- ignore
						else
							for k = j - 1, 1, -1  do
								self.tCurrentUIs:at(k):hide()
							end
							break
						end
					else
						if uiInfo.ui:getCanOptimize() then
							uiInfo:hide()
						else					
							uiInfo:show()
						end
					end
				end
				break
			end
		end
	end
end

function UIContext:_updateViewVisible(willCloseUIInfo)
	local show = true

	for i = 1, self.tCurrentUIs:size() do
		local uiInfo = self.tCurrentUIs:at(i)
		if not self:_ignore(uiInfo, willCloseUIInfo) and uiInfo.ui:getIsFullScreen() then
			show = false
		end
	end

	G_SysEventEmitter:emit(SysEvent.UPDATE_VIEW_VISIBLE, show)
end

return UIContext