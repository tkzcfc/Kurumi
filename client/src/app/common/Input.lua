local Input = class("Input")

function Input:ctor()
	self.axisName_value_Map = {}
	self.axisName_bool_Map = {}
	self.axisName_func_Map = {}
end

-----------------------------------------axis-----------------------------------------

function Input:setAxisValue(axisName, value)
	self.axisName_value_Map[axisName] = value
	self:callAxis(axisName, t.value)
end

function Input:getAxisValue(axisName)
	return self.axisName_value_Map[axisName]
end

function Input:axisActive(axisName)
	return self.axisName_bool_Map[axisName]
end

function Input:registerAxisCallback(axisName, func)
	if self.axisName_func_Map[axisName] == nil then
		self.axisName_func_Map[axisName] = {}
	end
	table.insert(self.axisName_func_Map[axisName], func)
end

function Input:unRegisterAxisCallback(axisName, func)
	local t = self.axisName_func_Map[axisName]
	if t == nil then
		return
	end
	for k,v in pairs(t) do
		if v == func then
			table.remove(k)
			return
		end
	end
end

function Input:callAxis(axisName, value)
	if not self.axisName_bool_Map[axisName] then
		return
	end

	local t = self.axisName_arr_Map[axisName]
	if t == nil then
		return
	end
	for k,v in pairs(t) do
		v(value)
	end
end

return Input

