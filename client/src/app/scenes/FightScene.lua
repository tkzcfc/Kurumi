-- @Author: fangcheng
-- @Date:   2021-05-16 16:22:11
-- @remark: 战斗场景

local FightLayer = require("app.fight.FightLayer")
local InputLayer = require("app.fight.InputLayer")
local FightScene = class("FightScene", G_Class.SceneBase)

function FightScene:onCreate()
    FightScene.super.onCreate(self)

    -- self:loadUILua("scenes.UI_FightScene")

    self:addChild(FightLayer.new())
end

function FightScene:initNetEvent()
    self:onSysMsg(SysEvent.FIGHT_INIT_FAIL, handler(self, self.onInitFightFail))
    self:onSysMsg(SysEvent.FIGHT_INIT_FINISH, handler(self, self.onInitFightFinish))
end

function FightScene:onInitFightFail()
    UIUtils:showOneBtnMsgBox("游戏初始化失败", function()
        _MyG.FightManager:exitFight()
    end)
end

function FightScene:onInitFightFinish()
    self:addChild(InputLayer.new())
end

return FightScene