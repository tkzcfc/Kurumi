-- @Author: fangcheng
-- @Date:   2022-1-16 20:29:09
-- @remark: 匹配界面

local Matching = class("Matching", G_Class.UIMainFrame)

function Matching:ctor()
	Matching.super.ctor(self)

	self:loadUILua("ccs.ui.pvp.UI_Matching")

    self:initUI()

    self.matchingTag = false
    _MyG.FightManager:requestStartPvP(0)
end

function Matching:initUI()
    self.ui.Text_Status:setString("匹配中...")
end

function Matching:initNetEvent()
    self:onNetMsg(MessageID.MSG_START_PVP_ACK, function(msg)
        if msg.code == errCode.PVP_MATCH_SUC then
            self.ui.Text_Status:setString("匹配成功")
            self.matchingTag = true
        else
            self.ui.Text_Status:setString("匹配中...")
        end
    end)
end

function Matching:onClickBack(sender)
	self:dismiss()
end

-- @brief 关闭UI
-- @param force 是否强制关闭
function Matching:dismiss(force)
    if self.matchingTag then
        Matching.super.dismiss(self, force)
        return
    end

    UIUtils:showTwoBtnMsgBox("是否结束匹配", function()
        Matching.super.dismiss(self, force)
    end)
end

return Matching