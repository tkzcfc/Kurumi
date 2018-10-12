_MyG = {}

require("lua_code.utils.functions")

OPEN_DEBUG = 1

local function onServerStartCall(svr, success)
    if success then
        print("服务器启动成功")
    else
        print("服务器启动失败")
    end
end

local function onServerCloseCall(svr)
    print("服务器已关闭")
end

local function onServerNewConnectCall(svr, session)
    _MyG.PlayerManager:connectToServer(session)
end

local function onServerRecvCall(svr, session, data, len)
    local msgName, msgTab = recvMsg(data)
    _MyG.NetMsgDispatcher:call(msgName, session, msgTab)
end

local function onServerDisconnectCall(svr, session)
    _MyG.PlayerManager:disconnectToServer(session)
end

local function main()
	json = require("lua_code.utils.json")
    require("lua_code.utils.tools")
    require("lua_code.net.registerMsg")

    _MyG.NetMsgDispatcher = require("lua_code.utils.dispatcher"):new()
    _MyG.PlayerManager = require("lua_code.players.playerManager"):new()

    local clients = {}
    local sendMsg = ""

    local server = DUServer:new()
    server:startServer("0.0.0.0", 1234, false)
    server:registerLuaHandle("onServerStartCall", onServerStartCall)
    server:registerLuaHandle("onServerCloseCall", onServerCloseCall)
    server:registerLuaHandle("onServerNewConnectCall", onServerNewConnectCall)
    server:registerLuaHandle("onServerRecvCall", onServerRecvCall)
    server:registerLuaHandle("onServerDisconnectCall", onServerDisconnectCall)

    -- local obj = TestOBJ:new()
    -- obj:Test()
    -- -- obj:delete()
    -- obj = nil

    -- local time = 0.0
    -- local scheduKey = DUScheduler:getInstance():registerScripSchedule(function(dt)
    --     time = time + dt
    --     print(time)
    --     collectgarbage("collect")
    --     if time >= 10.0 then
    --         print(scheduKey)
    --         DUScheduler:getInstance():unRegisterScripSchedule(scheduKey)
    --     end
    -- end, 1.0, false)
    -- print("scheduKey = ", scheduKey)
end




__G__TRACKBACK__ = function(msg)
    local msg = debug.traceback(msg, 3)
    local logmsg = os.date() .. ":"..msg
    print(logmsg)
    return msg
end

local status, msg = xpcall(main, __G__TRACKBACK__)
if not status then
end