-- @Author: fangcheng
-- @Date:   2020-11-07 16:34:33
-- @remark: 系统设置数据管理

local SysSetManager = class("SysSetManager", import(".BaseManager"))

function SysSetManager:override_onInit()
	SysSetManager.super.override_onInit(self)

    self.storage = G_Class.StorageObject.new("system.set")
    -- 登录游戏的账号
    self.storage:setDefault("strLoginAccount", "")
    -- 登录游戏的密码
    self.storage:setDefault("strLoginPassword", "")
end

function SysSetManager:getStorage()
	return self.storage
end

function SysSetManager:flush()
	self.storage:flush()
end

-- 登录游戏的账号
function SysSetManager:getLoginAcount()
	return self.storage.strLoginAccount
end

function SysSetManager:setLoginAcount(inValue)
	self.storage.strLoginAccount = inValue
end

-- 登录游戏的密码
function SysSetManager:getLoginPassword()
	return self.storage.strLoginPassword
end

function SysSetManager:setLoginPassword(inValue)
	self.storage.strLoginPassword = inValue
end

return SysSetManager