-- @Author: fangcheng
-- @Date:   2020-11-07 16:35:19
-- @remark: UI场景，可以将任何UIWindow对象场景化

local UIScene = class("UIScene", G_Class.SceneBase)

function UIScene:onCreate()
    UIScene.super.onCreate(self)
end

function UIScene:initWithParameter(args)
    if type(args) ~= 'table' then
        assert(0)
    	return
    end
    print("UIScene:initWithParameter begin", tostring(self))
    print_lua_value(args)
    print("UIScene:initWithParameter end", tostring(self))

    -- self:loadBG("resource/bg/loadingbg.png")

    self.args = args

    local windowName = self.args.windowName

    local window = require(windowName).new()
	window:disEnableAutoDismiss()
	window:setEnableCloseAnimation(false)
	window:setShowMask(false)
    window:keepOutOptimize()
    window:setLocalZOrder(0)
    self:addChild(window)

    if self.args.onInit then
        self.args.onInit(window, scene)
    end

	self.window = window

    window:iBeforeOpenedWindow()
end

-- function UIScene:loadBG(res, resType)

--     if self.__sprite_bg then
--         self.__sprite_bg:removeFromParent()
--         self.__sprite_bg = nil
--     end

--     resType = resType or 0
--     if resType == 0 then
--         if cc.FileUtils:getInstance():isFileExist(res) then
--             local sprite = cc.Sprite:create(res)
--             sprite:setPosition(G_MAC.SCREEN_WIDTH_HALF, G_MAC.SCREEN_HEIGHT_HALF)
--             self:addChild(sprite, -1)
--             self.__sprite_bg = sprite
--         else
--             logE("UIScene:loadBG  找不到资源", res, resType)
--         end
--     else
--         local sp = cc.SpriteFrameCache:getInstance():getSpriteFrame(res)
--         if sp then
--             local sprite = cc.Sprite:createWithSpriteFrame(sp)
--             sprite:setPosition(G_MAC.SCREEN_WIDTH_HALF, G_MAC.SCREEN_HEIGHT_HALF)
--             self:addChild(sprite, -1)

--             self.__sprite_bg = sprite
--         else
--             logE("UIScene:loadBG  找不到资源", res, resType)
--         end
--     end
-- end

function UIScene:onEnter()
    self.window:iAfterOpenedWindow()
    UIScene.super.onEnter(self)
end

function UIScene:onExit()
    self.window:iWillCloseWindow()
    self.window:iAfterClosedWindow()
    UIScene.super.onExit(self)
end

function UIScene:onKeyBackReleased()
    if self.args.onKeyBackReleasedCall then
        return self.args.onKeyBackReleasedCall()
    end
    if _MyG.ScenesManager:canPopScene() then
        _MyG.ScenesManager:popScene()
        return true
    end
end

return UIScene