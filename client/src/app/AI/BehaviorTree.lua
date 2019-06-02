local BehaviorTree = class("BehaviorTree")

BehaviorTree.DEBUG = true



----------------------------------------------------------------------------------------------------------------------------
--Public Function Begin
----------------------------------------------------------------------------------------------------------------------------

function BehaviorTree:execute(node, object, runLoop, endFunc)
	self.scriptNode = node
	self.object = object
	self.finish = false
	self.runLoop = runLoop
	self.executionResult = nil
	self.endFunc = endFunc

	local startNode = self.scriptNode.nodes[1]

	self.runCoroutine = coroutine.create(function()
		repeat
			self.executionResult = self:bt_run(startNode)
			coroutine.yield()
		until(not self.runLoop)

		self:bt_stop()
	end)
end

function BehaviorTree:update(delta)
	if self.runCoroutine == nil then
		return
	end

	local ret, msg = coroutine.resume(self.runCoroutine, delta)
	if not ret then
		print(msg)
	end
end

function BehaviorTree:isFinish()
	return self.finish
end

function BehaviorTree:doPauseUntil(condition)
	while(true)
	do
		if condition(coroutine.yield()) then
			break
		end
	end
end

function BehaviorTree:doContinue()
	self.runLoop = true
end

function BehaviorTree:doBreak()
	self.runLoop = false
end

function BehaviorTree:getExecutionResult()
	return self.executionResult
end

function BehaviorTree:doForceStop()
	self:bt_stop()
end

----------------------------------------------------------------------------------------------------------------------------
--Public Function End
----------------------------------------------------------------------------------------------------------------------------



----------------------------------------------------------------------------------------------------------------------------
-- Function Begin
----------------------------------------------------------------------------------------------------------------------------

function BehaviorTree:bt_run(curNode)
	if BehaviorTree.DEBUG then
		print("run node '" .. curNode.type .. "'")
	end
	return self[curNode.type](self, curNode)
end

function BehaviorTree:bt_call(curNode)
	if BehaviorTree.DEBUG then
		print("call '" .. curNode.func .. "(" .. curNode.arg .. ")'")
	end
	return self.object[curNode.func](self.object, curNode.arg)
end

function BehaviorTree:bt_stop()
	self.runCoroutine = nil
	self.finish = true
	self.runLoop = false
	if type(self.endFunc) == "function" then
		self.endFunc()
	end
end

----------------------------------------------------------------------------------------------------------------------------
-- Function Begin
----------------------------------------------------------------------------------------------------------------------------



----------------------------------------------------------------------------------------------------------------------------
-- Node Begin
----------------------------------------------------------------------------------------------------------------------------

-- Start
function BehaviorTree:Start(node)
	return self:bt_run(node.children[1])
end

-- Wait
function BehaviorTree:Wait(node)
	node.arg = tonumber(node.arg)

	local curTime = 0
	while(true)
	do
		curTime = curTime + coroutine.yield()

		--break condition
		if node.func ~= "" and self.object[node.func](self.object, curTime) then
			break
		end

		if node.arg ~= -1 and curTime >= node.arg then
			break
		end
	end

	return self:Start(node)
end

-- Selector
function BehaviorTree:Selector(node)
	local return_value = false

	for _, child in ipairs(node.children) do

		return_value = self:bt_run(child)

		if return_value == true then
			break
		end
	end

	return return_value
end

-- RandomSelector
function BehaviorTree:RandomSelector(node)
	local childrenTmp = node.children
	if childrenTmp == nil or #childrenTmp < 0 then
		return false
	end

	local return_value = false
	
	if #childrenTmp == 1 then

		return_value = self:bt_run(childrenTmp[1].type)

		if return_value == true then
			return return_value
		end

		return false
	end

	local curIndex = 1
	local count = #childrenTmp

	while(true)
	do
		local randIndex = math.random(curIndex, count)
		local randChild = childrenTmp[randIndex]
		local tmpChild = childrenTmp[curIndex]

		if tmpChild ~= randChild then
			childrenTmp[curIndex] = randChild
			childrenTmp[randIndex] = tmpChild
		end

		return_value = self:bt_run(randChild)

		if return_value == true then
			break
		else
			return_value = false
		end
		curIndex = curIndex + 1
		if curIndex > count then
			break
		end
	end
	return return_value
end

-- Sequence
function BehaviorTree:Sequence(node)
	local return_value = true
	for _, child in ipairs(node.children) do

		return_value = self:bt_run(child)

		if not return_value then
			return_value = false
			break
		end
	end
	return return_value
end
 
-- Behaviour Node
-- Action
function BehaviorTree:Action(node)
	return self:bt_call(node)
end
-- Condition Action
function BehaviorTree:Condition(node)
	if self.object[node.name](self.object) then
		self:bt_call(node)
		return true
	else
		return false
	end
end

-- Condition Node
-- Filter
function BehaviorTree:Filter(node)
	if self:bt_call(node) then
		return self:Start(node)
	else
		return false
	end
end

-- True
function BehaviorTree:True(node)
	if node.func ~= "" then
		self:bt_call(node)
	end
	return true
end

-- False
function BehaviorTree:False(node)
	if node.func ~= "" then
		self:bt_call(node)
	end
	return false
end


----------------------------------------------------------------------------------------------------------------------------
-- Node End
----------------------------------------------------------------------------------------------------------------------------

return BehaviorTree
