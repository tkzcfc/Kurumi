-- @Author : fc
-- @Date   : 2022-02-06 15:53:02
-- @remark : 

local ScrollItem = class("ScrollItem", function()
	return ccui.Widget:create()
end)

-- local ScrollItem = class("ScrollItem", ccui.Widget)

-- function ScrollItem:ctor() end

function ScrollItem:setRender(render)
	render:setPosition(0, 0)
	render:setVisible(true)
	self:addChild(render)

	self.render = render
end

function ScrollItem:iItemWillUpdate(...)
	if self.onUpdateCall then
		self.onUpdateCall(...)
	end
end

function ScrollItem:setUpdateCallback(cb)
	self.onUpdateCall = cb
end

function ScrollItem:getRender()
	return self.render
end

return ScrollItem
