local Vector = {}

local function retain(obj)
	if obj and type(obj) == "userdata" and obj.retain then
		obj:retain()
	end
end

local function release(obj)
	if obj and type(obj) == "userdata" and obj.release then
		obj:release()
	end
end

function Vector:new(needRetain)
	needRetain = needRetain or false
	local object = { }

	setmetatable(object, self)
	self.__index = self
	object.needRetain = needRetain

	return object
end

function Vector:insert(index, obj)
	table.insert(self, index, obj)
	if self.needRetain then
		retain(obj)
	end
end

function Vector:at(index)
	if self[index] then
		return self[index]
	end
end

function Vector:back()
	return self:at(self:size())
end

function Vector:front()
	return self:at(1)
end
	
function Vector:size()
	return #self
end

function Vector:empty()
	if (self:size() > 0) then
		return false
	else
		return true
	end
end

function Vector:popBack()
	if self.needRetain then
		release(self[self:size()])
	end
	self[self:size()] = nil
end

function Vector:clear()
	for i = 1, self:size() do
		if self.needRetain then
			release(self[i])
		end
		self[i] = nil
	end
end

function Vector:pushBack(obj)
	self[self:size() + 1] = obj
	if self.needRetain then
		retain(obj)
	end
end

function Vector:contains(obj)
	for key, var in ipairs(self) do
		if (var == obj) then
			return true
		end
	end
	return false
end

function Vector:getIndex(obj)
	for key, var in ipairs(self) do
		if (var == obj) then
			return key
		end
	end
end

function Vector:erase(index)
	if self.needRetain then
		release(self[index])
	end
	table.remove(self, index)
end

function Vector:eraseObject(obj)
	for key, var in ipairs(self) do
		if (var == obj) then
			if self.needRetain then
				release(self[key])
			end
			table.remove(self, key)
			return true
		end
	end
	return false
end

return Vector