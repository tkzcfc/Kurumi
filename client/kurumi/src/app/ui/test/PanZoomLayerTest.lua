-- @Author : fc
-- @Date   : 2022-02-06 16:54:37
-- @remark : 


local PanZoomLayerTest = class("PanZoomLayerTest", G_Class.UIMainFrame)

function PanZoomLayerTest:ctor()
	PanZoomLayerTest.super.ctor(self)

	self:loadUILua("ccs.ui.test.UI_PanZoomLayer")

	self:initUI()
end

function PanZoomLayerTest:initUI()
	self:test1()
end

function PanZoomLayerTest:test1()

	local sp = cc.Sprite:create("plist/arden.png")
	sp:setAnchorPoint(0, 0)
	sp:setPosition(0, 0)

	local layer = G_Class.PanZoomLayer.new(cc.size(display.width * 0.6, display.height * 0.6))
	layer:setAnchorPoint(cc.p(0.5, 0.5))
	layer:setPosition(display.width * 0.5, display.height * 0.5)
	layer:addUnit(sp)
	layer:setContainerSize(sp:getContentSize())
	layer:setBackGroundColorType(1)
	layer:setBackGroundColor(cc.c4b(200, 100, 0))
	layer:setBackGroundColorOpacity(200)

	-- 是否启用边界碰撞
	layer:setBoundCollisionEnabled(true)

	layer:setContainerZoom(4)
	layer:setBounceable(true)
	layer:setBounceRange(50)
	layer:setBounceFactor(0.1)
	layer.container:setMultipleTouchEnabled(true)
	-- layer:setDirection(1)
	self:addChild(layer)

	cc.Director:getInstance():getEventDispatcher():setGlobalMultiTouchEnabled(true)
end

function PanZoomLayerTest:onClickBack(sender)
	self:dismiss()
end

return PanZoomLayerTest

