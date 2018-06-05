--------------------------------------------------------------
-- This file was automatically generated by Cocos Studio.
-- Do not make changes to this file.
-- All changes will be lost.
--------------------------------------------------------------

local luaExtend = require "LuaExtend"

-- using for layout to decrease count of local variables
local layout = nil
local localLuaFile = nil
local innerCSD = nil
local innerProject = nil
local localFrame = nil

local Result = {}
------------------------------------------------------------
-- function call description
-- create function caller should provide a function to 
-- get a callback function in creating scene process.
-- the returned callback function will be registered to 
-- the callback event of the control.
-- the function provider is as below :
-- Callback callBackProvider(luaFileName, node, callbackName)
-- parameter description:
-- luaFileName  : a string, lua file name
-- node         : a Node, event source
-- callbackName : a string, callback function name
-- the return value is a callback function
------------------------------------------------------------
function Result.create(callBackProvider)

local result={}
setmetatable(result, luaExtend)

--Create Scene
local Scene=cc.Node:create()
Scene:setName("Scene")

--Create Panel_1
local Panel_1 = ccui.Layout:create()
Panel_1:ignoreContentAdaptWithSize(false)
Panel_1:setClippingEnabled(false)
Panel_1:setBackGroundColorType(1)
Panel_1:setBackGroundColor({r = 150, g = 200, b = 255})
Panel_1:setBackGroundColorOpacity(102)
Panel_1:setTouchEnabled(true);
Panel_1:setLayoutComponentEnabled(true)
Panel_1:setName("Panel_1")
Panel_1:setTag(19)
Panel_1:setCascadeColorEnabled(true)
Panel_1:setCascadeOpacityEnabled(true)
Panel_1:setOpacity(51)
Panel_1:setColor({r = 0, g = 0, b = 0})
layout = ccui.LayoutComponent:bindLayoutComponent(Panel_1)
layout:setPercentWidthEnabled(true)
layout:setPercentHeightEnabled(true)
layout:setPercentWidth(1.0000)
layout:setPercentHeight(1.0000)
layout:setSize({width = 1136.0000, height = 640.0000})
layout:setHorizontalEdge(3)
layout:setVerticalEdge(3)
Scene:addChild(Panel_1)

--Create Image_BG
local Image_BG = ccui.ImageView:create()
Image_BG:ignoreContentAdaptWithSize(false)
Image_BG:loadTexture("messagebox/ti_bg.png",0)
Image_BG:setScale9Enabled(true)
Image_BG:setCapInsets({x = 172, y = 74, width = 178, height = 77})
Image_BG:setLayoutComponentEnabled(true)
Image_BG:setName("Image_BG")
Image_BG:setTag(21)
Image_BG:setCascadeColorEnabled(true)
Image_BG:setCascadeOpacityEnabled(true)
Image_BG:setPosition(568.0000, 320.0000)
layout = ccui.LayoutComponent:bindLayoutComponent(Image_BG)
layout:setPositionPercentXEnabled(true)
layout:setPositionPercentYEnabled(true)
layout:setPositionPercentX(0.5000)
layout:setPositionPercentY(0.5000)
layout:setPercentWidth(0.4752)
layout:setPercentHeight(0.5112)
layout:setSize({width = 539.8820, height = 327.1826})
layout:setLeftMargin(298.0590)
layout:setRightMargin(298.0590)
layout:setTopMargin(156.4087)
layout:setBottomMargin(156.4087)
Scene:addChild(Image_BG)

--Create Text_show
local Text_show = ccui.Text:create()
Text_show:ignoreContentAdaptWithSize(false)
Text_show:setFontSize(25)
Text_show:setString([[Text Label]])
Text_show:setTextHorizontalAlignment(1)
Text_show:setTextVerticalAlignment(1)
Text_show:setLayoutComponentEnabled(true)
Text_show:setName("Text_show")
Text_show:setTag(24)
Text_show:setCascadeColorEnabled(true)
Text_show:setCascadeOpacityEnabled(true)
Text_show:setPosition(269.9429, 202.4549)
layout = ccui.LayoutComponent:bindLayoutComponent(Text_show)
layout:setPositionPercentXEnabled(true)
layout:setPositionPercentX(0.5000)
layout:setPositionPercentY(0.6188)
layout:setPercentWidth(0.7657)
layout:setPercentHeight(0.5496)
layout:setSize({width = 413.3877, height = 179.8267})
layout:setLeftMargin(63.2490)
layout:setRightMargin(63.2452)
layout:setTopMargin(34.8144)
layout:setBottomMargin(112.5415)
Image_BG:addChild(Text_show)

--Create Button_OK
local Button_OK = ccui.Button:create()
Button_OK:ignoreContentAdaptWithSize(false)
Button_OK:loadTextureNormal("messagebox/button_yes.png",0)
Button_OK:setTitleFontSize(14)
Button_OK:setTitleColor({r = 65, g = 65, b = 70})
Button_OK:setScale9Enabled(true)
Button_OK:setCapInsets({x = 15, y = 11, width = 128, height = 34})
Button_OK:setLayoutComponentEnabled(true)
Button_OK:setName("Button_OK")
Button_OK:setTag(22)
Button_OK:setCascadeColorEnabled(true)
Button_OK:setCascadeOpacityEnabled(true)
Button_OK:setPosition(134.9705, 65.4365)
if callBackProvider~=nil then
      Button_OK:addClickEventListener(callBackProvider("MessageBox.lua", Button_OK, "onClickOK"))
end
layout = ccui.LayoutComponent:bindLayoutComponent(Button_OK)
layout:setPositionPercentXEnabled(true)
layout:setPositionPercentYEnabled(true)
layout:setPositionPercentX(0.2500)
layout:setPositionPercentY(0.2000)
layout:setPercentWidth(0.2927)
layout:setPercentHeight(0.1712)
layout:setSize({width = 158.0000, height = 56.0000})
layout:setLeftMargin(55.9705)
layout:setRightMargin(325.9115)
layout:setTopMargin(233.7461)
layout:setBottomMargin(37.4365)
Image_BG:addChild(Button_OK)

--Create Button_Cancel
local Button_Cancel = ccui.Button:create()
Button_Cancel:ignoreContentAdaptWithSize(false)
Button_Cancel:loadTextureNormal("messagebox/button_no.png",0)
Button_Cancel:setTitleFontSize(14)
Button_Cancel:setTitleColor({r = 65, g = 65, b = 70})
Button_Cancel:setScale9Enabled(true)
Button_Cancel:setCapInsets({x = 15, y = 11, width = 128, height = 34})
Button_Cancel:setLayoutComponentEnabled(true)
Button_Cancel:setName("Button_Cancel")
Button_Cancel:setTag(23)
Button_Cancel:setCascadeColorEnabled(true)
Button_Cancel:setCascadeOpacityEnabled(true)
Button_Cancel:setAnchorPoint(0.4596, 0.5000)
Button_Cancel:setPosition(404.9115, 65.4365)
if callBackProvider~=nil then
      Button_Cancel:addClickEventListener(callBackProvider("MessageBox.lua", Button_Cancel, "onClickCancel"))
end
layout = ccui.LayoutComponent:bindLayoutComponent(Button_Cancel)
layout:setPositionPercentXEnabled(true)
layout:setPositionPercentYEnabled(true)
layout:setPositionPercentX(0.7500)
layout:setPositionPercentY(0.2000)
layout:setPercentWidth(0.2927)
layout:setPercentHeight(0.1712)
layout:setSize({width = 158.0000, height = 56.0000})
layout:setLeftMargin(332.2987)
layout:setRightMargin(49.5832)
layout:setTopMargin(233.7461)
layout:setBottomMargin(37.4365)
Image_BG:addChild(Button_Cancel)

--Create Animation
result['animation'] = ccs.ActionTimeline:create()
  
result['animation']:setDuration(0)
result['animation']:setTimeSpeed(1.0000)
--Create Animation List

result['root'] = Scene
return result;
end

return Result

