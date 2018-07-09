local msgViewBase = require("app.common.msgViewBase")

local LoadResource = class("LoadResource", msgViewBase)

LoadResource.RES_TYPE = 
{
	PLIST = 0,
	EXPORTJSON = 1,
	PNG = 2
}

function LoadResource:onCreate()
	self.super.onCreate(self)

	self.ui = _MyG.loadStudioFile("LoadResource", self)
    self:addChild(self.ui.root)

    self.totalWidth = self.ui.Image_LoadBG:getContentSize().width
    self.panelheight = self.ui.Panel_Load:getContentSize().height
    self:updateUI(0.0)

    --load
    self.loadPlistFileList = {}
    self.loadExportJsonFileList = {}
    self.loadPngFileList = {}

	self.curLoadExportJsonCount = 0
	self.curLoadPlistCount = 0
	self.curLoadPngCount = 0
	self.totalLoadCount = 0

	self.pngFileIsLoadFinish = false

	--release
    self.releasePlistFileList = {}
    self.releaseExportJsonFileList = {}
    self.releasePngFileList = {}
end

function LoadResource:onExit()
	LoadResource.super.onExit(self)
	self:stopScheduler()
end

function LoadResource:setNextSceneInfo(sceneID, transition, time, more, args)
	self.nextSceneInfo = {}
	self.nextSceneInfo["sceneID"] = sceneID
	self.nextSceneInfo["transition"] = transition
	self.nextSceneInfo["time"] = time
	self.nextSceneInfo["more"] = more
	self.nextSceneInfo["args"] = args

	local preSceneID = _MyG.GameSceneSwither:getPreSceneID()
	if preSceneID and _MyG.SceneResourceLoadConfig[preSceneID] then
		_MyG.SceneResourceLoadConfig[preSceneID].ReleaseResourceFunc(self, args)
	end
	_MyG.SceneResourceLoadConfig[sceneID].LoadResourceFunc(self, args)
end

function LoadResource:getNextSceneInfo()
	self.nextSceneInfo
end

function LoadResource:updateUI(percent)
	self.ui.ldrunning:setPositionX(percent * self.totalWidth)
	self.ui.Panel_Load:setContentSize({width = percent * self.totalWidth, height = self.panelheight})
end

----------------------------------------------------------load----------------------------------------------------------

function LoadResource:addLoadResource(type, path)	
	if self.isStart then
		print("[ERROR]资源加载已开始")
		return
	end

	if path == nil or path == "" then
		print("[ERROR]资源路径不合法")
		return
	end

	if type == LoadResource.RES_TYPE.PLIST then
		table.insert(self.loadPlistFileList, path)
		table.insert(self.loadPngFileList, string.gsub(path, ".plist", ".png"))
	elseif type == LoadResource.RES_TYPE.EXPORTJSON then
		table.insert(self.loadExportJsonFileList, path)
	elseif type == LoadResource.RES_TYPE.PNG then
		table.insert(self.loadPngFileList, path)
	else
		print("[ERROR]未知格式资源")
	end
end

function LoadResource:startLoad()
	if self.isStart then
		print("[ERROR]资源加载已开始")
		return
	end
	self.isStart = true

	self.totalLoadCount = #self.loadPlistFileList + #self.loadExportJsonFileList + #self.loadPngFileList

	--异步加载exportjson
	for i = 1, #self.loadExportJsonFileList do
		ccs.ArmatureDataManager:getInstance():addArmatureFileInfoAsync(self.loadExportJsonFileList[i], function(percent)
			self.curLoadExportJsonCount = #self.loadExportJsonFileList * percent
		end)
	end

	--异步加载图片资源
	local textureCache = cc.Director:getInstance():getTextureCache()
	for i = 1, #self.loadPngFileList do
		textureCache:addImageAsync(self.loadPngFileList[i], function(...) self:pngLoadCall(...) end)
	end
	
	--
	local scheduler=cc.Director:getInstance():getScheduler()
    self.scriptEntryID = scheduler:scheduleScriptFunc(function(...) self:loadFileUpdate(...) end,1 / 20.0,false)
end

function LoadResource:pngLoadCall()
	self.curLoadPngCount = self.curLoadPngCount + 1
	if self.curLoadPngCount >= #self.loadPngFileList then
		self.pngFileIsLoadFinish = true
	end
end

function LoadResource:loadFileUpdate()

	--加载plist文件
	if self.pngFileIsLoadFinish and self.curLoadPlistCount < #self.loadPlistFileList then
		self.curLoadPlistCount = self.curLoadPlistCount + 1
		cc.SpriteFrameCache:getInstance():addSpriteFrames(self.loadPlistFileList[self.curLoadPlistCount])
	end

	--进度刷新
	local curCount = self.curLoadExportJsonCount + self.curLoadPlistCount + self.curLoadPngCount
	self:updateUI(curCount / self.totalLoadCount)

	--加载完成
	if curCount > self.totalLoadCount then
		self:stopScheduler()
		self:loadFinish()
	end
end

function LoadResource:stopScheduler()
	if self.scriptEntryID ~= nil then
		local scheduler=cc.Director:getInstance():getScheduler()
		scheduler:unscheduleScriptEntry(self.scriptEntryID)
	end
	self.scriptEntryID = nil
end

function LoadResource:loadFinish()
	if self.isDelayReleaseResource then
		self:doRelease()
	end
	_MyG.GameSceneSwither:runScene(self.nextSceneInfo["sceneID"], 
									self.nextSceneInfo["transition"], 
									self.nextSceneInfo["time"],
									self.nextSceneInfo["more"])
end

----------------------------------------------------------release----------------------------------------------------------
function LoadResource:addReleaseResource(type, path)	
	if self.isStart then
		print("[ERROR]资源加载已开始")
		return
	end

	if path == nil or path == "" then
		print("[ERROR]资源路径不合法")
		return
	end

	if type == LoadResource.RES_TYPE.PLIST then
		table.insert(self.releasePlistFileList, path)
		table.insert(self.releasePngFileList, string.gsub(path, ".plist", ".png"))
	elseif type == LoadResource.RES_TYPE.EXPORTJSON then
		table.insert(self.releaseExportJsonFileList, path)
	elseif type == LoadResource.RES_TYPE.PNG then
		table.insert(self.releasePngFileList, path)
	else
		print("[ERROR]未知格式资源")
	end
end

function LoadResource:delayRelease()
	self.isDelayReleaseResource = true
end

function LoadResource:doRelease()
	for i = 1, #self.releaseExportJsonFileList do
		ccs.ArmatureDataManager:getInstance():removeArmatureFileInfo(self.releaseExportJsonFileList[i])
	end

	local textureCache = cc.Director:getInstance():getTextureCache()
	for i = 1, #self.releasePngFileList do
		textureCache:removeTextureForKey(self.releasePngFileList[i])
	end

	local spriteFrameCache = cc.SpriteFrameCache:getInstance()
	for i = 1, #self.releasePlistFileList do
		spriteFrameCache:removeSpriteFramesFromFile(self.releasePlistFileList[i])
	end
end

return LoadResource