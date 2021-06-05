-- @Author: fangcheng
-- @Date:   2021-05-07 20:55:19
-- @remark: 系统事件定义

return enum {
    "WILL_ENTER_SCENE",     -- 场景切换开始
    "ENTER_SCENE_FINISH",   -- 场景切换完毕
    "ON_KEY_BACK_CLICK",    -- 返回按键按下事件

    "NET_CONNECT_SUC",      -- 网络连接成功
    "NET_CONNECT_FAIL",     -- 网络连接失败
    "NET_DISCONNECT",       -- 网络连接断开

    "FIGHT_RE_JOINT",       -- 断线重连重新加入战斗

    "FIGHT_INIT_FINISH",     -- 战斗初始化完毕
    "FIGHT_INIT_FAIL",       -- 战斗初始化失败
    "FIGHT_UPLOAD_INPUT",    -- 战斗上传输入
}
