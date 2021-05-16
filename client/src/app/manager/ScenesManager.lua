-- @Author: fangcheng
-- @Date:   2020-11-08 14:36:29
-- @remark: 场景管理器


local ScenesManager = class("ScenesManager", import(".BaseManager"))

function ScenesManager:override_onInit()
	ScenesManager.super.override_onInit(self)
	self.scenesInfoStack = G_Class.Vector:new(false)
end

-- @brief 切换场景
-- @param sceneID 场景id
-- @param args 要传递给新场景的参数
-- @param isPush 是否将当前场景push到场景栈中暂停
-- @return 如果马上执行的是资源加载/释放场景则会返回资源加载场景的运行实例
--			可以在他的任务管道添加自定义任务
function ScenesManager:switchScene(sceneID, args, isPush)
	if _MyG.SCENE_MAP[sceneID] == nil then
		self:log("[EEROR]:<1>不存在场景ID", sceneID)
		return
	end

	local curSceneID = self:getCurSceneID()

	local function doResourceScene()
		local loadResourceScene = self:runScene(_MyG.SCENE_ID_LOAD_RESOURCE, nil, isPush)
		loadResourceScene:setNextSceneInfo(curSceneID, sceneID, args)

		collectgarbage("collect")
		return loadResourceScene
	end

	-- 查询场景配置中此场景是否有资源加载逻辑

	-- 此场景没有资源加载函数
	if _MyG.SceneResourceLoadConfig[sceneID].LoadResourceFunc == nil then
	    if curSceneID ~= nil and _MyG.SCENE_MAP[curSceneID] ~= nil then
	    	-- 当前正在执行的场景有资源释放函数,则先切换至资源加载/释放场景
	    	if _MyG.SceneResourceLoadConfig[curSceneID].ReleaseResourceFunc then
	    		return doResourceScene()
	    	else
	    	-- 否则直接进入目标场景
	    		self:runScene(sceneID, args, isPush)
	    	end
	    else
	    	-- 否则直接进入目标场景
			self:runScene(sceneID, args, isPush)
	    end
	else
		-- 有资源加载逻辑,先切换至资源加载/释放场景
		return doResourceScene()
	end
end

-- @brief 推入场景
-- @param sceneID 场景id
-- @param args 要传递给新场景的参数
function ScenesManager:pushScene(sceneID, args)
	self:switchScene(sceneID, args, true)
end

-- @brief 弹出场景
function ScenesManager:popScene()
	G_AppInstance:popScene()
	self:popScenesInfo()
	G_WindowManager:pop()
end

-- @brief 是否可以弹出场景
function ScenesManager:canPopScene()
	return self.scenesInfoStack:size() > 1
end

-- @brief 获取当前运行的场景ID
function ScenesManager:getCurSceneID()
	local curInfo = self.scenesInfoStack:back()
	if curInfo then
		return curInfo.curSceneID
	end
end

-- @brief 如果场景栈中有上一个场景的信息,返回上一个场景的场景ID
function ScenesManager:getPreSceneID()
	if self.scenesInfoStack:size() > 1 then
		local curInfo = self.scenesInfoStack:at(self.scenesInfoStack:size() - 1)
		if curInfo then
			return curInfo.curSceneID
		end
	end
end

-- @brief 获取当前在运行的View
function ScenesManager:getRuningView()
	local curInfo = self.scenesInfoStack:back()
	if curInfo then
		return curInfo.runningView
	end
end

-- @brief 获取当前在运行的场景
function ScenesManager:getRunningScene()
	local curInfo = self.scenesInfoStack:back()
	if curInfo then
		return curInfo.runningScene
	end
end

------------------------------------------------- private -------------------------------------------------

-- @brief 运行场景
-- @param sceneID 场景ID
-- @param args 要传递给新场景的参数
-- @param isPush 是否为推入模式
function ScenesManager:runScene(sceneID, args, isPush)
	if _MyG.SCENE_MAP[sceneID] == nil then
		self:log("[EEROR]:<2>不存在场景ID", sceneID)
		return
	end

	-- 是推入模式,WindowContext也相应的新建一个,否则清空当前场景的所有Window
	if isPush then
		G_WindowManager:push()
	else
		G_WindowManager:removeAllWindow()
	end

	G_SysEventEmitter:emit(SysEvent.WILL_ENTER_SCENE)

	local runningView, runningScene

	if isPush then
		runningView = G_AppInstance:pushScene(_MyG.SCENE_MAP[sceneID])
	else
		self:popScenesInfo()
		runningView = G_AppInstance:enterScene(_MyG.SCENE_MAP[sceneID])
	end

	runningScene = runningView:getScene()

	self:pushScenesInfo(sceneID, runningView, runningScene)

	runningView:initWithParameter(args)

	G_SysEventEmitter:emit(SysEvent.ENTER_SCENE_FINISH)

	return runningView, runningScene
end

-- @brief 推入场景信息
function ScenesManager:pushScenesInfo(_curSceneID, _runningView, _runningScene)
	self.scenesInfoStack:pushBack({
		curSceneID = _curSceneID, 
		runningView = _runningView,
		runningScene = _runningScene,
	})
end

-- @brief 弹出场景信息
function ScenesManager:popScenesInfo()
	if not self.scenesInfoStack:empty() then
		self.scenesInfoStack:popBack()
	end
end


return ScenesManager

