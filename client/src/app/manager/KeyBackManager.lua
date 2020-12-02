-- @Author: fangcheng
-- @Date:   2020-11-08 14:59:55
-- @remark: 返回按键管理

local KeyBackManager = class("KeyBackManager", import(".BaseManager"))

function KeyBackManager:override_onInit()
	KeyBackManager.super.override_onInit(self)

	G_SysEventEmitter:on("event_onKeyBackReleased", function()
		-- 常驻节点窗口优先截取返回事件
		if _MyG.NotifiNodeManager:getWinContext():popWindow() then return end
		
		-- 弹出窗口截取返回事件
		if G_WindowManager:popWindow() then return end

		-- 运行的场景接收返回事件
		local curView = _MyG.ScenesManager:getRuningView()
		if curView then
			if curView:onKeyBackReleased() then return end
		end

		-- 退出游戏弹窗
		self:showExitGameBox()
	end)
end

-- @brief 显示退出游戏弹窗
function KeyBackManager:showExitGameBox()
    local box = require("app.ui.UIMessageBox").new()
    box:showTwoButton("Exit Game", function()
    	restartApp()
    	-- appExit()
	end)
    box:setLocalZOrder(G_Const.WINDOW_Z.EXIT_MSGBOX)
    _MyG.NotifiNodeManager:showWindow(box)
end

return KeyBackManager

