-- @Author: fangcheng
-- @Date:   2021-05-23 13:29:43
-- @remark: 

local FightLayer = class("FightLayer", cc.Node)

local logic_interval = 1 / 30

function FightLayer:ctor()
    self:enableNodeEvents()

    self.fFreeTime = 0

    local tWorldInfo = _MyG.FightManager:getWorldInfo()
    local MapConfig = require("app.config.MapConfig")
    local cfg = MapConfig["map" .. tWorldInfo.mapId]

    self.loader = G_Class.LoadAsync.new()
    for k, v in pairs(cfg.loadResourceList) do
        self.loader:addLoadResource(v, true)
    end
    self.loader:start(handler(self, self.onProcessCallback), handler(self, self.onFinishCallback), handler(self, self.onErrorCallback))
end

function FightLayer:onEnter()
    self:initEvent()
end

function FightLayer:initEvent()
    G_SysEventEmitter:on(SysEvent.FIGHT_RE_JOINT, handler(self, self.onReJoinFight), self)

    G_NetEventEmitter:on(MessageID.MSG_LOADING_PERCENT_ACK, handler(self, self.onPlayerLoadingAck), self)
    G_NetEventEmitter:on(MessageID.MSG_PUSH_FRAME_BEGIN, handler(self, self.onPushFrameInputBegin), self)
    G_NetEventEmitter:on(MessageID.MSG_PUSH_FRAME_INPUT, handler(self, self.onPushFrameInput), self)
    G_NetEventEmitter:on(MessageID.MSG_PUSH_FRAME_END, handler(self, self.onPushFrameInputEnd), self)
    G_NetEventEmitter:on(MessageID.MSG_RUN_NEXT_FRAME_ACK, handler(self, self.onRunNextFrameAck), self)
end

function FightLayer:onExit()
    G_NetEventEmitter:offByTag(self)
    G_SysEventEmitter:offByTag(self)
end

function FightLayer:onCleanup()
    if self.pGameWorld then
        self.pGameWorld:delete()
    end

    if self.scheduleHandler then
        local sharedScheduler = cc.Director:getInstance():getScheduler()
        sharedScheduler:unscheduleScriptEntry(self.scheduleHandler)
        self.scheduleHandler = nil
    end
end

-- @brief 资源加载进度回调
function FightLayer:onProcessCallback(taskPercent, totalPercent, pipe)
    print("totalPercent----------------->>", totalPercent)

    local curTime = G_Helper:gettime()
    if self.fLastSendTime ~= nil and curTime - self.fLastSendTime < 0.5 then
        return
    end
    self.fLastSendTime = curTime
    _MyG.FightManager:sendPlayerLoadingReq(totalPercent, false)
end

-- @brief 资源加载完成回调
function FightLayer:onFinishCallback(pipe)
    _MyG.FightManager:sendPlayerLoadingReq(1, true)

    -- 游戏已经开始
    local tWorldInfo = _MyG.FightManager:getWorldInfo()
    local svr_status = tWorldInfo.svr_status
    if svr_status ~= Const.SVR_FIGHT_STATE.WAIT_CONNECT and svr_status ~= Const.SVR_FIGHT_STATE.READY then
        self:initGameWorld()
    end
end

-- @brief 资源加载出错回调
function FightLayer:onErrorCallback(msg, pipe)
    print("加载失败:", msg)
    _MyG.FightLayer:exitFight()
end

function FightLayer:onReJoinFight()

end

-- @brief 玩家进度加载更新
function FightLayer:onPlayerLoadingAck(msg)
    if msg.finish then
        self:initGameWorld()
    end
end

-- @brief 推帧开始
function FightLayer:onPushFrameInputBegin(msg)
    self:initGameWorld()
    self.isPushing = true
end

-- @brief 推帧
function FightLayer:onPushFrameInput(msg)
    self.svrLogicFrame = msg.lastFrame

    -- for k, v in pairs(msg.frames or {}) do
    -- end
end

-- @brief 推帧结束
function FightLayer:onPushFrameInputEnd(msg)
    self.isPushing = false
end

-- @brief 进入下一帧
function FightLayer:onRunNextFrameAck(msg)
    self.svrLogicFrame = msg.nextFrame

    if msg.frames then
        for k, v in pairs(msg.frames) do
            local pid = v.pid
            self.pGameWorld:input(pid, v.frame, v.input.key_down)
        end
    end
end

function FightLayer:initGameWorld()
    if self.pGameWorld then
        return
    end

    self.pGameWorld = GGameWorld:new()
    local tWorldInfo = _MyG.FightManager:getWorldInfo()
    if not self.pGameWorld:init(tWorldInfo.mapId, tWorldInfo.randomSeed, tWorldInfo.uuidSeed, self) then
        _MyG.FightManager:exitFight()
    end

    local sharedScheduler = cc.Director:getInstance():getScheduler()
    self.scheduleHandler = sharedScheduler:scheduleScriptFunc(handler(self, self.update), logic_interval, false)
end

function FightLayer:update(dt)
    if self.svrLogicFrame == nil then
        return
    end
    if self.pGameWorld:getGameLogicFrame() > self.svrLogicFrame then
        self.fFreeTime = self.fFreeTime + dt
        if self.fFreeTime > 1.0 then
            self.fFreeTime = 0
            _MyG.FightManager:sendRunNextFrameReq(0)
        end
        return
    end
    self.fFreeTime = 0

    self.pGameWorld:update(logic_interval)
    self.pGameWorld:render()
    _MyG.FightManager:setLogicFrame(self.pGameWorld:getGameLogicFrame())

    if not self.isPushing then
        _MyG.FightManager:sendRunNextFrameReq(0)
    end
    -- print("GameLogicFrame---------->>", self.pGameWorld:getGameLogicFrame())
end




return FightLayer