local player = class("player")

function player:ctor(client)
	self.client = client

	self.playerInfo = require("lua_code.players.playerInfo"):new()
end

function sendMsg(msgKey, msgData)
	assert(self.client ~= nil)
	sendMsgToGame(self.client, msgKey, msgData)
end

return player