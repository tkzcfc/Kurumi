-- @Author : fangcheng
-- @Date   : 2020-07-18 10:59:38
-- @remark : 循环滚动列表

local PanZoomLayer = import(".PanZoomLayer")

local CycleListView = class("CycleListView", PanZoomLayer)

local VirtualNode = class("VirtualNode")

-- 水平方向定义
local HORIZONTAL = 0

-- 默认滚动速度
local kDefaultScrollSpeed = 1000

-- 默认翻页阈值,超过四分之一视为翻页
local kDefaultTurnPageThreshold = 0.25

local EventType = PanZoomLayer.EventType

local emptyLoadCellCall = function()
	return cc.Node:create()
end


function CycleListView:ctor(size)
	CycleListView.super.ctor(self, size)

	self.queFreeCell = {}
	self.arrAllCell = {}
	self.arrLogicNode = {}
	
	-- 滚动方向
	self:setDirection(HORIZONTAL)

	self.pageMode = false
	self:setZoomEnabled(false)
	self:setBoundCollisionEnabled(false)
	self:setDefaultScrollSpeed(kDefaultScrollSpeed)
	self:setDefaultScrollMaxTime(0.3)
	self:setTurnPageThreshold(kDefaultTurnPageThreshold)

	self:setOnLoadCellCallback(emptyLoadCellCall)
end

---------------------------------------------------- public ----------------------------------------------------

--@brief cell创建函数
function CycleListView:setOnLoadCellCallback(call)
	self.onLoadCellCallback = call
end

-- @brief cell复用函数
--		  当虚拟列表未开启时,此回调不会调用
function CycleListView:setOnReloadCellCallback(call)
	self.onReloadCellCallback = call
end

-- @brief 设置为虚拟列表(不可逆操作)
--		  默认不开启,即不使用cell复用,只做异步加载,当该选项开启后不能关闭
--		  元素不是很多时没必要使用cell复用
function CycleListView:setVirtualList()
	self.isVirtualList = true
end

-- @brief 设置为普通列表模式(不可逆操作),只能在 loadList 调用之前调用
function CycleListView:setNormalList()
	if self.loadListTag then error("只能在'loadList'调用之前调用") end
	self.isNormalList = true
end

-- @brief 设置cell数量
function CycleListView:setCellCount(count)
	self.cellCount = count
end

-- @brief 设置cell大小
function CycleListView:setCellSize(size)
	self.cellSize = size
end

-- @brief 设置为翻页模式(不可逆操作)
function CycleListView:setPageMode()
	self.pageMode = true
	self:setCellSize(self:getContentSize())
	-- 翻页模式禁用惯性
	self:setInertiaScrollEnabled(false)
end

-- @brief 设置默认滚动速度
function CycleListView:setDefaultScrollSpeed(speed)
	self.defaultScrollSpeed = speed
end

-- @brief 设置默认滚动最大时间
function CycleListView:setDefaultScrollMaxTime(time)
	self.defaultScrollMaxTime = time
end

-- @brief 设置翻页的阈值
--		  按百分比设置,当触摸时cell的移动距离超过阈值则进入下一页,所以这个值必须小于0.5
--		  如果翻页模式为水平翻页,则阈值为宽度*value
--		  如果翻页模式为垂直翻页,则阈值为高度*value
function CycleListView:setTurnPageThreshold(value)
	if value > 0.5 then value = 0.5	end
	if value < 0.0 then value = 0.1 end
	self.turnPageThreshold = value
end

-- @brief 滚动到某个页面
-- @param index 下标从1开始
-- @param duration 持续时间
function CycleListView:scrollToPage(index, duration)
	local offsetValue = self:scrollToPageDistance(index)
	if duration == nil then
		duration = math.abs(offsetValue / self.defaultScrollSpeed)
		if duration > self.defaultScrollMaxTime then
			duration = self.defaultScrollMaxTime
		end
	end

	if self.direction == HORIZONTAL then
		self:setContentOffsetInDuration(cc.p(-offsetValue, 0), duration)
	else
		self:setContentOffsetInDuration(cc.p(0, -offsetValue), duration)
	end
end

-- @brief 滚动到某个页面需要偏移的值
-- @param index 下标从1开始
function CycleListView:scrollToPageDistance(index)
	local offsetValue = 0
	local curPageIndex = self:getCurrentPageIndex()

	if curPageIndex ~= index then
		-- 普通列表
		if self.isNormalList then
			local diffCount = curPageIndex - index

			offsetValue = self:getCellOffsetInView(curPageIndex)
			if self.direction == HORIZONTAL then
				offsetValue = offsetValue - diffCount * self.cellSize.width
			else
				offsetValue = offsetValue - diffCount * self.cellSize.height			
			end
		-- 虚拟列表
		else
			-- 计算滚动到目标界面最小距离
			local stepCount = 0
			local curIndex = curPageIndex
			repeat
				stepCount = stepCount + 1
				curIndex = self:step(curIndex)
				if curIndex == index then
					break
				end
			until(false)

			local diffCount = 0
			curIndex = curPageIndex
			repeat
				diffCount = diffCount + 1
				curIndex = self:diff(curIndex)
				if curIndex == index then
					break
				end
			until(false)

			offsetValue = self:getCellOffsetInView(curPageIndex)

			local cellValue = self.cellSize.height
			if self.direction == HORIZONTAL then
				cellValue = self.cellSize.width
			end

			-- 正向滚动移动距离最小
			if stepCount < diffCount then
				offsetValue = offsetValue + stepCount * cellValue		
			-- 逆向滚动移动距离最小
			else
				offsetValue = offsetValue - diffCount * cellValue
			end
		end
	else
		offsetValue = self:getCellOffsetInView(index)
	end
	
	return offsetValue
end

-- @brief 滚动到下一页
-- @param duration 动画时间
function CycleListView:scrollToNextPage(duration)
	local curPageIndex = self:getCurrentPageIndex()
	self:scrollToPage(self:step(curPageIndex), duration)
end

-- @brief 滚动到上一页
-- @param duration 动画时间
function CycleListView:scrollToPrePage(duration)
	local curPageIndex = self:getCurrentPageIndex()
	self:scrollToPage(self:diff(curPageIndex), duration)
end

-- @brief 获取当前页面下标
function CycleListView:getCurrentPageIndex()
	-- 视口大小
	local lsize = self:getContentSize()
	-- 偏移量
	local offsetx, offsety = self.container:getPosition()

	-- 计算视口当前显示的node
	local viewCellIndex, nodePosValue = -1, 0
	for k, node in pairs(self.arrLogicNode) do
		if self.direction == HORIZONTAL then
			local curValue = node:getPositionX() + offsetx
			if curValue >= 0 and curValue < lsize.width then
				viewCellIndex = k
				nodePosValue = curValue
				break
			end
		else
			local curValue = node:getPositionY() + offsety
			if curValue>= 0 and curValue < lsize.height then
				viewCellIndex = k
				nodePosValue = curValue
				break
			end
		end
	end

	-- 正常逻辑不会出现找不到的情况
	assert(viewCellIndex > 0)

	return viewCellIndex, nodePosValue
end

-- @brief 获取某个cell相对于视口的偏移值
-- @param index cell的下标 从1开始
function CycleListView:getCellOffsetInView(index)
	-- 视口大小
	local lsize = self:getContentSize()
	-- 偏移量
	local offsetx, offsety = self.container:getPosition()

	local node = self.arrLogicNode[index]

	if not node then
		return 0
	end

	if self.direction == HORIZONTAL then
		return node:getPositionX() + offsetx
	else
		return node:getPositionY() + offsety
	end
end

-- @brief 加载循环列表，需要外部手动调用才能完成列表的加载,在设置好所有参数之后最后调用
-- @param isFreeze 是否保持当前滑动位置
function CycleListView:loadList(isFreeze)
	self:stoppedAnimatedScroll()

	local oldvalue
	if isFreeze then
		if self.loadListTag then
			oldvalue = {}
			oldvalue.isRunCycle = self.isRunCycle
			oldvalue.cellCount = self.cellCount
		end
	else
		self:resetTransform()
	end

	self.loadListTag = true

	-- 移除多余的逻辑节点
	for k, v in pairs(self.arrLogicNode) do
		v:onDestroy()
	end
	self.arrLogicNode = {}
	-- for i = 1, #self.arrLogicNode - self.cellCount do
	-- 	local node = table.remove(self.arrLogicNode)
	-- 	node:onDestroy()
	-- end
	-- 添加缺少的逻辑节点
	for i = #self.arrLogicNode + 1, self.cellCount do
		local node = VirtualNode.new(self, i)
		table.insert(self.arrLogicNode, node)
	end

	-- 逻辑节点初始化
	for i = 1, self.cellCount do
		local node = self.arrLogicNode[i]
		node:setIndex(i)
		if self.direction == HORIZONTAL then
			node:setPositionX((i - 1) * self.cellSize.width)
		else
			node:setPositionY((i - 1) * self.cellSize.height)			
		end
	end

	if self.isNormalList then
		self.isRunCycle = false
	else
		-- 标记当前运行循环列表模式
		self.isRunCycle = self:canRunWithCycle()
	end

	if self.isRunCycle then
		self:setBoundCollisionEnabled(false)
	else
		self:setBoundCollisionEnabled(true)
		local viewSize = self:getContentSize()
		if self.direction == HORIZONTAL then
			local width = math.max(viewSize.width, self.cellCount * self.cellSize.width)
			self:setContainerSize(cc.size(width, viewSize.height))
		else
			local height = math.max(viewSize.height, self.cellCount * self.cellSize.height)
			self:setContainerSize(cc.size(viewSize.width, height))
		end

		if oldvalue and oldvalue.isRunCycle then
			self:resetTransform()
		end
	end

	self:onChangePosition(0, 0)
end


-- @brief 获取某个cell渲染节点
-- @param index cell的下标 从1开始
function CycleListView:getCellRender(index)
	local node = self.arrLogicNode[index]
	if node then
		return node:getRender()
	end
end

---------------------------------------------------- private ----------------------------------------------------
function CycleListView:onTouchesBegan(point)
	CycleListView.super.onTouchesBegan(self, point)
	if self.pageMode then
		self.touchBeganPageIndex = self:getCurrentPageIndex()
	end
	self.onTouchBeginHoldTag = self.isHolding
end

function CycleListView:onTouchesEnded(point)
	CycleListView.super.onTouchesEnded(self, point)

	if self.isHolding and self.onTouchBeginHoldTag then
		return
	end

	if self.pageMode and #self.touches <= 0 then
		-- 视口大小
		local lsize = self:getContentSize()
		local viewCellIndex, cellPosValue = self:getCurrentPageIndex()

		if viewCellIndex > 0 then
			local lvalue, rvalue

			if self.direction == HORIZONTAL then
				lvalue = lsize.width * self.turnPageThreshold
				rvalue = lsize.width * (1 - self.turnPageThreshold)
			else
				lvalue = lsize.height * self.turnPageThreshold
				rvalue = lsize.height * (1 - self.turnPageThreshold)
			end

			if cellPosValue <= lvalue then
				self:scrollToPage(viewCellIndex)
			elseif rvalue <= cellPosValue then
				self:scrollToPage(self:diff(viewCellIndex))
			else
				if self.touchBeganPageIndex == viewCellIndex then
					self:scrollToPage(self:diff(viewCellIndex))
				else
					self:scrollToPage(viewCellIndex)
				end
			end
		end
	end
end

-- @brief 是否能运行循环滚动列表
function CycleListView:canRunWithCycle()
	local viewSize = self:getContentSize()
	-- 间距
	local spaceValue = self.cellSize.width
	-- 边框最大值
	local boundMaxValue = viewSize.width

	if self.direction ~= HORIZONTAL then 
		boundMaxValue = viewSize.height
		spaceValue 	  = self.cellSize.height
	end

	local total = self.cellCount * spaceValue
	if total - spaceValue <= boundMaxValue or self.cellCount < 2 then
		return false
	end
	return true
end

function CycleListView:_updateCellPos_Cycle()
	local viewSize = self:getContentSize()
	-- 间距
	local spaceValue = self.cellSize.width
	-- 边框最小值
	local boundMinValue = 0
	-- 边框最大值
	local boundMaxValue = viewSize.width

	if self.direction ~= HORIZONTAL then 
		boundMaxValue = viewSize.height
		spaceValue 	  = self.cellSize.height
	end

	local total = self.cellCount * spaceValue
	if total - spaceValue <= boundMaxValue or self.cellCount < 2 then
		return
	end

	-- 隐藏所有cell
	for k,v in pairs(self.arrLogicNode) do
		v:setVisible(false)
	end

	local offset = math.abs(self.offsetValue) % total
	local curPosValue = 0
	local curMinValue = 0
	local curIndex

	-- 寻找起始下标
	if self.offsetValue <= 0 then
		curIndex = 0
		curMinValue = -offset

		local tmp
		for i = 1, self.cellCount do
			tmp = curMinValue + spaceValue
			if tmp < boundMinValue or curMinValue > boundMaxValue then
			else
				curIndex = i
				break
			end
			curMinValue = tmp
		end

		local count = curIndex - 1
		-- 起始下标偏移量
		local beginOffset = self.offsetValue + offset
		-- 起始坐标
		curPosValue = count * spaceValue - beginOffset
	else
		curIndex = self:diff(1)
		curMinValue = offset

		local tag, count, tmp = false, 0
		for i = 1, self.cellCount do
			tmp = curMinValue - spaceValue
			if curMinValue < boundMinValue or tmp > boundMaxValue then
				if tag then
					count = i - 1
					curIndex = self:step(curIndex)
					break					
				end
			else
				tag = true
			end
			curIndex = self:diff(curIndex)
			curMinValue = tmp
		end

		if count == 0 then
			count = self.cellCount
			curIndex = 1
		end

		-- 起始下标偏移量
		local beginOffset = self.offsetValue - offset
		-- 起始坐标
		curPosValue = -count * spaceValue - beginOffset
	end

	for i = 1, self.cellCount do
		local tmp = curMinValue + spaceValue
		if tmp < boundMinValue or curMinValue > boundMaxValue then
			break
		else
			if self.direction == HORIZONTAL then
				self.arrLogicNode[curIndex]:setPositionX(curPosValue)
			else
				self.arrLogicNode[curIndex]:setPositionY(curPosValue)
			end
			self.arrLogicNode[curIndex]:setVisible(true)
			curPosValue = curPosValue + spaceValue
			curIndex = self:step(curIndex)
		end
		curMinValue = tmp
	end


	-- 事件回调
	for k,node in pairs(self.arrLogicNode) do
		if not node:isVisible() then
			node:onHide()
		end
	end
	for k,node in pairs(self.arrLogicNode) do
		if node:isVisible() then
			node:onShow()
		end
	end
end

function CycleListView:_updateCellPos_Normal()
	local viewSize = self:getContentSize()
	-- 边框最小值
	local boundMinValue = -self.offsetValue
	-- 边框最大值
	local boundMaxValue
	if self.direction == HORIZONTAL then
		boundMinValue = boundMinValue - self.cellSize.width
		boundMaxValue = boundMinValue + viewSize.width + self.cellSize.width
	else
		boundMinValue = boundMinValue - self.cellSize.height
		boundMaxValue = boundMinValue + viewSize.height + self.cellSize.height
	end

	local curValue, curNode
	for i = 1, self.cellCount do
		curNode = self.arrLogicNode[i]
		if self.direction == HORIZONTAL then
			curValue = curNode.x
		else
			curValue = curNode.y
		end
		if curValue < boundMinValue or curValue > boundMaxValue then
			curNode:onHide()
		else
			curNode:onShow()
		end
	end
end

function CycleListView:step(i)
	i = i + 1
	if i > self.cellCount then
		i = 1
	end
	return i
end

function CycleListView:diff(i)
	i = i - 1
	if i < 1 then
		i = self.cellCount
	end
	return i
end

function CycleListView:onChangePosition(curx, cury)
	CycleListView.super.onChangePosition(self, curx, cury)
	if self.direction == HORIZONTAL then
		self.offsetValue = self.container:getPositionX()
	else
		self.offsetValue = self.container:getPositionY()
	end
	if self.isRunCycle then
		self:_updateCellPos_Cycle()
	else
		self:_updateCellPos_Normal()
	end
end

function CycleListView:allocCell(index)
	if #self.queFreeCell <= 0 then
		local cell = self.onLoadCellCallback(index)
		if cell then
			cell:retain()
			self:addUnit(cell)
		else
			error("返回值不能为空")
		end
		table.insert(self.arrAllCell, cell)
		return cell, true
	end

	local cell = table.remove(self.queFreeCell)
	self.onReloadCellCallback(cell, index)
	self:addUnit(cell)
	return cell, false
end

function CycleListView:freeCell(cell)
	cell:removeFromParent()
	table.insert(self.queFreeCell, cell)
end

function CycleListView:onCleanup()
	for k,v in pairs(self.arrLogicNode) do
		v:onDestroy()
	end

	for k,v in pairs(self.arrAllCell) do
		-- print("release", k)
		v:release()
	end
	self.arrAllCell = {}
	self.queFreeCell = {}
	self.arrLogicNode = {}
end




------------------------------- VirtualNode begin -------------------------------
function VirtualNode:ctor(listView, index)
	self.x, self.y = 0, 0
	self.listView = listView
	self.index = index
	self.visible = true
end

-- @brief 设置当前下标,仅用于校验之前的逻辑是否正确
function VirtualNode:setIndex(index)
	if self.index ~= index then error("self.index ######") end
end

-- @brief 逻辑节点位置设置
function VirtualNode:setPositionX(x)
	self.x = x
	if self.render then self.render:setPositionX(x) end
end

-- @brief 逻辑节点位置设置
function VirtualNode:setPositionY(y)
	self.y = y
	if self.render then self.render:setPositionY(y) end
end

-- @brief 逻辑节点位置获取
function VirtualNode:getPositionX(x)
	return self.x
end

-- @brief 逻辑节点位置获取
function VirtualNode:getPositionY(y)
	return self.y
end

-- @brief 逻辑节点显示隐藏标记
function VirtualNode:setVisible(visible)
	self.visible = visible
end

-- @brief 逻辑节点显示隐藏标记
function VirtualNode:isVisible()
	return self.visible
end

-- @brief 获取渲染节点
function VirtualNode:getRender()
	return self.render
end

-- @brief 逻辑节点显示
function VirtualNode:onShow()
	if self.render == nil then
		local render, isNew = self.listView:allocCell(self.index)
		self.render = render
		self:setPositionX(self.x)
		self:setPositionY(self.y)

		if isNew then
			self.listView:dispatchEvent(EventType.EVENT_NEW_CELL_CREATE)
		end
	end
	self.render:setVisible(true)
end

-- @brief 逻辑节点隐藏
function VirtualNode:onHide()
	if self.render and self.listView.isVirtualList then
		self.listView:freeCell(self.render)
		self.render = nil
	end
	if self.render then self.render:setVisible(false) end
end

-- @brief 逻辑节点销毁
function VirtualNode:onDestroy()
	self:onHide()
	if self.render then
		self.render:removeFromParent()
		self.render = nil
	end
	self.listView = nil
end

------------------------------- VirtualNode end -------------------------------


return CycleListView
