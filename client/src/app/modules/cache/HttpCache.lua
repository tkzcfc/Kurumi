-- @Author: fangcheng
-- @Date:   2020-11-07 16:34:50
-- @remark: http缓存管理对象

local http = require('http')
local md5 = require('md5')

local cache = {}

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
  print("ok, to", ok, to)
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

function cache.fetch(url, func)
  -- print('getting '..url)
  local to = prefix..md5.sum(url)

  url_fetchCalls[to] = url_fetchCalls[to] or {}

  local key = #url_fetchCalls[to] + 1
  local token = {to, key}
  setmetatable(token, lockMeta)

  url_fetchCalls[to][key] = func

  if fu:isFileExist(to) then
    -- print('already cached as:', to)
    oRoutine(o_once(function()
    	onFetch(true, to)
	end))
    return token
  end
  
  if url_reqMap[to] then return token end
  url_reqMap[to] = true
  -- print("http to get", url)
  http.fetch(url, to, onFetch)
  return token
end

function cache.cancel(token)
	local to = token[1]
	local key = token[2]
	url_fetchCalls[to][key] = fetchDefaultCall
end

return cache
