-- @Author : fc
-- @Date   : 2022-07-06 21:48:54
-- @remark : 

local PseudoRichTextTest = class("PseudoRichTextTest", G_Class.UIMainFrame)

function PseudoRichTextTest:ctor()
	PseudoRichTextTest.super.ctor(self)

	self:loadUILua("ccs.ui.test.UI_PseudoRichTextTest")

	self:initUI()
end

function PseudoRichTextTest:initUI()
	G_Class.PseudoRichText:setString(self.ui.Text, "<font color=#FF6000>我是橙色文本</font>  <font>我是默认颜色文本</font> <font color=#0002FF>我是蓝色文本</font>")
	G_Class.TyperLabel.doTyper(self.ui.Text, 0.2, function()
		print("finish===>")
	end)
end

function PseudoRichTextTest:onClickBack(sender)
	self:dismiss()
end

return PseudoRichTextTest
