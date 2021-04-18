-- @Author: fangcheng
-- @Date:   2020-11-12 21:34:25
-- @remark: 管理器基类

local BaseManager = class("BaseManager")

function BaseManager:ctor()
	table.insert(_MyG.arrManagers, self)
	self:override_onInit()
end

-- @brief 初始化调用
function BaseManager:override_onInit()
end

-- @brief 销毁时调用
function BaseManager:override_onDestroy()
end

function BaseManager:log(...)
	if self.disenableLog then return end
	print(self.__cname .. " :", ...)
end

-- @brief 关闭日志输出
function BaseManager:closeLog()
	self.disenableLog = true
end

return BaseManager
