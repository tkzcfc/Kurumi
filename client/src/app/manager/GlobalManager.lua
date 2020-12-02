-- @Author: fangcheng
-- @Date:   2020-11-07 16:34:33
-- @remark: 一些全局逻辑管理

local GlobalManager = class("GlobalManager", import(".BaseManager"))

-- @brief 初始化调用
function GlobalManager:override_onInit()
	GlobalManager.super.override_onInit(self)
end

-- @brief 销毁时调用
function GlobalManager:override_onDestroy()
	GlobalManager.super.override_onDestroy(self)
end

return GlobalManager