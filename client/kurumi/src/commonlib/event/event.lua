-- @Author : fc
-- @Date   : 2021-10-29 11:18:38
-- @remark : 

local SysEvent = enum {
    --  BasePanel内部派发的事件
    "UI_BEFORE_OPENED", -- UI打开之前事件通知
    "UI_AFTER_OPENED",  -- UI打开完毕事件通知
    
    "UI_WILL_CLOSE",    -- UI即将关闭通知
    "UI_AFTER_CLOSED",  -- UI关闭完毕通知

    -- UIManager派发的事件
    "UI_SHOW_START",    -- UI加入UIManager中
    "UI_SHOW_FINISH",   -- UI显示完成（播放打开动画完毕）
    "UI_DISMISS",       -- UI被销毁(从UIManager中移除)

    -- 系统事件
    "ON_GAME_WILL_EXIT", -- 游戏即将退出
    "ON_RESTART_GAME",  -- 即将重启游戏
}

cc.exports.SysEvent = SysEvent
