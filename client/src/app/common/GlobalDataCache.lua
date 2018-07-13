--全局数据缓存
local GlobalDataCache = class("GlobalDataCache")

--副本地图ID相关
GlobalDataCache.GameMapID = {
	preMapID = nil,
	curMapID = nil,
}

--人物上一次进入游戏副本中时选择的人物

--上一次进入游戏副本时的怪物列表

return GlobalDataCache