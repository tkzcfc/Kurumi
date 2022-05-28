-- @Author: fangcheng
-- @Date:   2020-11-07 21:42:39
-- @remark: 消息弹窗

local UIMessageBox = class("UIMessageBox", G_Class.UIDialog)

function UIMessageBox:ctor()
	UIMessageBox.super.ctor(self)

    local ui = G_Helper.loadStudioFile("ccs.ui.general.UI_MessageBox", self, true)
    self:addChild(ui.root)

    self.ui = ui
    self.preOKButtonPosX = self.ui.Button_OK:getPositionX()
    self.OKButtonCenterPosX = self.ui.Image_BG:getContentSize().width * 0.5

	self.ui.Text_show:setString("")

	self:setContentView(ui.Image_BG)
end

function UIMessageBox:showOneButton(content, okcall)
	self.okcall = okcall
	self.content = content

	self.ui.Text_Title:setString("提示")
	self.ui.Text_show:setString(self.content)

	self.ui.Button_OK:setPositionX(self.OKButtonCenterPosX)
	self.ui.Button_Cancel:setVisible(false)

	self.ui.Text_Title:setVisible(false)
	self.ui.Text_show:setVisible(false)

	self:setAutoDismiss(false)
	self:eternal()

	return self
end

function UIMessageBox:showTwoButton(content, okcall, cancelcall)
	self.okcall = okcall
	self.cancelcall = cancelcall
	self.content = content

	self.ui.Text_Title:setString("提示")
	self.ui.Text_show:setString(self.content)

	self.ui.Button_OK:setPositionX(self.preOKButtonPosX)
	self.ui.Button_Cancel:setVisible(true)

	self.ui.Text_Title:setVisible(false)
	self.ui.Text_show:setVisible(false)

	self:setAutoDismiss(true)
	self:setUICloseCondition()

	return self
end

function UIMessageBox:iAfterOpened()
	UIMessageBox.super.iAfterOpened(self)
	self.ui.Text_show:setVisible(true)
	self.ui.Text_Title:setVisible(true)
end

function UIMessageBox:iWillClose()
	UIMessageBox.super.iWillClose(self)
	self.ui.Button_OK:setTouchEnabled(false)
	self.ui.Button_Cancel:setTouchEnabled(false)

	if not self.bTriggerCB then
		if self.cancelcall then
			self.cancelcall()
		end
	end
end

function UIMessageBox:setTitle(title)
	self.ui.Text_Title:setString(title)
	return self
end

function UIMessageBox:onClickOK(sender)
	self.bTriggerCB = true
	local okcall = self.okcall

	self:setUICloseCondition()
	self:dismiss()

	if okcall then
		okcall()
	end
end

function UIMessageBox:onClickCancel(sender)
	self.bTriggerCB = true
	local cancelcall = self.cancelcall

	self:setUICloseCondition()
	self:dismiss()

	if cancelcall then
		cancelcall()
	end
end

return UIMessageBox