-- -- @Author : fc
-- -- @Date   : 2022-02-06 16:54:37
-- -- @remark : 


-- local PanZoomLayerTest = class("PanZoomLayerTest", G_Class.UIMainFrame)

-- function PanZoomLayerTest:ctor()
-- 	PanZoomLayerTest.super.ctor(self)

-- 	self:loadUILua("ccs.ui.test.UI_PanZoomLayer")

-- 	self:initUI()
-- end

-- function PanZoomLayerTest:initUI()
-- 	self:test1()
-- end

-- function PanZoomLayerTest:test1()

-- 	local PanZoomLayer = require("ui.PanZoomLayer")

-- 	local sp = cc.Sprite:create("plist/arden.png")
-- 	sp:setAnchorPoint(0, 0)
-- 	sp:setPosition(0, 0)

-- 	local layer = PanZoomLayer.new(cc.size(display.width * 0.6, display.height * 0.6))
-- 	layer:setAnchorPoint(cc.p(0.5, 0.5))
-- 	layer:setPosition(display.width * 0.5, display.height * 0.5)
-- 	layer:addUnit(sp)
-- 	layer:setContainerSize(sp:getContentSize())
-- 	layer:setBackGroundColorType(1)
-- 	layer:setBackGroundColor(cc.c4b(200, 100, 0))
-- 	layer:setBackGroundColorOpacity(200)

-- 	-- 是否启用边界碰撞
-- 	layer:setBoundCollisionEnabled(true)

-- 	layer:setContainerZoom(4)
-- 	layer:setBounceable(true)
-- 	layer:setBounceRange(50)
-- 	layer:setBounceFactor(0.1)
-- 	layer.container:setMultipleTouchEnabled(true)
-- 	-- layer:setDirection(1)
-- 	self:addChild(layer)
-- end

-- function PanZoomLayerTest:onClickBack(sender)
-- 	self:dismiss()
-- end

-- return PanZoomLayerTest



local arr = {
	1,5,3,9,10,2,1,8
}

local len = #arr


local swap = function(t, i, j)
	local tmp = t[i]
	t[i] = t[j]
	t[j] = tmp
end

for i = 1, len do
	for j = 1, len - i do
		if arr[j] > arr[j +1] then
			swap(arr, j, j + 1)
		end 
	end
end

print(table.concat(arr, ", "))


local function quick_sort(arr, left, right)
	if left < right then
		local middle = sort_ex(arr, left, right)
		quick_sort(arr, left, middle - 1)
		quick_sort(arr, middle + 1, right)
	end
end

function sort_ex(arr, left, right)
	local base = arr[left]
	repeat
		if left >= right then break end

		repeat
			if left >= right then break end
			if arr[right] < base then
				break
			end
			right = right - 1
		until(false)
		arr[left] = arr[right]


		repeat
			if left >= right then break end
			if arr[left] > base then
				break
			end
			left = left + 1
		until(false)
		arr[right] = arr[left]

	until(false)
	arr[left] = base
	return left
end

arr = {
	1,5,3,9,10,2,1,8
}

quick_sort(arr, 1, #arr)
print(table.concat(arr, ", "))