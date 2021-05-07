-- @Author: fangcheng
-- @Date:   2021-05-07 21:48:33
-- @remark: UI弹窗类型

local UIDialog = class("UIDialog", require("app.common.UIBase"))

function UIDialog:ctor()
	UIDialog.super.ctor(self)

	self:setAutoDismiss(true)
	self:setPlayOpenAction(true)
	self:setPlayCloseAction(true)
end

return UIDialog

