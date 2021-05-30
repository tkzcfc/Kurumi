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

-- 战斗输入
Const.InputKey = {
    G_KEY_MOVE_LEFT     = CommonUtils.U32_L_SHIFT(1, 1),
    G_KEY_MOVE_RIGHT    = CommonUtils.U32_L_SHIFT(1, 2),
    G_KEY_MOVE_UP       = CommonUtils.U32_L_SHIFT(1, 3),
    G_KEY_MOVE_DOWN     = CommonUtils.U32_L_SHIFT(1, 4),
    G_KEY_JUMP          = CommonUtils.U32_L_SHIFT(1, 5),
    G_KEY_SKILL_1       = CommonUtils.U32_L_SHIFT(1, 6),
    G_KEY_SKILL_2       = CommonUtils.U32_L_SHIFT(1, 7),
    G_KEY_SKILL_3       = CommonUtils.U32_L_SHIFT(1, 8),
    G_KEY_SKILL_4       = CommonUtils.U32_L_SHIFT(1, 9),
    G_KEY_SKILL_5       = CommonUtils.U32_L_SHIFT(1, 10),
    G_KEY_SKILL_6       = CommonUtils.U32_L_SHIFT(1, 11),
    G_KEY_SKILL_7       = CommonUtils.U32_L_SHIFT(1, 12),
}

return Const