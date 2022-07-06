-- @Author : fc
-- @Date   : 2022-02-06 15:38:00
-- @remark : 


local TestMain = class("TestMain", G_Class.UIMainFrame)

function TestMain:ctor()
	TestMain.super.ctor(self)

	self:loadUILua("ccs.ui.test.UI_TestMain")

	self.datas = {
		{name = "ListView", script = "app.ui.test.ScrollViewEx"},
		{name = "CycleListView", script = "app.ui.test.CycleListViewTest"},
		{name = "PanZoomLayer", script = "app.ui.test.PanZoomLayerTest"},
		{name = "RichText", script = "app.ui.test.RichTest"},
		{name = "TyperLabel", script = "app.ui.test.TyperLabelTest"},
		{name = "PseudoRichText", script = "app.ui.test.PseudoRichTextTest"}
	}
	

	self:initUI()
end

function TestMain:initUI()
	local itemSize = self.ui.template:getContentSize()
	self.ui.template:setVisible(false)

	self.ui.scrollList:setItemCreatedCallback(function(item)
		item:setUpdateCallback(function(index)
			item:getRender():getChildByName("Text"):setString(self.datas[index].name)
		end)
		item:setRender(self.ui.template:clone())
		item:getRender():addClickEventListener(function()
			local script = self.datas[item.iIndex].script
			require(script).new():show()
		end)
	end)
	self.ui.scrollList:setItemsMargin(3, 3)
	self.ui.scrollList:setItemViewModelAndHideBar(G_Class.ScrollItem, #self.datas, itemSize, 5, true)
end

function TestMain:onClickBack(sender)
	self:dismiss()
end

return TestMain