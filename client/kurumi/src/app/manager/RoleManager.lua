-- @Author: fangcheng
-- @Date:   2020-11-07 16:34:33
-- @remark: 角色数据管理

local RoleManager = class("RoleManager", import(".BaseManager"))

function RoleManager:override_onInit()
	RoleManager.super.override_onInit(self)
	self.roleDatas = {}

    -- 游戏服回复的消息相关
    G_NetEventEmitter:on(MessageID.MSG_PUSH_ROLE_DATA, handler(self, self.onPushRoleSimpleInfo), self)
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
function RoleManager:onPushRoleSimpleInfo(data)
	local jsonDataStr = data.jsonData
	local jsonData = json.decode(jsonDataStr)

	------------------ 初始化jsonData的一些默认值 ------------------
	-- 角色二进制文件
	if data.occupation == Const.Role.DAO then
		jsonData.roleFile = "binary/R1001.bytes"
		jsonData.skin = 1
	else
		jsonData.roleFile = "binary/R1002.bytes"
		jsonData.skin = 2	
	end

	data.jsonDataStr = jsonDataStr
	data.jsonData = jsonData

	self:setRoleData(data.roleId, data)
end

return RoleManager