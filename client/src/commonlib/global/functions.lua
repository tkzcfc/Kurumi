-- @Author : fangcheng
-- @Date   : 2020-07-22 16:44:57
-- @remark : 全局函数定义

local co_resume = coroutine.resume
local co_yield = coroutine.yield
local table_insert = table.insert
local sharedScheduler = cc.Director:getInstance():getScheduler()

local function format_lua_value_ex(tab, excludeKeys)
    excludeKeys = excludeKeys or {}

    if type(tab) ~= "table" then
        return { tostring(tab) }
    end

    local lookup = {}
    local lines = {}
   	table_insert(lines, "{")

    local function format_lua_table (lua_table, indent)
        if lookup[lua_table] then
            com_log("[ERROR]:循环引用 table")
            return
        end

        lookup[lua_table] = true
        indent = indent or 0
        
        for k, v in pairs(lua_table) do
			if not excludeKeys[k] then    
                if type(k) == "string" then
                    k = string.format("%q", k)
                end
    
                local szPrefix = string.rep("    ", indent)
                if type(v) == "table" then
                    table_insert(lines, szPrefix .. "[" .. k .. "] = {")
                    format_lua_table(v, indent + 1)
                    table_insert(lines, szPrefix .. "},")
                else
                    local szValue = ""
                    if type(v) == "string" then
                        szValue = string.format("%q", v)
                    else
                        szValue = tostring(v)
                    end
                    table_insert(lines, szPrefix.."[" .. k .. "] = " .. szValue .. ",")
                end
            end
        end
    end
    format_lua_table(tab, 1)

	table_insert(lines, "}")
    lookup = nil

    return lines
end

local defaultExcludeKeys = {
    ["class"] = true,
}

-- @brief 打印lua变量(主要是table)
-- @param excludeKeys 要忽略的key集合
local print_lua_value = function(tab, excludeKeys)
    excludeKeys = excludeKeys or defaultExcludeKeys
	for k,v in pairs( format_lua_value_ex(tab, excludeKeys) ) do
		print(v)
	end
end

-- @brief 格式化lua变量(主要是table)
-- @param excludeKeys 要忽略的key集合
local format_lua_value = function(tab, excludeKeys)
    excludeKeys = excludeKeys or defaultExcludeKeys
	return table.concat( format_lua_value_ex(tab, excludeKeys), "\n" )
end



-- @brief 异步任务执行
-- @param job 任务函数
-- @param endFunc 任务结束回调,错误信息不为空则表示任务执行出错
--[[ 
    example:

    async_run(function()
        for i = 1, 10 do
            print("i = ", i)
            local count = 0
            async_wait(function()
                count = count + 1
                -- 挂起一秒
                async_yield(1)
                return count >= 5
            end)
        end
    end)

    结果：每隔5秒输出一次i的值
]]
local DirectorDeltaTime = 0
local async_run = function(job, endFunc)
    local handle, finish

    local worker = coroutine.create(function()
        job()
        finish = true
    end)

    handle = sharedScheduler:scheduleScriptFunc(function(dt)
        DirectorDeltaTime = dt

        local result, err = co_resume(worker)

        -- 任务出错,输出错误信息,停止任务
        if not result then
            sharedScheduler:unscheduleScriptEntry(handle)
            
            if endFunc then endFunc(err) end

            -- 输出错误信息给开发者
            com_log(string.rep("*\n", 4))
            com_log("async_run ERROR:", err)
            com_log(string.rep("*\n", 4))
            -- 调用error函数,防止开发者没有看到上面的输出信息
            error(err)
            return
        end

        if finish == true then
            sharedScheduler:unscheduleScriptEntry(handle)
            if endFunc then endFunc() end
        end
    end, 0, false)

    return handle
end

-- @brief 异步任务挂起
-- @param duration 挂起时间,为空则默认挂起一帧
local async_yield = function(duration)
    if duration == nil then
        co_yield()
        return
    end

    local cur = 0
    repeat
        cur = cur + DirectorDeltaTime
        co_yield()
        if cur >= duration then break end
    until(false)
end

-- @brief 异步任务等待
-- @param condition 等待条件,返回true结束等待
local async_wait = function(condition)
    repeat
        co_yield()
        if condition() then break end
    until(false)
end

-- @brief 取消异步任务
-- @param handle 异步任务句柄
local async_cancel = function(handle)
    sharedScheduler:unscheduleScriptEntry(handle)
end




-- 设置table只读
local function read_only(inputTable)
    local travelled_tables = {}
    local function __read_only(tbl)
        if not travelled_tables[tbl] then
            local tbl_mt = getmetatable(tbl)
            if not tbl_mt then
                tbl_mt = {}
                setmetatable(tbl, tbl_mt)
            end

            local proxy = tbl_mt.__read_only_proxy
            if not proxy then
                proxy = {}
                tbl_mt.__read_only_proxy = proxy
                local proxy_mt = {
                    __index = tbl,
                    __newindex = function (t, k, v) error("error write to a read-only table with key = " .. tostring(k)) end,
                    __pairs = function (t) return pairs(tbl) end,
                    -- __ipairs = function (t) return ipairs(tbl) end,  
                    __len = function (t) return #tbl end,
                    __read_only_proxy = proxy
                }
                setmetatable(proxy, proxy_mt)
            end
            travelled_tables[tbl] = proxy
            for k, v in pairs(tbl) do
                if type(v) == "table" then
                    tbl[k] = __read_only(v)
                end
            end
        end
        return travelled_tables[tbl]
    end
    return __read_only(inputTable)
end



-- 退出游戏
local function appExit()
    local final = function()
        if G_MAC.IS_IOS then
            os.exit(0)
        else
            cc.Director:getInstance():endToLua()
        end
    end
    
    async_run(function()
        G_SysEventEmitter:emit("event_appWillExit")
    end, final)
end

-- fmt( "%{%{1}} = {0} + {0}", 100, 200)
-- {200} = 100 + 100
local function fmt(format, ...)
    local args = {...}

    format = string.gsub(format, "({%d+})", function(arg)
        local idx = string.match(arg, "{(%d+)}")
        idx = idx + 1
        return tostring(args[idx])
    end)

    format = string.gsub(format, "%%{%%", "{")
    format = string.gsub(format, "%%}%%", "}")

    return format
end

-- @brief 枚举定义
local function enum(et)
    local t = {}
    local s, i = 0, 0

    for k, v in pairs(et) do
        if type(v) == 'number' then
            s = v
            i = 0
        else
            t[v] = s + i
            i = i + 1
        end
    end
    return t
end

local function property(t, name)
    local funcName = string.sub(name, 2)
    t["get" .. funcName] = function(this)
        return this[name]
    end
    t["set" .. funcName] = function(this, value)
        this[name] = value
    end
end





-------------------------------------------------------------------- 导出为全局函数 --------------------------------------------------------------------
-- 格式化table相关
cc.exports.print_lua_value = print_lua_value
cc.exports.format_lua_value = format_lua_value
-- 异步任务相关
cc.exports.async_run = async_run
cc.exports.async_yield = async_yield
cc.exports.async_wait = async_wait
cc.exports.async_cancel = async_cancel
-- 设置table只读
cc.exports.read_only = read_only
-- 退出游戏
cc.exports.appExit = appExit
-- 格式化函数
cc.exports.fmt = fmt
-- 枚举定义函数
cc.exports.enum = enum

cc.exports.property = property
