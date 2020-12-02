-- @Author: fangcheng
-- @Date:   2020-11-15 20:49:39
-- @remark: 


local LoginWindow = class("LoginWindow", G_Class.UIWindow)

function LoginWindow:ctor()
	LoginWindow.super.ctor(self)

    local ui = G_Helper.loadStudioFile("windows.login.UI_LoginWindow", self)
    self:addChild(ui.root)
end

-- @brief 登录游戏按钮回调
function LoginWindow:onClickStart(sender)
	_MyG.ScenesManager:switchUIScene("app.windows.home.CreateWindow")
end

return LoginWindow