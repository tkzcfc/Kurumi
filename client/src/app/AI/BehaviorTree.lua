local BehaviorTree = class("BehaviorTree")

BehaviorTree.DEBUG = true

if table.unpack == nil then
	table.unpack = unpack
end

local function concat(arg)
  local data = ""
  for _, v in ipairs(arg) do
    if data == "" then
      data = data .. tostring(v)
    else
      data = data .. "," .. tostring(v)
    end
  end
  return data
end

local function randomf(min, max)
    return min + (max - min) * math.random()
end

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
		print("call '" .. curNode.func .. "(" .. concat(curNode.arg, ", ") .. ")'")
	end
	return self.object[curNode.func]( self.object, table.unpack(curNode.arg) )
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
	local waitTime = node.arg[1]
	if waitTime ~= -1 and node.arg[2] then
		waitTime = randomf(waitTime, node.arg[2])
	end

	local curTime = 0
	while(true)
	do
		curTime = curTime + coroutine.yield()

		--break condition
		if node.func ~= "" and self.object[node.func](self.object, curTime) then
			break
		end

		if waitTime ~= -1 and curTime >= waitTime then
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

function BehaviorTree.getRandomSelectorIndex(weight, begin)
  local totalVale = 0

  for i=begin,#weight do
    totalVale = totalVale + weight[i]
  end

  local randValue = randomf(0.0, totalVale)

  local tmp = 0
  for i=begin,#weight do
    if tmp <= randValue and randValue <= tmp + weight[i] and weight[i] ~= 0 then
      return i
    end
    tmp = tmp + weight[i]
  end

  return begin
end

-- RandomSelector
function BehaviorTree:RandomSelector(node)
	local childrenTmp = {}
	local weightTmp = {}
	for k,v in pairs(node.children) do
		childrenTmp[k] = v
	end

	for k,v in pairs(node.arg) do
		weightTmp[k] = v
	end

	local return_value = false
	
	if #childrenTmp == 1 then

		return_value = self:bt_run(childrenTmp[1].type)

		if return_value == true then
			return return_value
		end

		return false
	end

	if #weightTmp ~= #childrenTmp then
		error("#weightTmp ~= #childrenTmp")
		return false
	end

	local curIndex = 1
	local count = #childrenTmp

	while(true)
	do
		local randIndex = self.getRandomSelectorIndex(weightTmp, curIndex)

		local randChild = childrenTmp[randIndex]

		weightTmp[curIndex], weightTmp[randIndex] = weightTmp[randIndex], weightTmp[curIndex]
		childrenTmp[curIndex], childrenTmp[randIndex] = childrenTmp[randIndex], childrenTmp[curIndex]

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
