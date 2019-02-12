local LuaGameWorld = class("LuaGameWorld", GameWorld)

function LuaGameWorld:ctor()
	self.mapNode = self:getNode(GAMEWORLD_NODE_MAP)
	self.uiNode = self:getNode(GAMEWORLD_NODE_UI)

	self:registerLuaHandle("onWorldDestroy", function(...) return self:override_onWorldDestroy(...) end)
end

function LuaGameWorld:loadMap(mapID)
	local mapConfig = require("app.config.MapConfig")
    local map = mapConfig:loadMap(mapID)

    self:setGameMap(map)
    self:enableBox2DPhysics(true, 20.0, 20.0, 0.0, map:getMinPosY())

    self.mapActorNode = map:getActorNode()
end

function LuaGameWorld:override_onWorldDestroy()
end

return LuaGameWorld


