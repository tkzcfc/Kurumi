local msgViewBase = require("app.common.msgViewBase")

local LoadResource = class("LoadResource", msgViewBase)

_MyG.RES_TYPE = 
{
	PLIST = 0,
	EXPORTJSON = 1,
	PNG = 2
}

LoadResource.STAGE = {
	FREE = 0,
	RELEASE_RES = 1,
	LOAD_RES = 2,
	DELAY_RELEASE_RES = 4,
	FINISH = 5,
}


local OPEN_LOG = false
local function log_print(...)
	if OPEN_LOG == true then
		print(...)
	end 
end

local MAX_RELEASE_EXPRTJSON_COUNT = 2
local MAX_RELEASE_PNG_COUNT = 10
local MAX_RELEASE_PLIST_COUNT = 10
local MAX_RELEASE_RES_COUNT = 15

function LoadResource:onCreate()
	LoadResource.super.onCreate(self)

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

    self.curReleaseCount = 0
    self.totalReleaseCount = 0

	--delay release
    self.delayReleasePlistFileList = {}
    self.delayReleaseExportJsonFileList = {}
    self.delayReleasePngFileList = {}

    self.curDelayReleaseCount = 0
    self.totalDelayReleaseCount = 0

    self.curStage = LoadResource.STAGE.FREE
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

	local preSceneID = _MyG.ScenesManager:getPreSceneID()
	if preSceneID and _MyG.SceneResourceLoadConfig[preSceneID].ReleaseResourceFunc then
		_MyG.SceneResourceLoadConfig[preSceneID].ReleaseResourceFunc(self)
	end

	if _MyG.SceneResourceLoadConfig[sceneID].PreReleaseResourceFunc then
		_MyG.SceneResourceLoadConfig[sceneID].PreReleaseResourceFunc(self, args)
	end
	if _MyG.SceneResourceLoadConfig[sceneID].LoadResourceFunc then
		_MyG.SceneResourceLoadConfig[sceneID].LoadResourceFunc(self, args)
	end
	self:start()
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

----------------------------------------------------------load----------------------------------------------------------

function LoadResource:addLoadResource(resType, path)	
	if self.curStage ~= LoadResource.STAGE.FREE then
		log_print("[ERROR]资源加载已开始")
		return
	end

	if path == nil or path == "" then
		log_print("[ERROR]资源路径不合法")
		return
	end

	if _MyG.DEBUG then
		log_print("add resource:", path)
	end

	if resType == _MyG.RES_TYPE.PLIST then
		table.insert(self.loadPlistFileList, path)
		local str = string.gsub(path, ".plist", ".png")
		table.insert(self.loadPngFileList, str)
	elseif resType == _MyG.RES_TYPE.EXPORTJSON then
		table.insert(self.loadExportJsonFileList, path)
	elseif resType == _MyG.RES_TYPE.PNG then
		table.insert(self.loadPngFileList, path)
	else
		log_print("[ERROR]未知格式资源")
	end
end

function LoadResource:addReleaseResource(resType, path)	
	if self.curStage ~= LoadResource.STAGE.FREE then
		log_print("[ERROR]请调用addDelayReleaseResource")
		return
	end

	if path == nil or path == "" then
		log_print("[ERROR]资源路径不合法")
		return
	end

	if _MyG.DEBUG then
		log_print("add release resource:", path)
	end

	if resType == _MyG.RES_TYPE.PLIST then
		table.insert(self.releasePlistFileList, path)
		local str = string.gsub(path, ".plist", ".png")
		table.insert(self.releasePngFileList, str)
	elseif resType == _MyG.RES_TYPE.EXPORTJSON then
		table.insert(self.releaseExportJsonFileList, path)
	elseif resType == _MyG.RES_TYPE.PNG then
		table.insert(self.releasePngFileList, path)
	else
		log_print("[ERROR]未知格式资源")
	end
end

function LoadResource:addDelayReleaseResource(resType, path)	
	if path == nil or path == "" then
		log_print("[ERROR]资源路径不合法")
		return
	end

	log_print("add delay release resource:", path)

	if resType == _MyG.RES_TYPE.PLIST then
		table.insert(self.delayReleasePlistFileList, path)
		local str = string.gsub(path, ".plist", ".png")
		table.insert(self.delayReleasePngFileList, str)
	elseif resType == _MyG.RES_TYPE.EXPORTJSON then
		table.insert(self.delayReleaseExportJsonFileList, path)
	elseif resType == _MyG.RES_TYPE.PNG then
		table.insert(self.delayReleasePngFileList, path)
	else
		log_print("[ERROR]未知格式资源")
	end
end

---------------------------------------------------------------------------------------------------------

function LoadResource:start()
	log_print("开始执行...")
	if self.curStage ~= LoadResource.STAGE.FREE then
		log_print("[ERROR]资源加载已开始")
		return
	end

	log_print("资源释放开始...")
	self.curStage = LoadResource.STAGE.RELEASE_RES

	self.curLoadExportJsonCount = 0
	self.curLoadPlistCount = 0
	self.curLoadPngCount = 0
	self.totalLoadCount = #self.loadPlistFileList + #self.loadExportJsonFileList + #self.loadPngFileList
   
    self.curReleaseCount = 1
    self.totalReleaseCount = #self.releasePlistFileList + #self.releaseExportJsonFileList + #self.releasePngFileList + 1


	local scheduler=cc.Director:getInstance():getScheduler()
    self.scriptEntryID = scheduler:scheduleScriptFunc(function(time) self:logicUpdate(time) end,1 / 20.0,false)
end

function LoadResource:logicUpdate()

	if self.curStage == LoadResource.STAGE.RELEASE_RES then
		self:releaseUpdate()
	elseif self.curStage == LoadResource.STAGE.LOAD_RES then
		self:loadUpdate()
	elseif self.curStage == LoadResource.STAGE.DELAY_RELEASE_RES then
		self:delayReleaseUpdate()
	elseif self.curStage == LoadResource.STAGE.FINISH then
		self:stopScheduler()
		self:loadFinish()
	end

	--进度条刷新
	local curCount = self.curLoadExportJsonCount + self.curLoadPlistCount + self.curLoadPngCount + self.curReleaseCount
	local totalCount = self.totalLoadCount + self.totalReleaseCount
	self:updateUI(curCount / totalCount)
end

function LoadResource:stopScheduler()
	if self.scriptEntryID ~= nil then
		local scheduler=cc.Director:getInstance():getScheduler()
		scheduler:unscheduleScriptEntry(self.scriptEntryID)
	end
	self.scriptEntryID = nil
end

function LoadResource:loadFinish()
	log_print("执行完毕,进入下一场景...")
	_MyG.ScenesManager:runScene(self.nextSceneInfo["sceneID"], 
									self.nextSceneInfo["transition"], 
									self.nextSceneInfo["time"],
									self.nextSceneInfo["more"],
									self.nextSceneInfo["args"])
end

-------------------------------------------------------------release begin-------------------------------------------------------------

function LoadResource:releaseUpdate()
	local breakRelease = false
	local curExportCount = 0
	local curPngCount = 0
	local curPlistCount = 0
	local curCount = 0

	for i = self.curReleaseCount, #self.releaseExportJsonFileList do
		log_print("release", self.releaseExportJsonFileList[i])

		ccs.ArmatureDataManager:getInstance():removeArmatureFileInfo(self.releaseExportJsonFileList[i])
		curExportCount = curExportCount + 1
		curCount = curCount + 1
		self.curReleaseCount = self.curReleaseCount + 1

		if curExportCount > MAX_RELEASE_EXPRTJSON_COUNT then
			breakRelease = true
			break
		end
		if curCount > MAX_RELEASE_RES_COUNT then
			breakRelease = true
			break
		end
	end

	if breakRelease then
		return
	end

	local beginIndex = self.curReleaseCount - #self.releaseExportJsonFileList

	local textureCache = cc.Director:getInstance():getTextureCache()

	for i = beginIndex, #self.releasePngFileList do

		log_print("release", self.releasePngFileList[i])

		textureCache:removeTextureForKey(self.releasePngFileList[i])
		curPngCount = curPngCount + 1
		curCount = curCount + 1
		self.curReleaseCount = self.curReleaseCount + 1

		if curPngCount > MAX_RELEASE_PNG_COUNT then
			breakRelease = true
			break
		end
		if curCount > MAX_RELEASE_RES_COUNT then
			breakRelease = true
			break
		end
	end

	if breakRelease then
		return
	end

	local beginIndex = self.curReleaseCount - #self.releaseExportJsonFileList -#self.releasePngFileList

	local spriteFrameCache = cc.SpriteFrameCache:getInstance()
	for i = beginIndex, #self.releasePlistFileList do

		log_print("release", self.releasePlistFileList[i])

		spriteFrameCache:removeSpriteFramesFromFile(self.releasePlistFileList[i])		
		curPlistCount = curPlistCount + 1
		curCount = curCount + 1
		self.curReleaseCount = self.curReleaseCount + 1

		if curPlistCount > MAX_RELEASE_PLIST_COUNT then
			breakRelease = true
			break
		end
		if curCount > MAX_RELEASE_RES_COUNT then
			breakRelease = true
			break
		end
	end

	if breakRelease then
		return
	end
	log_print(self.curReleaseCount, self.totalReleaseCount)
	if self.curReleaseCount >= self.totalReleaseCount then
		log_print("资源释放结束...")
		log_print("资源加载开始...")
		self.curStage = LoadResource.STAGE.LOAD_RES
		self:startLoad()
	end 
end

-------------------------------------------------------------release end-------------------------------------------------------------

-------------------------------------------------------------load begin-------------------------------------------------------------
function LoadResource:startLoad()
	--异步加载exportjson
	for i = 1, #self.loadExportJsonFileList do
		ccs.ArmatureDataManager:getInstance():addArmatureFileInfoAsync(self.loadExportJsonFileList[i], function(percent)
			self.curLoadExportJsonCount = #self.loadExportJsonFileList * percent
		end)
		if _MyG.DEBUG then
			log_print("load exportjson:", self.loadExportJsonFileList[i])
		end
	end

	--异步加载图片资源
	local textureCache = cc.Director:getInstance():getTextureCache()
	for i = 1, #self.loadPngFileList do
		textureCache:addImageAsync(self.loadPngFileList[i], function(...) self:pngLoadCall(...) end)
		if _MyG.DEBUG then
			log_print("load image:", self.loadPngFileList[i])
		end
	end
end

function LoadResource:pngLoadCall()
	self.curLoadPngCount = self.curLoadPngCount + 1
	if self.curLoadPngCount >= #self.loadPngFileList then
		self.pngFileIsLoadFinish = true
	end
end

function LoadResource:loadUpdate()
	--加载plist文件
	if self.pngFileIsLoadFinish and self.curLoadPlistCount < #self.loadPlistFileList then
		self.curLoadPlistCount = self.curLoadPlistCount + 1
		cc.SpriteFrameCache:getInstance():addSpriteFrames(self.loadPlistFileList[self.curLoadPlistCount])

		if _MyG.DEBUG then
			log_print("load plist:", self.loadPlistFileList[self.curLoadPlistCount])
		end
	end

	--加载资源完成
	local curCount = self.curLoadExportJsonCount + self.curLoadPlistCount + self.curLoadPngCount
	if curCount >= self.totalLoadCount then

		local sceneID = self.nextSceneInfo["sceneID"]
		if _MyG.SceneResourceLoadConfig[sceneID].DelayReleaseResourceFunc then
			_MyG.SceneResourceLoadConfig[sceneID].DelayReleaseResourceFunc(self, self.nextSceneInfo["args"])
		end
		self.curDelayReleaseCount = 1
    	self.totalDelayReleaseCount = #self.delayReleasePlistFileList + #self.delayReleaseExportJsonFileList + #self.delayReleasePngFileList + 1

		self.curStage = LoadResource.STAGE.DELAY_RELEASE_RES
		log_print("资源加载结束...")
		log_print("延迟资源释放开始...")
	end
end

-------------------------------------------------------------load end-------------------------------------------------------------


----------------------------------------------------------delay release begin----------------------------------------------------------

function LoadResource:delayReleaseUpdate()
	local breakRelease = false
	local curExportCount = 0
	local curPngCount = 0
	local curPlistCount = 0
	local curCount = 0

	for i = self.curDelayReleaseCount, #self.delayReleaseExportJsonFileList do
		log_print("delay release", self.delayReleaseExportJsonFileList[i])
		ccs.ArmatureDataManager:getInstance():removeArmatureFileInfo(self.delayReleaseExportJsonFileList[i])
		curExportCount = curExportCount + 1
		curCount = curCount + 1
		self.curDelayReleaseCount = self.curDelayReleaseCount + 1

		if curExportCount > MAX_RELEASE_EXPRTJSON_COUNT then
			breakRelease = true
			break
		end
		if curCount > MAX_RELEASE_RES_COUNT then
			breakRelease = true
			break
		end
	end

	if breakRelease then
		return
	end

	local beginIndex = self.curReleaseCount - #self.releaseExportJsonFileList

	local textureCache = cc.Director:getInstance():getTextureCache()

	for i = beginIndex, #self.delayReleasePngFileList do
		log_print("delay release", self.delayReleasePngFileList[i])
		textureCache:removeTextureForKey(self.delayReleasePngFileList[i])
		curPngCount = curPngCount + 1
		curCount = curCount + 1
		self.curDelayReleaseCount = self.curDelayReleaseCount + 1

		if curPngCount > MAX_RELEASE_PNG_COUNT then
			breakRelease = true
			break
		end
		if curCount > MAX_RELEASE_RES_COUNT then
			breakRelease = true
			break
		end
	end

	if breakRelease then
		return
	end

	local beginIndex = self.curReleaseCount - #self.releaseExportJsonFileList - #self.delayReleasePngFileList

	local spriteFrameCache = cc.SpriteFrameCache:getInstance()
	for i = beginIndex, #self.delayReleasePlistFileList do
		log_print("delay release", self.delayReleasePlistFileList[i])
		spriteFrameCache:removeSpriteFramesFromFile(self.delayReleasePlistFileList[i])		
		curPlistCount = curPlistCount + 1
		curCount = curCount + 1
		self.curDelayReleaseCount = self.curDelayReleaseCount + 1

		if curPlistCount > MAX_RELEASE_PLIST_COUNT then
			breakRelease = true
			break
		end
		if curCount > MAX_RELEASE_RES_COUNT then
			breakRelease = true
			break
		end
	end

	if breakRelease then
		return
	end

	if self.curDelayReleaseCount >= self.totalDelayReleaseCount then
		self.curStage = LoadResource.STAGE.FINISH
		log_print("延迟资源释放结束...")
	end 
end

----------------------------------------------------------delay release end----------------------------------------------------------

return LoadResource