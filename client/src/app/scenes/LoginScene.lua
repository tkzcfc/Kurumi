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
end

function LoginScene:initNetEvent()
	self:onNetMsg(MessageID.MSG_LOGIN_GATE_ACK, handler(self, self.onLoginGateAck))
	self:onNetMsg(MessageID.MSG_LOGIN_ACK, handler(self, self.onLoginAck))
end

-- @brief 登录游戏按钮回调
function LoginScene:onClickStart(sender)
	if self.httpToken then return end

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

	self:request_login(account, pasword)
end

-- @brief 登录请求
function LoginScene:request_login(account, pasword)
	if self.httpToken then return end

	local url = string.format("%s/api/login?user=%s&pwd=%s&platform=%s", _MyG.startURL, account, pasword, device.platform)
	self.httpToken = _MyG.HttpManager:read(url, function(ok, data)
		self.httpToken = nil
		self:hideLoading()

		if not ok then
			UIUtils:showError(2)
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
				UIUtils:showTwoBtnMsgBox(STR(11001), function()
					self:request_register(account, pasword)
				end)
			elseif data.code == errCode.WRONG_PASSWORD then
				UIUtils:showError(106)
			else
				UIUtils:showError(1, data.code)
			end
		end
	end)
	self:showLoading()
end

-- @brief 注册请求
function LoginScene:request_register(account, pasword)
	if self.httpToken then return end

	local url = string.format("%s/api/register?user=%s&pwd=%s&platform=%s", _MyG.startURL, account, pasword, device.platform)
	self.httpToken = _MyG.HttpManager:read(url, function(ok, data)
		self.httpToken = nil
		self:hideLoading()

		if not ok then
			UIUtils:showError(2)
			self:request_login(account, pasword)
			return
		end

		data = json.decode(data)
		if data.code == errCode.SUCCESS then
			-- 注册成功
			UIUtils:showRemind(STR(11002))
		else
			UIUtils:showError(1, data.code)
		end
	end)
	self:showLoading()
end

-- @brief 服务器列表请求
function LoginScene:request_svrlist()
	if self.httpToken then return end

	_MyG.NetManager:clearAllSessionInfo()

	local url = string.format("%s/api/svrlist", _MyG.startURL)
	self.httpToken = _MyG.HttpManager:read(url, function(ok, data)
		self.httpToken = nil
		self:hideLoading()

		-- 服务器列表获取失败
		if not ok then
			UIUtils:showError(108)
			return
		end

		data = json.decode(data)
		local list = data.list or {}

		-- 服务器列表为空
		if #list <= 0 then
			UIUtils:showError(109)
			return
		end

		-- 暂时默认连第一个服
		local svrInfo = json.decode(list[1])
		_MyG.NetManager:setGameInfo(svrInfo.ip, svrInfo.port)

		self:showLoading()
	end)
	self:showLoading()
end

function LoginScene:onExit()
	LoginScene.super.onExit(self)
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
		self:hideLoading()
		UIUtils:showError(1, msg.code)
	end
end

-- @brief 登录回复
function LoginScene:onLoginAck(msg)
	self:hideLoading()
	if msg.code == errCode.SUCCESS then
		-- 登录成功
		_MyG.AccountInfo.playerID 	= msg.infos[1].playerID
		_MyG.AccountInfo.name		= msg.infos[1].name

		_MyG.ScenesManager:switchScene(_MyG.SCENE_ID_MAIN)
	-- token 找不到
	elseif msg.code == errCode.NOT_FOUND then
		UIUtils:showError(112)
	-- 此账号有多个玩家信息
	elseif msg.code == errCode.GAME_LOGIN_MUT_PID then
		UIUtils:showError(111)
	-- 没有找到对应玩家信息
	elseif msg.code == errCode.GAME_LOGIN_NO_FOUND_PLAYER then
		UIUtils:showError(110)
	else
		UIUtils:showError(1, msg.code)
	end
end

return LoginScene