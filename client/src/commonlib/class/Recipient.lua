-- @Author: fangcheng
-- @URL: github.com/tkzcfc
-- @Date:   2019-10-17 21:26:05
-- @Last Modified by:   fangcheng
-- @Last Modified time: 2020-04-04 19:01:55
-- @Description: 事件订阅器

local Recipient = class("Recipient")

function Recipient:ctor(_eventEmitter)
	self.event_lamdaMap = {}
   self.eventEmitter = _eventEmitter
end

-- @brief 订阅事件
-- @param event 事件key
-- @param listener 监听者
-- @param priority 派发优先级 默认3
function Recipient:on(event, listener, priority)
	if self.event_lamdaMap[event] then
		com_log("警告：重复注册消息订阅", event)
	end
	self.event_lamdaMap[event] = listener
	self.eventEmitter:on(event, listener, priority)
end

-- @brief 订阅一次事件
function Recipient:once(event, listener, priority)
	self.event_lamdaMap[event] = listener
	self.eventEmitter:once(event, listener, priority)
end

-- @brief 订阅事件
-- @param event 事件key
-- @param _listener 监听者
-- @param _count 订阅次数
-- @param priority 派发优先级 默认3
function Recipient:addListener(event, listener, _count, priority)
	self.event_lamdaMap[event] = listener
	self.eventEmitter:addListener(event, listener, _count, priority)
end

-- @brief 取消所有订阅的事件
function Recipient:clear()
	for k, v in pairs(self.event_lamdaMap) do
		self.eventEmitter:removeListener(k, v)
	end
	self.event_lamdaMap = {}
end

-- @brief 取消订阅事件
-- @param event 事件key
function Recipient:remove(event)
	if self.event_lamdaMap[event] then
		self.eventEmitter:removeListener(event, self.event_lamdaMap[event])
		self.event_lamdaMap[event] = nil
	end
end

return Recipient




   -- local eventEmitter = Class.EventEmitter.new()
   -- local recipient = Class.Recipient.new(eventEmitter)
   -- recipient:on("1", function(...) print(...) end)
   -- recipient:once("2", function(...) print(...) end)
   -- recipient:once("3", function(...) print(...) end)
   -- recipient:on("4", function(...) print(...) end)
   -- recipient:remove("3")
   -- recipient:remove("4")

   -- eventEmitter:emit("1", "key_1",2,1)
   -- eventEmitter:emit("2", "key_2",2,2)
   -- eventEmitter:emit("2", "key_2",2,3)
   -- eventEmitter:emit("3", "key_3",2,4)
   -- eventEmitter:emit("1", "key_1",2,5)
   -- eventEmitter:emit("4", "key_4",2,6)

   -- recipient:clear()

   -- eventEmitter:emit("1", "key_1",2,1)
   -- eventEmitter:emit("2", "key_2",2,2)
   -- eventEmitter:emit("2", "key_2",2,3)
   -- eventEmitter:emit("3", "key_3",2,4)
   -- eventEmitter:emit("1", "key_1",2,5)
   -- eventEmitter:emit("4", "key_4",2,6)

-- [LUA-print] key_1       2       1
-- [LUA-print] key_2       2       2
-- [LUA-print] key_1       2       5