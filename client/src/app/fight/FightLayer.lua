-- @Author: fangcheng
-- @Date:   2021-05-23 13:29:43
-- @remark: 

local FightLayer = class("FightLayer", cc.Node)

local logic_interval = 1 / 40

function FightLayer:ctor()
    self:enableNodeEvents()

    self.fFreeTime = 0
    self.fightMgr = _MyG.FightManager

    -- 世界信息
    local tWorldInfo = self.fightMgr:getWorldInfo()
    local MapConfig = require("app.config.MapConfig")
    local cfg = MapConfig["map" .. tWorldInfo.mapId]

    -- 异步加载器创建
    self.loader = G_Class.LoadAsync.new()
    for k, v in pairs(cfg.loadResourceList) do
        self.loader:addLoadResource(v, true)
    end
    self.loader:start(handler(self, self.onProcessCallback), handler(self, self.onFinishCallback), handler(self, self.onErrorCallback))

    -- loading界面
    self.loadLayer = require("app.fight.FightLoading").new()
    self:addChild(self.loadLayer, 0xff)

    self.iLogicCount = 0
    schedule(self, function()
        print("logic fps", self.iLogicCount)
        self.iLogicCount = 0
    end, 1)
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

    local sharedScheduler = cc.Director:getInstance():getScheduler()
    if self.fixUpdateTimer then
        sharedScheduler:unscheduleScriptEntry(self.fixUpdateTimer)
        self.fixUpdateTimer = nil
    end

    if self.renderUpdateTimer then
        sharedScheduler:unscheduleScriptEntry(self.renderUpdateTimer)
        self.renderUpdateTimer = nil
    end
end

-- @brief 资源加载进度回调
function FightLayer:onProcessCallback(taskPercent, totalPercent, pipe)
    self.loadLayer:setPercent(totalPercent)

    local curTime = G_Helper:gettime()
    if self.fLastSendTime ~= nil and curTime - self.fLastSendTime < 0.5 then
        return
    end
    self.fLastSendTime = curTime
    self.fightMgr:sendPlayerLoadingReq(totalPercent, false)
end

-- @brief 资源加载完成回调
function FightLayer:onFinishCallback(pipe)    
    self.fightMgr:sendPlayerLoadingReq(1, true)

    -- 游戏已经开始
    local tWorldInfo = self.fightMgr:getWorldInfo()
    local svr_status = tWorldInfo.svr_status
    if svr_status ~= Const.SVR_FIGHT_STATE.WAIT_CONNECT and svr_status ~= Const.SVR_FIGHT_STATE.READY then
        self:initGameWorld()
    end
end

-- @brief 资源加载出错回调
function FightLayer:onErrorCallback(msg, pipe)
    print("加载失败:", msg)
    G_SysEventEmitter:emit(SysEvent.FIGHT_INIT_FAIL)
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

    for k, v in pairs(msg.frames or {}) do
        -- local pid = v.pid
        local pid = 0
        self.pGameWorld:input(pid, v.frame, v.input.key_down)
    end
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
            -- local pid = v.pid
            local pid = 0
            self.pGameWorld:input(pid, v.frame, v.input.key_down)
        end
    end

    self.iLogicCount = self.iLogicCount + 1
end

function FightLayer:initGameWorld()
    if self.pGameWorld then
        return
    end

    self.pGameWorld = GGameWorld:new()
    local tWorldInfo = self.fightMgr:getWorldInfo()
    if not self.pGameWorld:init(tWorldInfo.mapId, tWorldInfo.randomSeed, tWorldInfo.uuidSeed, self) then
        G_SysEventEmitter:emit(SysEvent.FIGHT_INIT_FAIL)
        return
    end

    local sharedScheduler = cc.Director:getInstance():getScheduler()
    self.fixUpdateTimer = sharedScheduler:scheduleScriptFunc(handler(self, self.fixUpdate), logic_interval, false)
    self.renderUpdateTimer = sharedScheduler:scheduleScriptFunc(handler(self, self.renderUpdate), 0.0, false)

    -- 移除loading界面
    performWithDelay(self, function()
        self.loadLayer:removeFromParent()
        self.loadLayer = nil
        G_SysEventEmitter:emit(SysEvent.FIGHT_INIT_FINISH)
    end, 0.2)
end

function FightLayer:fixUpdate()
    if not self.isPushing then
        G_SysEventEmitter:emit(SysEvent.FIGHT_UPLOAD_INPUT)
    end
    self:updateFrame(logic_interval)
end

function FightLayer:renderUpdate(dt)
    self.pGameWorld:render(dt)
end

function FightLayer:updateFrame(dt)
    if self.svrLogicFrame == nil then
        return
    end

    local frameDiff = self.svrLogicFrame - self.pGameWorld:getGameLogicFrame()

    if frameDiff >= 0 then
        local count = 0
        repeat
            if self.pGameWorld:getGameLogicFrame() > self.svrLogicFrame then
                break
            end

            self.pGameWorld:update(dt)
            -- print("GameLogicFrame---------->>", self.pGameWorld:getGameLogicFrame())

            count = count + 1

            -- 相差不大,二倍数播放,相差太大则直接播放到最新帧
            if frameDiff < 10 then
                if frameDiff > 5 then
                    if count >= 5 then break end
                else
                    break
                end
            end
        until(false)

        self.fightMgr:setLogicFrame(self.pGameWorld:getGameLogicFrame())
    end
end

return FightLayer