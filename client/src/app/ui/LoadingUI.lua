local LoadingUI = class("LoadingUI", cc.Node)


function LoadingUI:ctor()
    self.ui = _MyG.loadStudioFile("LoadingScene", self)

    self:addChild(self.ui.root)

    self:setGlobalZOrder(100)
end

function LoadingUI:showLoading(time, node)
    self:hideLoding()
    
    if type(time) == "number" then
        self.time = time
        local function timer()
            self.time = self.time - 1
            if self.time <= 0 then
                self:hideLoding()
            end
        end
        schedule(self, timer, 1.0)
    end
    if node == nil then
        --cc.Director:getInstance():getNotificationNode():addChild(self)
        _MyG.APP:getCurView():addChild(self)
    else
        node:addChild(self)
    end
end

function LoadingUI:hideLoding()
    self:stopAllActions()
    if self:getParent() then
        self:removeFromParent()
    end
end

return LoadingUI