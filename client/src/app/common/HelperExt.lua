-- @Author: fangcheng
-- @Date:   2020-11-07 16:33:58
-- @remark: 针对commonlib/G_Helper的扩展

cc.exports.socket = {}
local socket = require("socket")

function G_Helper.loadStudioFileEx(ui)
	local root = ui.root
	local name = root:getName()

	if name ~= "Node" then
		if name == "Layer" then
			local size = root:getContentSize()
			if size.width == CC_DESIGN_RESOLUTION.width and size.height == CC_DESIGN_RESOLUTION.height then
				root:setContentSize(display.size)
				ccui.Helper:doLayout(root)
			end
		else
			root:setContentSize(display.size)
			ccui.Helper:doLayout(root)
		end
	end
end

function G_Helper:gettime()
	return socket.gettime()
end
