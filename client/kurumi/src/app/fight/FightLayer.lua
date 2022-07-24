-- @Author: fangcheng
-- @Date:   2021-05-23 13:29:43
-- @remark: 

local FightLayer = class("FightLayer", G_Class.SuperNode)

propertyReadOnly(FightLayer, "iSelfRoleId")

local logic_interval = 1 / 30


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
    -- 开始资源加载
    self.loader:start(handler(self, self.onProcessCallback), handler(self, self.onFinishCallback), handler(self, self.onErrorCallback))

    -- loading界面
    self.loadLayer = require("app.fight.FightLoading").new()
    self:addChild(self.loadLayer, 0xff)

    -- 是否是离线模式
    self.isOfflineMode = tWorldInfo.isOfflineMode == true

    -- 角色Id, 本地实体id映射关系
    self.roleId_EntityIdMap = {}

    self.iLogicCount = 0
    -- if not self.isOfflineMode then
    --     -- 打印一秒之内执行的逻辑帧数
    --     self:schedule(function()
    --         print("logic fps", self.iLogicCount)
    --         self.iLogicCount = 0
    --     end, 1)
    -- end
end

function FightLayer:onEnter()
    self:initEvent()
end

function FightLayer:initEvent()
    G_SysEventEmitter:on(SysEvent.FIGHT_RE_JOINT, handler(self, self.onReJoinFight), self)

    G_NetEventEmitter:on("msg.PlayerLoadingAck", handler(self, self.onPlayerLoadingAck), self)
    G_NetEventEmitter:on("msg.PushFrameInputBegin", handler(self, self.onPushFrameInputBegin), self)
    G_NetEventEmitter:on("msg.PushFrameInput", handler(self, self.onPushFrameInput), self)
    G_NetEventEmitter:on("msg.PushFrameInputEnd", handler(self, self.onPushFrameInputEnd), self)
    G_NetEventEmitter:on("msg.RunNextFrameAck", handler(self, self.onRunNextFrameAck), self)
end

function FightLayer:onExit()
    G_NetEventEmitter:offByTag(self)
    G_SysEventEmitter:offByTag(self)
end

function FightLayer:onCleanup()
    if self.pGameWorld then
        self.pGameWorld:delete()
        self.pGameWorld = nil
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
    -- 离线模式不接受服务器的推帧
    if self.isOfflineMode then return end

    self.svrLogicFrame = msg.lastFrame

    for k, v in pairs(msg.frames or {}) do
        self.pGameWorld:input(self.roleId_EntityIdMap[v.pid], v.frame, v.key_down)
    end
end

-- @brief 推帧结束
function FightLayer:onPushFrameInputEnd(msg)
    self.isPushing = false
end

-- @brief 进入下一帧
function FightLayer:onRunNextFrameAck(msg)
    -- 离线模式不接受服务器的推帧
    if self.isOfflineMode then return end

    self.svrLogicFrame = msg.nextFrame

    if msg.frames then
        for k, v in pairs(msg.frames) do
            self.pGameWorld:input(self.roleId_EntityIdMap[v.pid], v.frame, v.key_down)
        end
    end

    self.iLogicCount = self.iLogicCount + 1
end

function FightLayer:initGameWorld()
    if self.pGameWorld then
        return
    end

    local tWorldInfo = self.fightMgr:getWorldInfo()

    -- 查找服务器下发的角色id是否存在
    self.roleDatas = {}
    for k, v in pairs(tWorldInfo.roles) do
        local data = _MyG.RoleManager:getRoleData(v)
        -- 玩家不存在，战斗初始化失败
        if data == nil then
            print("角色id:", v, "数据不存在，战斗初始化失败")
            G_SysEventEmitter:emit(SysEvent.FIGHT_INIT_FAIL)
            return
        end
        table.insert(self.roleDatas, data)
    end

    self.pGameWorld = GGameWorld:create(tWorldInfo.mapId, tWorldInfo.randomSeed, self)
    if not self.pGameWorld then
        G_SysEventEmitter:emit(SysEvent.FIGHT_INIT_FAIL)
        return
    end

    self.pGameWorld:enableDebugDraw(true)

    -- 将玩家加入游戏世界中
    for k, v in pairs(self.roleDatas) do
        -- 角色数据
        local data = v.jsonData
        -- 角色形象
        local spineFile = G_Config.RoleSkin:getItem(data.skin, "SpineFile")
        
        -- 创建出来的角色对象
        local actor = self.pGameWorld:spwanActor(data.roleFile, {x = 100 + 100 * k, y = 0, z = 0}, spineFile or "")

        self.roleId_EntityIdMap[v.roleId] = actor:getId()

        -- 是自己的角色
        if _MyG.RoleManager:isSelfRole(v.roleId) then
            assert(self.iSelfRoleId == nil)
            self.pGameWorld:setLocalPlayer(actor)
            self.iSelfRoleId = v.roleId
        end
    end

    if self.iSelfRoleId == nil then
        print("战斗初始化失败找不到自己的本地操作对象")
        G_SysEventEmitter:emit(SysEvent.FIGHT_INIT_FAIL)
        return        
    end

    -- 定时器开启
    local sharedScheduler = cc.Director:getInstance():getScheduler()
    self.fixUpdateTimer = sharedScheduler:scheduleScriptFunc(handler(self, self.fixUpdate), logic_interval, false)
    -- self.renderUpdateTimer = sharedScheduler:scheduleScriptFunc(handler(self, self.renderUpdate), 0.0, false)

    -- 移除loading界面
    self:performWithDelay(function()
        self.loadLayer:removeFromParent()
        self.loadLayer = nil
    end, 0.2)

    -- 游戏加载完成
    G_SysEventEmitter:emit(SysEvent.FIGHT_INIT_FINISH)
end

-- @brief 固定更新
function FightLayer:fixUpdate()
    -- 离线模式
    if self.isOfflineMode then
        local frame = self.pGameWorld:getGameLogicFrame()

        -- 离线模式,输入直接作用到游戏世界
        local inputKey = _MyG.FightContext:getInputLayer():getInputKey()
        self.pGameWorld:input(self.roleId_EntityIdMap[self.iSelfRoleId], frame, inputKey)

        self.svrLogicFrame = frame + 1
    else
        -- 服务端推帧时不上传输入
        if not self.isPushing then
            G_SysEventEmitter:emit(SysEvent.FIGHT_UPLOAD_INPUT)
        end
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

            self.pGameWorld:step()
            self:renderUpdate(dt)
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