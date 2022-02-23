-- @Author : fc
-- @Date   : 2022-02-04 19:52:57
-- @remark : 

local function G_GetComponent(entity, componentName, componentType)
	local component = entity:getComponent(componentName)
	return tolua.cast(component, componentType or componentName)
end



if cc and cc.exports then
	cc.exports.G_GetComponent = G_GetComponent
else
	_G["G_GetComponent"] = G_GetComponent
end

