-- @Author : fc
-- @Date   : 2021-11-12 10:01:02
-- @remark : 

local TestScene = class("TestScene", function()
    return display.newScene("TestScene")
end)

function TestScene:ctor()

    self:init()
    -- self:addComponent(cc.ComponentLua:create("mugen/TestComponent.lua"))
end

function TestScene:init()

    self.uiPage = require("ccs.scenes.UI_TestScene").create(function (path, node, funcName)
        return function(...) 
            if self[funcName] and type(self[funcName]) == "function" then
                self[funcName](self, ...)
            else
                print(string.format("[%s -> %s]: %s方法未实现", path, node:getName(), funcName))
            end
         end
    end)
    self:addChild(self.uiPage.root)

    self.uiPage.root:setContentSize(display.size)
    ccui.Helper:doLayout(self.uiPage.root)

    self.uiPage.text_left:setVisible(false)
    self.uiPage.text_right:setVisible(false)
    self.uiPage.text_normal:setVisible(false)

    self.uiPage.btn_left:setMultipleTouchEnabled(true)
    self.uiPage.btn_right:setMultipleTouchEnabled(true)


    self:setGlobalMultiTouchEnabled(false)

    local spr = cc.Sprite:create("role/pvp_role/hero_pk_dao_baiji.png")
    spr:addTo(self, 0xffff)
    spr:setPosition(display.cx, display.cy)
    spr:addNodeEventListener(cc.NODE_TOUCH_EVENT, function(event)
        if event.name == "began" then
            spr:setColor(cc.c4b(255, 0, 0, 255))
        elseif event.name == "ended" or event.name == "cancelled" then
            spr:setColor(cc.c4b(255, 255, 255, 255))
        end
        return true
    end)
    -- TOUCHES_ALL_AT_ONCE
    -- TOUCHES_ONE_BY_ONE
    spr:setTouchMode(cc.TOUCHES_ALL_AT_ONCE)
    spr:setTouchEnabled(true)
end

function TestScene:onTouchLeft(sender, type)
    self.uiPage.text_left:setVisible(type < 2)
end

function TestScene:onTouchRight(sender, type)
    self.uiPage.text_right:setVisible(type < 2)
end

function TestScene:onTouchBtnNormal(sender, type)
    self.uiPage.text_normal:setVisible(type < 2)    
end

function TestScene:onClickBtnGlobal(sender)
    self:setGlobalMultiTouchEnabled(not self:getEventDispatcher():isGlobalMultiTouchEnabled())
end

function TestScene:setGlobalMultiTouchEnabled(enabled)
    self:getEventDispatcher():setGlobalMultiTouchEnabled(enabled)

    if enabled then
        self.uiPage.text_global:setString("开启全局范围多点触摸")
    else
        self.uiPage.text_global:setString("关闭全局范围多点触摸")
    end
    self.uiPage.text_global:setVisible(false)
end

return TestScene