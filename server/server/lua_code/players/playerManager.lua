local playerManager = class("playerManager")

function playerManager:ctor()
	self.onlinePlayers = {}	-- {[1]player, [2]player...}
	self.offlinePlayers = {} --{[1]player, [2]player...}
	self.unknownPlayers = {} --{[1] = client, [2] = client, ...}

	_MyG.NetMsgDispatcher:register("login.C2S_login", function(...) self:dis_login(...) end)
	_MyG.NetMsgDispatcher:register("login.C2S_register", function(...) self:dis_register(...) end)
end

function playerManager:connectToServer(client)
	for i=1,#self.unknownPlayers do
		if self.unknownPlayers[i] == client then
			print(client, "客户端已存在")
			return
		end
	end
	table.insert(self.unknownPlayers, client)
end

function playerManager:disconnectToServer(client)
	local find = false
	for i,player in ipairs(self.onlinePlayers) do
		if self.onlinePlayers[i].client == client then
			player.client = nil
			table.insert(self.offlinePlayers, player)
			table.remove(self.onlinePlayers, i)
			find = true
			break
		end
	end

	if find then
		return
	end

	for i = 1, #self.unknownPlayers do
		if self.unknownPlayers[i] == client then
			table.remove(self.unknownPlayers, i)
			break
		end
	end
end

function playerManager:dis_login(client, msgdata)

	local index = nil
	local login_ret = {code = 0, msg = ""}
	local function sendret()
		sendMsgToGame(client, "login.S2C_login_ret", login_ret)
	end

	for i = 1, #self.unknownPlayers do
		if self.unknownPlayers[i] == client then
			index = i
			break
		end
	end

	if index == nil then
		for i,player in ipairs(self.onlinePlayers) do
			if player.client == client then
				login_ret.code = 3
				login_ret.msg = "您已进入游戏，无需重复登录"
				sendret()
				return
			end
		end
		login_ret.code = 3
		login_ret.msg = "未知客户端"
		sendret()
		return
	end

	for i,player in ipairs(self.offlinePlayers) do
		if player.playerInfo.account == msgdata.account then
			if player.playerInfo.password == msgdata.password then
				sendret()
			else
				login_ret.code = 2
				login_ret.msg = "密码错误"
				sendret()
			end
			return
		end
	end

	login_ret.code = 1
	login_ret.msg = "账号不存在"
	sendret()
end

function playerManager:dis_register(client, msgdata)
	local index = nil
	local register_ret = {msg = "", code = 0}
	local function sendret()
		sendMsgToGame(client, "login.S2C_register_ret", register_ret)
	end

	for i,player in ipairs(self.onlinePlayers) do
		if player.playerInfo.account == msgdata.account then
			register_ret.code = 1
			register_ret.msg = "账号已存在"
			sendret()
			return
		end
	end

	for i,player in ipairs(self.offlinePlayers) do
		if player.playerInfo.account == msgdata.account then
			register_ret.code = 1
			register_ret.msg = "账号已存在"
			sendret()
			return
		end
	end

	local player = require("lua_code.players.player"):new(nil)
	player.playerInfo.account = msgdata.account
	player.playerInfo.password = msgdata.password
	table.insert(self.offlinePlayers, player)
	sendret()
end

return playerManager