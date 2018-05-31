local playerInfo = class("playerInfo")

function playerInfo:ctor()
	self.account = ""
	self.password = ""
	self.registertime = 0
end

return playerInfo