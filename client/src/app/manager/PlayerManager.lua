-- @Author: fangcheng
-- @Date:   2020-11-07 16:34:33
-- @remark: 玩家管理

local PlayerManager = class("PlayerManager", import(".BaseManager"))

function PlayerManager:override_onInit()
	PlayerManager.super.override_onInit(self)
	self.playerDatas = {}

	self.selfPlayerData = {}
end

function PlayerManager:setSelfPlayerData(data)
	self.selfPlayerData = data
end

function PlayerManager:getSelfPlayerData()
	return self.selfPlayerData
end

function PlayerManager:addPlayerData(playerID, playerData)
	self.playerDatas[playerID] = playerData
end

function PlayerManager:getPlayerData(playerID)
	return self.playerDatas[playerID]
end

return PlayerManager