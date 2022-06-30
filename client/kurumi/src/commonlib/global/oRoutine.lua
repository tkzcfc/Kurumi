-- @Author : fangcheng
-- @Date   : 2020-03-11 21:05:18
-- @remark : 协程相关

if oRoutine then return end

print("load oRoutine-------->>")

local yield = coroutine.yield
local wrap = coroutine.wrap
local table_insert = table.insert
local table_remove = table.remove

------------------------------------------------------------------------------------------------------------------------------

local debug_enable = true
local DirectordeltaTime = 0.0

local log = print

local function Routine_end() return true end

local function Error_hook(err)
	if debug_enable then
		log(debug.traceback(err, 3))
	end
	return true
end

------------------------------------------------------------------------------------------------------------------------------
local function wait(cond)
	repeat
		yield(false)
	until not cond(DirectordeltaTime)
end

local function once(job)
	return wrap(function()
		job()
		return true
	end)
end

local function loop(job)
	return wrap(function()
		repeat yield(false) until job() == true
		return true
	end)
end

local function seconds(duration)
	local time = 0
	return function(deltaTime)
		time = time + deltaTime
		return time < duration
	end
end

local function cycle(duration,work)
	local time = 0
	local function worker()
		local deltaTime = DirectordeltaTime
		time = time + deltaTime
		if time < duration then
			work(time/duration)
			return true
		else
			work(1)
			return false
		end
	end
	while worker() do
		yield(false)
	end
end

------------------------------------------------------------------------------------------------------------------------------

local M = {}

function M.new()
	local t = setmetatable({}, {__index = M, __call = function(self, routine) 
		return self:create(routine) 
	end})
	t:ctor()
	return t
end

function M:ctor()
	self.threads = {}
end

function M:create(routine)
	table_insert(self.threads, routine)
	return routine
end

function M:clear()
	while #self.threads > 0 do
		table_remove(self.threads)
	end
end

function M:skill(routine)
	for i = 1,#self.threads do
		if self.threads[i] == routine then
			self.threads[i] = Routine_end
			return true
		end
	end
	return false
end

local tmpvalue, retvalue
function M:update()
	if self.pauseTag then
		return
	end

	local i,count = 1,#self.threads
	while i <= count do
		tmpvalue, retvalue = xpcall(self.threads[i], Error_hook)
		if retvalue then
			self.threads[i] = self.threads[count]
			table_remove(self.threads,count)
			i = i-1
			count = count-1
		end
		i = i+1
	end
end

function M:pause()
	self.pauseTag = true
end

function M:resume()
	self.pauseTag = false
end

M.remove = M.skill

------------------------------------------------------------------------------------------------------------------------------

local Routine = M.new()
local schedulerid = nil

function Routine:start()
	self:stop()

	local scheduler = cc.Director:getInstance():getScheduler()
	schedulerid = scheduler:scheduleScriptFunc(function (dt)
		DirectordeltaTime = dt
		Routine:update()
	end, 1 / 60.0, false)
end

function Routine:stop()
	if schedulerid then
		cc.Director:getInstance():getScheduler():unscheduleScriptEntry(schedulerid)
		schedulerid = nil
	end
end

Routine:start()

global.o_wait 		= wait
global.o_once 		= once
global.o_loop 		= loop
global.o_seconds 	= seconds
global.o_cycle 		= cycle

global.oRoutine 	= Routine


-- example

-- oRoutine(o_once(function() 
-- 	local x = nil
-- 	x = x + 1
-- 	o_wait(o_seconds(1.0))
-- 	print("wait 1.0")
-- 	o_wait(o_seconds(5.0))
-- 	print("wait 5.0")
-- end))


-- oRoutine(o_loop(function()
-- 	o_wait(o_seconds(3))
-- 	print("every 3 second")
-- end))

-- local routine = oRoutine(o_once(function()
-- 	o_wait(o_seconds(20))
-- 	print("this routine will be cancelled")
-- end))

-- oRoutine(o_once(function()
-- 	o_wait(o_seconds(10))
-- 	oRoutine:remove(routine)
-- 	print("after 10 seconds, cancel routine above")
-- end))

-- local progress = 0

-- oRoutine(o_once(function()
-- 	o_cycle(2, function(percent)
-- 		progress = percent
-- 	end)
-- end))

-- oRoutine(o_once(function()
-- 	o_wait(function() return progress < 1 end)
-- 	print("now progress is", progress)
-- end))
