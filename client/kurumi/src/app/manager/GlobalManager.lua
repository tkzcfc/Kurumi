-- @Author: fangcheng
-- @Date:   2020-11-07 16:34:33
-- @remark: 一些全局逻辑管理

local GlobalManager = class("GlobalManager", import(".BaseManager"))

-- @brief 初始化调用
function GlobalManager:override_onInit()
	GlobalManager.super.override_onInit(self)

	G_NetEventEmitter:on(MessageID.MSG_EXIT_GAME_NTF, handler(self, self.onExitGameNtf), self)

    G_SysEventEmitter:on(SysEvent.NET_CONNECT_FAIL, handler(self, self.onNetConnectFail), self)
end

-- @brief 退出游戏通知
function GlobalManager:onExitGameNtf(msg)
	local content = string.format(STR(11006), checknumber(msg.code))
	-- 账号在其他地方登录
	if msg.code == errCode.EXIT_GAME_LOGIN_REPEAT then
		content = STR(11005)
	end

	_MyG.NetManager:clearAllSessionInfo()

	UIUtils:showOneBtnMsgBox(content, function()
		appExit()
	end)
end

function GlobalManager:onNetConnectFail(isFightSvr, sessionID)
	if isFightSvr then return end

    -- 连接服务器失败,是否重试
    UIUtils:showTwoBtnMsgBox(STR(11004), 
    function()
        _MyG.NetManager:doConnect(sessionID)
    end, 
    function()
        appExit()
    end)
end

return GlobalManager