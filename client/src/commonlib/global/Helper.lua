-- @Author : fangcheng
-- @Date   : 2020-03-22 14:14:13
-- @remark : helper相关

local Helper = {}

Helper.log = function(...)
	if G_MAC.DEBUG then
		print(...)
	end
end

function Helper.copyTable(tb)
	local tab = { }
	for k, v in pairs(tb or { }) do
		if type(v) ~= "table" then
			tab[k] = v
		else
			tab[k] = Helper.copyTable(v)
		end
	end
	return tab
end


--[[
local tab = {name = 'AAA'}
local ref = {count = 0}
tab.ref1 = ref
tab.ref2 = ref

local m = wholeCloneNoRef(tab)
m.ref1.count = 10

print(m.ref1.count) -- 10
print(m.ref2.count) -- 0
]]
function Helper.wholeCloneNoRef(orig)
    local function _copy(orig)
        if type(orig) ~= "table" then
            return orig
        end
        local newObject = {}
        for key, value in pairs(orig) do
            newObject[_copy(key)] = _copy(value)
        end
        return newObject
    end
    return _copy(orig)
end

--[[
local tab = {name = 'AAA'}
local ref = {count = 0}
tab.ref1 = ref
tab.ref2 = ref

local m = wholeClone(tab)
m.ref1.count = 10

print(m.ref1.count) -- 10
print(m.ref2.count) -- 10
]]
function Helper.wholeClone(orig)
    local lookup_table = {}
    local function _copy(orig)
        if type(orig) ~= "table" then
            return orig
        elseif lookup_table[orig] then
            return lookup_table[orig]
        end
        local newObject = {}
        lookup_table[orig] = newObject
        for key, value in pairs(orig) do
            newObject[_copy(key)] = _copy(value)
        end
        return newObject
    end
    return _copy(orig)
end

function Helper.findEleInTab(tb, ele)
	local find_pos = nil
	for k, v in pairs(tb) do
		if ele == v then
			find_pos = k
			break
		end
	end
	return find_pos
end

function Helper.lerp(x, y, alpha)
	local ret = x + alpha *(y - x)
	return ret
end

function Helper.loadStudioFile(fileName, target)
	local root = require(fileName).create(function (path, node, funcName)
		if target == nil then
			return
		end
        return function(...) 
            if target[funcName] and type(target[funcName]) == "function" then
                target[funcName](target, ...)
            else
                Helper.log(string.format("[%s -> %s]: %s方法未实现", path, node:getName(), funcName))
            end
        end
    end)

	if root and Helper.loadStudioFileEx then
		Helper.loadStudioFileEx(root)
	end

    return root
end

function Helper.serialMap2Url(tb)
	if type(tb) == "table" then
		local s = ""
		for key, val in pairs(tb) do
			s = s .. key .. "=" .. val
			s = s .. "&"
		end
		return string.sub(s, 1, #s - 1)
	else
		return tb
	end
end

function Helper.httpPost(url, data, callback, response_type)
	if not url then
		return
	end
	local xhr = cc.XMLHttpRequest:new()
	xhr.responseType = response_type or cc.XMLHTTPREQUEST_RESPONSE_JSON
	xhr:open("POST", url)
	local function onReadyStateChange()
		if xhr.readyState == 4 and(xhr.status >= 200 and xhr.status < 207) then
			local response = xhr.response
			local output = nil
			if response and #response > 0 and xhr.responseType == cc.XMLHTTPREQUEST_RESPONSE_JSON then
				output = json.decode(response, 1)
            else
                output = response
			end
			Helper.log(string.format("Http Responds: %s", response))
			callback(output, xhr)
		else
			Helper.log(string.format("xhr.readyState is:%s ,xhr.status is:%s", xhr.readyState, xhr.status))
			callback(nil)
		end
	end
	xhr:registerScriptHandler(onReadyStateChange)
	local post_str = Helper.serialMap2Url(data)
	Helper.log("http post data: ", post_str)
	xhr:send(post_str)
end

function Helper.httpGet(url, callback)
	if not url then
		return
	end
	local xhr = cc.XMLHttpRequest:new()
	xhr.responseType = cc.XMLHTTPREQUEST_RESPONSE_STRING
	xhr:open("GET", url)

	local function onReadyStateChange()
		if xhr.readyState == 4 and(xhr.status >= 200 and xhr.status < 207) then
			local statusString = "Http Status Code:" .. xhr.statusText
			Helper.log(statusString)
			callback(xhr.response, xhr)
		else
			Helper.log("xhr.readyState is:", xhr.readyState, "xhr.status is: ", xhr.status)
			callback(nil)
		end
	end
	xhr:registerScriptHandler(onReadyStateChange)
	xhr:send()
end

--依据宽度截断字符
-- local str = "更具function appdf.stringEllipsis(szText, sizeE,sizeCN,maxWidth)"
-- local ret = Helper.stringEllipsis(str, 10, 20, 100)
-- print(ret) -- 更具func...
function Helper.stringEllipsis(szText, sizeE, sizeCN, maxWidth)
	--当前计算宽度
	local width = 0
	--截断位置
	local lastpos = 0
	--截断结果
	local szResult = "..."
	--完成判断
	local bOK = false
	 
	local i = 1
	 
	while true do
		local cur = string.sub(szText,i,i)
		local byte = string.byte(cur)
		if byte == nil then
			break
		end
		if byte > 128 then
			if width +sizeCN <= maxWidth - 3*sizeE then
				width = width +sizeCN
				 i = i + 3
				 lastpos = i+2
			else
				bOK = true
				break
			end
		elseif	byte ~= 32 then
			if width +sizeE <= maxWidth - 3*sizeE then
				width = width +sizeE
				i = i + 1
				lastpos = i
			else
				bOK = true
				break
			end
		else
			i = i + 1
			lastpos = i
		end
	end
	if lastpos ~= 0 then
		szResult = string.sub(szText, 1, lastpos)
		if(bOK) then
			szResult = szResult.."..."
		end
	end
	return szResult
end

-- example:
--     Helper.registerTouchEventListener(self, button, "onButtonClick")
--
function Helper.registerTouchEventListener(this, node, funcName)
	node:addClickEventListener( function(sender)
		local func = this[funcName]
		if func ~= nil then
			func(this, sender)
		end
	end )
end

function Helper.md5(str)
	local md5 = require("commonlib.utils.md5")
	return md5.sumhexa(str)
end

function Helper.getUTF8SubString(input, subLen)
	local len = string.len(input)
	local left = len
	local cnt = 0
	local arr = { 0, 0xc0, 0xe0, 0xf0, 0xf8, 0xfc }
	while left ~= 0 do
		local tmp = string.byte(input, - left)
		local i = #arr
		while arr[i] do
			if tmp >= arr[i] then
				left = left - i
				break
			end
			i = i - 1
		end
		cnt = cnt + 1
		if cnt >= subLen then
			return string.sub(input, 1, - left - 1)
		end
	end
	return input
end

return Helper
