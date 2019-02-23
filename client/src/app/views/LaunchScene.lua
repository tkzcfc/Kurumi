local msgViewBase = require("app.common.msgViewBase")

local LaunchScene = class("LaunchScene", msgViewBase)

function LaunchScene:onCreate()
	LaunchScene.super.onCreate(self)

    self.ui = _MyG.loadStudioFile("LaunchScene", self)
    self:addChild(self.ui.root)

    self:Timer(self.ui.root, 0.2, function()
    	_MyG.APP:enterScene("UpdateScene")
    end)
end

function LaunchScene:Timer( node, delay, callback )
    local delay = cc.DelayTime:create( delay )
    local sequence = cc.Sequence:create( delay, cc.CallFunc:create( callback ) )
    node:runAction( sequence )
end

return LaunchScene