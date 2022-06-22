-- @Author: fangcheng
-- @Date:   2020-11-07 16:34:33
-- @remark: 角色数据管理

local RoleManager = class("RoleManager", import(".BaseManager"))

function RoleManager:override_onInit()
	RoleManager.super.override_onInit(self)
	self.roleDatas = {}

    -- 推送角色信息
    G_NetEventEmitter:on("msg.PushRoleData", handler(self, self.onPushRoleData), self)
end

-- @brief 设置自己当前登录角色的详细信息
function RoleManager:setSelfRoleData(data)
	self.selfRoleData = data
end

function RoleManager:getSelfRole()
	return self.selfRoleData
end

function RoleManager:isSelfRole(roleId)
	return self.selfRoleData.roleId == roleId
end

-- @brief 设置角色信息(简要信息)
function RoleManager:setRoleData(roleId, data)
	self.roleDatas[roleId] = data
end

function RoleManager:getRoleData(roleId)
	return self.roleDatas[roleId]
end


------------------------------------------------- private -------------------------------------------------
function RoleManager:onPushRoleData(data)
	local info = data.info
	
	local jsonDataStr = info.jsonData
	local jsonData = json.decode(jsonDataStr)

	------------------ 初始化jsonData的一些默认值 ------------------
	-- 角色二进制文件
	if info.occupation == Const.Role.DAO then
		jsonData.roleFile = "binary/R1001.bytes"
		jsonData.skin = 1
	else
		jsonData.roleFile = "binary/R1002.bytes"
		jsonData.skin = 2	
	end

	info.jsonDataStr = jsonDataStr
	info.jsonData = jsonData

	self:setRoleData(info.roleId, info)
end

return RoleManager