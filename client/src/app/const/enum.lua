-- @Author: fangcheng
-- @Date:   2021-05-23 13:55:52
-- @remark: 

Const.SVR_FIGHT_STATE = enum {
    "WAIT_CONNECT", -- 等待客户端连接服务器
    "READY",        -- 准备状态,等待玩家全部准备完毕
    "RUN",          -- 正常运行状态
    "WAIT",         -- 等待状态,等待逻辑帧最慢的客户端跟上服务器逻辑帧
}

