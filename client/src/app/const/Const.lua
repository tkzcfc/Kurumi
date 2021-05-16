-- @Author: fangcheng
-- @Date:   2021-05-09 16:56:57
-- @remark: 

local Const =  {}

-- 窗口Zorder
Const.WindowZ = {
    UI                  = 1000,     -- 普通UI
    LOADING             = 1010,     -- 普通loading
    MSGBOX              = 1020,     -- 普通弹窗

    ------------- 全局节点 -------------
    UI_MASK             = 1021,     -- ui mask节点
    LOADING             = 1030,     -- 全局loading
    G_MSGBOX            = 1040,     -- 全局弹窗
    EXIT_MSGBOX         = 1050,     -- 退出游戏弹窗
}


-- 角色定义相关
Const.Role = {
    DAO     = 1,    -- 刀
    GONG    = 2     -- 弓
}


return Const