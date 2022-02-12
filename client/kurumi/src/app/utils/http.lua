-- @Author : fc
-- @Date   : 2021-11-03 16:32:48
-- @remark : quick有http封装到lua的接口,不重新导入以前的C++代码了,这儿兼容以前的C++接口

local http = {}

local log = print
-- local log = function() end

-- @brief 文件获取
-- @param downUrl
-- @param tofile
-- @param resultCall 结果回调
-- @param percentCall 进度回调
function http.fetch(downUrl, tofile, resultCall, percentCall)
    log("http.fetch", downUrl)
    local request = network.createHTTPDownload(function(event)
        local request = event.request
        if event.name == "completed" then
            local code = request:getResponseStatusCode()
            if code ~= 200 and code ~= 206 then
                log("http.fetch error:", code)
                resultCall(false, tofile)
                return
            end
            log("http.fetch completed:", request:getResponseString())
            resultCall(true, tofile)
        elseif event.name == "progress" then
            local now = event.dltotal
            local total = event.total
            if percentCall then percentCall(now, total) end
        else
            log("http.fetch error:", request:getErrorCode())
            resultCall(false, tofile)
        end
    end, downUrl, tofile)

    request:start()
end


function http.read(param, resultCall, percentCall)
    local url = param
    local method = "GET"
    local headers

    if type(param) == "table" then
        -- 地址
        url = param.url
        -- if url == nil then
        --     local protocol = param.protocol or "http"
        --     local host = param.host or ""
        --     local path = param.path or ""
        --     url = string.format("%s://", protocol, host, path)
        -- end

        -- 请求方法:'GET'|'POST'|'PUT'|'DELETE'
        method = param.method or "GET"

        -- headers
        headers = param.headers
    end
    log("http.read", url)

    local request = network.createHTTPRequest(function(event)
        local request = event.request
        if event.name == "completed" then
            local code = request:getResponseStatusCode()
            if code ~= 200 then
                log("http.read error:", code)
                resultCall(false, code)
                return
            end

            log("http.read completed:", request:getResponseString())
            resultCall(true, request:getResponseString())
        elseif event.name == "progress" then
            local now = event.dltotal
            local total = event.total
            if percentCall then percentCall(now, total) end
        else
            log("http.read error:", request:getErrorCode())
            resultCall(false, request:getErrorCode())
        end
    end, url, method)

    request:setTimeout(15)
    if headers then
        request:addRequestHeader(headers)
    end
    request:start()
end


return http
