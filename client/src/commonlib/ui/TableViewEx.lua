-- @Author : fangcheng
-- @Date   : 2020-03-22 15:59:20
-- @remark : tableView扩展

local TableViewEx = class("TableViewEx", function(size)
	return cc.TableView:create(size)
end)

function TableViewEx:ctor()
    self:registerScriptHandler(handler(self, self.onNumberOfCellsInTableView),cc.NUMBER_OF_CELLS_IN_TABLEVIEW)
    self:registerScriptHandler(handler(self, self.onTableCellSizeInTableView),cc.TABLECELL_SIZE_FOR_INDEX)
    self:registerScriptHandler(handler(self, self.onTableCellSizeAtIndex),cc.TABLECELL_SIZE_AT_INDEX)
	self:setDirection(cc.SCROLLVIEW_DIRECTION_VERTICAL)
	self:setVerticalFillOrder(cc.TABLEVIEW_FILL_TOPDOWN)
end

--------------------------------------------- public ---------------------------------------------
-- @brief cell数量回调
function TableViewEx:setCellCountCallback(call)
	self.onCellCountCall = call
end

--@brief cell大小设置回调
function TableViewEx:setCellSizeCallback(call)
	self.onCellSizeCall = call
end

--@brief cell创建回调
function TableViewEx:setCreateCellCallback(call)
	self.onCreateCellCall = call
end

--@brief cell刷新回调
function TableViewEx:setReloadCellCallback(call)
	self.onReloadCellCall = call
end

--@brief 刷新
-- @param freeze 是否保持当前位置
function TableViewEx:reloadData(freeze)
	if freeze and self.__initTag then
		local offset = self:getContentOffset()
		local oldContentSize = self:getContentSize()

		cc.TableView.reloadData(self)

		if self:getDirection() == cc.SCROLLVIEW_DIRECTION_VERTICAL  then
			local contentHeight = self:getContentSize().height
			if math.abs(oldContentSize.height - contentHeight) < 1 then
				self:setContentOffset(offset)
				return
			end

			if contentHeight <= self:getViewSize().height then
				return
			end

			offset.y = offset.y + (oldContentSize.height - contentHeight)
			offset.y = math.min(offset.y, 0)
			self:setContentOffset(offset)
		else
			local contentWidth = self:getContentSize().width
			if oldContentSize.width <= contentWidth + 1 then
				self:setContentOffset(offset)
				return
			end

			local viewWidth = self:getViewSize().width
			if contentWidth <= viewWidth then
				return
			end
			
			offset.x = math.max(offset.x, viewWidth - contentWidth)
			self:setContentOffset(offset)
		end
	else
		cc.TableView.reloadData(self)
	end
	self.__initTag = true
end

--------------------------------------------- private ---------------------------------------------

function TableViewEx:onNumberOfCellsInTableView(tableView)
	return self.onCellCountCall()
end

function TableViewEx:onTableCellSizeInTableView(tableView, index)
	return self.onCellSizeCall(index)
end

function TableViewEx:onTableCellSizeAtIndex(tableView, index)
	local cell = tableView:dequeueCell()
	local status

	if cell == nil then
		cell = cc.TableViewCell:new()
		local status = xpcall(function()
			local node = self.onCreateCellCall(index, cell)
			if node then
				cell:addChild(node)
			end
		end, __G__TRACKBACK__)

		if not status then
			cell.__ExceptionTag = true
		end
	end

	if cell.__ExceptionTag then
		return cell
	end

	status = xpcall(function()
		self.onReloadCellCall(index, cell)
	end, __G__TRACKBACK__)

	if not status then
		cell.__ExceptionTag = true
		cell:removeAllChildren()
	end

	return cell
end

return TableViewEx