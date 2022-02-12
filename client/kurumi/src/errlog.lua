-- @Author : fc
-- @Date   : 2021-11-29 18:04:49
-- @remark : 错误日志上传

local errlog = {}

local httpCount = 0
local logMap = {}
local headURL = "http://1.14.65.70:8502"

function errlog:send(errMsg)
    -- 限制最大请求数量
    if httpCount > 5 then return end

    -- 同一错误同一时间只上传一次
    if logMap[errMsg] then return end
    logMap[errMsg] = true


    local user = ""
    local err = cc.Crypto:encodeBase64(errMsg, string.len(errMsg))
    local platform = ""
    if device and device.platform then
        platform = device.platform
    end

    httpCount = httpCount + 1

    local url = string.format("%s/lua_err?user=%s&platform=%s", headURL, user, platform)
    local request = cc.HTTPRequest:createWithUrl(function(event)
        if event.name ~= "progress" then
            httpCount = httpCount - 1
            logMap[errMsg] = false
            if httpCount <= 0 then logMap = {} end
        end
    end, url, 1) -- post = 1
    request:addRequestHeader("err_log: " .. err)
    request:setTimeout(15)
    request:start()
end


return errlog
