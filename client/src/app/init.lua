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

	cc.exports._MyG = {}
	package.loaded["app.ipConfig"] = nil
	require("app.ipConfig")
	self:init()
end

function Loader:init()
	-- 配置加载
	self:push(function()
		-- 游戏Excel配置
		cc.exports.G_Config = require("XXConfig.XXConfig")
		-- -- 锁定游戏配置, read_only会影响性能，只在debug中使用
		-- if G_MAC.DEBUG then
		-- 	self:push(function() G_Config = read_only(G_Config) end)
		-- end
		
		require("app.config.SceneConfig")
	end)

	-- 全局变量定义
	self:push(function()
		cc.exports.logI = print
		cc.exports.logW = print
		cc.exports.logE = print
		cc.exports.logF = print
		cc.exports.json = require("cjson")
		ccui.Button = MyButton

		_MyG.StartSceneID = _MyG.SCENE_ID_LOGIN
	end)

	self:push(function()
		require("app.common.HelperExt")
		require("app.const._init_")
		require("app.utils.UIUtils")
	end)

	self:push(function()
		-- 常用class 导出
		G_Class.UIWindow = require("app.common.UIWindow")
		G_Class.UIDialog = require("app.common.UIDialog")
		G_Class.SceneBase = require("app.common.SceneBase")
	end)

	-- self:push(function()
	-- 	-- 公用loading
	-- 	_MyG.Loading = require("app.ui.LoadingUI"):new()
	-- 	_MyG.Loading:retain()
	-- end)

	self:push(function()
		-- manager模块初始化
		require("app.manager._init_")
	end)
end

function Loader:push(func)
	self.pipe:pushTask(LoadTask.new(func))
end

-- @brief 开始执行
-- @param processCallback 执行进度回调
-- @param finishCallback 执行完成回调
-- @param errorCallback 错误回调
function Loader:start(processCallback, finishCallback, errorCallback)
	self.pipe:start(processCallback, finishCallback, errorCallback)
end

function Loader:load(finishCallback)
	self:start(function(taskPercent, totalPercent)
		print("init load", totalPercent)
	end, finishCallback)
end

return Loader
