-- @Author: fangcheng
-- @Date:   2020-11-22 19:18:29
-- @remark: 角色创建界面

local CreateWindow = class("CreateWindow", G_Class.UIWindow)

function CreateWindow:ctor()
	CreateWindow.super.ctor(self)

    local ui = G_Helper.loadStudioFile("windows.home.UI_CreateWindow", self)
    self:addChild(ui.root)
end

function CreateWindow:onClickSelect()
end

function CreateWindow:onClickCreate()
end

return CreateWindow