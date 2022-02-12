
require("config")
require("cocos.init")
require("framework.init")

local AppBase = require("framework.AppBase")
local MyApp = class("MyApp", AppBase)

function MyApp:ctor()
    MyApp.super.ctor(self)
end

function MyApp:run()
	cc.Label:setTTFScaleFactor(display.contentScaleFactor) -- make TTF Label Anti-Aliasing

    math.newrandomseed()
    display.replaceScene(require("scenes.SplashScene").new())


    -- display.replaceScene(require("scenes.TestScene").new())
    
end

return MyApp

