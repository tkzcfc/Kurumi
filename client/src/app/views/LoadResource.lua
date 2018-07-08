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

    self.plistFileList = {}
    self.exportJsonFileList = {}
    self.pngFileList = {}

	self.curExportJsonCount = 0
	self.curPlistCount = 0
	self.curPngCount = 0
	self.totalCount = 0

	self.pngFileIsLoadFinish = false
end

function LoadResource:onExit()
	LoadResource.super.onExit(self)
	self:stopScheduler()
end

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
		table.insert(self.plistFileList, path)
	elseif type == LoadResource.RES_TYPE.EXPORTJSON then
		table.insert(self.exportJsonFileList, path)
		table.insert(self.pngFileList, string.gsub(path, ".plist", ".png"))
	elseif type == LoadResource.RES_TYPE.PNG then
		table.insert(self.pngFileList, path)
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

	self.totalCount = #self.plistFileList + #self.exportJsonFileList + #self.pngFileList

	--异步加载exportjson
	for i = 1, #self.exportJsonFileList do
		ccs.ArmatureDataManager:getInstance():addArmatureFileInfoAsync(loadRole[i], function(percent)
			self.curExportJsonCount = #self.exportJsonFileList * percent
		end)
	end

	--异步加载图片资源
	local textureCache = cc.Director:getInstance():getTextureCache()
	for i = 1, #self.pngFileList do
		textureCache:addImageAsync(self.pngFileList[i], function(...) self:pngLoadCall(...) end)
	end
	
	--
	local scheduler=cc.Director:getInstance():getScheduler()
    self.scriptEntryID = scheduler:scheduleScriptFunc(function(...) self:loadFileUpdate(...) end,1 / 20.0,false)
end

function LoadResource:pngLoadCall()
	self.curPngCount = self.curPngCount + 1
	if self.curPngCount >= #self.pngFileList then
		self.pngFileIsLoadFinish = true
	end
end

function LoadResource:loadFileUpdate()

	--加载plist文件
	if self.pngFileIsLoadFinish and self.curPlistCount < #self.plistFileList then
		self.curPlistCount = self.curPlistCount + 1
		cc.SpriteFrameCache:getInstance():addSpriteFrames(self.plistFileList[self.curPlistCount])
	end

	--进度刷新
	local curCount = self.curExportJsonCount + self.curPlistCount + self.curPngCount
	self:updateUI(curCount / self.totalCount)

	--加载完成
	if curCount > self.totalCount then
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

function LoadResource:updateUI(percent)
	self.ui.ldrunning:setPositionX(percent * self.totalWidth)
	self.ui.Panel_Load:setContentSize({width = percent * self.totalWidth, height = self.panelheight})
end

function LoadResource:loadFinish()
end

return LoadResource