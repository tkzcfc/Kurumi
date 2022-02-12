-- @Author : fc
-- @Date   : 2021-10-29 15:21:42
-- @remark : 

local GameScene = class("GameScene", function()
    return display.newScene("GameScene")
end)

propertyReadOnly(GameScene, "pViewRoot")
propertyReadOnly(GameScene, "pMaskLayer")

local Z = enum {
    "VIEW_ROOT",
    "MASK_LAYER"
}

function GameScene:ctor()
    _MyG.GameScene = self
    self:initialize()
end

function GameScene:initialize()    
    -- 界面根节点
    self.pViewRoot = cc.Node:create()
    self:addChild(self.pViewRoot, Z.VIEW_ROOT)

    self:createMaskLayer()

    -- 初始化界面管理
    _MyG.ViewManager:clear()
    _MyG.ViewManager:setViewRoot(self.pViewRoot)

    -- 进入登录界面
    _MyG.ViewManager:runView(require("app.views.LoginView").new())
end

-- @brief 创建mask层
function GameScene:createMaskLayer()
    local maskLayer = ccui.Layout:create()
    maskLayer:setContentSize(display.size)
    maskLayer:setBackGroundColorType(ccui.LayoutBackGroundColorType.solid)
    maskLayer:setBackGroundColor(cc.c3b(0, 0, 0))
    maskLayer:setBackGroundColorOpacity(255)
    maskLayer:setVisible(false)
    maskLayer:setTouchEnabled(true)
    self:addChild(maskLayer, Z.MASK_LAYER)

    self.pMaskLayer = maskLayer
end

return GameScene

