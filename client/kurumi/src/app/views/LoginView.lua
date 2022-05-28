-- @Author : fc
-- @Date   : 2021-10-29 17:22:25
-- @remark : 登录界面


local Super = import(".ViewBase")

local LoginView = class("LoginView", Super)

function LoginView:onLoadView()
    Super.onLoadView(self)

    self:loadUILua("ccs.views.UI_LoginView")

    local account = _MyG.SysSetManager:getLoginAcount()
    local pasword = _MyG.SysSetManager:getLoginPassword()
    self.ui.TextField_Account:setString(account)
    self.ui.TextField_Password:setString(pasword)

    _MyG.LoginManager:setLoadingHandle(handler(self, self.showLoading), handler(self, self.hideLoading))
end

-- @brief 登录游戏按钮回调
function LoginView:onClickStart(sender)
    local account = self.ui.TextField_Account:getString()
    local pasword = self.ui.TextField_Password:getString()

    if account == "" then
        UIUtils:showError(100)
        return
    end
    if pasword == "" then
        UIUtils:showError(101)
        return
    end

    _MyG.LoginManager:requestLogin(account, pasword)

    -- local box = require("app.ui.general.UIMessageBox").new()
    -- box:setEnableDrag(true)
    -- box:showOneButton("I an 11111111111111 Box", function()
    --     local ui = require("app.ui.test.RichTest").new():show()
        
    --     local close = require("app.ui.general.UIMessageBox").new()
    --     close:setEnableDrag(true)
    --     close:showOneButton("I an 22222222222 Box", function()
    --         if tolua.isnull(ui) then
    --             close:dismiss()
    --         end
    --     end)
    --     close:show(true)
    -- end)
    -- box:show()
end

function LoginView:onExit()
    Super.onExit(self)
    if self.loading then
        self:hideLoading()
        self.loading:release()
        self.loading = nil
    end
end

function LoginView:showLoading()
    if self.loading == nil then
        self.loading = require("app.ui.general.UILoading").new()
        self.loading:retain()
    end
    self.loading:showLoading(nil, nil, self)
end

function LoginView:hideLoading()
    if self.loading then
        self.loading:hideLoding()
    end
end

return LoginView

