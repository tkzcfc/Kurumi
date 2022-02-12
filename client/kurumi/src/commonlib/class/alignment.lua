-- @Author : fangcheng
-- @Date   : 2020-05-07 17:31:21
-- @remark : 用于节点对齐

local alignment = class("alignment")

alignment.LEFT 		= 0
alignment.CENTER	= 1
alignment.RIGHT 	= 2
alignment.TOP		= alignment.LEFT
alignment.BOTTOM 	= alignment.RIGHT

alignment.vertical  			= 0	-- 垂直
alignment.horizontal  			= 1	-- 水平
alignment.verticalHorizontal	= 2 -- 垂直与水平

local table_insert = table.insert
-- @brief 获取真实大小
local function getRealSize(node)
	local size = node:getContentSize()
	return cc.size(math.abs(size.width * node:getScaleX()), math.abs(size.height * node:getScaleY()))
end

-- @brief 设置节点X位置
local function setNodePositionX(node, value, realSize)
	local anchor = node:getAnchorPoint().x
	if node:getScaleX() < 0 then
		anchor = 1 - anchor
	end
	node:setPositionX(value + anchor * realSize.width)
end

-- @brief 设置节点Y位置
local function setNodePositionY(node, value, realSize)
	local anchor = node:getAnchorPoint().y
	if node:getScaleY() < 0 then
		anchor = 1 - anchor
	end
	node:setPositionY(value + anchor * realSize.height)
end


-----------------------------------------------

function alignment:ctor()
	self.elements = {}
	self.doLayoutElements = {}
	self.dataDirty = true
	self:setDirection(alignment.verticalHorizontal)
	self:setGravity(alignment.vertical, alignment.CENTER, 0, true)
	self:setGravity(alignment.horizontal, alignment.CENTER, 0)
	self:setElementInterval(alignment.verticalHorizontal, 0)
end

-- @brief 提交更改的数据
function alignment:submission()
	self.dataDirty = true
end

-- @brief 画布设置
function alignment:setCanvas(canvas)
	self.canvas = canvas
	self:submission()
end

-- @brief 设置元素
function alignment:setElements(elements)
	self.elements = elements or {}
	self:submission()
end

function alignment:addElement(element)
	self.elements[#self.elements + 1] = element
	self:submission()
end

function alignment:removeElement(element)
	for k,v in pairs(self.elements) do
		if element then
			table.remove(self.elements, k)
			break
		end
	end
	self:submission()
end

-- @brief 设置布局方向
function alignment:setDirection(direction)
	self.direction  = direction
	self:submission()
end

-- @brief 设置布局重力方向
-- @param direction 垂直|水平
-- @param gravityDir 重力方向
-- @param offset 偏移量
-- @param sameLine 是否对齐到同一条线
function alignment:setGravity(direction, gravityDir, offset, sameLine)
	if direction == alignment.vertical then
		self.verticalGravityDir 	= gravityDir
		self.verticalGravityOffset 	= offset
		self.verticalSameLine		= sameLine
	else
		self.horizontalGravityDir 	= gravityDir
		self.horizontalGravityOffset= offset
		self.horizontalSameLine		= sameLine
	end
	self:submission()
end

-- @brief 元素间隔
-- @param direction 垂直|水平
-- @param interval 元素间距
function alignment:setElementInterval(direction, interval)
	if direction == alignment.vertical then
		self.eleVerticalInterval = interval
	elseif direction == alignment.horizontal then
		self.eleHorizontalInterval = interval
	else
		self.eleVerticalInterval = interval
		self.eleHorizontalInterval = interval		
	end
	self:submission()
end

-- @brief 布局开始
function alignment:doLayout(force)

	if not self.dataDirty and not force then
		return
	end

	self.dataDirty = false

	if self.canvas == nil or self.elements == nil or #self.elements < 1 then
		return
	end

	self.doLayoutElements = {}
	for k,element in pairs(self.elements) do
		if element:isVisible() then
			table_insert(self.doLayoutElements, element)
		end
	end

	if #self.doLayoutElements < 1 then
		return
	end

	-- 计算元素真实大小
	local eleSizeArr = {}
	for k,v in ipairs(self.doLayoutElements) do
		eleSizeArr[k] = getRealSize(v)
	end

	if self.direction == alignment.vertical then
		if self.verticalSameLine then
			self:doLayoutVerticalSameLine(eleSizeArr)
		else
			self:doLayoutVertical(eleSizeArr)
		end
	elseif self.direction == alignment.horizontal then
		if self.horizontalSameLine then
			self:doLayoutHorizontalSameLine(eleSizeArr)
		else
			self:doLayoutHorizontal(eleSizeArr)
		end
	else
		if self.verticalSameLine then
			self:doLayoutVerticalSameLine(eleSizeArr)
		else
			self:doLayoutVertical(eleSizeArr)
		end
		if self.horizontalSameLine then
			self:doLayoutHorizontalSameLine(eleSizeArr)
		else
			self:doLayoutHorizontal(eleSizeArr)
		end
	end
end

-- @brief 垂直对齐
function alignment:doLayoutVertical(eleSizeArr)
	local canvasSize = self.canvas:getContentSize()
	local totalValue = (#self.doLayoutElements - 1) * self.eleVerticalInterval

	for k,v in ipairs(eleSizeArr) do
		totalValue = totalValue + v.height
	end

	local beginValue = 0
	if self.verticalGravityDir == alignment.TOP then
		beginValue = canvasSize.height - totalValue - self.verticalGravityOffset
	elseif self.verticalGravityDir == alignment.BOTTOM then
		beginValue = self.verticalGravityOffset
	else
		beginValue = canvasSize.height * 0.5 + self.verticalGravityOffset - totalValue * 0.5
	end

	for k,v in ipairs(self.doLayoutElements) do
		setNodePositionY(v, beginValue, eleSizeArr[k])
		beginValue = beginValue + eleSizeArr[k].height + self.eleVerticalInterval
	end
end


-- @brief 垂直对齐到同一条线
function alignment:doLayoutVerticalSameLine(eleSizeArr)
	local canvasSize = self.canvas:getContentSize()

	if self.verticalGravityDir == alignment.TOP then
		for k,v in ipairs(self.doLayoutElements) do
			setNodePositionY(v, canvasSize.height - eleSizeArr[k].height - self.verticalGravityOffset, eleSizeArr[k])
		end
	elseif self.verticalGravityDir == alignment.BOTTOM then
		for k,v in ipairs(self.doLayoutElements) do
			setNodePositionY(v, self.verticalGravityOffset, eleSizeArr[k])
		end
	else
		for k,v in ipairs(self.doLayoutElements) do
			setNodePositionY(v, canvasSize.height * 0.5 - eleSizeArr[k].height * 0.5 + self.verticalGravityOffset, eleSizeArr[k])
		end
	end
end

-- @brief 水平对齐
function alignment:doLayoutHorizontal(eleSizeArr)
	local canvasSize = self.canvas:getContentSize()
	local totalValue = (#self.doLayoutElements - 1) * self.eleHorizontalInterval

	for k,v in ipairs(eleSizeArr) do
		totalValue = totalValue + v.width
	end

	local beginValue = 0
	if self.horizontalGravityDir == alignment.RIGHT then
		beginValue = canvasSize.width - totalValue - self.horizontalGravityOffset
	elseif self.horizontalGravityDir == alignment.LEFT then
		beginValue = self.horizontalGravityOffset
	else
		beginValue = canvasSize.width * 0.5 + self.horizontalGravityOffset - totalValue * 0.5
	end

	for k,v in ipairs(self.doLayoutElements) do
		setNodePositionX(v, beginValue, eleSizeArr[k])
		beginValue = beginValue + eleSizeArr[k].width + self.eleHorizontalInterval
	end
end

-- @brief 水平对齐到同一条线
function alignment:doLayoutHorizontalSameLine(eleSizeArr)
	local canvasSize = self.canvas:getContentSize()

	if self.horizontalGravityDir == alignment.RIGHT then
		for k,v in ipairs(self.doLayoutElements) do
			setNodePositionX(v, canvasSize.width - eleSizeArr[k].width - self.horizontalGravityOffset, eleSizeArr[k])
		end
	elseif self.horizontalGravityDir == alignment.LEFT then
		for k,v in ipairs(self.doLayoutElements) do
			setNodePositionX(v, self.horizontalGravityOffset, eleSizeArr[k])
		end
	else
		for k,v in ipairs(self.doLayoutElements) do
			setNodePositionX(v, canvasSize.width * 0.5 - eleSizeArr[k].width * 0.5 + self.horizontalGravityOffset, eleSizeArr[k])
		end
	end
end

return alignment