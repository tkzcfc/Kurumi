local inputInstance = require("app.common.Input"):new()
local axisKey = {}


axisKey.Vertical 		= 0
axisKey.Horizontal 		= 1


for k,v in pairs(axisKey) do
	inputInstance:setAxisValue(v, 0)
end


_MyG.Input = inputInstance
_MyG.AXIS_KEY = axisKey