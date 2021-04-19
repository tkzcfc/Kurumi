-- @Author: fangcheng
-- @Date:   2020-11-12 22:23:28
-- @remark: 登录场景

local LoginScene = class("LoginScene", G_Class.SceneBase)

function LoginScene:onCreate()
	LoginScene.super.onCreate(self)

	self.ui = G_Helper.loadStudioFile("scenes.UI_LoginScene", self)
    self:addChild(self.ui.root)

	local account = _MyG.SysSetManager:getLoginAcount()
	local pasword = _MyG.SysSetManager:getLoginPassword()
	self.ui.TextField_Account:setString(account)
	self.ui.TextField_Password:setString(pasword)
end

function LoginScene:initNetEvent()
	self:onNetMsg(MessageID.MSG_LOGIN_GATE_ACK, handler(self, self.onLoginGateAck))
end

-- @brief 登录游戏按钮回调
function LoginScene:onClickStart(sender)
	if self.waitLogin then return end
	if self.httpToken then return end

	local account = self.ui.TextField_Account:getString()
	local pasword = self.ui.TextField_Password:getString()

	if account == "" then
		G_UIUtils:showError(100)
		return
	end
	if pasword == "" then
		G_UIUtils:showError(101)
		return
	end

	self:request_login(account, pasword)
end

function LoginScene:request_login(account, pasword)
	if self.httpToken then return end

	local url = string.format("%s/api/login?user=%s&pwd=%s&platform=%s", _MyG.startURL, account, pasword, device.platform)
	self.httpToken = _MyG.HttpManager:read(url, function(ok, data)
		self.httpToken = nil
		self:hideLoading()

		if not ok then
			G_UIUtils:showError(2)
			return
		end

		data = json.decode(data)
		if data.code == errCode.SUCCESS then

			_MyG.SysSetManager:setLoginAcount(account)
			_MyG.SysSetManager:setLoginPassword(pasword)

			-- 登录成功
			_MyG.AccountInfo = {}
			_MyG.AccountInfo.token = data.token
			_MyG.AccountInfo.account = data.playerid
			-- 请求服务器列表
			self:request_svrlist()
		else
			if data.code == errCode.ACCOUNT_NOT_EXIST then
				G_UIUtils:showTwoBtnMsgBox(STR(11001), function()
					self:request_register(account, pasword)
				end)
			elseif data.code == errCode.WRONG_PASSWORD then
				G_UIUtils:showError(106)
			else
				G_UIUtils:showError(1, data.code)
			end
		end
	end)
	self:showLoading()
end

function LoginScene:request_register(account, pasword)
	if self.httpToken then return end

	local url = string.format("%s/api/register?user=%s&pwd=%s&platform=%s", _MyG.startURL, account, pasword, device.platform)
	self.httpToken = _MyG.HttpManager:read(url, function(ok, data)
		self.httpToken = nil
		self:hideLoading()

		if not ok then
			G_UIUtils:showError(2)
			self:request_login(account, pasword)
			return
		end

		data = json.decode(data)
		if data.code == errCode.SUCCESS then
			-- 注册成功
			G_UIUtils:showRemind(STR(11002))
		else
			G_UIUtils:showError(1, data.code)
		end
	end)
	self:showLoading()
end

-- @brief 服务器列表请求
function LoginScene:request_svrlist()
	if self.httpToken then return end

	local url = string.format("%s/api/svrlist", _MyG.startURL)
	self.httpToken = _MyG.HttpManager:read(url, function(ok, data)
		self.httpToken = nil
		self:hideLoading()

		-- 服务器列表获取失败
		if not ok then
			G_UIUtils:showError(108)
			return
		end

		data = json.decode(data)
		local list = data.list or {}

		-- 服务器列表为空
		if #list <= 0 then
			G_UIUtils:showError(109)
			return
		end

		-- 暂时默认连第一个服
		local svrInfo = json.decode(list[1])
		_MyG.NetManager:setGameInfo(svrInfo.ip, svrInfo.port)


		self:showLoading()
		self.waitLogin = true
	end)
	self:showLoading()
end

function LoginScene:onExit()
	_MyG.HttpManager:cancel(self.httpToken)
	if self.loading then
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

-- @brief 游戏连接到网关回复
function LoginScene:onLoginGateAck(msg)
	if msg.code == errCode.SUCCESS then
		-- 网关连接成功
		_MyG.NetManager:sendToGame(MessageID.MSG_LOGIN_REQ, {
			token = _MyG.AccountInfo.token,
			account = _MyG.AccountInfo.account,
			playerID = 0
		})
	else
		G_UIUtils:showError(1, msg.code)
	end
end



return LoginScene