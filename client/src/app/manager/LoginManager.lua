-- @Author: fangcheng
-- @Date:   2021-05-16 10:35:51
-- @remark: 登录管理

local LoginManager = class("LoginManager", import(".BaseManager"))

-- @brief 初始化调用
function LoginManager:override_onInit()
    LoginManager.super.override_onInit(self)

    G_NetEventEmitter:on(MessageID.MSG_LOGIN_GATE_ACK, handler(self, self.onLoginGateAck), self)
    G_NetEventEmitter:on(MessageID.MSG_LOGIN_ACK, handler(self, self.onLoginAck), self)
    G_NetEventEmitter:on(MessageID.MSG_ENTER_GAME_ACK, handler(self, self.onEnterGameAck), self)
end

-- @brief 销毁时调用
function LoginManager:override_onDestroy()
    G_NetEventEmitter:offByTag(self)
    _MyG.HttpManager:cancel(self.httpToken)

    LoginManager.super.override_onDestroy(self)
end

--------------------------------------------- public ---------------------------------------------

-- @brief 设置loading代理函数
function LoginManager:setLoadingHandle(showHandle, hideHandle)
    self.fShowHandle = showHandle
    self.fHideHandle = hideHandle
end

-- @brief 登录请求
-- @param account 账号
-- @param pasword 密码
function LoginManager:requestLogin(account, pasword)
    if self.httpToken then return end

    local url = string.format("%s/api/login?user=%s&pwd=%s&platform=%s", _MyG.startURL, account, pasword, device.platform)
    self.httpToken = _MyG.HttpManager:read(url, function(ok, data)        
        self.httpToken = nil
        self:hideLoading()

        print("requestLogin", ok, data)

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
            self:requestSvrlist()
        else
            if data.code == errCode.ACCOUNT_NOT_EXIST then
                UIUtils:showTwoBtnMsgBox(STR(11001), function()
                    self:requestRegister(account, pasword)
                end)
            else
                UIUtils:showError(data.code)
            end
        end
    end)
    self:showLoading()
end

-- @brief 注册请求
function LoginManager:requestRegister(account, pasword)
    if self.httpToken then return end

    local url = string.format("%s/api/register?user=%s&pwd=%s&platform=%s", _MyG.startURL, account, pasword, device.platform)
    self.httpToken = _MyG.HttpManager:read(url, function(ok, data)
        self.httpToken = nil
        self:hideLoading()

        if not ok then
            UIUtils:showError(2)
            return
        end

        data = json.decode(data)
        if data.code == errCode.SUCCESS then
            -- 注册成功
            UIUtils:showRemind(STR(11002))
            self:requestLogin(account, pasword)
        else
            UIUtils:showError(1, data.code)
        end
    end)
    self:showLoading()
end

-- @brief 服务器列表请求
function LoginManager:requestSvrlist()
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

-- @brief 请求进入游戏
-- @param 角色id
function LoginManager:requestEnterGame(roleID)
    _MyG.NetManager:sendToGame(MessageID.MSG_ENTER_GAME_REQ, {
        token = _MyG.AccountInfo.token,
        playerID = _MyG.AccountInfo.playerID,
        roleID = roleID
    })
end

-- @brief 网关服登录结果返回
function LoginManager:onLoginGateAck(msg)
    if msg.code == errCode.SUCCESS then
        -- 请求登录游戏服
        _MyG.NetManager:sendToGame(MessageID.MSG_LOGIN_REQ, {
            token = _MyG.AccountInfo.token,
            account = _MyG.AccountInfo.account,
            playerID = 0
        })
    else
        self:hideLoading()
        UIUtils:showError(msg.code)

        if _MyG.ScenesManager:getCurSceneID() ~= _MyG.SCENE_ID_LOGIN then
            if _MyG.ScenesManager:canPopScene() then
                _MyG.ScenesManager:popScene()
                _MyG.ScenesManager:switchScene(_MyG.SCENE_ID_LOGIN)
            else
                _MyG.ScenesManager:switchScene(_MyG.SCENE_ID_LOGIN)
            end
        end
        G_WindowManager:removeAllWindow()
    end
end

-- @brief 游戏服登录结果
function LoginManager:onLoginAck(msg)
    self:hideLoading()
    if msg.code == errCode.SUCCESS then
        local info = msg.infos[1]
        -- 登录成功
        _MyG.AccountInfo.playerID   = info.playerID
        _MyG.AccountInfo.name       = info.name

        if info.arrRoleIds == nil or #info.arrRoleIds <= 0 then
            require("app.windows.home.CreateWindow").new():show()
        else
            self:requestEnterGame(info.arrRoleIds[1])
        end
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

-- @brief 进入游戏
function LoginManager:onEnterGameAck(msg)
    if msg.code == errCode.SUCCESS then
        _MyG.AccountInfo.roleinfo = msg.roleinfo
        _MyG.ScenesManager:switchScene(_MyG.SCENE_ID_MAIN)
    else
        UIUtils:showError(msg.code)
    end
    self:hideLoading()
end

function LoginManager:showLoading()
    if self.fShowHandle then
        self.fShowHandle()
    end
end

function LoginManager:hideLoading()
    if self.fHideHandle then
        self.fHideHandle()
    end
end

return LoginManager
