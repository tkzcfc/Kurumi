-- @Author : fangcheng
-- @Date   : 2019-10-17 21:26:05
-- @remark : 事件派发

-- 最大优先级
local PRIORITY_LEVEL_MAX = 3
-- 默认优先级
local PRIORITY_LEVEL_DEFAULT = 2

local table_remove = table.remove

local EventEmitter = class("EventEmitter")

function EventEmitter:ctor()
	self.event_listenerMap = {}
	self.doEmit_Map = {}
	self.uniqueSeed = 0
end


-- @brief 订阅事件
-- @param event 事件key
-- @param listener 监听者
-- @param priority 派发优先级 默认3
function EventEmitter:on(event, listener, priority)
	return self:addListener(event, listener, -1, priority)
end

-- 订阅一次事件
function EventEmitter:once(event, listener, priority)
	return self:addListener(event, listener, 1, priority)
end

-- @brief 取消订阅事件
function EventEmitter:off(arg1, arg2)
	if type(arg2) == "function" then
		self:removeListener(event, listener)
	else
		if arg1 == nil then
			return
		end
		assert(type(arg1) == "number")
		self:removeListenerByUniqueID(arg1)
	end	
end

-- @brief 订阅事件
-- @param event 事件key
-- @param _listener 监听者
-- @param _count 订阅次数
-- @param priority 派发优先级 默认3
function EventEmitter:addListener(event, _listener, _count, priority)
	priority = priority or PRIORITY_LEVEL_DEFAULT
	
	if priority < 1 or priority > PRIORITY_LEVEL_MAX then
		assert(false)
		return
	end

	local listenerTabArr = self.event_listenerMap[event]

	if listenerTabArr == nil then
		listenerTabArr = {}
		for i = 1, PRIORITY_LEVEL_MAX do
			listenerTabArr[i] = {}
		end
		self.event_listenerMap[event] = listenerTabArr
	end

	self.uniqueSeed = self.uniqueSeed + 1

	local listenerTab = listenerTabArr[priority]
	listenerTab[#listenerTab + 1] = {listener = _listener, count = _count, uniqueID = self.uniqueSeed}

	self:clearInvalid()

	return self.uniqueSeed
end

-- @brief 取消订阅事件
-- @param event 事件key
-- @param listener 监听者
function EventEmitter:removeListener(event, listener)
	local listenerTabArr = self.event_listenerMap[event]

	if listenerTabArr then
		for _, listenerTab in pairs(listenerTabArr) do
			for k, v in pairs(listenerTab) do
				if v.listener == listener then
					v.count = 0
				end
			end

			if not self.doEmit_Map[event] then
				repeat
				until(not EventEmitter.removeOnce(listenerTab))
			end
		end
	end
end

-- @brief 取消订阅事件
function EventEmitter:removeListenerByUniqueID(uniqueID)
	if uniqueID == nil then
		return
	end
	
	for event, listenerTabArr in pairs(self.event_listenerMap) do
		for _, listenerTab in pairs(listenerTabArr) do
			for k, v in pairs(listenerTab) do
				if v.uniqueID == uniqueID then
					v.count = 0
				end
			end

			if not self.doEmit_Map[event] then
				repeat
				until(not EventEmitter.removeOnce(listenerTab))
			end
		end
	end
end

-- @brief 取消订阅事件
function EventEmitter:removeAllListeners(event)
	if not self.doEmit_Map[event] then
		self.event_listenerMap[event] = {}
	else
		local listenerTab = self.event_listenerMap[event]
		if listenerTab ~= nil then
			for k, v in pairs(listenerTab) do
				v.count = 0
			end
		end
	end
end

function EventEmitter:clear()
	self.event_listenerMap = {}
end

-- @brief 派发事件
-- @param event 事件key
function EventEmitter:emit(event, ...)
	local listenerTabArr = self.event_listenerMap[event]

	if listenerTabArr == nil then
		return 0
	end

	local callCount = 0
	local breakLoop = false

	self.doEmit_Map[event] = true

	for _, listenerTab in pairs(listenerTabArr) do
		for k, v in pairs(listenerTab) do
			if v.count ~= 0 then
				if v.count > 0 then
					v.count = v.count - 1
				end
				callCount = callCount + 1
				if v.listener(...) == true then
					breakLoop = true
					break
				end
			end
		end

		if breakLoop then
			break
		end
	end

	self.doEmit_Map[event] = false

	for _, listenerTab in pairs(listenerTabArr) do
		repeat
		until(not EventEmitter.removeOnce(listenerTab))
	end

	self:clearInvalid()

	return callCount
end

-- @brief 查询某个事件的订阅数量
-- @param event 事件key
function EventEmitter:listeners(event)
	local listenerTabArr = self.event_listenerMap[event]

	if listenerTabArr == nil then
		return 0
	end

	local count = 0
	
	for _, listenerTab in pairs(listenerTabArr) do
		for k, v in pairs(listenerTab) do
			if v.count ~= 0 then
				count = count + 1
			end
		end
	end
	
	return count
end

function EventEmitter:clearInvalid()
	if math.random(1, 200) ~= 1 then
		return
	end
	repeat
	until(not self:clearInvalidEx())
end

--------------------------------------------------------------------------------------------
function EventEmitter:clearInvalidEx()
	local del = true
	for event, listenerTabArr in pairs(self.event_listenerMap) do
		del = true
		for _, listenerTab in pairs(listenerTabArr) do
			for k,v in pairs(listenerTab) do
				del = false
				break
			end
			if not del then
				break
			end
		end

		if del then
			self.event_listenerMap[event] = nil
			return true
		end
	end
end

function EventEmitter.removeOnce(listenerTab)
	for k, v in pairs(listenerTab) do
		if v.count == 0 then
			table_remove(listenerTab, k)
			return true
		end
	end
	return false
end

return EventEmitter
