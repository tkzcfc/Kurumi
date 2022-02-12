-- @Author : fc
-- @Date   : 2021-04-17 16:52:49
-- @remark : ccui.ScrollView 扩展

local ScrollView = ccui.ScrollView

local ScrollViewDirection = {
    DIR_VERTICAL = 1,
    DIR_HORIZONTAL = 2,
    DIR_BOTH = 3,
}

-- 入场动画 item 飞入方向
local ScrollViewFlyFrom = {
    Up = 1,
    Down = 2,
    Left = 3,
    Right = 4,
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
local abs  = math.abs
local floor = math.floor

ScrollView.ScrollViewFlyFrom = ScrollViewFlyFrom
ScrollView.SCROLLVIEW_ALIGNMENT = SCROLLVIEW_ALIGNMENT

local ACTION_TAG = 0xfcfc

------------------------------------------------------------ public ------------------------------------------------------------

-- @brief 设置item被创建时的回调函数
function ScrollView:setItemCreatedCallback(callback)
    self.onItemCreatedCallback = callback
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
    self.vPadding = vPadding
    self.hPadding = hPadding
end

-- @brief 设置Item视图模型且禁用滑块
function ScrollView:setItemViewModelAndHideBar(...)
    self:setScrollBarEnabled(false)
    self:setItemViewModel(...)
end

-- @brief 设置Item视图模型
-- @param itemClass item对应的class对象, 此class对象必须实现方法 iItemWillUpdate
-- @param totalItemNum 总数量
-- @param itemSize item的尺寸
-- @param multiNum 一行显示个数
-- @param adaptationSize 是否适配item，自动缩放item
-- @param data 调用 iItemWillUpdate 函数时传入的数据
function ScrollView:setItemViewModel(itemClass, totalItemNum, itemSize, multiNum, adaptationSize, data)
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
    if self.iTotalItemNum <= 0 then
        return
    end

    assert(type(itemClass.iItemWillUpdate) == "function")

    self.tItemClass = itemClass
    self.tData      = data
    self.tItemContentSize = itemSize
    self.iMultiNum  = multiNum or 1
    self.tShowItems = self.tShowItems or {}
    -- item缩放系数
    self.fItemScale = 1

    adaptationSize = adaptationSize == nil and true or adaptationSize
    assert(self.iMultiNum > 0, "multiNum should larger than 0 !!")

    self.tContentSize = self:getContentSize()
    local viewSize = self:getContentSize()
    -- 显示的行数
    local lineCount = cond(self.iTotalItemNum % self.iMultiNum == 0, self.iTotalItemNum / self.iMultiNum, ceil(self.iTotalItemNum / self.iMultiNum))

    -- 计算实际需要大小
    if ScrollViewDirection.DIR_HORIZONTAL == self:getDirection() then
        if adaptationSize then
            local height = self.tContentSize.height - self.hPadding * 2 - self:_getMarginV(self.iMultiNum)
            local scale = height / self.iMultiNum / self.tItemContentSize.height

            self.fItemScale = scale
            self.tItemContentSize = {width = self.tItemContentSize.width * scale, height = self.tItemContentSize.height * scale}
        end

        self.tContentSize.width = self.tItemContentSize.width * lineCount + self:_getMarginH(lineCount) + self.vPadding * 2
        self.bFullView = self.tContentSize.width > viewSize.width
        self:setInnerContainerSize(self.tContentSize)
        self:setInnerContainerPosition(cc.p(0, 0))
    else
        if adaptationSize then
            local width = self.tContentSize.width - self.hPadding * 2 - self:_getMarginH(self.iMultiNum)
            local scale = width / self.iMultiNum / self.tItemContentSize.width

            self.fItemScale = scale
            self.tItemContentSize = {width = self.tItemContentSize.width * scale, height = self.tItemContentSize.height * scale}
        end

        self.tContentSize.height = self.tItemContentSize.height * lineCount + self:_getMarginV(lineCount) + self.vPadding * 2
        self.bFullView = self.tContentSize.height > viewSize.height
        self:setInnerContainerSize(self.tContentSize)
        if self.bFullView then
            self:setInnerContainerPosition(cc.p(0, viewSize.height - self.tContentSize.height))
        else
            self:setInnerContainerPosition(cc.p(0, 0))
        end
    end
    self.tContentSize = self:getInnerContainerSize()

    self:_enableUpdateView()
end

-- @brief 刷新所有的item
function ScrollView:updateAllItems(data)
    if self.tShowItems == nil then return end

    if data then
        self.tData = data
    end
    
    for _, item in pairs(self.tShowItems) do
        item:iItemWillUpdate(item.iIndex, self.tData)
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

-- @brief 设置ScrollView内Item是否居中显示
function ScrollView:setShowCenter(isCenter)
    local viewSize = self:getContentSize()
    if ScrollViewDirection.DIR_HORIZONTAL == self:getDirection() then
        local dertaValue = viewSize.width - self.tContentSize.width
        if isCenter then
            if dertaValue > 0 then
                self:getInnerContainer():setPositionX(dertaValue / 2)
            end
        else
            self:getInnerContainer():setPositionX(dertaValue)
        end
    elseif ScrollViewDirection.DIR_VERTICAL == self:getDirection() then
        local dertaValue = viewSize.height - self.tContentSize.height
        if isCenter then
            if dertaValue > 0 then
                self:getInnerContainer():setPositionY(dertaValue / 2)
            end
        else
            self:getInnerContainer():setPositionY(dertaValue)
        end
    end
end

-- @brief 跳转到某个item
-- @param index item下标
-- @param alignment 跳转到视图哪个位置
-- @param 偏移值
function ScrollView:jumpToItem(index, alignment, offset)
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
        self:jumpToPercentVertical(percent)
    end

    self:_updateView(true)
end


-- 入场动画配置
local LISTVIEW_DATA = {
    LIST_DELAY_TIME = 0.09,      -- 行间隔时间（秒）          1
    ITEM_DElAY_TIME = 0.05,      -- item间隔时间（秒）
    ITEM_MOVE_TIME = 0.16,       -- item移动时间（秒）
    ITEM_BOUNCE_TIME = 0.1,     -- item回弹时间（秒）
    ITEM_BOUNCE_DIS = 4,       -- item回弹偏移   x >= 0   
}

-- @brief 播放item入场动画
-- @param flyFrom 飞入方向
-- @param callback 回调
function ScrollView:playFlyInAction(flyFrom, callback)
    flyFrom = flyFrom or ScrollViewFlyFrom.Up   
    
    self:getAllShowItems(true)
    if #self.tShowItems <= 0 then
        if callback then callback() end
        return
    end

    local initDertaPos = cc.p(0, 0)
    local bouncePos = cc.p(0, 0)
    if flyFrom == ScrollViewFlyFrom.Up then
        initDertaPos = cc.p(0, self:getContentSize().height * 2)
        bouncePos = cc.p(0, -LISTVIEW_DATA.ITEM_BOUNCE_DIS)
    elseif flyFrom == ScrollViewFlyFrom.Down then
        initDertaPos = cc.p(0, -self:getContentSize().height * 2)
        bouncePos = cc.p(0, LISTVIEW_DATA.ITEM_BOUNCE_DIS)
    elseif flyFrom == ScrollViewFlyFrom.Left then
        initDertaPos = cc.p(-self:getContentSize().width * 2, 0)
        bouncePos = cc.p(LISTVIEW_DATA.ITEM_BOUNCE_DIS, 0)
    elseif flyFrom == ScrollViewFlyFrom.Right then
        initDertaPos = cc.p(self:getContentSize().width * 2, 0)
        bouncePos = cc.p(-LISTVIEW_DATA.ITEM_BOUNCE_DIS, 0)
    end

    for k, v in pairs(self.tShowItems) do
        local aimPos = cc.p(v:getPositionX(), v:getPositionY())

        local delayTime = (k - 1) * LISTVIEW_DATA.ITEM_DElAY_TIME
        if flyFrom == ScrollViewFlyFrom.Up then
            delayTime = (#self.tShowItems - k + 1) * LISTVIEW_DATA.ITEM_DElAY_TIME
        end

        v:setPosition(cc.pAdd(aimPos, initDertaPos))

        local actions = {
            cc.DelayTime:create(delayTime),
            cc.MoveTo:create(LISTVIEW_DATA.ITEM_MOVE_TIME, cc.pAdd(aimPos, bouncePos)),
            cc.MoveTo:create(LISTVIEW_DATA.ITEM_BOUNCE_TIME, aimPos),
        }

        if k == 1 then
            table.insert(actions, cc.CallFunc:create(function()
                self:playItemActionFinish()
                if callback then
                    callback()
                end
            end))
        end

        v:runAction(cc.Sequence:create(actions)):setTag(ACTION_TAG)
    end
    self:startPlayItemAction()
end

-- @brief 开始播放item动画（禁用 _updateView 调用）
function ScrollView:startPlayItemAction()
    self.bPlayFlyAction = true
end

-- @brief 播放item动画结束（开启 _updateView 调用）
function ScrollView:playItemActionFinish()
    self.bPlayFlyAction = false
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
local UPATE_INTERVAL = 1 / 30
function ScrollView:_enableUpdateView()
    local oldVal = self.bFullView
    self.bFullView = true
    self:_updateView(true)
    self.bFullView = oldVal

    if not self.bFullView then return end

    if self.__updateNode == nil then
        self.__updateNode = cc.Node:create()
        self.__updateNode:setVisible(false)
        self:addProtectedChild(self.__updateNode)

        local totalTime = 0
        self.__updateNode:addNodeEventListener(cc.NODE_ENTER_FRAME_EVENT, function(dt)
            totalTime = totalTime + dt
            if totalTime < UPATE_INTERVAL then return end
            totalTime = 0
            self:_updateView()
        end)
        self.__updateNode:scheduleUpdate()
        -- self.__updateNode:onUpdate(function(dt)
        --     totalTime = totalTime + dt
        --     if totalTime < UPATE_INTERVAL then return end
        --     totalTime = 0
        --     self:_updateView()
        -- end)
    end
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
                    item:iItemWillUpdate(index, self.tData)
                    item:setPosition(x, y)
                    table.insert(self.tShowItems, item)
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
                    item:iItemWillUpdate(index, self.tData)
                    item:setPosition(x, y)
                    table.insert(self.tShowItems, item)
                end
            end
            startLine = startLine + 1
        until(breakLoop)
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
    item:setScale(self.fItemScale)
    return item
end

-- @brief item入队,放入空闲队列
function ScrollView:_enqueueItem(item)
    self.tFreeItems = self.tFreeItems or {}
    item:setVisible(false)
    item:stopAllActionsByTag(ACTION_TAG)
    item.iIndex = -1
    table.insert(self.tFreeItems, item)
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