-- @Author: fangcheng
-- @Date:   2021-05-16 16:22:11
-- @remark: 战斗场景

local FightScene = class("FightScene", G_Class.SceneBase)

function FightScene:onCreate()
    FightScene.super.onCreate(self)

    self:loadUILua("scenes.UI_FightScene")
end

return FightScene