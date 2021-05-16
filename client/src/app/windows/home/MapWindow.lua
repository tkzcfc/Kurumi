-- @Author: fangcheng
-- @Date:   2020-11-22 19:18:48
-- @remark: 地图选择界面

local MapWindow = class("MapWindow", G_Class.UIWindow)

function MapWindow:ctor()
	MapWindow.super.ctor(self)

	self:loadUILua("windows.home.UI_MapWindow")

    self:initPageView()
end

function MapWindow:onExit()
    MapWindow.super.onExit(self)

    _MyG.SysSetManager:setProperty("iSelectPageIndex", self.iCurPage)
end

function MapWindow:initPageView()
    self.iTotalCount = 15
    
    local template = self.ui.Panel_Page
    for i=1,self.iTotalCount do
        local page = template:clone()
        self.ui.PageView:addPage(page)

        page:getChildByName("Image_bg"):loadTexture(string.format("plist/ui/fragment/fbmap%02d.png", i), 0)

        for j = 1, 3 do
            local str = string.format("副本%d-%d", i, j)
            local btn = page:getChildByName("Button_Map"..j)
            btn:loadTextureNormal(string.format("plist/ui/fragment/fbxmap%d.png", i),0)
            btn:getChildByName("Text"):setString(str)
            btn.mapIndex = i
            btn.levelIndex = j
            btn:addClickEventListener(function(...) self:onClickSelectMap(...) end)
        end
    end


    self.iCurPage = _MyG.SysSetManager:getProperty("iSelectPageIndex")
    self.ui.PageView:removePage(template)
    self.ui.PageView:setCurrentPageIndex(self.iCurPage)

    self:updateButtonState()
end

function MapWindow:onClickLeft()
    self.iCurPage = self.iCurPage - 1
    if self.iCurPage < 0 then
        self.iCurPage = 0
        return
    end
    self.ui.PageView:scrollToPage(self.iCurPage)

    self:updateButtonState()
end

function MapWindow:onClickRight()
    self.iCurPage = self.iCurPage + 1
    if self.iCurPage >= self.iTotalCount then
        self.iCurPage = self.iTotalCount - 1
        return
    end
    self.ui.PageView:scrollToPage(self.iCurPage)

    self:updateButtonState()
end

function MapWindow:updateButtonState()
    self.ui.Button_Left:setVisible(self.iCurPage > 0)
    self.ui.Button_Right:setVisible(self.iCurPage < self.iTotalCount - 1)
end

function MapWindow:onClickSelectMap(sender)
    --print(sender.mapIndex, sender.levelIndex)
    local args = 
    {
        mapID = "map"..sender.mapIndex
    }
    _MyG.ScenesManager:enterScene(_MyG.SCENE_ID_GAME_MAP, nil, nil, nil, args)
    --SCENE_ID_GAME_MAP
end

function MapWindow:onClickBack(sender)
	self:dismiss()
end

return MapWindow