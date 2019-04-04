local LuaCharacter = require("app.foundation.LuaCharacter")

local Monster_Base = class("Monster_Base", LuaCharacter)

function Monster_Base:ctor()
	Monster_Base.super.ctor(self)
end

function Monster_Base:onEnter()
	Monster_Base.super.onEnter(self)
end

function Monster_Base:onExit()
	Monster_Base.super.onExit(self)
	if self.AI then
		self.AI:setOwner(nil)
		self.AI:override_Exit()
		self.AI = nil
	end
end

return Monster_Base


