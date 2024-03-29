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
Panel_Content:setTag(212)
Panel_Content:setCascadeColorEnabled(true)
Panel_Content:setCascadeOpacityEnabled(true)
layout = ccui.LayoutComponent:bindLayoutComponent(Panel_Content)
layout:setPercentWidthEnabled(true)
layout:setPercentHeightEnabled(true)
layout:setPercentWidth(1.0000)
layout:setPercentHeight(1.0000)
layout:setSize({width = 1136.0000, height = 640.0000})
Scene:addChild(Panel_Content)

--Create Image_5
local Image_5 = ccui.ImageView:create()
Image_5:ignoreContentAdaptWithSize(false)
Image_5:loadTexture("plist/ui/fragment/beijing2.png",0)
Image_5:setLayoutComponentEnabled(true)
Image_5:setName("Image_5")
Image_5:setTag(66)
Image_5:setCascadeColorEnabled(true)
Image_5:setCascadeOpacityEnabled(true)
Image_5:setPosition(568.0000, 320.0000)
layout = ccui.LayoutComponent:bindLayoutComponent(Image_5)
layout:setPositionPercentXEnabled(true)
layout:setPositionPercentYEnabled(true)
layout:setPositionPercentX(0.5000)
layout:setPositionPercentY(0.5000)
layout:setPercentWidthEnabled(true)
layout:setPercentHeightEnabled(true)
layout:setPercentWidth(1.0500)
layout:setPercentHeight(1.0500)
layout:setSize({width = 1192.8000, height = 672.0000})
layout:setLeftMargin(-28.4000)
layout:setRightMargin(-28.3999)
layout:setTopMargin(-16.0000)
layout:setBottomMargin(-16.0000)
Panel_Content:addChild(Image_5)

--Create Text_Tip
local Text_Tip = ccui.Text:create()
Text_Tip:ignoreContentAdaptWithSize(true)
Text_Tip:setTextAreaSize({width = 0, height = 0})
Text_Tip:setFontSize(22)
Text_Tip:setString([[进入游戏..]])
Text_Tip:setLayoutComponentEnabled(true)
Text_Tip:setName("Text_Tip")
Text_Tip:setTag(60)
Text_Tip:setCascadeColorEnabled(true)
Text_Tip:setCascadeOpacityEnabled(true)
Text_Tip:setPosition(568.0000, 34.2335)
layout = ccui.LayoutComponent:bindLayoutComponent(Text_Tip)
layout:setPositionPercentXEnabled(true)
layout:setPositionPercentX(0.5000)
layout:setPositionPercentY(0.0535)
layout:setPercentWidth(0.0968)
layout:setPercentHeight(0.0344)
layout:setSize({width = 110.0000, height = 22.0000})
layout:setLeftMargin(513.0000)
layout:setRightMargin(513.0000)
layout:setTopMargin(594.7665)
layout:setBottomMargin(23.2335)
Panel_Content:addChild(Text_Tip)

--Create Image_LoadBG
local Image_LoadBG = ccui.ImageView:create()
Image_LoadBG:ignoreContentAdaptWithSize(false)
cc.SpriteFrameCache:getInstance():addSpriteFrames("plist/ui/ui1.plist")
Image_LoadBG:loadTexture("dljmld01.png",1)
Image_LoadBG:setLayoutComponentEnabled(true)
Image_LoadBG:setName("Image_LoadBG")
Image_LoadBG:setTag(61)
Image_LoadBG:setCascadeColorEnabled(true)
Image_LoadBG:setCascadeOpacityEnabled(true)
Image_LoadBG:setPosition(578.9056, 75.5121)
layout = ccui.LayoutComponent:bindLayoutComponent(Image_LoadBG)
layout:setPositionPercentXEnabled(true)
layout:setPositionPercentX(0.5096)
layout:setPositionPercentY(0.1180)
layout:setPercentWidth(0.8477)
layout:setPercentHeight(0.0469)
layout:setSize({width = 963.0322, height = 30.0000})
layout:setLeftMargin(97.3895)
layout:setRightMargin(75.5784)
layout:setTopMargin(549.4879)
layout:setBottomMargin(60.5121)
Panel_Content:addChild(Image_LoadBG)

--Create ArmatureNode_Load
local ArmatureNode_Load = ccs.Armature:create()
ArmatureNode_Load:setName("ArmatureNode_Load")
ArmatureNode_Load:setTag(62)
ArmatureNode_Load:setCascadeColorEnabled(true)
ArmatureNode_Load:setCascadeOpacityEnabled(true)
ArmatureNode_Load:setPosition(963.0322, 30.0000)
layout = ccui.LayoutComponent:bindLayoutComponent(ArmatureNode_Load)
layout:setPositionPercentXEnabled(true)
layout:setPositionPercentYEnabled(true)
layout:setPositionPercentX(1.0000)
layout:setPositionPercentY(1.0000)
layout:setLeftMargin(963.0322)
layout:setBottomMargin(30.0000)
ccs.ArmatureDataManager:getInstance():addArmatureFileInfo("plist/uianimation/ldrunning.ExportJson")
ArmatureNode_Load:init("ldrunning")
ArmatureNode_Load:getAnimation():play("running",-1, 1)
Image_LoadBG:addChild(ArmatureNode_Load)

--Create Panel_Load
local Panel_Load = ccui.Layout:create()
Panel_Load:ignoreContentAdaptWithSize(false)
Panel_Load:setClippingEnabled(true)
Panel_Load:setBackGroundColorOpacity(102)
Panel_Load:setTouchEnabled(true);
Panel_Load:setLayoutComponentEnabled(true)
Panel_Load:setName("Panel_Load")
Panel_Load:setTag(63)
Panel_Load:setCascadeColorEnabled(true)
Panel_Load:setCascadeOpacityEnabled(true)
Panel_Load:setAnchorPoint(0.0000, 0.5000)
Panel_Load:setPosition(0.0000, 15.0000)
layout = ccui.LayoutComponent:bindLayoutComponent(Panel_Load)
layout:setPositionPercentXEnabled(true)
layout:setPositionPercentYEnabled(true)
layout:setPositionPercentY(0.5000)
layout:setPercentWidthEnabled(true)
layout:setPercentHeightEnabled(true)
layout:setPercentWidth(1.0000)
layout:setPercentHeight(0.6500)
layout:setSize({width = 963.0322, height = 19.5000})
layout:setTopMargin(5.2500)
layout:setBottomMargin(5.2500)
Image_LoadBG:addChild(Panel_Load)

--Create Image_2
local Image_2 = ccui.ImageView:create()
Image_2:ignoreContentAdaptWithSize(false)
cc.SpriteFrameCache:getInstance():addSpriteFrames("plist/ui/ui1.plist")
Image_2:loadTexture("dljmld02.png",1)
Image_2:setScale9Enabled(true)
Image_2:setCapInsets({x = 4, y = 3, width = 6, height = 4})
Image_2:setLayoutComponentEnabled(true)
Image_2:setName("Image_2")
Image_2:setTag(64)
Image_2:setCascadeColorEnabled(true)
Image_2:setCascadeOpacityEnabled(true)
Image_2:setAnchorPoint(0.0000, 0.5000)
Image_2:setPosition(0.0000, 9.7500)
layout = ccui.LayoutComponent:bindLayoutComponent(Image_2)
layout:setPositionPercentYEnabled(true)
layout:setPositionPercentY(0.5000)
layout:setPercentHeightEnabled(true)
layout:setPercentWidth(1.0384)
layout:setPercentHeight(1.0000)
layout:setSize({width = 1000.0000, height = 19.5000})
layout:setRightMargin(-36.9678)
Panel_Load:addChild(Image_2)

--Create Animation
result['animation'] = ccs.ActionTimeline:create()
  
result['animation']:setDuration(0)
result['animation']:setTimeSpeed(1.0000)
--Create Animation List

result['root'] = Scene
return result;
end

return Result

