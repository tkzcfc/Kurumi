-- @Author : fc
-- @Date   : 2021-12-03 11:39:14
-- @remark : 游戏连接管理


local GameConnectManager = class("GameConnectManager", import(".BaseManager"))


-- @brief 初始化调用
function GameConnectManager:override_onInit()
    GameConnectManager.super.override_onInit(self)

    G_SysEventEmitter:on(SysEvent.NET_CONNECT_SUC, handler(self, self.onConnectSuccess), self)
end

-- @brief 游戏服连接成功
function GameConnectManager:onNetConnectSuc(isFightSvr)
    -- 只关心游戏服的连接
    if isFightSvr then return end

    
end

return GameConnectManager
