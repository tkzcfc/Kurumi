
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

local LOCAL_SERVER = true

if LOCAL_SERVER then
    _MyG.GAME_IP = "127.0.0.1"
    _MyG.GAME_PORT = 1234
else
    _MyG.GAME_IP = "www.kurumi.xin"
    _MyG.GAME_PORT = 1234
end

_MyG.OPEN_DEBUG = 1

-- _MyG.StartScene = "GameMain"
_MyG.StartScene = "LoginScene"





require("cocos.cocos2d.json")

_MyG.Net = require("app.models.net.gameNet"):new()
_MyG.PlayerDispatcher = require("app.common.dispatcher"):new()
_MyG.PlayerController = require("app.actor.role.PlayerController"):new()

_MyG.Loading = require("app.ui.LoadingUI"):new()
_MyG.Loading:retain()