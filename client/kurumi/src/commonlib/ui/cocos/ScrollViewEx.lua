-- @Author : fc
-- @Date   : 2021-04-17 16:52:49
-- @remark : ccui.ScrollView 扩展

local ScrollView = ccui.ScrollView

local ScrollViewDirection = {
    DIR_VERTICAL = 1,
    DIR_HORIZONTAL = 2,
    DIR_BOTH = 3,
}

-- item 对齐方向
local SCROLLVIEW_ALIGNMENT = {
    FIRST = 1,
    MID = 2,
    LAST = 3,
}

local function cond(c, a, b)
    if c then return a end
    return b
end

local ceil = math.ceil
local min  = math.min
local max  = math.max
local abs  = math.abs
local floor = math.floor
local unpack = unpack

ScrollView.SCROLLVIEW_ALIGNMENT = SCROLLVIEW_ALIGNMENT

local ACTION_TAG = 0xfcfc

ScrollView.ACTION_TAG = ACTION_TAG

------------------------------------------------------------ public ------------------------------------------------------------

-- @brief 设置item被创建时的回调函数
function ScrollView:setItemCreatedCallback(callback)
    self.onItemCreatedCallback = callback
end

-- @brief 设置item刷新时的回调函数
function ScrollView:setItemUpdateCallback(callback)
    self.onItemUpdateCallback = callback
end

-- @brief 设置item被回收是的回调函数
function ScrollView:setItemFreeCallback(callback)
    self.onItemFreeCallback = callback
end

-- @brief 设置重新布局后的回调函数
function ScrollView:setOnUpdateLayoutCallback(callback)
    self.onUpdateLayoutCallback = callback
end

-- @brief 设置item之间的间隙
-- @param hMargin 横向间距
-- @param vMargin 纵向间距
function ScrollView:setItemsMargin(hMargin, vMargin)
    self.vMargin = vMargin
    self.hMargin = hMargin
end

-- @brief 设置填充
-- @param hPadding 填充左右
-- @param vPadding 填充上下
function ScrollView:setPadding(hPadding, vPadding)
    if self.hPadding == hPadding and self.vPadding == vPadding then
        return false
    end
    self.hPadding = hPadding
    self.vPadding = vPadding
    return true
end

-- @brief 设置Item视图模型且禁用滑块
function ScrollView:setItemViewModelAndHideBar(...)
    self:setScrollBarEnabled(false)
    self:setItemViewModel(...)
end

-- @brief 在调用setItemViewModel时保持偏移位置不变
--        setItemViewModel 函数会调用完毕会自动将该值置位false
function ScrollView:freezeOffset(value)
    self.bFreezeOffset = value
end

-- @brief 设置Item视图模型
-- @param itemClass item对应的class对象, 此class对象必须实现方法 iItemWillUpdate
-- @param totalItemNum 总数量
-- @param itemSize item的尺寸
-- @param multiNum 一行显示个数
-- @param adaptationSize 是否适配item，自动缩放item
-- @param ... 调用 iItemWillUpdate 函数时传入的参数
function ScrollView:setItemViewModel(itemClass, totalItemNum, itemSize, multiNum, adaptationSize, ...)
    self:removeAllShowItems()
    self:stopOverallScroll()

    -- item间距
    self.vMargin = self.vMargin or 0
    self.hMargin = self.hMargin or 0
    -- 四周留白
    self.vPadding = self.vPadding or 0
    self.hPadding = self.hPadding or 0

    -- 总数量
    self.iTotalItemNum = totalItemNum or 0
    if self.iTotalItemNum <= 0 then return end

    self.tItemClass = itemClass
    self.tArgs      = {...}
    self.iMultiNum  = multiNum or 1
    self.tShowItems = self.tShowItems or {}
    -- item缩放系数
    self.fItemScale = 1
    -- 是否适配item，自动缩放item
    if adaptationSize == nil then adaptationSize = true end
    self.bAdaptationSize = adaptationSize

    -- 参数检查
    assert(type(itemClass.iItemWillUpdate) == "function")
    assert(self.iMultiNum > 0, "multiNum should larger than 0 !!")

    self.bInitTag = true

    self:_updateContentSize(self.bFreezeOffset, itemSize, adaptationSize)
    self.bFreezeOffset = false
end

-- @brief 刷新所有的item
function ScrollView:updateAllItems(...)
    if self.tShowItems == nil then return end

    local args = {...}
    if #args > 0 then
        self.tArgs = args
    end
    
    for _, item in pairs(self.tShowItems) do
        self:_updateItem(item)
    end
end

-- @brief 刷新指定下标item
function ScrollView:updateItemByIndex(index)
    local item = self:getItemByIndex(index)
    if item then
        self:_updateItem(item)
    end
end

-- @brief 获取当前滑动offset百分比[0,1]
function ScrollView:getScrollPercent()
    if ScrollViewDirection.DIR_VERTICAL == self:getDirection() then
        return self:getOffsetPercent(self:getInnerContainerPosition().y)
    else
        return self:getOffsetPercent(self:getInnerContainerPosition().x)
    end
end

-- @brief 通过滑动偏移值计算其滑动百分比[0,1]
function ScrollView:getOffsetPercent(offset)
    local dir = self:getDirection()
    local containerSize = self:getInnerContainerSize()
    local visibleViewSize = self:getContentSize()
    local percent = 0
    if dir == ScrollViewDirection.DIR_HORIZONTAL then
        local numerator = containerSize.width - visibleViewSize.width
        if numerator ~= 0 then
            percent = abs(offset/(containerSize.width - visibleViewSize.width))
        end
    elseif dir == ScrollViewDirection.DIR_VERTICAL then
        local numerator = containerSize.height - visibleViewSize.height
        if numerator ~= 0 then
            percent = abs(offset/(containerSize.height - visibleViewSize.height)) 
        end
    end

    if percent < 0 then return 0 end
    if percent > 1 then return 1 end
    return percent
end

-- @brief 设置ScrollView内Item居中显示(只会处理内容大小小于视口大小的轴)
--        原理:将四周留白扩大
function ScrollView:setShowCenter()
    if not self.bInitTag then return end
    local viewSize = self:getContentSize()

    local vPadding = self.vPadding
    local hPadding = self.hPadding
    
    local realWidth = self.tRealContentSize.width - self.hPadding * 2
    if realWidth < viewSize.width then
        hPadding = (viewSize.width - realWidth) * 0.5
    end

    local readHeight = self.tRealContentSize.height - self.vPadding * 2
    if readHeight < viewSize.height then
        vPadding = (viewSize.height - readHeight) * 0.5
    end

    if self:setPadding(hPadding, vPadding) then
        self:_updateContentSize(false, self.tItemContentSize, false)
        self:_updateCellPos()
    end
end

-- @brief 跳转到某个item
-- @param index item下标
-- @param alignment 跳转到视图哪个位置
-- @param 偏移值
-- @param timeInSec 滚动时间,为nil则跳转
function ScrollView:jumpToItem(index, alignment, offset, timeInSec)
    if not self.bFullView then
        return
    end

    offset = offset or 0
    alignment = alignment or SCROLLVIEW_ALIGNMENT.FIRST

    if index == nil or index < 1 or index > self.iTotalItemNum then
        assert(false, "ScrollView:jumpToItem   index is not invalid!")
        return
    end

    if self:getDirection() == ScrollViewDirection.DIR_HORIZONTAL then
        local line = cond(index % self.iMultiNum == 0, index / self.iMultiNum, ceil(index / self.iMultiNum))

        local posX = -self.tItemContentSize.width * (line - 1)
        posX = posX - self.hPadding - self:_getMarginH(line) + offset

        if alignment == SCROLLVIEW_ALIGNMENT.MID then
            posX = posX + self:getContentSize().width / 2 - self.tItemContentSize.width / 2
        elseif alignment == SCROLLVIEW_ALIGNMENT.LAST then
            posX = posX + self:getContentSize().width - self.tItemContentSize.width
        end

        -- 修正位置
        if posX < self:getContentSize().width - self.tContentSize.width then
            posX = self:getContentSize().width - self.tContentSize.width
        elseif posX > 0 then
            posX = 0
        end

        -- self:jumpToDestination(cc.p(posX, 0))
        -- jumpToDestination 未导出,此处使用 jumpToPercentHorizontal 实现反推percent
        local w = self:getContentSize().width - self:getInnerContainer():getContentSize().width
        local percent = posX / w * 100
        self:jumpToPercentHorizontal(percent)

        if timeInSec then
            self:scrollToPercentHorizontal(percent, timeInSec, true)
        else
            self:jumpToPercentHorizontal(percent)
            self:_updateView(true)
        end
    else
        local line = cond(index % self.iMultiNum == 0, index / self.iMultiNum, ceil(index / self.iMultiNum))

        local posY = self:getContentSize().height - self.tContentSize.height + self.tItemContentSize.height * (line - 1)
        posY = posY + self.vPadding + self:_getMarginV(line) + offset

        if alignment == SCROLLVIEW_ALIGNMENT.MID then
            posY = posY - self:getContentSize().height / 2 + self.tItemContentSize.height / 2
        elseif alignment == SCROLLVIEW_ALIGNMENT.LAST then
            posY = posY - self:getContentSize().height + self.tItemContentSize.height
        end

        -- 修正位置
        if posY > 0 then
            posY = 0
        elseif posY < self:getContentSize().height - self.tContentSize.height then
            posY = self:getContentSize().height - self.tContentSize.height
        end

        -- self:jumpToDestination(cc.p(0, posY))
        -- jumpToDestination 未导出,此处使用 jumpToPercentVertical 实现反推percent
        local minY = self:getContentSize().height - self:getInnerContainer():getContentSize().height
        local h = -minY
        local percent = (100 * (posY - minY)) / h

        if timeInSec then
            self:scrollToPercentVertical(percent, timeInSec, true)
        else
            self:jumpToPercentVertical(percent)
            self:_updateView(true)
        end
    end
end


-- @brief 播放item入场动画
-- @param actionType 动画类型
-- @param callback 回调
function ScrollView:playFlyInAction(actionType, callback)
    if self.bPlayFlyAction then return end

    self:getAllShowItems(true)
    
    local itemCount = #self.tShowItems
    if itemCount <= 0 then
        if callback then callback() end
        return
    end

    local MovePos = 40
    for k, item in ipairs(self.tShowItems) do
        item:setCascadeOpacityEnabled(true)
        item:setOpacity(0)
        item:stopAllActionsByTag(ACTION_TAG)
        item:setPositionY(item:getPositionY() - MovePos)

        local move_by = cc.EaseSineIn:create(cc.MoveBy:create(0.1, cc.p(0, MovePos)))
        local fade_in = cc.FadeIn:create(0.3)

        local actions = 
        {
            cc.DelayTime:create((k - 1) * 0.03),
            cc.Spawn:create(fade_in, move_by)
        }

        if k == itemCount then
            table.insert(actions, cc.CallFunc:create(function()
                self:playItemActionFinish()
                if callback then
                    callback()
                end
            end))
        end
        item:runAction(cc.Sequence:create(actions)):setTag(ACTION_TAG)
    end

    self:startPlayItemAction()
end

-- @brief 开始播放item动画（禁用 _updateView 调用）
function ScrollView:startPlayItemAction()
    self.bPlayFlyAction = true
    self.bCacheTouchEnable = self:isTouchEnabled()
    self:setTouchEnabled(false)
end

-- @brief 播放item动画结束（开启 _updateView 调用）
function ScrollView:playItemActionFinish()
    self.bPlayFlyAction = false
    if self.bCacheTouchEnable == nil then self.bCacheTouchEnable = true end
    self:setTouchEnabled(self.bCacheTouchEnable)
end

-- @brief 获取当前正在显示的item
function ScrollView:getAllShowItems(doSort)
    self.tShowItems = self.tShowItems or {}

    if doSort then
        table.sort(self.tShowItems, function(a, b)
            return a.iIndex < b.iIndex
        end)
    end
    return self.tShowItems
end

-- @brief 通过下标获取item
function ScrollView:getItemByIndex(index)
    if self.tShowItems == nil then return end
    
    for k,v in pairs(self.tShowItems) do
        if v.iIndex == index then
            return v
        end
    end
end

-- @brief 移除当前所有item
function ScrollView:removeAllShowItems()
    if self.tShowItems == nil then return end

    for k, v in pairs(self.tShowItems) do
        self:_enqueueItem(v)
    end
    self.tShowItems = {}
    self.bFullView = false
    self:playItemActionFinish()
end

-- @brief 清空当前所有缓存item
function ScrollView:clearCacheItems()
    if self.tFreeItems == nil then return end

    for k,v in pairs(self.tFreeItems) do
        v:removeFromParent()
    end
    self.tFreeItems = {}
end

-- @brief item是否填充满了view
function ScrollView:isFullView()
    return self.bFullView
end

------------------------------------------------------------ private ------------------------------------------------------------
-- local UPATE_INTERVAL = 1 / 60
function ScrollView:_enableUpdateView()
    local oldVal = self.bFullView
    self.bFullView = true
    self:_updateView(true)
    self.bFullView = oldVal

    if not self.bFullView then return end

    -- 使用事件刷新
    self:enableEventListener()

    -- if self.__updateNode == nil then
    --     self.__updateNode = cc.Node:create()
    --     self.__updateNode:setVisible(false)
    --     self:addProtectedChild(self.__updateNode)

    --     local totalTime = 0
    --     self.__updateNode:onUpdate(function(dt)
    --         totalTime = totalTime + dt
    --         if totalTime < UPATE_INTERVAL then return end
    --         totalTime = 0
    --         self:_updateView()
    --     end)
    -- end
end


-- @brief 获取开始行数 [1,)
-- @param offset 偏移值
-- @param padding 两端填充值
-- @param size 
-- @param margin item之间间隔
local function _getStartLines(offset, padding, size, margin)
    local value = 0
    local line = 1
    repeat
        value = padding + size * line + margin * (line - 1)
        if value > offset then break end
        line = line + 1
    until(false)
    return line
end

function ScrollView:_updateView(force)
    if not self.bFullView then return end
    if self.bPlayFlyAction then return end

    local isVertical = ScrollViewDirection.DIR_VERTICAL == self:getDirection()
    local containerOffset = self:getInnerContainerPosition()

    -- 添加缓存
    if not force and self.fCacheOffsetVal ~= nil then
        if isVertical then
            if abs(self.fCacheOffsetVal - containerOffset.y) < 0.01 then return end
        else
            if abs(self.fCacheOffsetVal - containerOffset.x) < 0.01 then return end
        end
    end
    
    if isVertical then
        self.fCacheOffsetVal = containerOffset.y
    else
        self.fCacheOffsetVal = containerOffset.x
    end

    local containerSize = self.tContentSize
    local viewSize = self:getContentSize()

    local viewVal
    local minViewVal = -self.tItemContentSize.width
    local maxViewVal = viewSize.width
    if isVertical then
        minViewVal = -self.tItemContentSize.height
        maxViewVal = viewSize.height
    end
    -- 移除超出视图范围外的item
    for i = #self.tShowItems, 1, -1 do
        local item = self.tShowItems[i]

        if isVertical then
            viewVal = containerOffset.y + item:getPositionY()
        else
            viewVal = containerOffset.x + item:getPositionX()
        end

        if viewVal < minViewVal or viewVal > maxViewVal then
            self:_enqueueItem(item)
            table.remove(self.tShowItems, i)
        end
    end

    -- 补充视图范围内没有显示的item
    if isVertical then
        local offsetVal = containerSize.height + containerOffset.y - viewSize.height
        local startLine = _getStartLines(offsetVal, self.vPadding, self.tItemContentSize.height, self.vMargin)
        local breakLoop = false

        repeat
            for i = 1, self.iMultiNum do
                local index = (startLine - 1) * self.iMultiNum + i

                if index > self.iTotalItemNum then
                    breakLoop = true
                    break
                end

                if not self:_containItem(index) then
                    local y = containerSize.height - startLine * self.tItemContentSize.height - self:_getMarginV(startLine) - self.vPadding
                    viewVal = containerOffset.y + y

                    if viewVal < minViewVal or viewVal > maxViewVal then
                        breakLoop = true
                        break
                    end

                    local x = (i - 1) * self.tItemContentSize.width + self:_getMarginH(i) + self.hPadding
                    local item = self:_dequeueItem()
                    item.iIndex = index     -- 索引下标
                    item.iRows = startLine  -- 行数
                    item.iColumns = i       -- 列数
                    item:setPosition(x, y)
                    table.insert(self.tShowItems, item)

                    self:_updateItem(item)
                end
            end
            startLine = startLine + 1
        until(breakLoop)
    else
        local offsetVal = -containerOffset.x
        local startLine = _getStartLines(offsetVal, self.hPadding, self.tItemContentSize.width, self.hMargin)
        local breakLoop = false

        repeat
            for i = 1, self.iMultiNum do
                local index = (startLine - 1) * self.iMultiNum + i

                if index > self.iTotalItemNum then
                    breakLoop = true
                    break
                end

                if not self:_containItem(index) then
                    local x = (startLine - 1) * self.tItemContentSize.width + self:_getMarginH(startLine) + self.hPadding
                    viewVal = containerOffset.x + x

                    if viewVal < minViewVal or viewVal > maxViewVal then
                        breakLoop = true
                        break
                    end

                    local y = containerSize.height - i * self.tItemContentSize.height - self:_getMarginV(i) - self.vPadding
                    local item = self:_dequeueItem()
                    item.iIndex = index     -- 索引下标
                    item.iRows = startLine  -- 行数
                    item.iColumns = i       -- 列数
                    item:setPosition(x, y)
                    table.insert(self.tShowItems, item)

                    self:_updateItem(item)
                end
            end
            startLine = startLine + 1
        until(breakLoop)
    end

    if self.onUpdateLayoutCallback then
        self.onUpdateLayoutCallback()
    end
end

-- @brief 更新内容大小
-- @param freezeOffset 是否保持当前偏移量
function ScrollView:_updateContentSize(freezeOffset, itemSize, adaptationSize)
    if not self.bInitTag then return end

    local viewSize    = self:getContentSize()
    local realContentSize = {}

    self.tRealContentSize = realContentSize
    self.tItemContentSize = clone(itemSize)
    self.tContentSize = clone(viewSize)

    -- 逻辑偏移值
    local logicOffset = 0
    if freezeOffset then logicOffset = self:_getLogicOffset() end

    -- 显示的行数
    local lineCount = cond(self.iTotalItemNum % self.iMultiNum == 0, self.iTotalItemNum / self.iMultiNum, ceil(self.iTotalItemNum / self.iMultiNum))

    -- 计算实际需要大小
    if ScrollViewDirection.DIR_HORIZONTAL == self:getDirection() then
        if adaptationSize then
            local height = viewSize.height - self.hPadding * 2 - self:_getMarginV(self.iMultiNum)
            local scale = height / self.iMultiNum / itemSize.height
            
            if scale > 0 then
                self.fItemScale = scale
                self.tItemContentSize = {width = itemSize.width * scale, height = itemSize.height * scale}
            else
                self.fItemScale = 1
                self.bAdaptationSize = false
            end
        end

        local multiNum = min(self.iTotalItemNum, self.iMultiNum)

        realContentSize.width = self.tItemContentSize.width * lineCount + self:_getMarginH(lineCount) + self.hPadding * 2
        realContentSize.height = self.tItemContentSize.height * multiNum + self:_getMarginV(multiNum) + self.vPadding * 2

        self.bFullView = realContentSize.width > viewSize.width
        self.tContentSize.width = max(realContentSize.width, viewSize.width)
        self:setInnerContainerSize(self.tContentSize)

        if freezeOffset then
            self:_setLogicOffset(logicOffset)
        else
            self:setInnerContainerPosition(cc.p(0, 0))
        end
    else
        if adaptationSize then
            local width = viewSize.width - self.hPadding * 2 - self:_getMarginH(self.iMultiNum)
            local scale = width / self.iMultiNum / itemSize.width

            if scale > 0 then
                self.fItemScale = scale
                self.tItemContentSize = {width = itemSize.width * scale, height = itemSize.height * scale}
            else
                self.fItemScale = 1
                self.bAdaptationSize = false
            end
        end

        local multiNum = min(self.iTotalItemNum, self.iMultiNum)

        realContentSize.width = self.tItemContentSize.width * multiNum + self:_getMarginH(multiNum) + self.hPadding * 2
        realContentSize.height = self.tItemContentSize.height * lineCount + self:_getMarginV(lineCount) + self.vPadding * 2

        self.bFullView = realContentSize.height > viewSize.height
        self.tContentSize.height = max(realContentSize.height, viewSize.height)
        self:setInnerContainerSize(self.tContentSize)

        if freezeOffset then
            self:_setLogicOffset(logicOffset)
        else
            if self.bFullView then
                self:setInnerContainerPosition(cc.p(0, viewSize.height - self.tContentSize.height))
            else
                self:setInnerContainerPosition(cc.p(0, 0))
            end
        end
    end
    -- 刷新一次
    self:_enableUpdateView()
end

-- @brief 刷新cell位置
function ScrollView:_updateCellPos()
    if self.tShowItems == nil or #self.tShowItems == 0 then return end

    local containerSize = self.tContentSize

    if ScrollViewDirection.DIR_VERTICAL == self:getDirection() then
        for k,item in pairs(self.tShowItems) do
            local x = (item.iColumns - 1) * self.tItemContentSize.width + self:_getMarginH(item.iColumns) + self.hPadding
            local y = containerSize.height - item.iRows * self.tItemContentSize.height - self:_getMarginV(item.iRows) - self.vPadding
            item:setPosition(x, y)
        end
    else
        for k,item in pairs(self.tShowItems) do
            local x = (item.iRows - 1) * self.tItemContentSize.width + self:_getMarginH(item.iRows) + self.hPadding
            local y = containerSize.height - item.iColumns * self.tItemContentSize.height - self:_getMarginV(item.iColumns) - self.vPadding
            item:setPosition(x, y)
        end
    end
end

-- @brief 更新item
function ScrollView:_updateItem(item)
    item:iItemWillUpdate(item.iIndex, unpack(self.tArgs))
    if self.onItemUpdateCallback then
        self.onItemUpdateCallback(item, unpack(self.tArgs))
    end
end

-- @brief item出队,移除空闲队列
function ScrollView:_dequeueItem()
    self.tFreeItems = self.tFreeItems or {}
    if #self.tFreeItems <= 0 then
        local item = self.tItemClass.new()
        item:setScale(self.fItemScale)
        self:addChild(item)

        if self.onItemCreatedCallback then
            self.onItemCreatedCallback(item)
        end
        return item
    end
    local item = table.remove(self.tFreeItems)
    item:setVisible(true)
    item:stopAllActionsByTag(ACTION_TAG)
    item:setOpacity(255)
    return item
end

-- @brief item入队,放入空闲队列
function ScrollView:_enqueueItem(item)
    local index = item.iIndex

    self.tFreeItems = self.tFreeItems or {}
    item:setVisible(false)
    item:stopAllActionsByTag(ACTION_TAG)
    item.iIndex = -1
    table.insert(self.tFreeItems, item)

    if self.onItemFreeCallback then
        self.onItemFreeCallback(item, index)
    end
end

-- @brief 下标为index的item是否存在
function ScrollView:_containItem(index)
    for k,v in pairs(self.tShowItems) do
        if v.iIndex == index then
            return true
        end
    end
end

function ScrollView:_getMarginH(count)
    if count <= 0 then return 0 end
    return self.hMargin * (count - 1)
end

function ScrollView:_getMarginV(count)
    if count <= 0 then return 0 end
    return self.vMargin * (count - 1)
end

-- @brief 获取逻辑偏移量
function ScrollView:_getLogicOffset()
    local containerOffset = self:getInnerContainerPosition()

    if ScrollViewDirection.DIR_HORIZONTAL == self:getDirection() then
        return containerOffset.x
    end

    local viewSize = self:getContentSize()
    local containerSize = self:getInnerContainerSize()
    return viewSize.height - containerSize.height - containerOffset.y
end

-- @brief 设置逻辑偏移量
function ScrollView:_setLogicOffset(value)
    local containerOffset = self:getInnerContainerPosition()
    local viewSize = self:getContentSize()
    local containerSize = self:getInnerContainerSize()

    if ScrollViewDirection.DIR_HORIZONTAL == self:getDirection() then
        local diffValue = viewSize.width - containerSize.width
        if diffValue < 0 then
            containerOffset.x = math.max(diffValue, value)
        end
    else
        containerOffset.y = math.min(viewSize.height - containerSize.height - value, 0)
    end
    self:setInnerContainerPosition(containerOffset)
end

function ScrollView:addEventListenerEx(callback)
    self.onEventCallback = callback
    self:enableEventListener()
end

-- @brief 开启事件监听
function ScrollView:enableEventListener()
    if self.bEnableEvent then return end
    self.bEnableEvent = true

    self:addEventListener(function(...)
        self:_updateView()

        if self.onEventCallback then
            self.onEventCallback(...)
        end
    end)
end
