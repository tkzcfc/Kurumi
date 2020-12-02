-- @Author: fangcheng
-- @Date:   2020-11-07 16:33:58
-- @remark: 

local Const = {}

-- 窗口Zorder
Const.WINDOW_Z = 
{
	UI 					= 1000,	-- 普通UI
	LOADING 			= 1010,	-- 普通loading
	MSGBOX 				= 1020,	-- 普通弹窗
	LOADING 			= 1030,	-- 全局loading
	G_MSGBOX 			= 1040,	-- 全局弹窗
	EXIT_MSGBOX 		= 1050,	-- 退出游戏弹窗
}

cc.exports.G_Const = Const