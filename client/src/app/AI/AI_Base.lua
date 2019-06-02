local AIBase = class("AIBase")

function AIBase:ctor()
	-- self.enemy = nil
end

function AIBase:start(owner, bhRoot)
	self.owner = owner

	self.behaviorTree = require("app.AI.BehaviorTree"):new()
	self.behaviorTree:init(bhRoot, self)

	local scheduler=cc.Director:getInstance():getScheduler()
    self.scriptEntryID = scheduler:scheduleScriptFunc(function(dt) 
    	self.behaviorTree:update(dt)
	end,1 / 20.0,false)

	return true
end

function AIBase:stop()
	if self.scriptEntryID ~= nil then
		local scheduler=cc.Director:getInstance():getScheduler()
		scheduler:unscheduleScriptEntry(self.scriptEntryID)
	end
	self.scriptEntryID = nil
	self.behaviorTree:stop()
end

function AIBase:ai_hasTarget()
	return self.enemy ~= nil
end

function AIBase:ai_canAttack()
	return true
end

function AIBase:ai_attackRangeTest()
	return true
end

function AIBase:ai_forward()
end

function AIBase:ai_backAway()
end

return AIBase



