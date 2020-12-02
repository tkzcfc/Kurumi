-- @Author: fangcheng
-- @Date:   2019-06-06 22:08:04
-- @remark: 

local UIScrollMsgBox = class("UIScrollMsgBox", G_Class.UIWindow)


function UIScrollMsgBox:ctor()
	UIScrollMsgBox.super.ctor(self)
	
	self.ui = _MyG.loadStudioFile("ui.UI_ScrollMessageBox", self)
    self:addChild(self.ui.root)

    self.preOKButtonPosX = self.ui.Button_OK:getPositionX()
    self.OKButtonCenterPosX = self.ui.Image_BG:getContentSize().width * 0.5
	self.ui.Text_Title:setString("提示")

	self.textColor = self.ui.Text_show:getTextColor()
	self.fontSize = self.ui.Text_show:getFontSize()
	self.fontName = self.ui.Text_show:getFontName()
	self.textType = self.ui.Text_show:getType()

	self.ui.Text_show:removeFromParent()
	self.ui.Text_show = nil
end

function UIScrollMsgBox:showBox(content, okcall, cancelcall)
	self:hideBox()
	self.okcall = okcall
	self.cancelcall = cancelcall

	self.ui.ScrollView_Content:removeAllChildren()
	local viewWidth = self.ui.ScrollView_Content:getContentSize().width
	local viewHeight = self.ui.ScrollView_Content:getContentSize().height

	local label = nil
	--Type::TTF : 1
	if self.textType == 1 then
		label = cc.Label:createWithTTF("", self.fontName, self.fontSize)
	-- Type::SYSTEM : 0
	else
		label = cc.Label:createWithSystemFont("", self.fontName, self.fontSize)
	end

	label:setTextColor(self.textColor)
	label:setDimensions(viewWidth, 0) -- 限定宽度
	label:setAnchorPoint({x = 0, y = 0})
	label:setString(content)
	self.ui.ScrollView_Content:addChild(label)

	local labelHeight = label:getContentSize().height
	if labelHeight > viewHeight then
		self.ui.ScrollView_Content:setInnerContainerSize({width = viewWidth, height = label:getContentSize().height})
	else
		self.ui.ScrollView_Content:setInnerContainerSize({width = viewWidth, height = viewHeight})
		label:setAnchorPoint({x = 0.5, y = 0.5})
		label:setPosition({x = viewWidth * 0.5, y = viewHeight * 0.5})
	end

	if cancelcall == nil then
		self.ui.Button_OK:setPositionX(self.OKButtonCenterPosX)
		self.ui.Button_Cancel:setVisible(false)
	else
		self.ui.Button_OK:setPositionX(self.preOKButtonPosX)
		self.ui.Button_Cancel:setVisible(true)
	end

	return self
end

function UIScrollMsgBox:hideBox()
	self:removeFromParent()
end

function UIScrollMsgBox:setTitle(title)
	self.ui.Text_Title:setString(title)
end

function UIScrollMsgBox:setButtonOKTitle(title)
	self.ui.Button_OK:setTitleText(title)
end

function UIScrollMsgBox:setButtonCancelTitle(title)
	self.ui.Button_Cancel:setTitleText(title)
end

function UIScrollMsgBox:onClickOK(sender)
	if self.okcall then
		self.okcall()
	end
	self:hideBox()
end

function UIScrollMsgBox:onClickCancel(sender)
	if self.cancelcall then
		self.cancelcall()
	end
	self:hideBox()
end

return UIScrollMsgBox



