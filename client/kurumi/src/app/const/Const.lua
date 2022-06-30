-- @Author: fangcheng
-- @Date:   2021-05-09 16:56:57
-- @remark: 

local Const =  {}

-- 角色定义相关
Const.Role = {
    DAO     = 1,    -- 刀
    GONG    = 2     -- 弓
}


-- 战斗输入
Const.InputKey = {
    G_KEY_MOVE_LEFT     = bit.lshift(1, 1),
    G_KEY_MOVE_RIGHT    = bit.lshift(1, 2),
    G_KEY_MOVE_UP       = bit.lshift(1, 3),
    G_KEY_MOVE_DOWN     = bit.lshift(1, 4),
    G_KEY_JUMP          = bit.lshift(1, 5),
    G_KEY_SKILL_1       = bit.lshift(1, 6),
    G_KEY_SKILL_2       = bit.lshift(1, 7),
    G_KEY_SKILL_3       = bit.lshift(1, 8),
    G_KEY_SKILL_4       = bit.lshift(1, 9),
    G_KEY_SKILL_5       = bit.lshift(1, 10),
    G_KEY_SKILL_6       = bit.lshift(1, 11),
    G_KEY_SKILL_7       = bit.lshift(1, 12),
}


-- 战斗状态
Const.SVR_FIGHT_STATE = enum {
    "WAIT_CONNECT", -- 等待客户端连接服务器
    "READY",        -- 准备状态,等待玩家全部准备完毕
    "RUN",          -- 正常运行状态
    "WAIT",         -- 等待状态,等待逻辑帧最慢的客户端跟上服务器逻辑帧
}



global.Const = Const