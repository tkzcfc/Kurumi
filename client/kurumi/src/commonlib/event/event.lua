-- @Author : fc
-- @Date   : 2021-10-29 11:18:38
-- @remark : 

local SysEvent = enum {
    --  BasePanel内部派发的事件
    "UI_BEFORE_OPENED", -- UI打开之前事件通知
    "UI_AFTER_OPENED",  -- UI打开完毕事件通知
    
    "UI_WILL_CLOSE",    -- UI即将关闭通知
    "UI_AFTER_CLOSED",  -- UI关闭完毕通知

    "UI_WILL_DESTROY",  -- UI被销毁

    -- UIManager派发的事件
    "UPDATE_VIEW_VISIBLE",-- 更新view的显示/隐藏状态

    -- 系统事件
    "ON_GAME_WILL_EXIT", -- 游戏即将退出
    "ON_RESTART_GAME",  -- 即将重启游戏
}

global.SysEvent = SysEvent
