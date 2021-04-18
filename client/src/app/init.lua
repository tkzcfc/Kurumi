-- @Author : fangcheng
-- @Date   : 2020-05-25 22:01:43
-- @remark : 游戏初始化，更新完毕之后加载

---------------------------------- begin ----------------------------------
-- comlib
require("commonlib.init")

G_LangManager:initWithTextRoot("XXConfig.Lang", G_LangManager.LANGUAGE.CH)
G_NetEventEmitter:clear()
G_SysEventEmitter:clear()

----------------------------------  end  ----------------------------------
local function unload(path)
	package.loaded[path] = nil
end

local function defaultUpdatePercent(percent)
	print(string.format("loading\t%.02f---------------------------------->", percent))
end


local Loader = {}

-- @brief 开始加载
-- @param finishCall 完成回调
-- @param errCall 加载失败回调
-- @param updateCall 进度更新回调
function Loader:load(finishCall, errCall, updateCall)
	self.updateCall = updateCall or defaultUpdatePercent

	self:init()

	local final = function(err)
		if err then
			if errCall then errCall() end
		else
			if finishCall then finishCall() end
		end
	end

	-- 启用协程异步载入
	async_run(function()
		self:doload()
	end, final)
end
---------------------------------- private ----------------------------------

function Loader:init()
	cc.exports._MyG = {}
	_MyG.initFinishTag = false

	self.tasks = {}

	self:push(function()
		unload("app.ipConfig")
		require("app.ipConfig")
		-- require("cocos.cocos2d.json")
		require("app.config.SceneConfig")
		require("app.common.HelperExt")
		require("app.common.Const")
		require("app.utils.UIUtils")
	end)

	-- self:push(function()
	-- 	-- 公用loading
	-- 	_MyG.Loading = require("app.ui.LoadingUI"):new()
	-- 	_MyG.Loading:retain()
	-- end)

	self:push(function()
		-- manager模块初始化
		require("app.manager.init")
	end)

	-- self:push(function()
	-- 	-- msg模块初始化
	-- 	require("msg.init")
	-- end)

	self:push(function()
		-- 常用class 导出
		G_Class.UIWindow = require("app.common.UIWindow")
		G_Class.SceneBase = require("app.common.SceneBase")
	end)

	self:push(function()
		-- 游戏Excel配置
		cc.exports.G_XXConfig = require("XXConfig.XXConfig")
	end)

	-- -- 锁定游戏配置, read_only会影响性能，只在debug中使用
	-- if G_MAC.DEBUG then
	-- 	self:push(function() G_Config = read_only(G_XXConfig) end)
	-- end

	self:push(function()
		cc.exports.logI = print
		cc.exports.logW = print
		cc.exports.logE = print
		cc.exports.logF = print
		ccui.Button = MyButton
		-- _MyG.StartSceneID = _MyG.SCENE_ID_LOGIN
		-- _MyG.StartSceneID = _MyG.SCENE_ID_MAIN

		_MyG.NetManager:setGameInfo(_MyG.startSvrTcpIP, _MyG.startSvrTcpPort)

		_MyG.StartSceneID = _MyG.SCENE_ID_TEST
	end)

	self:push(function()
		_MyG.initFinishTag = true
		print("init文件加载完成")
	end)
end

function Loader:push(func)
	self.tasks[#self.tasks + 1] = func
end

function Loader:doload()
	self.updateCall(0)
	local total = #self.tasks
	for i = 1, total do
		self.tasks[i]()
		self.updateCall(i / total)
		async_yield()
	end
	async_yield()
	self.updateCall(1)
end

return Loader
