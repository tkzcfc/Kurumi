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

--Create Panel_Content
local Panel_Content = ccui.Layout:create()
Panel_Content:ignoreContentAdaptWithSize(false)
Panel_Content:setClippingEnabled(false)
Panel_Content:setBackGroundColorOpacity(102)
Panel_Content:setLayoutComponentEnabled(true)
Panel_Content:setName("Panel_Content")
Panel_Content:setTag(169)
Panel_Content:setCascadeColorEnabled(true)
Panel_Content:setCascadeOpacityEnabled(true)
layout = ccui.LayoutComponent:bindLayoutComponent(Panel_Content)
layout:setPercentWidthEnabled(true)
layout:setPercentHeightEnabled(true)
layout:setPercentWidth(1.0000)
layout:setPercentHeight(1.0000)
layout:setSize({width = 1136.0000, height = 640.0000})
Scene:addChild(Panel_Content)

--Create Image_BG
local Image_BG = ccui.ImageView:create()
Image_BG:ignoreContentAdaptWithSize(false)
cc.SpriteFrameCache:getInstance():addSpriteFrames("plist/ui/ui1.plist")
Image_BG:loadTexture("tankuang02.png",1)
Image_BG:setScale9Enabled(true)
Image_BG:setCapInsets({x = 21, y = 21, width = 22, height = 22})
Image_BG:setLayoutComponentEnabled(true)
Image_BG:setName("Image_BG")
Image_BG:setTag(21)
Image_BG:setCascadeColorEnabled(true)
Image_BG:setCascadeOpacityEnabled(true)
Image_BG:setPosition(583.4496, 317.1840)
layout = ccui.LayoutComponent:bindLayoutComponent(Image_BG)
layout:setPositionPercentXEnabled(true)
layout:setPositionPercentYEnabled(true)
layout:setPositionPercentX(0.5136)
layout:setPositionPercentY(0.4956)
layout:setPercentWidth(0.4998)
layout:setPercentHeight(0.5629)
layout:setSize({width = 567.7244, height = 360.2833})
layout:setLeftMargin(299.5874)
layout:setRightMargin(268.6882)
layout:setTopMargin(142.6744)
layout:setBottomMargin(137.0423)
Panel_Content:addChild(Image_BG)

--Create Button_OK
local Button_OK = ccui.Button:create()
Button_OK:ignoreContentAdaptWithSize(false)
cc.SpriteFrameCache:getInstance():addSpriteFrames("plist/ui/ui1.plist")
Button_OK:loadTextureNormal("button01.png",1)
cc.SpriteFrameCache:getInstance():addSpriteFrames("plist/ui/ui1.plist")
Button_OK:loadTexturePressed("button02.png",1)
cc.SpriteFrameCache:getInstance():addSpriteFrames("plist/ui/ui1.plist")
Button_OK:loadTextureDisabled("button03.png",1)
Button_OK:setTitleFontSize(28)
Button_OK:setTitleText("确定")
Button_OK:setScale9Enabled(true)
Button_OK:setCapInsets({x = 15, y = 11, width = 34, height = 42})
Button_OK:setLayoutComponentEnabled(true)
Button_OK:setName("Button_OK")
Button_OK:setTag(22)
Button_OK:setCascadeColorEnabled(true)
Button_OK:setCascadeOpacityEnabled(true)
Button_OK:setPosition(147.3245, 63.6981)
if callBackProvider~=nil then
      Button_OK:addClickEventListener(callBackProvider("UI_MessageBox.lua", Button_OK, "onClickOK"))
end
layout = ccui.LayoutComponent:bindLayoutComponent(Button_OK)
layout:setPositionPercentXEnabled(true)
layout:setPositionPercentYEnabled(true)
layout:setPositionPercentX(0.2595)
layout:setPositionPercentY(0.1768)
layout:setPercentWidth(0.2466)
layout:setPercentHeight(0.1665)
layout:setSize({width = 140.0000, height = 60.0000})
layout:setLeftMargin(77.3245)
layout:setRightMargin(350.3999)
layout:setTopMargin(266.5852)
layout:setBottomMargin(33.6981)
Image_BG:addChild(Button_OK)

--Create Button_Cancel
local Button_Cancel = ccui.Button:create()
Button_Cancel:ignoreContentAdaptWithSize(false)
cc.SpriteFrameCache:getInstance():addSpriteFrames("plist/ui/ui1.plist")
Button_Cancel:loadTextureNormal("button01.png",1)
cc.SpriteFrameCache:getInstance():addSpriteFrames("plist/ui/ui1.plist")
Button_Cancel:loadTexturePressed("button02.png",1)
cc.SpriteFrameCache:getInstance():addSpriteFrames("plist/ui/ui1.plist")
Button_Cancel:loadTextureDisabled("button03.png",1)
Button_Cancel:setTitleFontSize(28)
Button_Cancel:setTitleText("取消")
Button_Cancel:setScale9Enabled(true)
Button_Cancel:setCapInsets({x = 15, y = 11, width = 34, height = 42})
Button_Cancel:setLayoutComponentEnabled(true)
Button_Cancel:setName("Button_Cancel")
Button_Cancel:setTag(23)
Button_Cancel:setCascadeColorEnabled(true)
Button_Cancel:setCascadeOpacityEnabled(true)
Button_Cancel:setAnchorPoint(0.4596, 0.5000)
Button_Cancel:setPosition(397.7477, 65.0311)
if callBackProvider~=nil then
      Button_Cancel:addClickEventListener(callBackProvider("UI_MessageBox.lua", Button_Cancel, "onClickCancel"))
end
layout = ccui.LayoutComponent:bindLayoutComponent(Button_Cancel)
layout:setPositionPercentXEnabled(true)
layout:setPositionPercentYEnabled(true)
layout:setPositionPercentX(0.7006)
layout:setPositionPercentY(0.1805)
layout:setPercentWidth(0.2466)
layout:setPercentHeight(0.1665)
layout:setSize({width = 140.0000, height = 60.0000})
layout:setLeftMargin(333.4037)
layout:setRightMargin(94.3207)
layout:setTopMargin(265.2522)
layout:setBottomMargin(35.0311)
Image_BG:addChild(Button_Cancel)

--Create ui33_4
cc.SpriteFrameCache:getInstance():addSpriteFrames("plist/ui/ui1.plist")
local ui33_4 = cc.Sprite:createWithSpriteFrameName("ui33.png")
ui33_4:setName("ui33_4")
ui33_4:setTag(67)
ui33_4:setCascadeColorEnabled(true)
ui33_4:setCascadeOpacityEnabled(true)
ui33_4:setPosition(160.8955, 326.1638)
layout = ccui.LayoutComponent:bindLayoutComponent(ui33_4)
layout:setPositionPercentX(0.2834)
layout:setPositionPercentY(0.9053)
layout:setPercentWidth(0.4157)
layout:setPercentHeight(0.0056)
layout:setSize({width = 236.0000, height = 2.0000})
layout:setLeftMargin(42.8955)
layout:setRightMargin(288.8289)
layout:setTopMargin(33.1195)
layout:setBottomMargin(325.1638)
ui33_4:setBlendFunc({src = 1, dst = 771})
Image_BG:addChild(ui33_4)

--Create ui33_4_0
cc.SpriteFrameCache:getInstance():addSpriteFrames("plist/ui/ui1.plist")
local ui33_4_0 = cc.Sprite:createWithSpriteFrameName("ui33.png")
ui33_4_0:setName("ui33_4_0")
ui33_4_0:setTag(68)
ui33_4_0:setCascadeColorEnabled(true)
ui33_4_0:setCascadeOpacityEnabled(true)
ui33_4_0:setPosition(401.3981, 326.1638)
layout = ccui.LayoutComponent:bindLayoutComponent(ui33_4_0)
layout:setPositionPercentX(0.7070)
layout:setPositionPercentY(0.9053)
layout:setPercentWidth(0.4157)
layout:setPercentHeight(0.0056)
layout:setSize({width = 236.0000, height = 2.0000})
layout:setLeftMargin(283.3981)
layout:setRightMargin(48.3264)
layout:setTopMargin(33.1195)
layout:setBottomMargin(325.1638)
ui33_4_0:setBlendFunc({src = 1, dst = 771})
Image_BG:addChild(ui33_4_0)

--Create ui33_4_1
cc.SpriteFrameCache:getInstance():addSpriteFrames("plist/ui/ui1.plist")
local ui33_4_1 = cc.Sprite:createWithSpriteFrameName("ui33.png")
ui33_4_1:setName("ui33_4_1")
ui33_4_1:setTag(69)
ui33_4_1:setCascadeColorEnabled(true)
ui33_4_1:setCascadeOpacityEnabled(true)
ui33_4_1:setPosition(160.8954, 281.1620)
layout = ccui.LayoutComponent:bindLayoutComponent(ui33_4_1)
layout:setPositionPercentX(0.2834)
layout:setPositionPercentY(0.7804)
layout:setPercentWidth(0.4157)
layout:setPercentHeight(0.0056)
layout:setSize({width = 236.0000, height = 2.0000})
layout:setLeftMargin(42.8954)
layout:setRightMargin(288.8290)
layout:setTopMargin(78.1213)
layout:setBottomMargin(280.1620)
ui33_4_1:setBlendFunc({src = 1, dst = 771})
Image_BG:addChild(ui33_4_1)

--Create ui33_4_0_0
cc.SpriteFrameCache:getInstance():addSpriteFrames("plist/ui/ui1.plist")
local ui33_4_0_0 = cc.Sprite:createWithSpriteFrameName("ui33.png")
ui33_4_0_0:setName("ui33_4_0_0")
ui33_4_0_0:setTag(70)
ui33_4_0_0:setCascadeColorEnabled(true)
ui33_4_0_0:setCascadeOpacityEnabled(true)
ui33_4_0_0:setPosition(401.3981, 281.1620)
layout = ccui.LayoutComponent:bindLayoutComponent(ui33_4_0_0)
layout:setPositionPercentX(0.7070)
layout:setPositionPercentY(0.7804)
layout:setPercentWidth(0.4157)
layout:setPercentHeight(0.0056)
layout:setSize({width = 236.0000, height = 2.0000})
layout:setLeftMargin(283.3981)
layout:setRightMargin(48.3264)
layout:setTopMargin(78.1213)
layout:setBottomMargin(280.1620)
ui33_4_0_0:setBlendFunc({src = 1, dst = 771})
Image_BG:addChild(ui33_4_0_0)

--Create Image_4
local Image_4 = ccui.ImageView:create()
Image_4:ignoreContentAdaptWithSize(false)
cc.SpriteFrameCache:getInstance():addSpriteFrames("plist/ui/ui1.plist")
Image_4:loadTexture("ui29.png",1)
Image_4:setScale9Enabled(true)
Image_4:setCapInsets({x = 15, y = 2, width = 16, height = 2})
Image_4:setLayoutComponentEnabled(true)
Image_4:setName("Image_4")
Image_4:setTag(71)
Image_4:setCascadeColorEnabled(true)
Image_4:setCascadeOpacityEnabled(true)
Image_4:setPosition(283.8622, 183.7873)
layout = ccui.LayoutComponent:bindLayoutComponent(Image_4)
layout:setPositionPercentXEnabled(true)
layout:setPositionPercentX(0.5000)
layout:setPositionPercentY(0.5101)
layout:setPercentWidth(0.8348)
layout:setPercentHeight(0.4515)
layout:setSize({width = 473.9308, height = 162.6747})
layout:setLeftMargin(46.8968)
layout:setRightMargin(46.8968)
layout:setTopMargin(95.1587)
layout:setBottomMargin(102.4499)
Image_BG:addChild(Image_4)

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
Text_show:setPosition(236.9654, 81.3373)
Text_show:setTextColor({r = 0, g = 0, b = 0})
layout = ccui.LayoutComponent:bindLayoutComponent(Text_show)
layout:setPositionPercentXEnabled(true)
layout:setPositionPercentYEnabled(true)
layout:setPositionPercentX(0.5000)
layout:setPositionPercentY(0.5000)
layout:setPercentWidthEnabled(true)
layout:setPercentHeightEnabled(true)
layout:setPercentWidth(0.9500)
layout:setPercentHeight(0.9500)
layout:setSize({width = 450.2343, height = 154.5410})
layout:setLeftMargin(11.8483)
layout:setRightMargin(11.8483)
layout:setTopMargin(4.0669)
layout:setBottomMargin(4.0669)
Image_4:addChild(Text_show)

--Create Text_Title
local Text_Title = ccui.Text:create()
Text_Title:ignoreContentAdaptWithSize(true)
Text_Title:setTextAreaSize({width = 0, height = 0})
Text_Title:setFontSize(28)
Text_Title:setString([[提示]])
Text_Title:setLayoutComponentEnabled(true)
Text_Title:setName("Text_Title")
Text_Title:setTag(74)
Text_Title:setCascadeColorEnabled(true)
Text_Title:setCascadeOpacityEnabled(true)
Text_Title:setPosition(283.8622, 304.2180)
layout = ccui.LayoutComponent:bindLayoutComponent(Text_Title)
layout:setPositionPercentXEnabled(true)
layout:setPositionPercentX(0.5000)
layout:setPositionPercentY(0.8444)
layout:setPercentWidth(0.0986)
layout:setPercentHeight(0.0777)
layout:setSize({width = 56.0000, height = 28.0000})
layout:setLeftMargin(255.8622)
layout:setRightMargin(255.8622)
layout:setTopMargin(42.0653)
layout:setBottomMargin(290.2180)
Image_BG:addChild(Text_Title)

--Create Animation
result['animation'] = ccs.ActionTimeline:create()
  
result['animation']:setDuration(0)
result['animation']:setTimeSpeed(1.0000)
--Create Animation List

result['root'] = Scene
return result;
end

return Result
