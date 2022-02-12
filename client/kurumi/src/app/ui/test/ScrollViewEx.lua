-- @Author : fc
-- @Date   : 2022-02-06 16:16:38
-- @remark : 


local ScrollViewEx = class("ScrollViewEx", G_Class.UIMainFrame)

function ScrollViewEx:ctor()
	ScrollViewEx.super.ctor(self)

	self:loadUILua("ccs.ui.test.UI_ScrollViewEx")

	self:initUI()
end

function ScrollViewEx:initUI()
	self.itemSize = self.ui.template:getContentSize()
	self.ui.template:setVisible(false)

	self.ui.scrollList:setItemCreatedCallback(function(item)
		item:setUpdateCallback(function(index)
			item:getRender():getChildByName("Text"):setString(index)
		end)
		item:setRender(self.ui.template:clone())
	end)

	self:updateList()
end

function ScrollViewEx:updateList()
	local count = checkint(self.ui.Text_Count:getString())

	self.ui.scrollList:setPadding(5, 5)
	self.ui.scrollList:setItemsMargin(3, 3)
	self.ui.scrollList:setItemViewModelAndHideBar(require("ui.ScrollItem"), 1000, self.itemSize, count, self.ui.CheckBox_1:isSelected())
end

function ScrollViewEx:onClickStep(sender)
	local count = checkint(self.ui.Text_Count:getString())
	local step = checkint(sender.UserData[1])

	if step > 0 then
		if count >= 10 then return end
	else
		if count <= 1 then return end
	end

	count = count + step
	self.ui.Text_Count:setString(count)

	self:updateList()
end

function ScrollViewEx:onEventCheckBox(sender)
	self:updateList()
end

function ScrollViewEx:onClickBack(sender)
	self:dismiss()
end

return ScrollViewEx
