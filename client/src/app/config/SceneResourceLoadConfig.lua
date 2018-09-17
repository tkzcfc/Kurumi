
_MyG.SCENE_ID_LOGIN 			= 0	--注册场景
_MyG.SCENE_ID_CREATE 			= 1	--创建角色场景
_MyG.SCENE_ID_MAIN				= 2	--主场景
_MyG.SCENE_ID_GAME_MAP			= 3	--游戏场景
_MyG.SCENE_ID_LOAD_RESOURCE		= 4	--资源加载场景
_MyG.SCENE_ID_SELECT			= 5 --选择地图场景

_MyG.SCENE_MAP = {}
_MyG.SCENE_MAP[_MyG.SCENE_ID_LOGIN] 		= "LoginScene"
_MyG.SCENE_MAP[_MyG.SCENE_ID_CREATE] 		= "CreateScene"
_MyG.SCENE_MAP[_MyG.SCENE_ID_MAIN] 			= "MainScene"
_MyG.SCENE_MAP[_MyG.SCENE_ID_GAME_MAP] 		= "GameScene"
_MyG.SCENE_MAP[_MyG.SCENE_ID_LOAD_RESOURCE] = "LoadResource"
_MyG.SCENE_MAP[_MyG.SCENE_ID_SELECT]		= "SelectScene"


local SceneResourceConfig = require("app.config.SceneResourceConfig")

_MyG.SceneResourceLoadConfig = {}


-- 调用流程图
-- 当前运行场景：A
-- 即将进入场景：B
-- B:ReleaseResourceFunc()
-- A:PreReleaseResourceFunc()
-- A:LoadResourceFunc()
-- A:DelayReleaseResourceFunc()

_MyG.SceneResourceLoadConfig[_MyG.SCENE_ID_LOGIN] = 
{
	--进入场景时资源加载函数
	--参数为：resourceScene，args
	LoadResourceFunc = nil,

	--资源释放函数，如果不为空则会在本场景退出时调用该函数
	--参数为：resourceScene
	ReleaseResourceFunc =  function(resourceScene, args)
		SceneResourceConfig:DefaultReleaseFunc(_MyG.SCENE_ID_LOGIN, resourceScene, args)
	end,

	--预释放资源函数，在LoadResourceFunc之前调用
	--参数为：resourceScene，args
	PreReleaseResourceFunc = nil,

	--释放资源函数，在LoadResourceFunc之后调用
	--参数为：resourceScene，args
	DelayReleaseResourceFunc = nil,
}


_MyG.SceneResourceLoadConfig[_MyG.SCENE_ID_CREATE] = 
{
	LoadResourceFunc = function(resourceScene, args)
		SceneResourceConfig:DefaultLoadFunc(_MyG.SCENE_ID_CREATE, resourceScene, args)
	end,

	ReleaseResourceFunc = function(resourceScene, args)
		SceneResourceConfig:DefaultReleaseFunc(_MyG.SCENE_ID_CREATE, resourceScene, args)
	end,

	PreReleaseResourceFunc = nil,

	DelayReleaseResourceFunc = nil,
}


_MyG.SceneResourceLoadConfig[_MyG.SCENE_ID_MAIN] = 
{
	LoadResourceFunc = function(resourceScene, args)
		SceneResourceConfig:DefaultLoadFunc(_MyG.SCENE_ID_MAIN, resourceScene, args)
	end,

	ReleaseResourceFunc = function(resourceScene, args)
		SceneResourceConfig:DefaultReleaseFunc(_MyG.SCENE_ID_MAIN, resourceScene, args)
	end,

	PreReleaseResourceFunc = nil,
	
	DelayReleaseResourceFunc = nil,
}

_MyG.SceneResourceLoadConfig[_MyG.SCENE_ID_GAME_MAP] = 
{
	LoadResourceFunc = function(resourceScene, args)
		local mapID = args.mapID
		local mapConfig = require("app.config.MapConfig")
		
		local list = mapConfig[mapID].loadResourceList.exportJson
		for k,v in pairs(list) do
			resourceScene:addLoadResource(_MyG.RES_TYPE.EXPORTJSON, v)
		end

		list = mapConfig[mapID].loadResourceList.image
		for k,v in pairs(list) do
			resourceScene:addLoadResource(_MyG.RES_TYPE.PNG, v)
		end

		list = mapConfig[mapID].loadResourceList.plist
		for k,v in pairs(list) do
			resourceScene:addLoadResource(_MyG.RES_TYPE.PLIST, v)
		end

		resourceScene:addLoadResource(_MyG.RES_TYPE.EXPORTJSON, "role/baiji/hero_shizhuak_dao.ExportJson")
		resourceScene:addLoadResource(_MyG.RES_TYPE.EXPORTJSON, "monster/boss5_leishen/boss5_leishen.ExportJson")
		resourceScene:addLoadResource(_MyG.RES_TYPE.EXPORTJSON, "monster/boss5_leishen/boss5_leigu.ExportJson")
		resourceScene:addLoadResource(_MyG.RES_TYPE.EXPORTJSON, "monster/boss5_leishen/boss5_dianqiu.ExportJson")
		resourceScene:addLoadResource(_MyG.RES_TYPE.EXPORTJSON, "monster/shengbo/shengbo.ExportJson")
	end,

	ReleaseResourceFunc = nil,

	PreReleaseResourceFunc =  function(resourceScene, args)
		
		_MyG.GlobalDataCache.preMapID = _MyG.GlobalDataCache.curMapID
		_MyG.GlobalDataCache.curMapID = args.mapID

		if _MyG.GlobalDataCache.preMapID == _MyG.GlobalDataCache.curMapID then
			return
		end

		local mapID = _MyG.GlobalDataCache.preMapID
		local mapConfig = require("app.config.MapConfig")
		if mapID == nil or mapConfig[mapID] == nil then
			return
		end

		local mapConfig = require("app.config.MapConfig")
		
		local list = mapConfig[mapID].releaseResourceList.exportJson
		for k,v in pairs(list) do
			resourceScene:addReleaseResource(_MyG.RES_TYPE.EXPORTJSON, v)
		end

		list = mapConfig[mapID].releaseResourceList.image
		for k,v in pairs(list) do
			resourceScene:addReleaseResource(_MyG.RES_TYPE.PNG, v)
		end

		list = mapConfig[mapID].releaseResourceList.plist
		for k,v in pairs(list) do
			resourceScene:addReleaseResource(_MyG.RES_TYPE.PLIST, v)
		end
	end,

	DelayReleaseResourceFunc = nil,
}

_MyG.SceneResourceLoadConfig[_MyG.SCENE_ID_SELECT] = 
{
	LoadResourceFunc = function(resourceScene, args)
		SceneResourceConfig:DefaultLoadFunc(_MyG.SCENE_ID_SELECT, resourceScene, args)
	end,

	ReleaseResourceFunc = function(resourceScene, args)
		SceneResourceConfig:DefaultReleaseFunc(_MyG.SCENE_ID_SELECT, resourceScene, args)
	end,

	PreReleaseResourceFunc = nil,
	
	DelayReleaseResourceFunc = nil,
}

