local msgViewBase = require("app.common.msgViewBase")

local LoginScene = class("LoginScene", msgViewBase)

function LoginScene:onCreate()
	self.super.onCreate(self)

	self.ui = _MyG.loadStudioFile("LoginScene", self)
    self:addChild(self.ui.root)

	if _MyG.Net:connect(_MyG.GAME_IP, _MyG.GAME_PORT) then
    	_MyG.Loading:showLoading(nil, self)
    end

    self:register("login.S2C_login_ret", function(...) self:dis_login_ret(...) end)
    self:register("login.S2C_register_ret", function(...) self:dis_register_ret(...) end)
end

function LoginScene:onClickStart(sender)
	local account = self.ui.TextField_Account:getString()
	local password = self.ui.TextField_Password:getString()

	if account == "" or password == "" then
		print("账号或密码不能为空")
		return
	end

	self:sendLoginMsg(account, password)
end

function LoginScene:registerAccount()
	local account = self.ui.TextField_Account:getString()
	local password = self.ui.TextField_Password:getString()

	if account == "" or password == "" then
		print("账号或密码不能为空")
		return
	end

	self:sendRegisterMsg(account, password)
end

function LoginScene:sendLoginMsg(account, password)
	local data = {account = account, password =password}
	_MyG.Net:sendMsgToGame("login.C2S_login", data)
	_MyG.Loading:showLoading(nil, self)
end

function LoginScene:sendRegisterMsg(account, password)
	local data = {account = account, password =password}
	_MyG.Net:sendMsgToGame("login.C2S_register", data)
	_MyG.Loading:showLoading(nil, self)
end

function LoginScene:dis_login_ret(data)
	_MyG.Loading:hideLoding()
	if data.code == 0 then
		_MyG.APP:run("CreateScene")
	elseif data.code == 1 then
		self:registerAccount()
	else
		print(data.msg)
	end
end

function LoginScene:dis_register_ret(data)
	_MyG.Loading:hideLoding()
	if data.code == 0 then
		self:onClickStart(nil)
	else
		print(data.msg)
	end
end


return LoginScene