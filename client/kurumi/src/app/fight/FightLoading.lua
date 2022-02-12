-- @Author: fangcheng
-- @Date:   2021-06-05 16:33:34
-- @remark: 战斗loading界面

local FightLoading = class("FightLoading", G_Class.SuperNode)

function FightLoading:ctor()
    self.ui = G_Helper.loadStudioFile("ccs.ui.fight.UI_FightLoading", self)
    self:addChild(self.ui.root)

    self.totalWidth = self.ui.Image_LoadBG:getContentSize().width
    self.panelheight = self.ui.Panel_Load:getContentSize().height
    self:updateUI(0.0)
end

function FightLoading:setPercent(percent)
    self:updateUI(percent)
end

function FightLoading:updateUI(percent)
    percent = math.max(percent, 0.0)
    percent = math.min(percent, 1.0)
    self.ui.ldrunning:setPositionX(percent * self.totalWidth)
    self.ui.Panel_Load:setContentSize({width = percent * self.totalWidth, height = self.panelheight})
end

return FightLoading


