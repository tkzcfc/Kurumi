-- @Author: fangcheng
-- @Date:   2021-05-16 17:09:54
-- @remark: 

local ShieldWindow = class("ShieldWindow", require("app.common.UIBase"))

function ShieldWindow:ctor()
    ShieldWindow.super.ctor(self)

    self:setAutoDismiss(false)
    self:setPlayOpenAction(false)
    self:setPlayCloseAction(false)
    self:eternal()
    self:setCanOptimize(true)
end

return ShieldWindow

