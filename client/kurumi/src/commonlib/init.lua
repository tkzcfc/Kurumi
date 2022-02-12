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

require("commonlib.event.event")


-- class导出
local class = {}
class.alignment 		= require("commonlib.class.alignment")
class.EventEmitter 		= require("commonlib.class.EventEmitter")
class.LoadAsync 		= require("commonlib.class.LoadAsync")
class.Task 				= require("commonlib.class.Task")
class.TaskFlowPipe 		= require("commonlib.class.TaskFlowPipe")
class.Vector 			= require("commonlib.class.Vector")
class.UIPanel 			= require("commonlib.class.UIPanel")
class.UIContext 	    = require("commonlib.class.UIContext")
class.UIManager 	    = require("commonlib.class.UIManager")
class.StorageObject     = require("commonlib.class.StorageObject")


class.RichLabel 		= require("commonlib.ui.rich.RichLabel")
class.CycleListView 	= require("commonlib.ui.CycleListView")
class.PanZoomLayer 		= require("commonlib.ui.PanZoomLayer")
class.TableViewEx 		= require("commonlib.ui.TableViewEx")
class.TyperLabel 		= require("commonlib.ui.TyperLabel")

cc.exports.G_Class = class

-- 宏定义
cc.exports.G_MACROS 			= require("commonlib.global.GameMacros")
-- 全局UI管理
cc.exports.G_UIManager 		    = G_Class.UIManager.new()
-- 全局网络事件派发器
cc.exports.G_NetEventEmitter 	= G_Class.EventEmitter.new()
-- 全局系统事件派发器
cc.exports.G_SysEventEmitter 	= G_Class.EventEmitter.new()
-- Helper
cc.exports.G_Helper 			= require("commonlib.global.Helper")