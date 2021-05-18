-- @Author: fangcheng
-- @Date:   2021-05-16 16:15:07
-- @remark: 战斗管理

local FightManager = class("FightManager", import(".BaseManager"))


-- @brief 初始化调用
function FightManager:override_onInit()
    FightManager.super.override_onInit(self)
    G_NetEventEmitter:on(MessageID.MSG_START_PVE_ACK, handler(self, self.onStartPVEFightAck), self)
    G_NetEventEmitter:on(MessageID.MSG_START_PVP_ACK, handler(self, self.onStartPVPFightAck), self)
    G_NetEventEmitter:on(MessageID.MSG_START_FIGHT_NTF, handler(self, self.onStartFightNTF), self)

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

function FightManager:joinFight()
    _MyG.NetManager:sendToFight(MessageID.MSG_JOIN_FIGHT_REQ, {
        fightUUID = self.tFightInfo.fightUUID,
        playerID = _MyG.AccountInfo.playerID,
        frame = 0,
    })
end

function FightManager:clearFightInfo()
    self.tFightInfo = nil
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

function FightManager:onNetConnectFail(isFightSvr)
    if not isFightSvr then return end
    self:hideShieldWindow()

    if _MyG.ScenesManager:getCurSceneID() == _MyG.SCENE_ID_LOGIN then
        return
    end
    UIUtils:showError(118)
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