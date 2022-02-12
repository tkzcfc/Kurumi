-- @Author : fangcheng
-- @Date   : 2020-02-28 21:26:16
-- @remark : 启动场景

local SplashScene = class("SplashScene", function()
    return display.newScene("SplashScene")
end)

function SplashScene:ctor()
	local ui = require("ccs.scenes.UI_SplashScene").create(function (path, node, funcName)
        return function(...) 
            if type(self[funcName]) == "function" then
                self[funcName](self, ...)
            else
                print(string.format("[%s -> %s]: %s方法未实现", path, node:getName(), funcName))
            end
        end
    end)

    ui.root:setContentSize(display.size)
    ccui.Helper:doLayout(ui.root)

    self:addChild(ui.root)
	self:loading()
end

function SplashScene:loading()
	local call = cc.CallFunc:create(function()
        require("app.ipConfig")
        display.replaceScene(require("scenes.UpdateScene").new())
	end)
	self:runAction(cc.Sequence:create(cc.DelayTime:create(0.1), call))
end

return SplashScene