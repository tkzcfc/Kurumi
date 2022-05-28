-- @Author: fangcheng
-- @Date:   2022-1-16 20:29:09
-- @remark: 匹配界面

local Matching = class("Matching", G_Class.UIMainFrame)

function Matching:ctor()
	Matching.super.ctor(self)

	self:loadUILua("ccs.ui.pvp.UI_Matching")
    self:initUI()

    self.matchingTag = true
    _MyG.FightManager:requestStartPvP(0)
end

function Matching:initUI()
    self.ui.Text_Status:setString("匹配中...")

    self:setUICloseCondition(function()
        if self.matchingTag then
            UIUtils:showTwoBtnMsgBox("是否结束匹配", function()
                _MyG.NetManager:sendToGame(MessageID.MSG_STOP_PVP_REQ, {})
            end)
            return false
        end

        return true
    end)
end

function Matching:initNetEvent()
    self:onNetMsg(MessageID.MSG_START_PVP_ACK, function(msg)
        if msg.code == errCode.PVP_MATCH_SUC then
            self.ui.Text_Status:setString("匹配成功")
            self.matchingTag = false
        else
            self.ui.Text_Status:setString("匹配中...")
        end
    end)

    self:onNetMsg(MessageID.MSG_STOP_PVP_ACK, function(msg)
        self.matchingTag = false
        self:dismiss()
    end)
end

function Matching:onClickBack(sender)
	self:dismiss()
end

return Matching