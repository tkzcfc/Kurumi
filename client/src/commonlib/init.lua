-- @Author : fangcheng
-- @Date   : 2020-02-28 21:26:16
-- @remark : commonlib初始化

cc.exports.com_log = function(...)
	print("[commonlib]:", ...)
end

-- 全局函数导入
require("commonlib.global.functions")
-- oRoutine
require("commonlib.global.oRoutine")


-- class导出
local class = {}
class.alignment 		= require("commonlib.class.alignment")
class.EventEmitter 		= require("commonlib.class.EventEmitter")
class.LoadAsync 		= require("commonlib.class.LoadAsync")
class.Task 				= require("commonlib.class.Task")
class.TaskFlowPipe 		= require("commonlib.class.TaskFlowPipe")
class.Vector 			= require("commonlib.class.Vector")
class.Window 			= require("commonlib.class.Window")
class.WindowContext 	= require("commonlib.class.WindowContext")
class.WindowManager 	= require("commonlib.class.WindowManager")


class.RichLabel 		= require("commonlib.ui.rich.RichLabel")
class.CycleListView 	= require("commonlib.ui.CycleListView")
class.PanZoomLayer 		= require("commonlib.ui.PanZoomLayer")
class.TableViewEx 		= require("commonlib.ui.TableViewEx")
class.TyperLabel 		= require("commonlib.ui.TyperLabel")

cc.exports.G_Class = class

-- 宏定义
cc.exports.G_MAC 				= require("commonlib.global.GameMacros")
-- 全局窗口管理
cc.exports.G_WindowManager 		= G_Class.WindowManager.new()
-- 全局网络事件派发器
cc.exports.G_NetEventEmitter 	= G_Class.EventEmitter.new()
-- 全局系统事件派发器
cc.exports.G_SysEventEmitter 	= G_Class.EventEmitter.new()
-- Helper
cc.exports.G_Helper 			= require("commonlib.global.Helper")
-- 系统设置
cc.exports.G_LangManager 		= require("commonlib.global.LangManager").new()
