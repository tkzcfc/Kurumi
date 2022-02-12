-- @Author : fangcheng
-- @Date   : 2020-07-12 18:32:16
-- @remark : 平移缩放图层

local radian_30 = math.pi / 6
local kMaxAccelerationFactor = 1
local kMinAccelerationFactor = 0.01


local function lerp(p1, p2, alpha)
	return p1 * (1 - alpha) + p2 * alpha
end

local function max(a, b)
	if a > b then return a end
	return b
end

local function min(a, b)
	if a < b then return a end
	return b
end

local table_remove = table.remove
local fabs = math.abs


local EventType =
{
	EVENT_SCROLLING = 1,		-- 滚动事件
	EVENT_AUTOSCROLL_BEGAN = 2,	-- 自动滚动开始
	EVENT_AUTOSCROLL_ENDED = 3,	-- 自动滚动结束
	EVENT_NEW_CELL_CREATE  = 4,	-- 循环列表事件-有新的cell被创建
}


-- 水平方向定义
local HORIZONTAL = 0
-- 垂直方向定义
local VERTICAL 	 = 1
-- 垂直&水平方向定义
local VERTICAL_HORIZONTAL = 2


local PanZoomLayer = class("PanZoomLayer", function()
	return ccui.Layout:create()
end)

PanZoomLayer.EventType = EventType

function PanZoomLayer:ctor(size)
	assert(size)

	self.touches 		  = {}
	self.deltaSum 		  = cc.p(0, 0)
	self.prevDeltaPoint   = cc.p(0, 0)
	self.isHolding 		  = false
	self.accelerationFactor = 0.0

	self.bounceRangeX = 0
	self.bounceRangeY = 0
	self.panBoundsRect = cc.rect(0, 0, 0, 0)

	-- 最大/小缩放系数
	self.maxScale = 2.5
	self.minScale = 0.3
	-- 缩放灵敏度
	self:setZoomFactor(1.0)

	self:setContentSize(size)
	-- 裁剪开启
	self:setClippingEnabled(true)

	-- touch layer
	self.container = cc.Layer:create()
	self.container:setAnchorPoint(cc.p(0, 0))
	self:addChild(self.container)

	-- 设置容器大小
	self:setContainerSize(size)
	-- 滚动方向
	self:setDirection(VERTICAL_HORIZONTAL)
	-- 惯性启用
	self:setInertiaScrollEnabled(true)
	-- 默认不启用缩放
	self:setZoomEnabled(false)
	-- 默认启用边界碰撞
	self:setBoundCollisionEnabled(true)
	-- 默认不启用回弹
	self:setBounceable(false)
	-- 设置回弹范围
	self:setBounceRange(100)
	-- 设置回弹系数
	self:setBounceFactor(0.5)
	-- 默认吞没事件
	self:setSwallowTouches(true)

	if self.enableNodeEvents then
		self:enableNodeEvents()
	else
		self:setNodeEventEnabled()
	end

	self:onUpdate(handler(self, self.update))
end

function PanZoomLayer:onEnter()
	self:_enableTouch()
end

function PanZoomLayer:onExit()
	self:_disenableTouch()
	self.touches = {}
end

--@brief 添加子节点到容器中
function PanZoomLayer:addUnit(u)
	self.container:addChild(u)
end

--@brief 移除容器所有
function PanZoomLayer:removeAllUnit()
	self.container:removeAllChildren()
end

--@brief 设置容器大小
function PanZoomLayer:setContainerSize(size)
	self.container:setContentSize(size)
	self.containerSize = size
	self:_updateBoundsRect(size)
end

--@brief 屏蔽触摸事件
function PanZoomLayer:holding()
	self.isHolding = true
end

--@brief 启用触摸事件
function PanZoomLayer:unHolding()
	self.isHolding = false
end

--@brief 最大缩放系值
function PanZoomLayer:setMaxScale(value)
	self.maxScale = value
end

--@brief 最小缩放值
function PanZoomLayer:setMinScale(value)
	self.minScale = value
end

--@brief 是否启用缩放功能
function PanZoomLayer:setZoomEnabled(enable)
	self.zoomEnable = enable
end

function PanZoomLayer:isZoomEnabled()
	return self.zoomEnable
end

--@brief 是否启用边界碰撞
function PanZoomLayer:setBoundCollisionEnabled(enable)
	self.boundCollisionEnable = enable
end

function PanZoomLayer:isBoundCollisionEnabled()
	return self.boundCollisionEnable
end

-- @brief 是否启用回弹
function PanZoomLayer:setBounceable(enable)
	self.bounceable = enable
end

function PanZoomLayer:isBounceable()
	return self.bounceable
end

-- @brief 设置回弹范围
function PanZoomLayer:setBounceRange(value, yValue)
	yValue = yValue or value

	self.bounceRangeX = value
	self.bounceRangeY = yValue

	self.panBoundsRect_SB = cc.rect(
		self.panBoundsRect.x - value,
		self.panBoundsRect.y - yValue,
		self.panBoundsRect.width + value * 2,
		self.panBoundsRect.height + yValue * 2
		)
end

-- @brief 设置回弹系数
function PanZoomLayer:setBounceFactor(value)
	self.bounceFactor = value
end

--@brief 设置容器缩放
--@param viewportAnchor : 相对于视口的缩放锚点
function PanZoomLayer:setContainerZoom(zoom, viewportAnchor)
	if not viewportAnchor then
		viewportAnchor = cc.p(0.5, 0.5)
	end

	local lsize = self:getContentSize()
	viewportAnchor.x = viewportAnchor.x * lsize.width
	viewportAnchor.y = viewportAnchor.y * lsize.height

	self:_setContainerZoomPos(zoom, viewportAnchor)
end

--@brief 设置容器位置
function PanZoomLayer:setContainerPosition(posx, posy)
	local x, y = self.container:getPosition()
	self:onChangePosition(posx - x, posy - y)
end

--@brief 设置碰撞矩形原点(默认0,0)
function PanZoomLayer:setBoundsRectOrigin(oringin)
	self.boundsRectOrigin = oringin
	local size = self.containerSize
	local curScale = self.container:getScale()
	self:_updateBoundsRect(cc.size(size.width * curScale, size.height * curScale))
end

--@brief 位置数据重置
function PanZoomLayer:resetTransform()
	self.container:setScale(1)
	self.container:setPosition(0, 0)
end

--@brief 设置缩放灵敏度
function PanZoomLayer:setZoomFactor(value)
	self.zoomFactor = value
end

function PanZoomLayer:getZoomFactor(value)
	return self.zoomFactor
end

--@brief 惯性启用
function PanZoomLayer:setInertiaScrollEnabled(enable)
	self.inertiaScrollEnabled = enable
end

function PanZoomLayer:isInertiaScrollEnabled()
	return self.inertiaScrollEnabled
end

-- @brief 设置容器滚动偏移
-- @param offset 偏移量
-- @param duration 动画持续时间
function PanZoomLayer:setContentOffsetInDuration(offset, duration)
	local curPosition = cc.p(self.container:getPosition())
	self:performedAnimatedScroll(cc.pAdd(curPosition, offset), duration)
end

-- @brief 获取容器滚动偏移
function PanZoomLayer:getContentOffset()
	return cc.p(self.container:getPosition())
end

-- @brief 开启容器滚动逻辑
-- @param position 滚动的目标位置
-- @param duration 动画持续时间
function PanZoomLayer:performedAnimatedScroll(position, duration)
	self:stoppedAnimatedScroll()

	if duration and duration < 0 then
		duration = -duration
	end

	if duration == nil or duration <= 0 then
		self:setContainerPosition(position.x, position.y)
		self:dispatchEvent(EventType.EVENT_AUTOSCROLL_ENDED)
		return
	end

	local curPosition = cc.p(self.container:getPosition())
	local time = 0
	self.container:scheduleUpdateWithPriorityLua(function(dt)
		time = time + dt
		local percent = time / duration
		if percent >= 1.0 then
			self:setContainerPosition(position.x, position.y)
			self:stoppedAnimatedScroll()
			self:dispatchEvent(EventType.EVENT_AUTOSCROLL_ENDED)
		else
			if self.easeFunc then
				percent = self.easeFunc(percent)
			end
			local posx = lerp(curPosition.x, position.x, percent)
			local posy = lerp(curPosition.y, position.y, percent)
			self:setContainerPosition(posx, posy)
		end
	end, 0)

	self:dispatchEvent(EventType.EVENT_AUTOSCROLL_BEGAN)
end

-- @brief 停止滚动逻辑
function PanZoomLayer:stoppedAnimatedScroll()
	self.container:unscheduleUpdate()
end

-- @brief 事件派发
function PanZoomLayer:dispatchEvent(eventType)
	if self.onEventCallback then
		self.onEventCallback(eventType)
	end
end

-- @brief 设置事件派发订阅者
function PanZoomLayer:setEventListener(listener)
	self.onEventCallback = listener
end

-- @brief 设置动画缓动函数
function PanZoomLayer:setAnimationEaseFunc(func)
	self.easeFunc = func
end

-- @brief 设置滚动方向
-- @param value 0水平 1垂直 2垂直&水平
function PanZoomLayer:setDirection(value)
	self.direction = value
end

-- @brief 是否吞噬触摸
function PanZoomLayer:setSwallowTouches(value)
	self.swallowTouch = value
	if self.touchListener then
		self.touchListener:setSwallowTouches(value)
	end
end

--------------------------------------------------------- private ---------------------------------------------------------

function PanZoomLayer:selfVisible(node)
	if node == nil then return true end
	
	if node:isVisible() then
		return self:selfVisible(node:getParent())
	end
	return false
end

function PanZoomLayer:_enableTouch()
	self:_disenableTouch()

	local listener = cc.EventListenerTouchOneByOne:create()
	listener:setSwallowTouches(self.swallowTouch)

	listener:registerScriptHandler(function(touch, event)
		if #self.touches == 1 and not self.zoomEnable then
			return false
		end

		if not self:selfVisible(self) then
			return false
		end

		local location = self:getParent():convertToNodeSpace(touch:getLocation())
		if cc.rectContainsPoint(self:getBoundingBox(), location) then
			self:onTouchesBegan(self:_convertTouch(touch))
	    	return true
		end
	end, cc.Handler.EVENT_TOUCH_BEGAN)

	listener:registerScriptHandler(function(touch, event)
		self:onTouchesMoved(self:_convertTouch(touch))
	end, cc.Handler.EVENT_TOUCH_MOVED)

	listener:registerScriptHandler(function(touch, event)
		self:onTouchesEnded(self:_convertTouch(touch))
	end, cc.Handler.EVENT_TOUCH_ENDED)

	listener:registerScriptHandler(function(touch, event)
		self:onTouchesEnded(self:_convertTouch(touch))
	end, cc.Handler.EVENT_TOUCH_CANCELLED)

	self.container:getEventDispatcher():addEventListenerWithSceneGraphPriority(listener, self.container)
	self.touchListener = listener
end

function PanZoomLayer:_convertTouch(touch)
	local point = self:convertToNodeSpace(touch:getLocation())
	point.id = touch:getId()
	return point
end

function PanZoomLayer:_disenableTouch()
	if self.touchListener then
		self:getEventDispatcher():removeEventListener(self.touchListener)
		self.touchListener = nil
	end
end

function PanZoomLayer:update(dt)
	if not self.inertiaScrollEnabled then
		return
	end

	if self.accelerationFactor > kMinAccelerationFactor then
		self.accelerationFactor = self.accelerationFactor - (self.accelerationFactor * dt * 4)
	else
		self.accelerationFactor = 0
		return
	end

	if #self.touches == 0 then
		local adderX = self.deltaSum.x * self.accelerationFactor
		local adderY = self.deltaSum.y * self.accelerationFactor

		if self:checkSpringback() then
			self.accelerationFactor = 0
			self:doSpringback()
		else
			self:onChangePosition(adderX, adderY)
			if fabs(adderX) < 0.6 and fabs(adderY) < 0.6 then
				self.accelerationFactor = 0
			end
		end
	end
end

function PanZoomLayer:onTouchesBegan(point)
	if self.isHolding then
		return
	end

	point.previousPoint = cc.p(point.x, point.y)
	self.touches[#self.touches + 1] = point

	self.deltaSum = cc.p(0, 0)
	self.accelerationFactor = 0

	self:stoppedAnimatedScroll()
end

function PanZoomLayer:onTouchesMoved(point)
	if self.isHolding then
		return
	end

	for _, t in pairs(self.touches) do
		if point.id == t.id then
			t.previousPoint = cc.p(t.x, t.y)
			t.x, t.y = point.x, point.y
		end
	end

	if #self.touches == 1 then
		local touch = self.touches[1]

		local deltaPosition = cc.p(touch.x - touch.previousPoint.x, touch.y - touch.previousPoint.y)

		if self.direction == HORIZONTAL then deltaPosition.y = 0 end
		if self.direction == VERTICAL then deltaPosition.x = 0 end

		if self.bounceable then
			local ix, iy, ax, ay = self:_containerOffsetRange(false)
			local curx, cury = self.container:getPosition()
			if curx < ix or curx > ax then
				deltaPosition.x = deltaPosition.x * self.bounceFactor
			end
			if cury < iy or cury > ay then
				deltaPosition.y = deltaPosition.y * self.bounceFactor
			end
		end

		self:onChangePosition(deltaPosition.x, deltaPosition.y)

		local prevAngle = cc.pToAngleSelf(self.prevDeltaPoint)
		local angle = cc.pToAngleSelf(deltaPosition)
		if fabs( prevAngle - angle ) <= radian_30 then
			self.deltaSum = cc.p( 0, 0 )
		end

		self.prevDeltaPoint = deltaPosition
		
		self.deltaSum.x = self.deltaSum.x + deltaPosition.x
		self.deltaSum.y = self.deltaSum.y + deltaPosition.y

		if self.inertiaScrollEnabled then
			if self.accelerationFactor < kMaxAccelerationFactor then
				self.accelerationFactor = self.accelerationFactor + cc.pGetLength(self.deltaSum) / 100
			end
			if self.accelerationFactor > kMaxAccelerationFactor then
				self.accelerationFactor = kMaxAccelerationFactor
			end
		end
	elseif #self.touches == 2 then
		if not self.zoomEnable then
			return
		end

		local touch1 = self.touches[1]
		local touch2 = self.touches[2]

		local prevPosTouch1 = touch1.previousPoint
		local prevPosTouch2 = touch2.previousPoint

		local curDistance = cc.pGetDistance(touch1, touch2)
		local preDistance = cc.pGetDistance(prevPosTouch1, prevPosTouch2)

		-- 计算新的缩放值
		local prevScale = self.container:getScale()
		local curScale  = prevScale * curDistance / preDistance

		curScale = lerp(prevScale, curScale, self.zoomFactor)

		-- 计算焦点坐标
		local midPoint = cc.pMidpoint(touch1, touch2)
		-- 进行缩放
		self:_setContainerZoomPos(curScale, midPoint)
	end
end

function PanZoomLayer:onTouchesEnded(point)
	for k, t in pairs(self.touches) do
		if point.id == t.id then
			table_remove(self.touches, k)
			break
		end
	end
	
	if self.isHolding then
		return
	end

	if #self.touches == 0 then
		self:doSpringback()
	end
end

-- @brief 检测是否需要回弹
function PanZoomLayer:checkSpringback()
	if not self.boundCollisionEnable then return false end
	if not self.bounceable then return false end

	local ix, iy, ax, ay = self:_containerOffsetRange(false)
	local curx, cury = self.container:getPosition()

	local runTag = false
	local tox, toy = curx, cury
	if curx < ix or curx > ax or cury < iy or cury > ay then
		runTag = true
	end

	if curx < ix then tox = ix end
	if curx > ax then tox = ax end
	if cury < iy then toy = iy end
	if cury > ay then toy = ay end

	return runTag, tox, toy
end

-- @brief 开始回弹逻辑
function PanZoomLayer:doSpringback()
	local runTag, tox, toy = self:checkSpringback()
	if runTag then
		self:performedAnimatedScroll(cc.p(tox, toy), 0.15)
	end
end

-- @brief 设置容器缩放
-- @param zoom 缩放值
-- @param pos 容器坐标点(缩放的锚点)
function PanZoomLayer:_setContainerZoomPos(zoom, pos)
	local realCurPosLayer1 = self.container:convertToNodeSpace(self:convertToWorldSpace(pos))

	self:onChangeScale(zoom)

	local realCurPosLayer2 = self.container:convertToNodeSpace(self:convertToWorldSpace(pos))

	local deltaX = realCurPosLayer2.x - realCurPosLayer1.x
	local deltaY = realCurPosLayer2.y - realCurPosLayer1.y
	local curScale  = self.container:getScale()
	self:onChangePosition(deltaX * curScale, deltaY * curScale)
end

-- @brief 更新碰撞区域
function PanZoomLayer:_updateBoundsRect(size)
	local curSize = self:getContentSize()

	local maxW = math.max(curSize.width, size.width)
	local maxH = math.max(curSize.height, size.height)
	local x = curSize.width - maxW
	local y = curSize.height - maxH

	if self.boundsRectOrigin then
		self.panBoundsRect = cc.rect(self.boundsRectOrigin.x, self.boundsRectOrigin.y, size.width - x, size.height - y)
	else
		self.panBoundsRect = cc.rect(x, y, size.width - x, size.height - y)
	end
	self:setBounceRange(self.bounceRangeX, self.bounceRangeY)
end

-- @brief 获取offset范围
-- @param isSpringback 是否是回弹范围
function PanZoomLayer:_containerOffsetRange(isSpringback)
	local scale = self.container:getScale()
	local size  = self.containerSize

	local rect = self.panBoundsRect
	if self.bounceable and isSpringback then
		rect = self.panBoundsRect_SB
	end

    local min_x = cc.rectGetMinX(rect)
    local max_x = cc.rectGetMaxX(rect)
    local min_y = cc.rectGetMinY(rect)
    local max_y = cc.rectGetMaxY(rect)

    return min_x, min_y, max_x - size.width * scale, max_y - size.height * scale
end

function PanZoomLayer:onChangeScale(curScale)
	if self.maxScale < curScale then
		curScale = self.maxScale
	elseif curScale < self.minScale then
		curScale = self.minScale
	end
	self.container:setScale(curScale)

	local size = self.containerSize
	local newSize = cc.size(size.width * curScale, size.height * curScale)
	self:_updateBoundsRect(newSize)
end

function PanZoomLayer:onChangePosition(offsetx, offsety)
	local curx, cury = self.container:getPosition()

	curx = curx + offsetx
	cury = cury + offsety

	if not self.boundCollisionEnable then
		self.container:setPosition(curx, cury)
		self:dispatchEvent(EventType.EVENT_SCROLLING)
		return
	end

	local ix, iy, ax, ay = self:_containerOffsetRange(true)
	curx = max(curx, ix)
	cury = max(cury, iy)
	curx = min(curx, ax)
	cury = min(cury, ay)

	self.container:setPosition(curx, cury)
	self:dispatchEvent(EventType.EVENT_SCROLLING)
end

return PanZoomLayer