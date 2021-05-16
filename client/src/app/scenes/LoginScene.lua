-- @Author: fangcheng
-- @Date:   2020-11-12 22:23:28
-- @remark: 登录场景

local LoginScene = class("LoginScene", G_Class.SceneBase)

function LoginScene:onCreate()
	LoginScene.super.onCreate(self)

	self:loadUILua("scenes.UI_LoginScene")

	local account = _MyG.SysSetManager:getLoginAcount()
	local pasword = _MyG.SysSetManager:getLoginPassword()
	self.ui.TextField_Account:setString(account)
	self.ui.TextField_Password:setString(pasword)

	_MyG.LoginManager:setLoadingHandle(handler(self, self.showLoading), handler(self, self.hideLoading))
end

-- @brief 登录游戏按钮回调
function LoginScene:onClickStart(sender)
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
end

function LoginScene:onExit()
	LoginScene.super.onExit(self)
	if self.loading then
		self:hideLoading()
		self.loading:release()
		self.loading = nil
	end
end

function LoginScene:showLoading()
	if self.loading == nil then
		self.loading = require("app.ui.UILoading").new()
		self.loading:retain()
	end
	self.loading:showLoading(nil, nil, self)
end

function LoginScene:hideLoading()
	if self.loading then
		self.loading:hideLoding()
	end
end

return LoginScene