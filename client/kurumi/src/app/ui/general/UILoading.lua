-- @Author: fangcheng
-- @Date:   2020-11-07 21:41:24
-- @remark: 

local UILoading = class("UILoading", G_Class.SuperNode)


function UILoading:ctor()
    self.ui = G_Helper.loadStudioFile("ccs.ui.general.UI_Loading", self)
    self:addChild(self.ui.root)
end

function UILoading:showLoading(time, timeOutCall, node, zorder)
    self:hideLoding()
    
    if type(time) == "number" then
        self.co_timeout = oRoutine(o_once(function() 
            o_wait(o_seconds(time))
            if timeOutCall then
                timeOutCall()
            end
            self:hideLoding()
        end))
    end

    if node == nil then
        cc.Director:getInstance():getRunningScene():addChild(self, 0xffff)
    else
        node:addChild(self, zorder or 0xffff)
    end
end

function UILoading:hideLoding()
    if self.co_timeout then
        oRoutine:skill(self.co_timeout)
        self.co_timeout = nil
    end
    if self:getParent() then
        self:removeFromParent()
    end
end

return UILoading