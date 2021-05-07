
local msgViewBase = require("app.common.msgViewBase")
local MainScene = class("MainScene", msgViewBase)

function MainScene:onCreate()
    MainScene.super.onCreate(self)
    self.ui = _MyG.loadStudioFile("zhucheng", self)
    self:addChild(self.ui.root)
    changeParticleSystemPositionType(self.ui.root, 2)

    self.ui.ScrollView:jumpToPercentHorizontal(35)
    self.ui.ScrollView:setScrollBarEnabled(false)

    local children = self.ui.Panel_Touch:getChildren()
    for k, v in pairs(children) do
        
    end
end

function MainScene:onClickEnter()
    _MyG.ScenesManager:enterScene(_MyG.SCENE_ID_SELECT)
end

function MainScene:onKeyBackReleased()
    _MyG.MessageBox:showBox("是否退出游戏", function() 
    	os.exit(0)
    end, function() end)
end

return MainScene
