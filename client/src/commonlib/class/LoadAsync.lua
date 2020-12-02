-- @Author: fangcheng
-- @Date  : 2019-10-17 21:26:05
-- @remark: 异步资源加载

local Task = import(".Task")
local TaskFlowPipe = import(".TaskFlowPipe")

-- 纹理加载是否使用多线程
local USE_IMAGE_ASYNC = false

local ENABLE_DEBUG = true

local table_insert = table.insert
local spriteFrameCache = cc.SpriteFrameCache:getInstance()
local textureCache = cc.Director:getInstance():getTextureCache()

----------------------------------------------------------------
-- 资源释放任务
local ReleaseResourceTask = class("LoadTextureTask", Task)

function ReleaseResourceTask:ctor()
	self.textureFileArr = {}
	self.spriteFrameFileArr = {}
end

function ReleaseResourceTask:addTextureFile(fileName)
	table_insert(self.textureFileArr, fileName)
end

function ReleaseResourceTask:addSpriteFramesFile(fileName)
	table_insert(self.spriteFrameFileArr, fileName)
end

function ReleaseResourceTask:run(taskFlowPipe)
	for k,v in pairs(self.textureFileArr) do
		if ENABLE_DEBUG then
			com_log("unload image:", v)
		end
		textureCache:removeTextureForKey(v)
	end

	for k,v in pairs(self.spriteFrameFileArr) do
		if ENABLE_DEBUG then
			com_log("unload sprite frames:", v)
		end
		spriteFrameCache:removeSpriteFramesFromFile(v)
	end
	self.curProgress = self.progressWeight
end

function ReleaseResourceTask:updateProgressWeight()
	self.progressWeight = 0--#self.textureFileArr + #self.spriteFrameFileArr
	self.progressWeight = self.progressWeight + 1
end




----------------------------------------------------------------
-- 资源加载任务
local LoadResourceTask = class("LoadResourceTask", Task)

function LoadResourceTask:ctor()
	self.textureFileArr = {}
	self.spriteFrameFileArr = {}

	self.asyncImageKeyArr = {}
	self.cache_loadImage = {}
end 

function LoadResourceTask:addTextureFile(fileName)
	if not self.cache_loadImage[fileName] then
		self.cache_loadImage[fileName] = true
		table_insert(self.textureFileArr, fileName)
	end
end

function LoadResourceTask:addSpriteFramesFile(fileName)
	table_insert(self.spriteFrameFileArr, fileName)
end

function LoadResourceTask:updateProgressWeight()
	self.progressWeight = #self.textureFileArr + #self.spriteFrameFileArr
	self.progressWeight = self.progressWeight + 1
end

function LoadResourceTask:loadTexture(taskFlowPipe)
	local totalLoadCount = #self.textureFileArr
	local curLoadCount = 0

	if USE_IMAGE_ASYNC then
		local curTime = 0
		local callback = function()
			curLoadCount = curLoadCount + 1
			curTime = 0
			self.curProgress = curLoadCount
		end
	
		for k,v in pairs(self.textureFileArr) do
			if ENABLE_DEBUG then
				com_log("async load image:", v)
			end
			local key = v .. "@async"
			textureCache:addImageAsync(v, callback, key)
			asyncImageKeyArr[v] = key
		end
		
		-- 循环等待异步资源加载
		repeat
			curTime = curTime + taskFlowPipe:yield()
			if curLoadCount >= totalLoadCount then
				break
			end
			-- 异步加载数量长时间未变化，,还是让程序回调(防止程序一直卡在界面)
			-- 其实后面直接加载资源也是一样的,只是可能卡点点而已
			if curTime > 5.0 then
				break
			end
		until(false)
	else
		for k,v in pairs(self.textureFileArr) do
			if ENABLE_DEBUG then
				com_log("load image:", v)
			end
			textureCache:addImage(v)
			self.curProgress = k
			taskFlowPipe:yield()
		end
	end

	self.curProgress = totalLoadCount
end

function LoadResourceTask:run(taskFlowPipe)
	self:loadTexture(taskFlowPipe)

	local count = 0
	for k,v in pairs(self.spriteFrameFileArr) do
		if ENABLE_DEBUG then
			com_log("load sprite frames:", v)
		end

		spriteFrameCache:addSpriteFrames(v)
		self.curProgress = self.curProgress + 1
		count = count + 1
		if count > 3 then
			count = 0
			taskFlowPipe:yield()
		end
	end
end

function LoadResourceTask:abort(isError)
	if USE_IMAGE_ASYNC then
		for k,v in pairs(self.asyncImageKeyArr) do
			if ENABLE_DEBUG then
				com_log("unbind image async:", v)
			end
			textureCache:unbindImageAsync(v)
		end
	end
end


----------------------------------------------------------------
local autoReleaseFile = {}

-- 异步加载
local LoadAsync = class("LoadAsync")

function LoadAsync:ctor()
	local pipe = TaskFlowPipe.new()
	local releaseTask = ReleaseResourceTask.new()
	local loadTask 	  = LoadResourceTask.new()

	pipe:pushTask(releaseTask)
	pipe:pushTask(loadTask)

	self.pipe = pipe
	self.releaseTask = releaseTask
	self.loadTask = loadTask

	self:clearAutoReleaseFile()
end

-- @brief 添加要加载的资源
-- @param fileName 资源名称
-- @param isAutoRelease 是否自动释放
-- @param resType 资源类型（后缀名，为空自动通过fileName取出）
function LoadAsync:addLoadResource(fileName, isAutoRelease, resType)
	if resType == nil then
		resType = LoadAsync.getExtension(fileName)
	end

	if isAutoRelease then
		table.insert(autoReleaseFile, LoadAsync.allocFileData(fileName, resType))
	end

	if resType == "plist" then
		self.loadTask:addSpriteFramesFile(fileName)
		fileName = string.gsub(fileName, ".plist$", ".png")
		self.loadTask:addTextureFile(fileName)
	elseif resType == "png" then
		self.loadTask:addTextureFile(fileName)
	else
		com_log("未知资源格式", fileName)
	end
end

-- @brief 添加要释放的资源
-- @param fileName 资源名称
-- @param resType 资源类型（后缀名，为空自动通过fileName取出）
function LoadAsync:addReleaseResource(fileName, resType)
	if resType == nil then
		resType = LoadAsync.getExtension(fileName)
	end

	if resType == "plist" then
		self.releaseTask:addSpriteFramesFile(fileName)
		fileName = string.gsub(fileName, ".plist$", ".png")
		self.releaseTask:addTextureFile(fileName)
	elseif resType == "png" then
		self.releaseTask:addTextureFile(fileName)
	else
		com_log("未知资源格式", fileName)
	end
end

function LoadAsync:pushTask(task)
	self.pipe:pushTask(task)
end

-- @brief 插入任务
function LoadAsync:insertTask(task, idx)
	self.pipe:insertTask(task, idx)
end

-- @brief 加载开始
-- @param processCallback 加载进度回调
-- @param finishCallback 加载完成回调
-- @param errorCallback 错误回调
function LoadAsync:start(processCallback, finishCallback, errorCallback)
	self.loadTask:updateProgressWeight()
	self.releaseTask:updateProgressWeight()
	self.pipe:start(processCallback, finishCallback, errorCallback)
end

-- @brief 中断
function LoadAsync:abort()
	self.pipe:done()
end

-- @brief 清空缓存，将上次自动释放的图片加入本次资源释放任务中
function LoadAsync:clearAutoReleaseFile()
	for k, v in pairs(autoReleaseFile) do
		self:addReleaseResource(v.fileName, v.resType)
	end
	autoReleaseFile = {}
end

-- @brief 获取当前所有任务的进度权重值
function LoadAsync:getTotalProgressWeight()
	self.loadTask:updateProgressWeight()
	self.releaseTask:updateProgressWeight()
	return self.loadTask.progressWeight + self.releaseTask.progressWeight
end

function LoadAsync.getExtension(fileName)
	local extension = string.match(fileName, "%.(%w+)$")
	if extension == nil then
		extension = ""
	end
	return extension
end

function LoadAsync.allocFileData(fileName, resType)
	local t = {}
	t["fileName"] = fileName
	t["resType"] = resType
	return t
end

return LoadAsync
