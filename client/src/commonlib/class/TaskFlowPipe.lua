-- @Author: fangcheng
-- @Date  : 2020-06-02 11:35:41
-- @remark: 任务流管道

local PHASE = {
	FREE 	= 0,
	RUN 	= 1,
	FINISH  = 2,
	ERROR 	= 3,
}


local ENABLE_DEBUG = false
local sharedScheduler = cc.Director:getInstance():getScheduler()
local co_yield = coroutine.yield
local co_resume = coroutine.resume


if not __G__TRACKBACK__ then
	__G__TRACKBACK__ = function(msg)
	    local msg = debug.traceback(msg, 3)
	    print(msg)
	    return msg
	end
end

local function safeCall(func)
	xpcall(function() 
		func()
	end, __G__TRACKBACK__)
end





local TaskFlowPipe = class("TaskFlowPipe")

function TaskFlowPipe:ctor()
	self.tasks = {}
	self.phase = PHASE.FREE
end

-- @brief 添加任务
function TaskFlowPipe:pushTask(task)
	return self:insertTask(task)
end

-- @brief 插入任务
function TaskFlowPipe:insertTask(task, idx)
	assert(self.phase == PHASE.FREE)
	idx = idx or #self.tasks + 1
	idx = math.max(idx, 1)
	table.insert(self.tasks, idx, task)
	return self
end

-- @brief 开始执行
-- @param processCallback 执行进度回调
-- @param finishCallback 执行完成回调
-- @param errorCallback 错误回调
-- @param externalPower 是否外部调用 update 函数
function TaskFlowPipe:start(processCallback, finishCallback, errorCallback, externalPower)
	assert(self.phase == PHASE.FREE)

	self.phase 				= PHASE.RUN
	self.executeCount		= 0
	self.onProcessCallback 	= processCallback
	self.onFinishCallback 	= finishCallback
	self.onErrorCallback 	= errorCallback

	self.runCoroutine = coroutine.create(function()
		self:_doLogic()
	end)

	if not externalPower then
		self:_stopScheduler()
		self.scheduleHandler = sharedScheduler:scheduleScriptFunc(handler(self, self.update), 0, false)
	end
	return self
end

-- @brief update 函数，可由外部驱动
-- @param delta 间隔时间
function TaskFlowPipe:update(delta)
	if self.phase ~= PHASE.RUN then
		return
	end

	local ret, msg = co_resume(self.runCoroutine, delta)
	if not ret then
		com_log("TASK ERROR BEGIN **********************")
		com_log(msg)
		com_log("TASK ERROR END   **********************")

		self.phase = PHASE.ERROR
		self:_stopScheduler()

		if self.onErrorCallback then
			safeCall(function()
				self.onErrorCallback(msg, self)
			end)
		end

		self:done()
	end
end

-- @brief 执行完毕,进行清理工作
-- 		  可手动调用,视为中断任务流执行
function TaskFlowPipe:done()
	self:_stopScheduler()

	if self.phase == PHASE.ERROR or self.phase == PHASE.RUN then
		local curTask = self.curRunTask
		if curTask then
			curTask:abort(self.phase == PHASE.ERROR)
		end
	end

	self.tasks 			= {}
	self.phase 			= PHASE.FREE
	self.curRunTask 	= nil
	self.runCoroutine 	= nil
	self.executeCount 	= 0

	self.onProcessCallback = nil
	self.onFinishCallback  = nil
	self.onErrorCallback   = nil
end

-- @brief 获取当前正在执行的任务
function TaskFlowPipe:getCurRunTask()
	return self.curRunTask
end

-- @brief 任务挂起
-- @param fastMode 是否启用快速模式,快速模式下不进行进度更新
function TaskFlowPipe:yield(fastMode)
	if not fastMode then
		self:_updatePercent()
	end
	return co_yield()
end

------------------------------------------------------------public end------------------------------------------------------------

function TaskFlowPipe:_stopScheduler()
	if self.scheduleHandler then
		sharedScheduler:unscheduleScriptEntry(self.scheduleHandler)
		self.scheduleHandler = nil
	end
end

-- @brief 主逻辑
function TaskFlowPipe:_doLogic()
	self:yield()

	for i = 1, #self.tasks do
		local task = self.tasks[i]
		self.curRunTask = task
		task:run(self)
		self.executeCount = i
		self:yield()
	end
	self.curRunTask = nil

	self:yield(true)

	self.phase = PHASE.FINISH
	if self.onFinishCallback then
		safeCall(function() 
			self.onFinishCallback(self)
		end)
	end

	self:done()
end

-- @brief 进度更新
function TaskFlowPipe:_updatePercent()
	if self.onProcessCallback == nil then
		return
	end

	local total = #self.tasks
	if total <= 0 then
		self.onProcessCallback(1, 1, self)
		return
	end

	local cur = self.executeCount
	cur = math.min(cur, total)

	-- 任务全部执行完毕
	if self.executeCount >= total then
		self.onProcessCallback(1, 1, self)
		return
	end

	-- 任务执行进度(按任务数量来算)
	local taskPercent = cur / total

	-- 计算真实进度
	total, cur = 0, 0
	for k,task in pairs(self.tasks) do
		if self.executeCount > k - 1 then
			cur = cur + task.progressWeight
		elseif self.executeCount == k - 1 then
			cur = cur + math.min(task.progressWeight, task.curProgress)
		end
		total = total + task.progressWeight
	end

	-- 整体总进度(按任务进度权重来算，可视为总体真实进度)
	total = math.max(total, 1)
	local totalPercent = cur / total

	self.onProcessCallback(taskPercent, totalPercent, self)

	if ENABLE_DEBUG then
		com_log(taskPercent, totalPercent)
	end
end

return TaskFlowPipe