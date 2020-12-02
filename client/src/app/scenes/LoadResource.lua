-- @Author: fangcheng
-- @Date:   2019-09-27 22:37:23
-- @remark: 资源加载场景

local LoadResource = class("LoadResource", G_Class.SceneBase)

local OPEN_LOG = true
local function log_print(...)
	if OPEN_LOG == true then
		print(...)
	end 
end

function LoadResource:onCreate()
	LoadResource.super.onCreate(self)

	self.ui = G_Helper.loadStudioFile("scenes.UI_LoadResource", self)
    self:addChild(self.ui.root)

    self.totalWidth = self.ui.Image_LoadBG:getContentSize().width
    self.panelheight = self.ui.Panel_Load:getContentSize().height
    self:updateUI(0.0)

    self.loader = G_Class.LoadAsync.new()
end

-- @brief 设置下一个场景的信息
-- @param curSceneID 正在运行的场景ID
-- @param sceneID 下一个运行的场景id
-- @param args 要传递给场景的参数
function LoadResource:setNextSceneInfo(curSceneID, sceneID, args)
	self.nextSceneInfo = {}
	self.nextSceneInfo["sceneID"] = sceneID
	self.nextSceneInfo["args"] = args

	-- 执行当前场景的资源释放逻辑
	if curSceneID and _MyG.SceneResourceLoadConfig[curSceneID].ReleaseResourceFunc then
		_MyG.SceneResourceLoadConfig[curSceneID].ReleaseResourceFunc(self.loader, args)
	end

	-- 执行要运行的场景的资源加载逻辑
	if _MyG.SceneResourceLoadConfig[sceneID].LoadResourceFunc then
		_MyG.SceneResourceLoadConfig[sceneID].LoadResourceFunc(self.loader, args)
	end

	-- 延迟一帧执行,方便外部对loader添加自定义任务
	performWithDelay(self, function()
		self:start()
	end, 1 / 60)
end

function LoadResource:getNextSceneInfo()
	return self.nextSceneInfo
end

function LoadResource:updateUI(percent)
	percent = math.max(percent, 0.0)
	percent = math.min(percent, 1.0)
	self.uiPercent = percent
	self.ui.ldrunning:setPositionX(percent * self.totalWidth)
	self.ui.Panel_Load:setContentSize({width = percent * self.totalWidth, height = self.panelheight})
end

---------------------------------------------------------------------------------------------------------

function LoadResource:start()
	log_print("开始执行...")

	if self.startTag then
		error("~~~~~~~~~~~~~")
		return
	end

	local processCallback = function(taskPercent, totalPercent, pipe)
		self:updateUI(totalPercent)
	end

	local finishCallback = function(pipe)
		self:loadFinish()
	end

	local errorCallback = function(msg, pipe)
		print("加载失败:", msg)
	end

	self.loader:start(processCallback, finishCallback, errorCallback)
	self.startTag = true
end

function LoadResource:loadFinish()
	log_print("执行完毕,进入下一场景...")
	_MyG.ScenesManager:runScene(self.nextSceneInfo["sceneID"], self.nextSceneInfo["args"])
end

return LoadResource