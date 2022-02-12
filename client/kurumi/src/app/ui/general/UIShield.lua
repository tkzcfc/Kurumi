-- @Author: fangcheng
-- @Date:   2021-05-16 17:09:54
-- @remark: 屏蔽层

local UIShield = class("UIShield", require("app.common.UIBase"))

function UIShield:ctor()
    UIShield.super.ctor(self)

    -- 不自动关闭
    self:setAutoDismiss(false)
    self:setPlayOpenAction(false)
    self:setPlayCloseAction(false)
    self:eternal()
    self:setCanOptimize(true)
end

return UIShield

