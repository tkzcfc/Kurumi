_MyG = {}

GAME_ORI_LEFT = -1
GAME_ORI_RIGHT = 1

cc.FileUtils:getInstance():setPopupNotify(false)
cc.FileUtils:getInstance():addSearchPath("src/")
cc.FileUtils:getInstance():addSearchPath("res/")

local cacheLoadedTab = {}
local cachePreloadedTab = {}
local gAppInstance = nil

local function runApp(sceneName)
    require("app.init.preInit")
    _MyG.APP = gAppInstance

    if sceneName == nil then
        sceneName = _MyG.DefaultScene
    end

    gAppInstance:run(sceneName)
end

function restartApp(sceneName)
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

    runApp(sceneName)
end


require "config"
require "cocos.init"

local function main()

    local writablePath = cc.FileUtils:getInstance():getWritablePath()
    local storagePath = writablePath .. "new_version"

    local searchPaths = cc.FileUtils:getInstance():getSearchPaths()

    local newSearchPaths = {}
    newSearchPaths[1] = storagePath.."/src/"
    newSearchPaths[2] = storagePath.."/res/"

    for k,v in pairs(searchPaths) do
        newSearchPaths[k + 2] = v
    end
    cc.FileUtils:getInstance():setSearchPaths(newSearchPaths)
    
    cacheLoadedTab = {}
    for k,v in pairs(package.loaded) do
        cacheLoadedTab[k] = true
    end
    
    cachePreloadedTab = {}
    for k,v in pairs(package.preload) do
        cachePreloadedTab[k] = true
    end

    gAppInstance = require("app.MyApp"):create()
    runApp()
end

__G__TRACKBACK__ = function(msg)
    local errormsg = debug.traceback(msg, 3)
    local logmsg = os.date() .. ":"..errormsg
    print(logmsg)

    if _MyG.Net == nil then
        return errormsg
    end

    local targetPlatform = cc.Application:getInstance():getTargetPlatform()
	if targetPlatform == cc.PLATFORM_OS_ANDROID 
	or targetPlatform == cc.PLATFORM_OS_IPHONE
	or targetPlatform == cc.PLATFORM_OS_IPAD then
    	local data = {exception = logmsg}
		_MyG.Net:sendMsgToGame("debug.C2S_luaexception", data)
	end
    return errormsg
end

local status, msg = xpcall(main, __G__TRACKBACK__)
if not status then
end
