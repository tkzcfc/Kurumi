-- @Author: fangcheng
-- @Date:   2020-11-08 14:36:29
-- @remark: view管理器


local ViewManager = class("ViewManager", import(".BaseManager"))

property(ViewManager, "pViewRoot")

function ViewManager:override_onInit()
	ViewManager.super.override_onInit(self)
	self.viewStack = G_Class.Vector:new(true)
	self.bAsyncLoad = false
end

-- @brief 是否正在加载资源
function ViewManager:isAsyncLoad()
	return self.bAsyncLoad
end

-- @brief run view
function ViewManager:runView(view)
	assert(not self.bAsyncLoad)
	local curView = self.viewStack:back()

	if curView then
		G_UIManager:pop()
		curView:removeFromParent()
		self.viewStack:popBack()
	end

	self:pushBackView(view)
end

-- @brief pop view
function ViewManager:popView()
	assert(not self.bAsyncLoad)
	local curView = self.viewStack:back()

	if curView == nil then
		return
	end

	G_UIManager:pop()
	curView:removeFromParent()
	self.viewStack:popBack()

	curView = self.viewStack:back()
	if curView then
		curView:setVisible(true)
	end

	return true
end

-- @brief push view
function ViewManager:pushView(view)
	assert(not self.bAsyncLoad)
	local curView = self.viewStack:back()
	if curView then
		curView:setVisible(false)
	end
	self:pushBackView(view)
end

-- @brief 获取view栈深度
function ViewManager:getStackDepth()
	return self.viewStack:size()
end

-- @brief 
function ViewManager:getCurView()
	return self.viewStack:back()
end

-- @brief 清理所有view
function ViewManager:clear()
	repeat
		if self.viewStack:empty() then break end
		self:popView()
	until(false)
end

-- @brief 获取当前view的名称
function ViewManager:getCurViewName()
	local curView = self:getCurView()
	if curView then
		return curView.__cname
	end
end

-- @brief 是否处于某个界面
-- @param viewName 界面名称
function ViewManager:isInView(viewName)
	local curView = self:getCurView()
	if curView then
		return curView.__cname == viewName
	end
	return false
end

------------------------------------------------- private -------------------------------------------------
function ViewManager:pushBackView(view)
	G_UIManager:push()
	G_UIManager:curContext():setDefaultRootNode(view:getUIRoot())
	
	self.pViewRoot:addChild(view)
	self.viewStack:pushBack(view)
	
	local loader = G_Class.LoadAsync.new()
	
	-- 没有可加载的资源
	if not view:onAsyncLoad(loader) then
		view:onLoadView()
		return
	end

	-- 正在加载标记
	self.bAsyncLoad = true

	local processCallback = function(taskPercent, totalPercent, pipe)
		print("totalPercent", totalPercent)
	end

	local finishCallback = function(pipe)
		self.bAsyncLoad = false
		-- 资源加载完成
		view:onLoadView()
	end

	local errorCallback = function(msg, pipe)
		print("加载失败:", msg)
	end
	loader:start(processCallback, finishCallback, errorCallback)
end

return ViewManager

