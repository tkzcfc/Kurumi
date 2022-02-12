-- @Author: fangcheng
-- @Date:   2020-11-08 14:39:12
-- @remark: http请求管理

local http = require('app.utils.http')

local fileUtils = cc.FileUtils:getInstance()

local HttpManager = class("HttpManager", import(".BaseManager"))

-- @brief 初始化调用
function HttpManager:override_onInit()
	HttpManager.super.override_onInit(self)

	self.eventEmitter = G_Class.EventEmitter.new()
end

-- @brief 销毁时调用
function HttpManager:override_onDestroy()
	HttpManager.super.override_onDestroy(self)
	self.eventEmitter:clear()
end

-- @brief 文件下载
-- @param url
-- @param func 完成回调
-- @param tofile 下载之后的文件位置,可选.为空则默认储存在.cache目录
-- @return token
function HttpManager:fetch(url, func, tofile)
	self:initCacheDir()

	local to = tofile
	if to == nil then
		local ext = string.match(url, "(%.%w+)$") or ""
		to = self.cacheDir .. crypto.md5(url) .. ext
	end

	local token = self.eventEmitter:once(url, func, self)

	-- 请求已创建
	if self.eventEmitter:listeners(url) > 1 then
		return token
	end

	-- 本地有缓存
	if fileUtils:isFileExist(to) then
		oRoutine(o_once(function()
			self.eventEmitter:emit(url, true, to)
		end))
		return token
	end

	http.fetch(url, to, function(ok, to)
		self.eventEmitter:emit(url, ok, to)
	end)

	return token
end

-- @brief http请求
-- @param url 为字符串时代表请求地址,为table时具体查看 http_read 源码
function HttpManager:read(url, func)
	http.read(url, function(ok, responseData)
		self.eventEmitter:emit(url, ok, responseData)
	end)

	return self.eventEmitter:once(url, func, self)
end

-- @brief 取消回调
-- @param token fetch返回的token
function HttpManager:cancel(token)
	if token == nil then return end
	self.eventEmitter:off(token)
end

-- @brief 缓存目录初始化
function HttpManager:initCacheDir()
	if self.isInitDirTag then
		return
	end

	local prefix = fileUtils:getWritablePath() .. '.cache/'
	if not fileUtils:isDirectoryExist(prefix) then
		if not fileUtils:createDirectory(prefix) then
			error("缓存目录创建失败")
			prefix = fileUtils:getWritablePath()
		end
	end

	self.isInitDirTag = true
	self.cacheDir = prefix

	return
end

return HttpManager



