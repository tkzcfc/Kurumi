-- @Author: fangcheng
-- @Date:   2021-05-16 16:15:07
-- @remark: 战斗管理

local FightManager = class("FightManager", import(".BaseManager"))

-- 世界初始化参数
property(FightManager, "tWorldInfo")
-- 当前运行到第几帧
property(FightManager, "iLogicFrame", 0)

-- @brief 初始化调用
function FightManager:override_onInit()
    FightManager.super.override_onInit(self)
    G_NetEventEmitter:on(MessageID.MSG_START_PVE_ACK, handler(self, self.onStartPVEFightAck), self)
    G_NetEventEmitter:on(MessageID.MSG_START_PVP_ACK, handler(self, self.onStartPVPFightAck), self)
    G_NetEventEmitter:on(MessageID.MSG_START_FIGHT_NTF, handler(self, self.onStartFightNTF), self)
    G_NetEventEmitter:on(MessageID.MSG_JOIN_FIGHT_ACK, handler(self, self.onJoinFightAck), self)
    G_NetEventEmitter:on(MessageID.MSG_EXIT_FIGHT_ACK, handler(self, self.onExitFightAck), self)
    G_NetEventEmitter:on(MessageID.MSG_PLAYER_EXIT_FIGHT_NTF, handler(self, self.onPlayerExitFightNotify), self)


    G_SysEventEmitter:on(SysEvent.NET_CONNECT_SUC, handler(self, self.onNetConnectSuc), self)
    G_SysEventEmitter:on(SysEvent.NET_CONNECT_FAIL, handler(self, self.onNetConnectFail), self)
end

-- @brief 销毁时调用
function FightManager:override_onDestroy()
    G_NetEventEmitter:offByTag(self)
    G_SysEventEmitter:offByTag(self)
    FightManager.super.override_onDestroy(self)
end

-- @param carbonId副本id
-- @param 进入副本的玩家信息
function FightManager:requestStartPvE(carbonId, roles, call)
    self.onStartCall = call
    self:clearFightInfo()
    self:showShieldWindow()
    _MyG.NetManager:sendToGame(MessageID.MSG_START_PVE_REQ, {
        carbonId = carbonId,
        roles = roles
    })
end

-- @brief 发送加入战斗请求
function FightManager:joinFight()
    _MyG.NetManager:sendToFight(MessageID.MSG_JOIN_FIGHT_REQ, {
        fightUUID = self.tFightInfo.fightUUID,
        playerID = _MyG.AccountInfo.playerID,
        frame = self.iLogicFrame,
    })
end

-- @brief 发送加载进度更新请求
function FightManager:sendPlayerLoadingReq(fPercent, isFinish)
    _MyG.NetManager:sendToFight(MessageID.MSG_LOADING_PERCENT_REQ, {
        percent = fPercent,
        finish = isFinish,
    })
end

-- @brief 发送进入下一逻辑帧请求
function FightManager:sendRunNextFrameReq(key_down)
    _MyG.NetManager:sendToFight(MessageID.MSG_RUN_NEXT_FRAME_REQ, {
        frame = self.iLogicFrame,
        input = {
            key_down = key_down
        }
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
    if _MyG.ScenesManager:getCurSceneID() == _MyG.SCENE_ID_FIGHT then
        _MyG.ScenesManager:switchScene(_MyG.SCENE_ID_MAIN)
    end

    if self.tFightInfo == nil then
        _MyG.NetManager:setFightInfo()
        return
    end

    _MyG.NetManager:sendToFight(MessageID.MSG_EXIT_FIGHT_REQ, {
        fightUUID = self.tFightInfo.fightUUID
    })

    self:clearFightInfo()
end

function FightManager:onStartPVEFightAck(msg)
    if msg.code ~= errCode.SUCCESS then
        UIUtils:showError(msg.code)
        self:hideShieldWindow()
    end
end

function FightManager:onStartPVPFightAck(msg)
    if msg.code ~= errCode.SUCCESS then
        UIUtils:showError(msg.code)
        self:hideShieldWindow()
    end
end

function FightManager:onStartFightNTF(msg)
    if msg.code ~= errCode.SUCCESS then
        UIUtils:showError(msg.code)
        self:hideShieldWindow()
        return
    end

    self.tFightInfo = msg
    _MyG.NetManager:setFightInfo()
    _MyG.NetManager:setFightInfo(msg.fightIP, msg.fightPort)
end

function FightManager:onJoinFightAck(msg)
    if msg.code ~= errCode.SUCCESS then
        UIUtils:showError(msg.code)
        self:hideShieldWindow()
        self:exitFight()
        return
    end
    self.tWorldInfo = msg.worldInfo

    if _MyG.ScenesManager:getCurSceneID() == _MyG.SCENE_ID_FIGHT then
        G_SysEventEmitter:emit(SysEvent.FIGHT_RE_JOINT)
    else
        _MyG.ScenesManager:switchScene(_MyG.SCENE_ID_FIGHT)
    end
end

function FightManager:onExitFightAck(msg)
    self:exitFight()
end

function FightManager:onPlayerExitFightNotify(msg)
    self:clearFightInfo()
    self:exitFight()
end

function FightManager:onNetConnectSuc(isFightSvr)
    if not isFightSvr then return end
    self:hideShieldWindow()

    print("hideShieldWindow-------->>")

    if _MyG.ScenesManager:getCurSceneID() == _MyG.SCENE_ID_LOGIN then
        return
    end

    if not self.tFightInfo then return end

    self:joinFight()
end

function FightManager:onNetConnectFail(isFightSvr, sessionID)
    if not isFightSvr then return end
    self:hideShieldWindow()

    if _MyG.ScenesManager:getCurSceneID() == _MyG.SCENE_ID_LOGIN then
        UIUtils:showError(118)
        return
    end
    -- 连接服务器失败,是否重试
    UIUtils:showTwoBtnMsgBox(STR(11004), 
    function()
        _MyG.NetManager:doConnect(sessionID)
    end, 
    function()
        self:exitFight()
    end)
end

function FightManager:showShieldWindow()
    if not G_WindowManager:hasWindow("ShieldWindow") then
        require("app.windows.general.ShieldWindow").new():show()
    end
end

function FightManager:hideShieldWindow()
    G_WindowManager:removeWindowByName("ShieldWindow", true)
end

return FightManager