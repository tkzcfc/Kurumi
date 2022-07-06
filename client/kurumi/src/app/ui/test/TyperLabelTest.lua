-- @Author : fc
-- @Date   : 2022-07-06 21:42:13
-- @remark : 


local TyperLabelTest = class("TyperLabelTest", G_Class.UIMainFrame)

function TyperLabelTest:ctor()
	TyperLabelTest.super.ctor(self)

	self:loadUILua("ccs.ui.test.UI_TyperLabelTest")

	self:initUI()
end

function TyperLabelTest:initUI()
	local TyperLabel = G_Class.TyperLabel

	TyperLabel.doTyper(self.ui.Text, 0.05, function()
		print("finish===>")
	end)
end

function TyperLabelTest:onClickBack(sender)
	self:dismiss()
end

return TyperLabelTest
