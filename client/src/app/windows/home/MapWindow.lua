-- @Author: fangcheng
-- @Date:   2020-11-22 19:18:48
-- @remark: 地图选择界面

local MapWindow = class("MapWindow", G_Class.UIWindow)

function MapWindow:ctor()
	MapWindow.super.ctor(self)

    local ui = G_Helper.loadStudioFile("windows.home.UI_MapWindow", self)
    self:addChild(ui.root)
end

return MapWindow