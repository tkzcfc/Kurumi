-- @Author : fc
-- @Date   : 2022-02-04 19:52:57
-- @remark : 

function G_GetComponent(entity, componentName, componentType)
	local component = entity:getComponent(componentName)
	return tolua.cast(component, componentType or componentName)
end
