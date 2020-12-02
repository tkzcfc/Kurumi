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

--Create PageView
local PageView = ccui.PageView:create()
PageView:ignoreContentAdaptWithSize(false)
PageView:setClippingEnabled(true)
PageView:setBackGroundColorOpacity(102)
PageView:setTouchEnabled(false);
PageView:setLayoutComponentEnabled(true)
PageView:setName("PageView")
PageView:setTag(142)
PageView:setCascadeColorEnabled(true)
PageView:setCascadeOpacityEnabled(true)
PageView:setAnchorPoint(0.5000, 0.5000)
PageView:setPosition(568.0000, 320.0000)
layout = ccui.LayoutComponent:bindLayoutComponent(PageView)
layout:setPositionPercentXEnabled(true)
layout:setPositionPercentYEnabled(true)
layout:setPositionPercentX(0.5000)
layout:setPositionPercentY(0.5000)
layout:setPercentWidthEnabled(true)
layout:setPercentHeightEnabled(true)
layout:setPercentWidth(1.0000)
layout:setPercentHeight(1.0000)
layout:setSize({width = 1136.0000, height = 640.0000})
Scene:addChild(PageView)

--Create Panel_Page
local Panel_Page = ccui.Layout:create()
Panel_Page:ignoreContentAdaptWithSize(false)
Panel_Page:setClippingEnabled(false)
Panel_Page:setBackGroundColorOpacity(102)
Panel_Page:setLayoutComponentEnabled(true)
Panel_Page:setName("Panel_Page")
Panel_Page:setTag(146)
Panel_Page:setCascadeColorEnabled(true)
Panel_Page:setCascadeOpacityEnabled(true)
layout = ccui.LayoutComponent:bindLayoutComponent(Panel_Page)
layout:setPercentWidth(1.0000)
layout:setPercentHeight(1.0000)
layout:setSize({width = 1136.0000, height = 640.0000})
PageView:addPage(Panel_Page)

--Create Image_bg
local Image_bg = ccui.ImageView:create()
Image_bg:ignoreContentAdaptWithSize(false)
Image_bg:loadTexture("plist/ui/fragment/fbmap01.png",0)
Image_bg:setLayoutComponentEnabled(true)
Image_bg:setName("Image_bg")
Image_bg:setTag(147)
Image_bg:setCascadeColorEnabled(true)
Image_bg:setCascadeOpacityEnabled(true)
Image_bg:setPosition(568.0000, 320.0000)
layout = ccui.LayoutComponent:bindLayoutComponent(Image_bg)
layout:setPositionPercentXEnabled(true)
layout:setPositionPercentYEnabled(true)
layout:setPositionPercentX(0.5000)
layout:setPositionPercentY(0.5000)
layout:setPercentWidthEnabled(true)
layout:setPercentHeightEnabled(true)
layout:setPercentWidth(1.0000)
layout:setPercentHeight(1.0000)
layout:setSize({width = 1136.0000, height = 640.0000})
Panel_Page:addChild(Image_bg)

--Create Button_Map1
local Button_Map1 = ccui.Button:create()
Button_Map1:ignoreContentAdaptWithSize(false)
Button_Map1:loadTextureNormal("plist/ui/fragment/fbxmap1.png",0)
Button_Map1:loadTextureDisabled("Default/Button_Disable.png",0)
Button_Map1:setTitleFontSize(14)
Button_Map1:setTitleColor({r = 65, g = 65, b = 70})
Button_Map1:setScale9Enabled(true)
Button_Map1:setCapInsets({x = 15, y = 11, width = 157, height = 84})
Button_Map1:setLayoutComponentEnabled(true)
Button_Map1:setName("Button_Map1")
Button_Map1:setTag(194)
Button_Map1:setCascadeColorEnabled(true)
Button_Map1:setCascadeOpacityEnabled(true)
Button_Map1:setPosition(216.6944, 177.6897)
if callBackProvider~=nil then
      Button_Map1:addClickEventListener(callBackProvider("UI_SelectScene.lua", Button_Map1, "onClickSelectMap"))
end
layout = ccui.LayoutComponent:bindLayoutComponent(Button_Map1)
layout:setPositionPercentX(0.1908)
layout:setPositionPercentY(0.2776)
layout:setPercentWidth(0.1646)
layout:setPercentHeight(0.1656)
layout:setSize({width = 187.0000, height = 106.0000})
layout:setLeftMargin(123.1944)
layout:setRightMargin(825.8056)
layout:setTopMargin(409.3103)
layout:setBottomMargin(124.6897)
Panel_Page:addChild(Button_Map1)

--Create Text
local Text = ccui.Text:create()
Text:ignoreContentAdaptWithSize(true)
Text:setTextAreaSize({width = 0, height = 0})
Text:setFontSize(25)
Text:setString([[副本1-1]])
Text:setLayoutComponentEnabled(true)
Text:setName("Text")
Text:setTag(150)
Text:setCascadeColorEnabled(true)
Text:setCascadeOpacityEnabled(true)
Text:setAnchorPoint(0.0000, 0.5000)
Text:setPosition(18.7000, 81.9062)
layout = ccui.LayoutComponent:bindLayoutComponent(Text)
layout:setPositionPercentXEnabled(true)
layout:setPositionPercentYEnabled(true)
layout:setPositionPercentX(0.1000)
layout:setPositionPercentY(0.7727)
layout:setPercentWidth(0.4759)
layout:setPercentHeight(0.2358)
layout:setSize({width = 89.0000, height = 25.0000})
layout:setLeftMargin(18.7000)
layout:setRightMargin(79.3000)
layout:setTopMargin(11.5938)
layout:setBottomMargin(69.4062)
Button_Map1:addChild(Text)

--Create Button_Map2
local Button_Map2 = ccui.Button:create()
Button_Map2:ignoreContentAdaptWithSize(false)
Button_Map2:loadTextureNormal("plist/ui/fragment/fbxmap1.png",0)
Button_Map2:loadTextureDisabled("Default/Button_Disable.png",0)
Button_Map2:setTitleFontSize(14)
Button_Map2:setTitleColor({r = 65, g = 65, b = 70})
Button_Map2:setScale9Enabled(true)
Button_Map2:setCapInsets({x = 15, y = 11, width = 157, height = 84})
Button_Map2:setLayoutComponentEnabled(true)
Button_Map2:setName("Button_Map2")
Button_Map2:setTag(195)
Button_Map2:setCascadeColorEnabled(true)
Button_Map2:setCascadeOpacityEnabled(true)
Button_Map2:setPosition(540.9020, 320.4590)
layout = ccui.LayoutComponent:bindLayoutComponent(Button_Map2)
layout:setPositionPercentX(0.4761)
layout:setPositionPercentY(0.5007)
layout:setPercentWidth(0.1646)
layout:setPercentHeight(0.1656)
layout:setSize({width = 187.0000, height = 106.0000})
layout:setLeftMargin(447.4020)
layout:setRightMargin(501.5980)
layout:setTopMargin(266.5410)
layout:setBottomMargin(267.4590)
Panel_Page:addChild(Button_Map2)

--Create Text
local Text = ccui.Text:create()
Text:ignoreContentAdaptWithSize(true)
Text:setTextAreaSize({width = 0, height = 0})
Text:setFontSize(25)
Text:setString([[副本1-1]])
Text:setLayoutComponentEnabled(true)
Text:setName("Text")
Text:setTag(196)
Text:setCascadeColorEnabled(true)
Text:setCascadeOpacityEnabled(true)
Text:setAnchorPoint(0.0000, 0.5000)
Text:setPosition(18.7000, 81.9062)
layout = ccui.LayoutComponent:bindLayoutComponent(Text)
layout:setPositionPercentXEnabled(true)
layout:setPositionPercentYEnabled(true)
layout:setPositionPercentX(0.1000)
layout:setPositionPercentY(0.7727)
layout:setPercentWidth(0.4759)
layout:setPercentHeight(0.2358)
layout:setSize({width = 89.0000, height = 25.0000})
layout:setLeftMargin(18.7000)
layout:setRightMargin(79.3000)
layout:setTopMargin(11.5938)
layout:setBottomMargin(69.4062)
Button_Map2:addChild(Text)

--Create Button_Map3
local Button_Map3 = ccui.Button:create()
Button_Map3:ignoreContentAdaptWithSize(false)
Button_Map3:loadTextureNormal("plist/ui/fragment/fbxmap1.png",0)
Button_Map3:loadTextureDisabled("Default/Button_Disable.png",0)
Button_Map3:setTitleFontSize(14)
Button_Map3:setTitleColor({r = 65, g = 65, b = 70})
Button_Map3:setScale9Enabled(true)
Button_Map3:setCapInsets({x = 15, y = 11, width = 157, height = 84})
Button_Map3:setLayoutComponentEnabled(true)
Button_Map3:setName("Button_Map3")
Button_Map3:setTag(197)
Button_Map3:setCascadeColorEnabled(true)
Button_Map3:setCascadeOpacityEnabled(true)
Button_Map3:setPosition(880.2784, 490.3156)
layout = ccui.LayoutComponent:bindLayoutComponent(Button_Map3)
layout:setPositionPercentX(0.7749)
layout:setPositionPercentY(0.7661)
layout:setPercentWidth(0.1646)
layout:setPercentHeight(0.1656)
layout:setSize({width = 187.0000, height = 106.0000})
layout:setLeftMargin(786.7784)
layout:setRightMargin(162.2216)
layout:setTopMargin(96.6844)
layout:setBottomMargin(437.3156)
Panel_Page:addChild(Button_Map3)

--Create Text
local Text = ccui.Text:create()
Text:ignoreContentAdaptWithSize(true)
Text:setTextAreaSize({width = 0, height = 0})
Text:setFontSize(25)
Text:setString([[副本1-1]])
Text:setLayoutComponentEnabled(true)
Text:setName("Text")
Text:setTag(198)
Text:setCascadeColorEnabled(true)
Text:setCascadeOpacityEnabled(true)
Text:setAnchorPoint(0.0000, 0.5000)
Text:setPosition(18.7000, 81.9062)
layout = ccui.LayoutComponent:bindLayoutComponent(Text)
layout:setPositionPercentXEnabled(true)
layout:setPositionPercentYEnabled(true)
layout:setPositionPercentX(0.1000)
layout:setPositionPercentY(0.7727)
layout:setPercentWidth(0.4759)
layout:setPercentHeight(0.2358)
layout:setSize({width = 89.0000, height = 25.0000})
layout:setLeftMargin(18.7000)
layout:setRightMargin(79.3000)
layout:setTopMargin(11.5938)
layout:setBottomMargin(69.4062)
Button_Map3:addChild(Text)

--Create Node_Yun
local Node_Yun=cc.Node:create()
Node_Yun:setName("Node_Yun")
Node_Yun:setTag(139)
Node_Yun:setCascadeColorEnabled(true)
Node_Yun:setCascadeOpacityEnabled(true)
layout = ccui.LayoutComponent:bindLayoutComponent(Node_Yun)
layout:setPositionPercentXEnabled(true)
layout:setPositionPercentYEnabled(true)
layout:setRightMargin(1136.0000)
layout:setTopMargin(640.0000)
Scene:addChild(Node_Yun)

--Create ArmatureNode_Yun
local ArmatureNode_Yun = ccs.Armature:create()
ArmatureNode_Yun:setName("ArmatureNode_Yun")
ArmatureNode_Yun:setTag(1)
ArmatureNode_Yun:setCascadeColorEnabled(true)
ArmatureNode_Yun:setCascadeOpacityEnabled(true)
ArmatureNode_Yun:setPosition(1137.5480, 529.2249)
layout = ccui.LayoutComponent:bindLayoutComponent(ArmatureNode_Yun)
layout:setLeftMargin(1137.5480)
layout:setRightMargin(-1137.5480)
layout:setTopMargin(-529.2249)
layout:setBottomMargin(529.2249)
ccs.ArmatureDataManager:getInstance():addArmatureFileInfo("plist/uianimation/fbylz.ExportJson")
ArmatureNode_Yun:init("fbylz")
ArmatureNode_Yun:getAnimation():play("fbya01",-1, 1)
Node_Yun:addChild(ArmatureNode_Yun)

--Create Button_Left
local Button_Left = ccui.Button:create()
Button_Left:ignoreContentAdaptWithSize(false)
cc.SpriteFrameCache:getInstance():addSpriteFrames("plist/ui/ui1.plist")
Button_Left:loadTextureNormal("vipui04.png",1)
Button_Left:setTitleFontSize(14)
Button_Left:setTitleColor({r = 65, g = 65, b = 70})
Button_Left:setScale9Enabled(true)
Button_Left:setCapInsets({x = 15, y = 11, width = 36, height = 74})
Button_Left:setLayoutComponentEnabled(true)
Button_Left:setName("Button_Left")
Button_Left:setTag(153)
Button_Left:setCascadeColorEnabled(true)
Button_Left:setCascadeOpacityEnabled(true)
Button_Left:setPosition(82.3876, 320.0000)
if callBackProvider~=nil then
      Button_Left:addClickEventListener(callBackProvider("UI_SelectScene.lua", Button_Left, "onClickLeft"))
end
layout = ccui.LayoutComponent:bindLayoutComponent(Button_Left)
layout:setPositionPercentYEnabled(true)
layout:setPositionPercentX(0.0725)
layout:setPositionPercentY(0.5000)
layout:setPercentWidth(0.0616)
layout:setPercentHeight(0.1563)
layout:setSize({width = 70.0000, height = 100.0000})
layout:setLeftMargin(47.3876)
layout:setRightMargin(1018.6120)
layout:setTopMargin(270.0000)
layout:setBottomMargin(270.0000)
Scene:addChild(Button_Left)

--Create Button_Right
local Button_Right = ccui.Button:create()
Button_Right:ignoreContentAdaptWithSize(false)
cc.SpriteFrameCache:getInstance():addSpriteFrames("plist/ui/ui1.plist")
Button_Right:loadTextureNormal("vipui04.png",1)
Button_Right:setTitleFontSize(14)
Button_Right:setTitleColor({r = 65, g = 65, b = 70})
Button_Right:setFlippedX(true)
Button_Right:setScale9Enabled(true)
Button_Right:setCapInsets({x = 15, y = 11, width = 36, height = 74})
Button_Right:setLayoutComponentEnabled(true)
Button_Right:setName("Button_Right")
Button_Right:setTag(154)
Button_Right:setCascadeColorEnabled(true)
Button_Right:setCascadeOpacityEnabled(true)
Button_Right:setPosition(1039.1150, 320.0000)
if callBackProvider~=nil then
      Button_Right:addClickEventListener(callBackProvider("UI_SelectScene.lua", Button_Right, "onClickRight"))
end
layout = ccui.LayoutComponent:bindLayoutComponent(Button_Right)
layout:setPositionPercentYEnabled(true)
layout:setPositionPercentX(0.9147)
layout:setPositionPercentY(0.5000)
layout:setPercentWidth(0.0616)
layout:setPercentHeight(0.1563)
layout:setSize({width = 70.0000, height = 100.0000})
layout:setLeftMargin(1004.1150)
layout:setRightMargin(61.8845)
layout:setTopMargin(270.0000)
layout:setBottomMargin(270.0000)
Scene:addChild(Button_Right)

--Create Button_2
local Button_2 = ccui.Button:create()
Button_2:ignoreContentAdaptWithSize(false)
cc.SpriteFrameCache:getInstance():addSpriteFrames("plist/ui/ui2.plist")
Button_2:loadTextureNormal("fbjmt01.png",1)
Button_2:setTitleFontSize(14)
Button_2:setTitleColor({r = 65, g = 65, b = 70})
Button_2:setScale9Enabled(true)
Button_2:setCapInsets({x = 15, y = 11, width = 34, height = 42})
Button_2:setLayoutComponentEnabled(true)
Button_2:setName("Button_2")
Button_2:setTag(32)
Button_2:setCascadeColorEnabled(true)
Button_2:setCascadeOpacityEnabled(true)
Button_2:setPosition(1084.4680, 583.5734)
if callBackProvider~=nil then
      Button_2:addClickEventListener(callBackProvider("UI_SelectScene.lua", Button_2, "onClickBack"))
end
layout = ccui.LayoutComponent:bindLayoutComponent(Button_2)
layout:setPositionPercentX(0.9546)
layout:setPositionPercentY(0.9118)
layout:setPercentWidth(0.0563)
layout:setPercentHeight(0.1000)
layout:setSize({width = 64.0000, height = 64.0000})
layout:setLeftMargin(1052.4680)
layout:setRightMargin(19.5316)
layout:setTopMargin(24.4266)
layout:setBottomMargin(551.5734)
Scene:addChild(Button_2)

--Create Animation
result['animation'] = ccs.ActionTimeline:create()
  
result['animation']:setDuration(0)
result['animation']:setTimeSpeed(1.0000)
--Create Animation List

result['root'] = Scene
return result;
end

return Result

