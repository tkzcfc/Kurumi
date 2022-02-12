-- @Author: fangcheng
-- @Date:   2021-05-07 21:48:33
-- @remark: 弹窗类型UI

local UIDialog = class("UIDialog", require("app.common.UIBase"))

function UIDialog:ctor()
	UIDialog.super.ctor(self)

	self:setAutoDismiss(true)
	self:setPlayOpenAction(true)
	self:setPlayCloseAction(true)
end

return UIDialog

