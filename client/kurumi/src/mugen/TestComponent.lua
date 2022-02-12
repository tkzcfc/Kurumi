-- @Author : fc
-- @Date   : 2022-02-04 16:33:56
-- @remark : 
local TestComponent = {}

function TestComponent:update(dt)
	print("TestComponent ", self, dt)
end

function TestComponent:onEnter()
	print("TestComponent onEnter", self)
end

return TestComponent 