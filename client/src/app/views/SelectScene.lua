
local msgViewBase = require("app.common.msgViewBase")
local SelectScene = class("SelectScene", msgViewBase)


function SelectScene:onCreate()
    self.super.onCreate(self)
    self.ui = _MyG.loadStudioFile("SelectScene", self)
    self:addChild(self.ui.root)


    self:initPageView()
    self:randomYun()
end

function SelectScene:initPageView()

    self.curPageIndex = self.ui.PageView:getCurrentPageIndex()
    self.totalPageCount = 15
    
    local template = self.ui.Panel_Page
    for i=2,self.totalPageCount do
        local page = template:clone()
        self.ui.PageView:addPage(page)

        page:getChildByName("Image_bg"):loadTexture(string.format("ui/fragment/fbmap%02d.png", i), 0)

        for j = 1, 3 do
            local str = string.format("副本%d-%d", i, j)
            local btn = page:getChildByName("Button_Map"..j)
            btn:loadTextureNormal(string.format("ui/fragment/fbxmap%d.png", i),0)
            btn:getChildByName("Text"):setString(str)        
        end

    end

    self:updateButtonState()
end

function SelectScene:randomYun()
    local winSize = cc.Director:getInstance():getVisibleSize()

    self.ui.Node_Yun:removeAllChildren()

    ccs.ArmatureDataManager:getInstance():addArmatureFileInfo("uianimation/fbylz.ExportJson")

    local hcount = 3
    local curCount = 1
    
    local heightArr = {}
    local tmph = winSize.height / (hcount + 1)
    for i=1,hcount do
        heightArr[i] = tmph * i
    end

    local totalTime = 17.0
    local totalCount = 4
    local singleTime = totalTime / totalCount

    local createYun = function(InIndex)
        local randomIndex = math.random(1, hcount)

        local ArmatureNode = ccs.Armature:create()
        ArmatureNode:init("fbylz")
        ArmatureNode:setPosition({x = winSize.width, y = heightArr[randomIndex]})        
        self.ui.Node_Yun:addChild(ArmatureNode)

        if type(InIndex) == "number" then
            ArmatureNode:getAnimation():play("fbya01",-1, 0)
            ArmatureNode:setPositionX(winSize.width / 3 * InIndex)
            print("InIndex = ", InIndex)
        else
            ArmatureNode:getAnimation():play("fbya01",-1, 1)
        end
    end

    createYun(1)
    createYun(2)
    createYun()

    for i=1,totalCount do
        local q = cc.Sequence:create(cc.DelayTime:create(i * singleTime), cc.CallFunc:create(createYun))
        self:runAction(q)
    end
end

function SelectScene:onClickLeft()
    self.curPageIndex = self.curPageIndex - 1
    if self.curPageIndex < 0 then
        self.curPageIndex = 0
        return
    end
    self.ui.PageView:scrollToPage(self.curPageIndex)

    self:updateButtonState()
end

function SelectScene:onClickRight()
    self.curPageIndex = self.curPageIndex + 1
    if self.curPageIndex >= self.totalPageCount then
        self.curPageIndex = self.totalPageCount - 1
        return
    end
    self.ui.PageView:scrollToPage(self.curPageIndex)

    self:updateButtonState()
end

function SelectScene:updateButtonState()
    self.ui.Button_Left:setVisible(self.curPageIndex > 0)
    self.ui.Button_Right:setVisible(self.curPageIndex < self.totalPageCount - 1)
end

return SelectScene
