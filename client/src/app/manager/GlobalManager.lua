-- @Author: fangcheng
-- @Date:   2020-11-07 16:34:33
-- @remark: 一些全局逻辑管理

local GlobalManager = class("GlobalManager", import(".BaseManager"))

-- @brief 初始化调用
function GlobalManager:override_onInit()
	GlobalManager.super.override_onInit(self)

	G_NetEventEmitter:on(MessageID.MSG_EXIT_GAME_NTF, handler(self, self.onExitGameNtf), self)
end

-- @brief 销毁时调用
function GlobalManager:override_onDestroy()
	G_NetEventEmitter:offByTag(self)

	GlobalManager.super.override_onDestroy(self)
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

return GlobalManager