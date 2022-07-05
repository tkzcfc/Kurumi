-- @Author : fc
-- @Date   : 2022-02-06 16:42:19
-- @remark : 


local CycleListViewTest = class("CycleListViewTest", G_Class.UIMainFrame)

function CycleListViewTest:ctor()
	CycleListViewTest.super.ctor(self)

	self:loadUILua("ccs.ui.test.UI_CycleListView")

	self:initUI()
end

function CycleListViewTest:initUI()
	self:test1(cc.p(display.cx - 200, display.cy))
	self:test2(cc.p(display.cx + 200, display.cy))
end


function CycleListViewTest:test1(pos)
	local cellSize = cc.size(300, 400)
	local cellCount = 5

	local view = G_Class.CycleListView.new(cellSize)
	view:setCellCount(cellCount)
	view:setCellSize(cellSize)
	view:setOnLoadCellCallback(function(idx)
		local lcolor = cc.LayerColor:create(cc.c4b(math.random(0, 200), math.random(0, 200), math.random(0, 200), 200), cellSize.width, cellSize.height)
		
		local label = cc.Label:create()
		label:setSystemFontSize(30)
		label:setSystemFontName("Arial")
		label:setString(tostring(idx))
		label:setColor(cc.c3b(0, 255, 100))
		label:setPosition(50, 100)
		label:setName("txt")
		lcolor:addChild(label)

		print("load", idx)
		return lcolor
	end)
	view:setOnReloadCellCallback(function(cell, index)
		print("reload", index)
		cell:getChildByName("txt"):setString(tostring(index))
	end)
	view:setAnchorPoint(cc.p(0.5, 0.5))
	view:setPosition(pos)
	view:setBackGroundColorType(1)
	view:setBackGroundColor(cc.c4b(200, 100, 0))
	view:setBackGroundColorOpacity(200)
	view:setDirection(0)
	-- view:setClippingEnabled(false)
	self:addChild(view)
	-- view:setPageMode()
	view:loadList()
end

function CycleListViewTest:test2(pos)
	local cellSize = cc.size(300, 400)
	local cellCount = 5

	local view = G_Class.CycleListView.new(cellSize)
	view:setCellCount(cellCount)
	view:setCellSize(cellSize)
	view:setOnLoadCellCallback(function(idx)
		local lcolor = cc.LayerColor:create(cc.c4b(math.random(0, 200), math.random(0, 200), math.random(0, 200), 200), cellSize.width, cellSize.height)
		
		local label = cc.Label:create()
		label:setSystemFontSize(30)
		label:setSystemFontName("Arial")
		label:setString(tostring(idx))
		label:setColor(cc.c3b(0, 255, 100))
		label:setPosition(50, 100)
		label:setName("txt")
		lcolor:addChild(label)

		print("load", idx)
		return lcolor
	end)
	view:setOnReloadCellCallback(function(cell, index)
		print("reload", index)
		cell:getChildByName("txt"):setString(tostring(index))
	end)
	view:setAnchorPoint(cc.p(0.5, 0.5))
	view:setPosition(pos)
	view:setBackGroundColorType(1)
	view:setBackGroundColor(cc.c4b(200, 100, 0))
	view:setBackGroundColorOpacity(200)
	view:setDirection(0)
	-- view:setClippingEnabled(false)
	self:addChild(view)
	view:setPageMode()
	view:loadList()
end

function CycleListViewTest:onClickBack(sender)
	self:dismiss()
end

return CycleListViewTest
