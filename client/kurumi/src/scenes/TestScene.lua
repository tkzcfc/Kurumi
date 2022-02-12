-- @Author : fc
-- @Date   : 2021-11-12 10:01:02
-- @remark : 

local TestScene = class("TestScene", function()
    return display.newScene("TestScene")
end)

function TestScene:ctor()

    -- self:init()
    self:addComponent(cc.ComponentLua:create("mugen/TestComponent.lua"))
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
end

return TestScene