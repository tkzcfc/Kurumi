-- @Author : fangcheng
-- @Date   : 2020-02-28 21:26:16
-- @remark : 启动场景


-- 是否开启热更新
local enableHotUpdate = true

local ViewBase = cc.load("mvc").ViewBase
local SplashScene = class("SplashScene", ViewBase)

function SplashScene:ctor()
	local ui = require("scenes.UI_SplashScene").create(function (path, node, funcName)
        return function(...) 
            if type(self[funcName]) == "function" then
                self[funcName](self, ...)
            else
                print(string.format("[%s -> %s]: %s方法未实现", path, node:getName(), funcName))
            end
        end
    end)

    self:addChild(ui.root)
	self:loading()
end

function SplashScene:loading()
	local call = cc.CallFunc:create(function()
		if enableHotUpdate then
			require("app.ipConfig")
			G_AppInstance:run("UpdateScene")
		else
			require("app.init"):load(function()
				_MyG.ScenesManager:switchScene(_MyG.StartSceneID)
			end)
		end
	end)
	self:runAction(cc.Sequence:create(cc.DelayTime:create(0.1), call))
end

return SplashScene