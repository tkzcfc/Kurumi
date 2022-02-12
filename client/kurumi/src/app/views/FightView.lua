-- @Author : fc
-- @Date   : 2021-10-29 18:15:16
-- @remark : 战斗界面

local FightLayer = require("app.fight.FightLayer")
local InputLayer = require("app.fight.InputLayer")
local FightView = class("FightView", import(".ViewBase"))

function FightView:onLoadView()
    FightView.super.onLoadView(self)
    -- self:loadUILua("ccs.views.UI_FightView")

    _MyG.FightContext = require("app.fight.FightContext").new()

    -- 战斗层创建
    local layer = FightLayer.new()
    self:addChild(layer)

    _MyG.FightContext:setFightLayer(layer)
end

function FightView:initNetEvent()
    self:onSysMsg(SysEvent.FIGHT_INIT_FAIL, handler(self, self.onInitFightFail))
    self:onSysMsg(SysEvent.FIGHT_INIT_FINISH, handler(self, self.onInitFightFinish))
end

-- @brief 战斗初始化失败
function FightView:onInitFightFail()
    UIUtils:showOneBtnMsgBox("游戏初始化失败", function()
        _MyG.FightManager:exitFight()
    end)
end

-- @brief 战斗初始化完成
function FightView:onInitFightFinish()
    -- 创建输入层
    local layer = InputLayer.new()
    self:addChild(layer)

    _MyG.FightContext:setInputLayer(layer)
end

-- @interface
-- @brief 返回按键按下
function FightView:onKeyBackReleased()
    UIUtils:showTwoBtnMsgBox("返回主场景", function()
        _MyG.FightManager:exitFight()
    end)
    return true
end

return FightView


