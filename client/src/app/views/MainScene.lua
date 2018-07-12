
local msgViewBase = require("app.common.msgViewBase")
local MainScene = class("MainScene", msgViewBase)


--MainScene.RESOURCE_FILENAME = "MainScene.csb"

function MainScene:onCreate()
    MainScene.super.onCreate(self)
    self.ui = _MyG.loadStudioFile("zhucheng", self)
    self:addChild(self.ui.root)
    changeParticleSystemPositionType(self.ui.root)

    self.ui.ScrollView:jumpToPercentHorizontal(35)
    self.ui.ScrollView:setScrollBarEnabled(false)
end

function MainScene:onClickEnter()
    _MyG.GameSceneSwither:enterScene(_MyG.SCENE_ID_SELECT)
end


--根据依赖编辑器中编辑框某些属性创建编辑框
--1需要替换的节点 2代理表(事件来时代理表[callname](代理表,...)) 3编辑框背景图片 nil
function MainScene:StudioTextFieldCreateEdit(TextField,HandleTable,backImagePath)

    -- if type(TextField) ~= "userdata" or tolua.type(TextField) ~= "ccui.TextField" then
    --     printError("传入节点错误导致创建失败TextField = ",tolua.type(TextField).."ParentName = "..TextField:getParent():getName())
    --     return nil
    -- elseif type(HandleTable) ~= "table" and type(HandleTable) ~= "userdata" then
    --     printError("代理表错误,请传入一个table表")
    --     return nil
    -- end

    --dump({TextField,HandleTable,backImagePath,type(TextField),tolua.type(TextField)})
    local TextFieldSize = TextField:getContentSize()
    if TextFieldSize.height > TextField:getFontSize() * 1.5 then
    else
        TextFieldSize.height = TextFieldSize.height * 1.5
    end
    local Edit = ccui.EditBox:create(TextFieldSize,backImagePath or "")--创建编辑框

    --拷贝属性
    --Edit:setIgnoreAnchorPointForPosition(false)
    Edit:setAnchorPoint(TextField:getAnchorPoint())
    Edit:setPosition(TextField:getPosition())
    Edit:setTag(TextField:getTag())
    Edit:setName(TextField:getName())
    Edit:setText(TextField:getString())
    Edit.PlaceholderFontSize = TextField:getFontSize()
    Edit:setPlaceholderFontSize(Edit.PlaceholderFontSize)--自动设置默认值的字体大小

    Edit.getPlaceholderFontSize = function (edit) return edit.PlaceholderFontSize end
    Edit:setPlaceHolder(TextField:getPlaceHolder())
    Edit:setMaxLength(TextField:getMaxLength())
    Edit._setMaxLength = function (self,MaxLength)
        self.MaxLength = MaxLength or self:getMaxLength()
        self:setMaxLength(100000)
    end
    Edit._getMaxLength = function (self)
        return self.MaxLength
    end
    --Edit:setMaxLength(TextField:getMaxLength())
    Edit:setPlaceholderFontColor(TextField:getColor())
    Edit:setFontName(TextField:getFontName())
    Edit:setFontSize(Edit.PlaceholderFontSize - 2)
    Edit.callbackname = TextField:getCallbackName()
    Edit:setCallbackName(Edit.callbackname)
    local ParentNode = TextField:getParent()
    Edit:registerScriptEditBoxHandler(function (eventName, sender)
        return true
        -- Edit.Type = eventName
        -- if eventName == "began" then
        --     Edit.__StartInText = true
        -- elseif (eventName == "ended" or eventName == "return") then
        --      tools.IntervalCallback(ParentNode,2,function ( ... )
        --         Edit.__StartInText = nil
        --         return false
        --     end)

        -- end
        -- -- if Edit.callbackname and type(HandleTable[Edit.callbackname]) == "function" then
        -- --     HandleTable[Edit.callbackname](HandleTable,eventName, sender)
        -- -- else--if _MyG.debug == true then
        -- --     --没有设置回调处理事件，或者代理表没有实现回调处理函数
        -- --     print(Edit.callbackname)
        -- -- end
    end)
    TextField:removeFromParent()
    ParentNode:addChild(Edit)
    --设置默认值
    Edit:setReturnType(cc.KEYBOARD_RETURNTYPE_DONE)
    return Edit
end

return MainScene
