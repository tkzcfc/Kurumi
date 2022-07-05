-- @Author: fangcheng
-- @Date:   2021-05-16 16:15:07
-- @remark: 战斗管理

local FightManager = class("FightManager", import(".BaseManager"))

-- 世界初始化参数
property(FightManager, "tWorldInfo")
-- 当前运行到第几帧
property(FightManager, "iLogicFrame", 0)
-- ping值
propertyReadOnly(FightManager, "iPing", 0)

-- @brief 初始化调用
function FightManager:override_onInit()
    FightManager.super.override_onInit(self)

    -- 游戏服回复的消息相关
    G_NetEventEmitter:on("msg.StartPVEFightAck", handler(self, self.onStartPVEFightAck), self)
    G_NetEventEmitter:on("msg.StartFightNTF", handler(self, self.onStartFightNTF), self)

    -- 战斗服回复的消息相关
    G_NetEventEmitter:on("msg.JoinFightAck", handler(self, self.onJoinFightAck), self)
    G_NetEventEmitter:on("msg.ExitFightAck", handler(self, self.onExitFightAck), self)
    G_NetEventEmitter:on("msg.PlayerExitFightNotify", handler(self, self.onPlayerExitFightNotify), self)
    G_NetEventEmitter:on("msg.Ping", handler(self, self.onPing), self)

    -- 系统事件
    G_SysEventEmitter:on(SysEvent.NET_CONNECT_SUC, handler(self, self.onNetConnectSuc), self)
    G_SysEventEmitter:on(SysEvent.NET_CONNECT_FAIL, handler(self, self.onNetConnectFail), self)
end

-- @brief pve战斗请求(目标：游戏服)
-- @param carbonId副本id
-- @param 进入副本的玩家信息
-- @param offlineMode 是否离线模式
function FightManager:requestStartPvE(carbonId, roles, offlineMode)
    -- offlineMode = false
    self:clearFightInfo()
    self:showShieldLayer()
    _MyG.NetManager:sendToGame("msg.StartPVEFightReq", {
        carbonId = carbonId,
        roles = roles,
        isOfflineMode = offlineMode == true,
    })
end

-- @brief pvp战斗请求（目标：游戏服）
-- @param foeId 对手id,为0则表示等待服务器匹配 为其他则表示挑战他人
function FightManager:requestStartPvP(foeId)
    self:clearFightInfo()
    _MyG.NetManager:sendToGame("msg.StartPVPFightReq", {
        foeId = foeId or 0,
    })
end

-- @brief 发送加入战斗请求(目标：战斗服)
function FightManager:joinFight()
    _MyG.NetManager:sendToFight("msg.JoinFightReq", {
        fightUUID = self.tFightInfo.fightUUID,
        playerID = _MyG.AccountInfo.playerID,
        frame = self.iLogicFrame,
    })
end

-- @brief 发送自己的加载进度情况(目标：战斗服)
-- @param fPercent 进度值
-- @param isFinish 是否加载完成
function FightManager:sendPlayerLoadingReq(fPercent, isFinish)
    _MyG.NetManager:sendToFight("msg.PlayerLoadingReq", {
        percent = fPercent,
        finish = isFinish,
    })
end

-- @brief 发送进入下一逻辑帧请求
-- @param key_down 本帧玩家的按键状态
function FightManager:sendRunNextFrameReq(key_down)
    if key_down == nil then print("wwwwwwwwwwwwwwwwwwwwwwwwwwwwwww") end
    
    _MyG.NetManager:sendToFight("msg.RunNextFrameReq", {
        frame = self.iLogicFrame,
        key_down = key_down or 0
    })
end

-- @brief 清除战斗信息
function FightManager:clearFightInfo()
    self.tFightInfo = nil
    self.iLogicFrame = 0
    self.tWorldInfo = 0
end

-- @brief 退出战斗
function FightManager:exitFight()
    -- 当前在战斗界面
    if self:isInFightView() then
        -- 切换回首页界面
        self:gotoMainView()
    end

    if self.tFightInfo == nil then
        -- 这种情况应该是收到MSG_EXIT_FIGHT_REQ消息回复后调用的本函数
        -- 已经发送过退出战斗请求了
        -- 清除网络管理器有关战斗服的信息
        -- 优雅关闭清理战斗服连接
        _MyG.NetManager:setFightInfo()
        return
    end

    -- 发送退出战斗请求
    _MyG.NetManager:sendToFight("msg.ExitFightReq", {
        fightUUID = self.tFightInfo.fightUUID
    })
    -- 清理战斗管理上的战斗信息
    self:clearFightInfo()
end

-- @brief pve战斗请求回复
function FightManager:onStartPVEFightAck(msg)
    if msg.code ~= errCode.SUCCESS then
        -- 提示错误信息
        UIUtils:showError(msg.code)
        self:hideShieldLayer()
    end
end

-- @brief 战斗开始通知(本消息是游戏服回复的)
function FightManager:onStartFightNTF(msg)
    -- 开始战斗失败,弹出错误信息
    if msg.code ~= errCode.SUCCESS then
        UIUtils:showError(msg.code)
        self:hideShieldLayer()
        return
    end

    -- 获取到战斗服的端口地址信息,连接战斗服
    self.tFightInfo = msg
    -- 清理之前的连接
    _MyG.NetManager:setFightInfo()
    -- 连接到战斗服
    _MyG.NetManager:setFightInfo(msg.fightIP, msg.fightPort, msg.netType)
end

-- @brief 加入战斗回复
function FightManager:onJoinFightAck(msg)
    -- 加入失败，弹出对应错误消息
    if msg.code ~= errCode.SUCCESS then
        UIUtils:showError(msg.code)
        self:hideShieldLayer()
        self:exitFight()
        return
    end
    self.tWorldInfo = msg.worldInfo

    if self:isInFightView() then
        -- 当前在战斗界面,发送事件通知:断线重连重新加入战斗
        G_SysEventEmitter:emit(SysEvent.FIGHT_RE_JOINT)
    else
        -- 进入战斗界面
        self:gotoFightView()
    end
end

-- @brief 收到退出战斗回复
function FightManager:onExitFightAck(msg)
    self:exitFight()
end

-- @brief 玩家被踢出战斗通知
function FightManager:onPlayerExitFightNotify(msg)
    self:clearFightInfo()
    self:exitFight()
end

-- @brief ping消息
function FightManager:onPing(msg)
    _MyG.NetManager:sendToFight("msg.Pong", {
        timestamp = msg.timestamp
    })

    self.iPing = msg.ping
end

-- @brief 战斗服连接成功
function FightManager:onNetConnectSuc(sessionID)
    if sessionID ~= SESSION_ID.FIGHT then return end

    -- 隐藏屏蔽层
    self:hideShieldLayer()

    -- 当前处于登录界面,不进行任何操作
    if self:isInLoginView() then
        return
    end

    -- 没有战斗信息了,表示已经退出战斗界面了才连接成功,不进行任何操作
    if not self.tFightInfo then return end

    -- 发送加入战斗请求
    self:joinFight()
end

-- @brief 战斗服连接失败
function FightManager:onNetConnectFail(sessionID)
    if sessionID ~= SESSION_ID.FIGHT then return end
    self:hideShieldLayer()

    -- 当前处于登录界面
    if self:isInLoginView() then
        -- 弹出软文提示:战斗服连接失败
        UIUtils:showError(118)
        return
    end

    -- 重新连接战斗服
    local function ok()
        _MyG.NetManager:doConnect(sessionID)
    end

    -- 退出战斗
    local function cancel()
        self:exitFight()        
    end

    -- 弹出弹窗:连接服务器失败,是否重试
    UIUtils:showTwoBtnMsgBox(STR(11004), ok, cancel)
end

------------------------------------------------------------------- helper -------------------------------------------------------------------

-- @brief 显示屏蔽层
function FightManager:showShieldLayer()
    if not G_UIManager:hasUI("UIShield") then
        require("app.ui.general.UIShield").new():show()
    end
end

-- @brief 隐藏屏蔽层
function FightManager:hideShieldLayer()
    G_UIManager:destroyUI("UIShield")
end

-- @brief 当前在战斗界面?
function FightManager:isInLoginView()
    return _MyG.ViewManager:isInView("LoginView")
end

-- @brief 当前在战斗界面?
function FightManager:isInFightView()
    return _MyG.ViewManager:isInView("FightView")
end

-- @brief 跳转到首页界面
function FightManager:gotoMainView()
    _MyG.ViewManager:runView(require("app.views.MainView").new())
end

-- @brief 跳转到战斗界面
function FightManager:gotoFightView()
    _MyG.ViewManager:runView(require("app.views.FightView").new())
end

return FightManager