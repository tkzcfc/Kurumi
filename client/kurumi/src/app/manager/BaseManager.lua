-- @Author: fangcheng
-- @Date:   2020-11-12 21:34:25
-- @remark: 管理器基类

local BaseManager = class("BaseManager")

-- 禁用输出
property(BaseManager, "bDisenableLog", false)

function BaseManager:ctor()
	table.insert(_MyG.arrManagers, self)
	self:override_onInit()
end

function BaseManager:destroy()
    G_NetEventEmitter:offByTag(self)
    G_SysEventEmitter:offByTag(self)
    self:override_onDestroy()
end

-- @brief 初始化调用
function BaseManager:override_onInit()
end

-- @brief 销毁时调用
function BaseManager:override_onDestroy()
end

function BaseManager:log(...)
	if self.bDisenableLog then return end
	print(self.__cname .. " :", ...)
end

-- @brief 关闭日志输出
function BaseManager:closeLog()
	self.bDisenableLog = true
end

return BaseManager
