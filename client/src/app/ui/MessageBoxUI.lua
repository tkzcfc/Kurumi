local MessageBoxUI = class("MessageBoxUI", cc.Node)


function MessageBoxUI:ctor()
	self.ui = _MyG.loadStudioFile("MessageBox", self)
    self:addChild(self.ui.root)

    self:setGlobalZOrder(100)

    self.preOKButtonPosX = self.ui.Button_OK:getPositionX()
    self.OKButtonCenterPosX = self.ui.Image_BG:getContentSize().width * 0.5
end

function MessageBoxUI:showBox(content, okcall, cancelcall)
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

	_MyG.APP:getCurView():addChild(self)
	return self
end

function MessageBoxUI:setTitle(title)
	self.ui.Text_Title:setString(title)
end

function MessageBoxUI:onClickOK(sender)
	if self.okcall then
		self.okcall()
	end
	self:removeFromParent()
end

function MessageBoxUI:onClickCancel(sender)
	if self.cancelcall then
		self.cancelcall()
	end
	self:removeFromParent()
end

return MessageBoxUI



