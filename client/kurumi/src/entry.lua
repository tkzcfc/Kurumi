-- @Author : fc
-- @Date   : 2021-10-29 13:59:29
-- @remark : 


local cacheLoadedTab = {}
local cachePreloadedTab = {}

-- @brief 重启游戏
function restartGame()
    local schedulerid

    local function restartAppEx()
        -- clean fullpath cache
        cc.FileUtils:getInstance():purgeCachedEntries()
        
        for k,v in pairs(package.loaded) do
            if not cacheLoadedTab[k] then
                package.loaded[k] = nil
                print("remove loaded:", k)
            end
        end
    
        for k,v in pairs(package.preload) do
            if not cachePreloadedTab[k] then
                package.preload[k] = nil
                print("remove preload:", k)
            end
        end
        _MyG = {}
        require("entry")()
    end

    local scheduler = cc.Director:getInstance():getScheduler()
    schedulerid = scheduler:scheduleScriptFunc(function (dt)
        cc.Director:getInstance():getScheduler():unscheduleScriptEntry(schedulerid)
        restartAppEx()
    end, 1 / 60.0, false)

    if G_SysEventEmitter and SysEvent then
        G_SysEventEmitter:emit(SysEvent.ON_GAME_WILL_EXIT)
    end
end

local function entry()
    -- 收集当前已加载的信息
    cacheLoadedTab = {}
    for k,v in pairs(package.loaded) do
        cacheLoadedTab[k] = true
    end    
    cachePreloadedTab = {}
    for k,v in pairs(package.preload) do
        cachePreloadedTab[k] = true
    end

    package.loaded["errlog"] = nil
    errlog = require("errlog")
    require("app.MyApp").new():run()
end

return entry
