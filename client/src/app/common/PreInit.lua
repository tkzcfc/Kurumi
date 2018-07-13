
_MyG.loadStudioFile = function(fileName, target)
	local root = require(fileName).create(function (path, node, funcName)
		if target == nil then
			return
		end
        return function(...) 
            if target[funcName] and type(target[funcName]) == "function" then
                target[funcName](target, ...)
            else
                print(string.format("[%s -> %s]: %s方法未实现", path, node:getName(), funcName))
            end
        end
    end)
    return root
end

local LOCAL_SERVER = false

if LOCAL_SERVER then
    _MyG.GAME_IP = "127.0.0.1"
    _MyG.GAME_PORT = 1234
else
    _MyG.GAME_IP = "www.kurumi.xin"
    _MyG.GAME_PORT = 1234
end

local targetPlatform = cc.Application:getInstance():getTargetPlatform()

if targetPlatform == cc.PLATFORM_OS_WINDOWS then
    _MyG.DEBUG = true
end


-- _MyG.StartScene = "GameMain"
_MyG.StartScene = "LoginScene"
-- _MyG.StartScene = "LoadResource"

if not _MyG.DEBUG then
    _MyG.GAME_IP = "www.kurumi.xin"
    _MyG.StartScene = "LoginScene"
end



----------------------------------------------------------------------------------
require("cocos.cocos2d.json")

require("app.config.SceneConfig")

_MyG.GameSceneSwither = require("app.common.GameSceneSwither")

_MyG.Net = require("app.models.net.gameNet"):new()
_MyG.PlayerDispatcher = require("app.common.dispatcher"):new()
_MyG.PlayerController = require("app.actor.role.PlayerController"):new()

_MyG.Loading = require("app.ui.LoadingUI"):new()
_MyG.Loading:retain()

_MyG.MessageBox = require("app.ui.MessageBoxUI"):new()
_MyG.MessageBox:retain()

_MyG.GlobalMsgRecipient = require("app.common.GlobalMsgRecipient")

_MyG.GlobalDataCache = require("app.common.GlobalDataCache")

