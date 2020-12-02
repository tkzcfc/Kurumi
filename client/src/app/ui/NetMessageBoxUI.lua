-- @Author: fangcheng
-- @Date:   2020-11-07 21:43:07
-- @remark: 

local NetMessageBoxUI = class("NetMessageBoxUI", cc.Node)


function NetMessageBoxUI:ctor()
	self.ui = G_Helper.loadStudioFile("ui.MessageBox_Net", self)
    self:addChild(self.ui.root)

    self.preOKButtonPosX = self.ui.Button_OK:getPositionX()
    self.OKButtonCenterPosX = self.ui.Image_BG:getContentSize().width * 0.5
end

function NetMessageBoxUI:showBox(content, okcall, cancelcall)
	self:hideBox()
	self.okcall = okcall
	self.cancelcall = cancelcall
	self.ui.Text_show:setString(content)
	self.ui.Text_Title:setString("提示")

	if cancelcall == nil then
		self.ui.Button_OK:setPositionX(self.OKButtonCenterPosX)
		self.ui.Button_Cancel:setVisible(false)
	else
		self.ui.Button_OK:setPositionX(self.preOKButtonPosX)
		self.ui.Button_Cancel:setVisible(true)
	end

	cc.Director:getInstance():getRunningScene():addChild(self, G_Const.WINDOW_Z.NET_MSGBOX)
	return self
end

function NetMessageBoxUI:hideBox()
    if self:getParent() then
        self:removeFromParent()
    end
end

function NetMessageBoxUI:setTitle(title)
	self.ui.Text_Title:setString(title)
end

function NetMessageBoxUI:onClickOK(sender)
	if self.okcall then
		self.okcall()
	end
	self:hideBox()
end

function NetMessageBoxUI:onClickCancel(sender)
	if self.cancelcall then
		self.cancelcall()
	end
	self:hideBox()
end

return NetMessageBoxUI


