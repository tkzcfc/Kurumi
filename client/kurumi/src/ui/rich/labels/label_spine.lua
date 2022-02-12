
--
-- <spine/> 标签解析
--

return function (self, params, default)
	if not params.src then return 
	end

	local spine = self:getSpine(params.src)
	if not spine then
		self:printf("<spine> - create spine failde")
		return
	end
	if params.scale then
		spine:setScale(params.scale)
	end
	if params.rotate then
		spine:setRotation(params.rotate)
	end
	if params.visible ~= nil then
		spine:setVisible(params.visible)
	end
	if params.anim then
		spine:playAnimation(params.anim,-1)
	end

	self:addChild(spine)
	spine:update(0.1)
	local contetSize = spine:getAabbContentSize()
	contetSize.width = contetSize.width*(params.scale or 1) + 5
	contetSize.height = contetSize.height*(params.scale or 1)
	spine:setContentSize(contetSize)
	spine:removeFromParent(false)
	self._leftSpaceWidth = self._leftSpaceWidth - contetSize.width

	return {spine}
end
