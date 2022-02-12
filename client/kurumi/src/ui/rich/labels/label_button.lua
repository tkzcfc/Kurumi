
--
-- <button/> 标签解析
--

local defaultTexture = "Default/Button_Disable.png"

return function (self, params, default)
	local btn = ccui.Button:create()
	btn:setSwallowTouches(true)
	btn:loadTextureNormal(params.src or defaultTexture)

	if params.scale then
		btn:setScale(params.scale)
	end
	if params.rotate then
		btn:setRotation(params.rotate)
	end
	if params.visible ~= nil then
		btn:setVisible(params.visible)
	end

	local contetSize = btn:getBoundingBox()
	self._leftSpaceWidth = self._leftSpaceWidth - contetSize.width

	return {btn}
end
