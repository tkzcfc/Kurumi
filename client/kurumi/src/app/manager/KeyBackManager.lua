-- @Author: fangcheng
-- @Date:   2020-11-08 14:59:55
-- @remark: 返回按键管理

local KeyBackManager = class("KeyBackManager", import(".BaseManager"))

function KeyBackManager:override_onInit()
	KeyBackManager.super.override_onInit(self)

	G_SysEventEmitter:on(SysEvent.ON_KEY_BACK_CLICK, function()
		-- 弹出窗口截取返回事件
		if G_UIManager:getCurUISize() > 0 then
			G_UIManager:popTopUI()
			return
		end

        if not _MyG.ViewManager:isAsyncLoad() then
    		-- 运行的场景接收返回事件
    		local curView = _MyG.ViewManager:getCurView()
    		if curView then
    			if curView:onKeyBackReleased() then return end

                if _MyG.ViewManager:getStackDepth() > 1 then
                    if _MyG.ViewManager:popView() then return end
                end
    		end
        end

		-- 退出游戏弹窗
		self:showExitGameBox()
	end, self)
end

-- @brief 显示退出游戏弹窗
function KeyBackManager:showExitGameBox()
    UIUtils:showTwoBtnMsgBox("Exit Game", function()
        -- restartGame()
        gameExit()
    end)
end

return KeyBackManager

