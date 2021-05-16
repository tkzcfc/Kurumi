-- @Author: fangcheng
-- @Date:   2020-11-07 16:34:33
-- @remark: 系统设置数据管理

local SysSetManager = class("SysSetManager", import(".BaseManager"))

local UserDefaultInstance = cc.UserDefault:getInstance()

local EValueType = 
{
	EString = 0,
	EInt 	= 1,
	EBool	= 2,
	EFloat	= 3,
}

function SysSetManager:override_onInit()
	SysSetManager.super.override_onInit(self)
	
	local proxy = {__newindex = function(t, k, v)
		local pair = self.db[k]
		if not pair then
			error("不存在key", k)
		end
		if pair.value ~= v then
			pair.value = v
			pair.dirty = true
			self.dirtyTag = true
			self:log("SysSetManager 数据发生改变--->")
		end
	end,
	__index = function(t, k)
		return self.db[k].value
	end}
	
	self.data = setmetatable({}, proxy)
	self.db = {}
	self.dirtyTag = false
	self:reloadData()

	-- 每隔一段时间自动储存一次
	local scheduler = cc.Director:getInstance():getScheduler()
    self.scriptEntryID = scheduler:scheduleScriptFunc(function(dt)
    	self:flush()
    end, 10,false)
end

function SysSetManager:reloadData()
	self:flush()
	self:initProperty()
	self.dirtyTag = false
end

function SysSetManager:initProperty()
	-- 是否开启音乐
	self:initPair("isOpenMusic", EValueType.EBool, true)
	-- 是否开启音效
	self:initPair("isOpenEffects", EValueType.EBool, true)
	-- 背景音乐音量
	self:initPair("fMusicVolume", EValueType.EFloat, 1.0)
	-- 音效音量
	self:initPair("fEffectVolume", EValueType.EFloat, 1.0)

	-- 登录游戏的账号
	self:initPair("strLoginAccount", EValueType.EString)
	-- 登录游戏的密码
	self:initPair("strLoginPassword", EValueType.EString)
	-- 当前选择语言
	self:initPair("strLang", EValueType.EString)
	-- 地图选择下标
	self:initPair("iSelectPageIndex", EValueType.EInt)
end

function SysSetManager:initPair(key, valueType, defaultValue)
	local t = {}
	t.valueType = valueType

	local storeKey = self:getStoreKey(key)
	if valueType == EValueType.EString then
		t.value = UserDefaultInstance:getStringForKey(storeKey, defaultValue or "")
	elseif valueType == EValueType.EInt then
		t.value = UserDefaultInstance:getIntegerForKey(storeKey, defaultValue or 0)
	elseif valueType == EValueType.EBool then
		t.value = UserDefaultInstance:getBoolForKey(storeKey, defaultValue or true)
	elseif valueType == EValueType.EFloat then
		t.value = UserDefaultInstance:getFloatForKey(storeKey, defaultValue or 0)
	end
	self.db[key] = t
end

function SysSetManager:getStoreKey(key)
	return 'Set_' .. key
end

----------------------------------- public -----------------------------------
-- @brief 获取值
function SysSetManager:getProperty(propertyName)
	return self.data[propertyName]
end

-- @brief 设置值
function SysSetManager:setProperty(propertyName, value)
	self.data[propertyName] = value
end

-- 登录游戏的账号
function SysSetManager:getLoginAcount()
	return self:getProperty("strLoginAccount")
end

function SysSetManager:setLoginAcount(inValue)
	self:setProperty("strLoginAccount", inValue)
end

-- 登录游戏的密码
function SysSetManager:getLoginPassword()
	return self:getProperty("strLoginPassword")
end

function SysSetManager:setLoginPassword(inValue)
	self:setProperty("strLoginPassword", inValue)
end

-----------------------------------------------------------------------------------------


-- @brief 销毁时调用
function SysSetManager:override_onDestroy()
	SysSetManager.super.override_onDestroy(self)
	
	local scheduler=cc.Director:getInstance():getScheduler()
	scheduler:unscheduleScriptEntry(self.scriptEntryID)

	self:flush()
end

function SysSetManager:flush()
	if not self.dirtyTag then
		return
	end

	self.dirtyTag = false

	local valueType, storeKey, value
	for k, v in pairs(self.db) do
		if v.dirty then
			valueType = v.valueType
			value = v.value
			storeKey = self:getStoreKey(k)

			if valueType == EValueType.EString then
				UserDefaultInstance:setStringForKey(storeKey, value)
			elseif valueType == EValueType.EInt then
				UserDefaultInstance:setIntegerForKey(storeKey, value)
			elseif valueType == EValueType.EBool then
				UserDefaultInstance:setBoolForKey(storeKey, value)
			elseif valueType == EValueType.EFloat then
				UserDefaultInstance:setFloatForKey(storeKey, value)
			end
		end
	end
end

-----------------------------------       -----------------------------------

return SysSetManager