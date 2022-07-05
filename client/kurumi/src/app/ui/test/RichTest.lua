-- @Author : fc
-- @Date   : 2022-02-06 17:02:27
-- @remark : 



local RichTest = class("RichTest", G_Class.UIMainFrame)

function RichTest:ctor()
	RichTest.super.ctor(self)

	self:loadUILua("ccs.ui.test.UI_RichTest")

	self:initUI()
end

function RichTest:initUI()
	local RichLabel = G_Class.RichLabel

	local test_text = {
	    "<div fontcolor=#ff0000>hello</div><div fontcolor=#00ff00>hello</div><div fontsize=12>你\"{ 一心向学}\"</div><div fontSize=26 fontcolor=#ff00bb>好</div>ok",
	    "<div outline=1,#ff0000>hello</div>",
	    "<div fontcolor=#ff0000>local </div><div fontcolor=#ffffff>label </div><div fontcolor=#ff0000>=</div><div fontcolor=#1e90ff>require</div>(<div fontcolor=#cdad6f>\"app.ui.rich.RichLabel\"</div>)",
	    "<div glow=#ff0000 underline=2,#ff0099 >hello</div>",
	    "<div shadow=2,-2,0.5,#ff0000 >hello</div>",
	    "hello<img src='role/pvp_role/hero_pk_dao_baiji.png' scale=0.35 rotate = 45 visible=true />world",
	    "hello<button src='Default/Button_Normal.png' rotate=30 tag = clickBtn />",
	    "hello<custom src='plist/bg_remind.png' tag = list /> QwQ",
	}
	    -- "hello<custom src='plist/bg_remind.png' tag = custom_1 />",
	-- local old = test_text
	-- test_text = {}
	-- test_text[1] = table.concat(old, "\n")

	local curPosY = display.height
	for i=1, #test_text do
	    local label = RichLabel.new {
	        fontName = "res/fonts/huakang.ttf",
	        fontSize = 20,
	        fontColor = cc.c3b(255, 255, 255),
	        maxWidth = display.width-200,
	        lineSpace = 0,
	        charSpace = 0,
	    }
	    -- 回调函数必须在setString之前
	    label:setCustomSpawnHook(function(params)
	    	if params.tag == "custom_1" then
	    		return display.newSprite(params.src)
	    	elseif params.tag == "list" then
	    		return self:createPanZoomLayer()
	    	end
		end)
	    label:setEleCreateHook(function(node, params)
	    	if params.tag == "clickBtn" then
	    		node:setTitleText("TxT")
	    		node:setTitleFontSize(30)
	    		node:setTitleColor(cc.c3b(0, 0, 0))
				node:addTouchEventListener(function (sender, eventType)
					print("on touch TxT", eventType)
				end)
	    	end
		end)
	    label:setString(test_text[i])
	    label:setPosition(cc.p(100,curPosY))
	    -- label:playAnimation(3)
	    self:addChild(label)

	    curPosY = curPosY - label:getContentSize().height

	    -- label:debugDraw()

	    -- print("size", label:getContentSize().width, label:getContentSize().height)
	end 
end


function RichTest:createPanZoomLayer()
	local PanZoomLayer = G_Class.PanZoomLayer

	local sp = cc.Sprite:create("plist/arden.png")
	sp:setAnchorPoint(0, 0)
	sp:setPosition(0, 0)

	local layer = PanZoomLayer.new(cc.size(display.width * 0.5, display.height * 0.4))
	layer:setAnchorPoint(cc.p(0.5, 0.5))
	layer:setPosition(display.width * 0.5, display.height * 0.5)
	layer:addUnit(sp)
	layer:setContainerSize(sp:getContentSize())
	layer:setBackGroundColorType(1)
	layer:setBackGroundColor(cc.c4b(200, 100, 0))
	layer:setBackGroundColorOpacity(200)

	-- 是否启用边界碰撞
	layer:setBoundCollisionEnabled(true)

	layer:setContainerZoom(2)
	layer:setBounceable(true)
	layer:setBounceRange(50)
	layer:setBounceFactor(0.1)
	layer.container:setMultipleTouchEnabled(true)
	-- layer:setDirection(1)

	return layer
end

function RichTest:onClickBack(sender)
	self:dismiss()
end

return RichTest
