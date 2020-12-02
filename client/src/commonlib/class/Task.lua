-- @Author : fangcheng
-- @Date   : 2020-06-02 14:46:06
-- @remark : 任务基类

local Task = class("Task")

-- 总进度权重
Task.progressWeight = 1
-- 当前进度
Task.curProgress = 0

-- @brief 任务执行时调用该函数
-- @param taskFlowPipe 执行该任务的任务流管线
function Task:run(taskFlowPipe)
end

-- @brief 执行该任务时被强制中断调用此函数,主要用来为未完成任务做清理工作
-- @param isError 	为true表示是在执行本任务函数run中发生错误导致中断的
--					为false则表明在任务执行中被强制调用done函数中断
function Task:abort(isError)
end

-- @brief 任务进度百分比
function Task:getPercent()
	return self.curProgress / self.progressWeight
end

-- @brief 通过百分比设置当前任务进度
function Task:toPercent(percent)
	self.curProgress = math.min(percent, 1.0) * self.progressWeight
end

return Task
