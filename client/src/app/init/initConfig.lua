local LOCAL_SERVER = false

if LOCAL_SERVER then
    _MyG.GAME_IP = "192.168.0.116"
    _MyG.GAME_PORT = 1234
else
    _MyG.GAME_IP = "www.kurumi.xin"
    _MyG.GAME_PORT = 1234
end

local targetPlatform = cc.Application:getInstance():getTargetPlatform()

if targetPlatform == cc.PLATFORM_OS_WINDOWS then
    _MyG.DEBUG = true
end


_MyG.StartScene = "GameScene"
-- _MyG.StartScene = "LoginScene"

if not _MyG.DEBUG then
    -- _MyG.GAME_IP = "www.kurumi.xin"
    _MyG.StartScene = "LoginScene"
end


_MyG.DefaultScene = "LaunchScene"
