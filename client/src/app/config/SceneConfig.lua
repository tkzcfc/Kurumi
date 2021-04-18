-- @Author: fangcheng
-- @Date:   2019-09-27 22:37:23
-- @remark: 场景配置相关

_MyG.SCENE_ID_LOAD_RESOURCE		= 0	-- 资源加载场景
_MyG.SCENE_ID_LOGIN 			= 1	-- 登录场景
_MyG.SCENE_ID_UI				= 2 -- UI公用场景
_MyG.SCENE_ID_MAIN 				= 3	-- 主场景
_MyG.SCENE_ID_GAME 				= 4	-- 游戏场景
_MyG.SCENE_ID_TEST 				= 100	-- 测试场景

_MyG.SCENE_MAP = {}
_MyG.SCENE_MAP[_MyG.SCENE_ID_LOAD_RESOURCE] = "LoadResource"
_MyG.SCENE_MAP[_MyG.SCENE_ID_LOGIN] 		= "LoginScene"
_MyG.SCENE_MAP[_MyG.SCENE_ID_UI]			= "UIScene"
_MyG.SCENE_MAP[_MyG.SCENE_ID_MAIN]			= "MainScene"
_MyG.SCENE_MAP[_MyG.SCENE_ID_GAME]			= "GameScene"
_MyG.SCENE_MAP[_MyG.SCENE_ID_TEST]			= "TestScene"



_MyG.SceneResourceLoadConfig = {}


-- 调用流程图
-- 当前运行场景：A
-- 即将进入场景：B
-- A -> ReleaseResourceFunc()
-- B -> LoadResourceFunc()

_MyG.SceneResourceLoadConfig[_MyG.SCENE_ID_LOAD_RESOURCE] = 
{
	--进入场景时资源加载函数
	--参数为：loader，args
	LoadResourceFunc = nil,

	--资源释放函数，如果不为空则会在本场景退出时调用该函数
	--参数为：resourceScene
	ReleaseResourceFunc =  nil,
}


_MyG.SceneResourceLoadConfig[_MyG.SCENE_ID_LOGIN] = 
{
	--进入场景时资源加载函数
	--参数为：resourceScene，args
	LoadResourceFunc = nil,

	--资源释放函数，如果不为空则会在本场景退出时调用该函数
	--参数为：resourceScene，args
	ReleaseResourceFunc =  function(resourceScene, args)
		SceneResourceConfig:DefaultReleaseFunc(_MyG.SCENE_ID_LOGIN, resourceScene, args)
	end,
}


_MyG.SceneResourceLoadConfig[_MyG.SCENE_ID_MAIN] = 
{
	LoadResourceFunc = function(resourceScene, args)
		-- SceneResourceConfig:DefaultLoadFunc(_MyG.SCENE_ID_MAIN, resourceScene, args)
	end,

	ReleaseResourceFunc = function(resourceScene, args)
		-- SceneResourceConfig:DefaultReleaseFunc(_MyG.SCENE_ID_MAIN, resourceScene, args)
	end,
}



for k, v in pairs(_MyG.SCENE_MAP) do
	if _MyG.SceneResourceLoadConfig[k] == nil then
		_MyG.SceneResourceLoadConfig[k] = {}
		print(string.format("警告:场景%q，没有资源管理函数", v))
	end
end
