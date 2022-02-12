-- @Author : fangcheng
-- @Date   : 2020-05-25 22:01:43
-- @remark : 游戏初始化，更新完毕之后加载

---------------------------------- commonlib ----------------------------------
-- comlib
require("commonlib.init")
G_NetEventEmitter:clear()
G_SysEventEmitter:clear()


----------------------------------  LoadTask  ----------------------------------

local LoadTask = class("LoadTask", G_Class.Task)

function LoadTask:ctor(func)
	self.func = func
end

function LoadTask:run(taskFlowPipe)
	self.func()
end


----------------------------------  Loader  ----------------------------------
local Loader = class("Loader")

function Loader:ctor()
	self.pipe = G_Class.TaskFlowPipe.new()
	self:init()
end

function Loader:init()
	cc.exports.logI = print
	cc.exports.logW = print
	cc.exports.logE = print
	cc.exports.logF = print
	cc.exports._MyG = {}
	cc.exports.G_InputEventEmitter = G_Class.EventEmitter.new()

	package.loaded["app.ipConfig"] = nil
	require("app.ipConfig")

	-- 配置加载
	self:push(function()
		-- 游戏Excel配置
		cc.exports.G_Config = require("config.config")
		-- -- 锁定游戏配置, read_only会影响性能，只在debug中使用
		-- if G_MACROS.DEBUG then
		-- 	G_Config = read_only(G_Config) 
		-- end
	end)

	self:push(function()
		require("app.utils.HelperExt")
		require("app.utils.UIUtils")
		require("app.const._init_")
		-- require("mugen.init")
		require("ui.init")
	end)

	self:push(function()
		-- 常用class 导出
		G_Class.UIDialog = require("app.common.UIDialog")
		G_Class.UIMainFrame = require("app.common.UIMainFrame")

		-- quick不能直接继承cc.Node，这儿统一用一个函数代替
		G_Class.SuperNode = function()
		    return cc.Node:create()
		end
	end)

	-- 常用plist文件加载
	self:push(function()
		cc.SpriteFrameCache:getInstance():addSpriteFrames("plist/ui/ui1.plist")
		cc.SpriteFrameCache:getInstance():addSpriteFrames("plist/ui/ui2.plist")
		cc.SpriteFrameCache:getInstance():addSpriteFrames("plist/ui/ui3.plist")
	end)

	self:push(function()
		-- manager模块初始化
		require("app.manager._init_")
	end)
end

function Loader:push(func)
	self.pipe:pushTask(LoadTask.new(func))
end

function Loader:load(updateCallback, finishCallback)
	local function progress(taskPercent, totalPercent)
		if updateCallback then updateCallback(totalPercent) end
	end
	self.pipe:start(progress, finishCallback)
end

return Loader
