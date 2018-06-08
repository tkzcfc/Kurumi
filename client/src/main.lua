_MyG = {}

cc.FileUtils:getInstance():setPopupNotify(false)
cc.FileUtils:getInstance():addSearchPath("src/")
cc.FileUtils:getInstance():addSearchPath("res/")

require "config"
require "cocos.init"

require("app.common.PreInit")

local function main()
    _MyG.APP = require("app.MyApp"):create()
    _MyG.APP:run()
end

__G__TRACKBACK__ = function(msg)
    local msg = debug.traceback(msg, 3)
    local logmsg = os.date() .. ":"..msg
    print(logmsg)
    local data = {exception = logmsg}
	_MyG.Net:sendMsgToGame("debug.C2S_luaexception", data)
    return msg
end

local status, msg = xpcall(main, __G__TRACKBACK__)
if not status then	
end
