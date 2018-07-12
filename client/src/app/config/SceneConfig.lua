
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

_MyG.SceneResourceLoadConfig = {}

_MyG.SceneResourceLoadConfig[_MyG.SCENE_ID_LOGIN] = 
{
	LoadResourceFunc = nil,

	ReleaseResourceFunc =  nil,
}


_MyG.SceneResourceLoadConfig[_MyG.SCENE_ID_CREATE] = 
{
	LoadResourceFunc = nil,

	ReleaseResourceFunc = nil,
}


_MyG.SceneResourceLoadConfig[_MyG.SCENE_ID_MAIN] = 
{
	LoadResourceFunc = nil,

	ReleaseResourceFunc = nil,
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

		resourceScene:addLoadResource(_MyG.RES_TYPE.EXPORTJSON, "role/baiji/hero_xiuluo_dao.ExportJson")

		resourceScene:startLoad()

		_MyG.SceneResourceLoadConfig[_MyG.SCENE_ID_GAME_MAP].CacheValue = mapID
	end,

	ReleaseResourceFunc =  function(resourceScene, args)
		local mapID = args.mapID

		if _MyG.SceneResourceLoadConfig[_MyG.SCENE_ID_GAME_MAP].CacheValue == mapID then
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

		resourceScene:delayRelease()
	end,

	CacheValue = nil,
}

_MyG.SceneResourceLoadConfig[_MyG.SCENE_ID_SELECT] = 
{
	LoadResourceFunc = nil,

	ReleaseResourceFunc = nil,
}

