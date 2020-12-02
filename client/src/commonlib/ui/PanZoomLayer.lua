-- @Author : fangcheng
-- @Date   : 2020-07-14 18:32:16
-- @remark : 平移缩放图层

local radian_30 = math.pi / 6
local kMaxAccelerationFactor = 1
local kMinAccelerationFactor = 0.01

local function lerp(p1, p2, alpha)
	return p1 * (1 - alpha) + p2 * alpha
end

local table_remove = table.remove

local EventType =
{
	EVENT_SCROLLING = 1,		-- 滚动事件
	EVENT_AUTOSCROLL_BEGAN = 2,	-- 自动滚动开始
	EVENT_AUTOSCROLL_ENDED = 3,	-- 自动滚动结束
	EVENT_NEW_CELL_CREATE  = 4,	-- 循环列表事件-有新的cell被创建
}

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

	-- 最大/小缩放系数
	self.maxScale = 2.5
	self.minScale = 0.3

	self:setZoomFactor(1.0)

	self.panBoundsRect = cc.rect(0, 0, display.width, display.height)

	self:setContentSize(size)
	self:setClippingEnabled(true)

	-- 惯性启用
	self:setInertiaScrollEnabled(true)

	-- touch layer
	self.container = cc.Layer:create()
	self.container:setAnchorPoint(cc.p(0, 0))
	self:addChild(self.container)

	self:setContainerSize(self:getContentSize())
	self:setZoomEnabled(false)
	self:setBoundCollisionEnabled(true)

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

-- @brief 开启容器滚动逻辑
-- @param position 滚动的目标位置
-- @param duration 动画持续时间
function PanZoomLayer:performedAnimatedScroll(position, duration)
	duration = math.abs(duration)
	self:stoppedAnimatedScroll()

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

--------------------------------------------------------- private ---------------------------------------------------------

function PanZoomLayer:_enableTouch()
	self:_disenableTouch()

	local listener = cc.EventListenerTouchOneByOne:create()
	listener:setSwallowTouches(true)

	listener:registerScriptHandler(function(touch, event)
		if #self.touches == 1 and not self.zoomEnable then
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
		self:onChangePosition(adderX, adderY)
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
		self:onChangePosition(deltaPosition.x, deltaPosition.y)

		local prevAngle = cc.pToAngleSelf(self.prevDeltaPoint)
		local angle = cc.pToAngleSelf(deltaPosition)
		if math.abs( prevAngle - angle ) <= radian_30 then
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
end

function PanZoomLayer:_setContainerZoomPos(zoom, pos)
	local realCurPosLayer1 = self.container:convertToNodeSpace(self:convertToWorldSpace(pos))

	self:onChangeScale(zoom)

	local realCurPosLayer2 = self.container:convertToNodeSpace(self:convertToWorldSpace(pos))

	local deltaX = realCurPosLayer2.x - realCurPosLayer1.x
	local deltaY = realCurPosLayer2.y - realCurPosLayer1.y
	local curScale  = self.container:getScale()
	self:onChangePosition(deltaX * curScale, deltaY * curScale)
end

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
end

function PanZoomLayer:_boundCollisionTest(curx, cury)
	local scale = self.container:getScale()
	local size  = self.containerSize

	local boundBox = cc.rect(curx, cury, size.width * scale, size.height * scale)

	local left 	 = cc.rectGetMinX(boundBox)
	local right  = cc.rectGetMaxX(boundBox)
	local top 	 = cc.rectGetMaxY(boundBox)
	local bottom = cc.rectGetMinY(boundBox)

    local min_x = cc.rectGetMinX(self.panBoundsRect)
    local max_x = cc.rectGetMaxX(self.panBoundsRect)
    local min_y = cc.rectGetMinY(self.panBoundsRect)
    local max_y = cc.rectGetMaxY(self.panBoundsRect)

    local arLeft 	= min_x
    local arRight 	= max_x - boundBox.width
    local arTop 	= max_y - boundBox.height
    local arBottom 	= min_y

    if arRight > arLeft then
    	if left < min_x then
    		curx = arLeft
    	end
    	if right > max_x then
    		curx = arRight
    	end
    else
    	if right > max_x or left < min_x then
    		curx = arLeft
    	end
	end
    
    if arTop > arBottom then
    	if bottom < min_y then
    		cury = arBottom
    	end
    	if top > max_y then
    		cury = arTop
    	end
    else
    	if bottom < min_y or top > max_y then
    		cury = arBottom
    	end
	end
	return curx, cury
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

    self.container:setPosition(self:_boundCollisionTest(curx, cury))

	self:dispatchEvent(EventType.EVENT_SCROLLING)
end

return PanZoomLayer