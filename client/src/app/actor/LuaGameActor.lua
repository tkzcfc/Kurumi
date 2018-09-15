local LuaGameActor = class("LuaGameActor", GameActor)

function LuaGameActor:ctor()

	self:registerLuaHandle("logicUpdate", function(...) return self:override_logicUpdate(...) end)

	self:registerLuaHandle("attLevelTest", function(...) return self:override_attLevelTest(...) end)

	self:registerLuaHandle("AABBCallback", function(...) return self:override_AABBCallback(...) end)

	self:registerLuaHandle("attOtherActorCallback", function(...) return self:override_attOtherActorCallback(...) end)

	self:registerLuaHandle("isRunAABB", function(...) return self:override_isRunAABB(...) end)


    self:registerScriptHandler(function(state)
        if state == "enter" then
            self:onEnter()
        elseif state == "exit" then
            self:onExit()
        end
    end)
end

function LuaGameActor:onEnter()
end

function LuaGameActor:onExit()
	self:unregisterScriptHandler()
end

function LuaGameActor:override_logicUpdate(time)
end

function LuaGameActor:override_attLevelTest(otherActor)
	return self:getActorType() > otherActor:getActorType()
end

function LuaGameActor:override_AABBCallback(otherActor)
end

function LuaGameActor:override_attOtherActorCallback(otherActor)
end

function LuaGameActor:override_isRunAABB(other)
	return self:getActorType() ~= other:getActorType()
end

return LuaGameActor
