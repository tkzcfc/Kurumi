
--
-- <custom/> 标签解析
--

return function (self, params, default)
	local node = self:doCustomSpawn(params)
	if not node then
		self:printf("<custom> - create node failde")		
	end

	local contetSize = node:getBoundingBox()
	self._leftSpaceWidth = self._leftSpaceWidth - contetSize.width

	return {node}
end
