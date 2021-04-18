-- @Author: fangcheng
-- @Date:   2020-11-08 14:39:12
-- @remark: http请求管理


local http = require('http')
local md5 = require('md5')

local HttpManager = class("HttpManager", import(".BaseManager"))

local fu = cc.FileUtils:getInstance()
local prefix = fu:getWritablePath() .. '.cache/'
fu:createDirectory(prefix)

local url_reqMap = {}
local url_fetchCalls = {}
local fetchDefaultCall = function() end
local lockMeta = {
    __newindex = function(_, name, value)
        error("error write to a read-only table with key = " .. tostring(name))
    end
}

local function onFetch(ok, to)
	-- print("ok, to", ok, to)
	url_reqMap[to] = false

	local t = url_fetchCalls[to]
	if t == nil then
		return
	end
	for k,v in pairs(t) do
		v(ok, to)
	end
	url_fetchCalls[to] = nil
end

-- @brief 文件下载
-- @param url
-- @param func 完成回调
-- @param tofile 下载之后的文件位置,可选.为空则默认储存在.cache目录
-- @return token
function HttpManager:fetch(url, func, tofile)
	self:log('getting '..url)
	local to = tofile
	if to == nil then
		local ext = string.match(url, "(%.%w+)$") or ""
		to = prefix .. md5.sum(url) .. ext
	end

	url_fetchCalls[to] = url_fetchCalls[to] or {}

	local key = #url_fetchCalls[to] + 1
	local token = {to, key}
	setmetatable(token, lockMeta)

	url_fetchCalls[to][key] = func

	-- 本地有缓存
	if fu:isFileExist(to) then
	  self:log('already cached as:', to)
	  oRoutine(o_once(function()
	  	onFetch(true, to)
	end))
	  return token
	end
	
	-- 此请求正在进行
	if url_reqMap[to] then return token end

	url_reqMap[to] = true
	self:log("http to get", url)
	http.fetch(url, to, onFetch)
	return token
end

-- @brief 取消文件下载
-- @param token fetch返回的token
function HttpManager:cancel(token)
	local to = token[1]
	local key = token[2]
	url_fetchCalls[to][key] = fetchDefaultCall
end

-- @brief 初始化调用
function HttpManager:override_onInit()
	HttpManager.super.override_onInit(self)
	url_reqMap = {}
	url_fetchCalls = {}
end

-- @brief 销毁时调用
function HttpManager:override_onDestroy()
	HttpManager.super.override_onDestroy(self)
	url_reqMap = {}
	url_fetchCalls = {}
end


return HttpManager



