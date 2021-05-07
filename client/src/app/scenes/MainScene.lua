-- @Author: fangcheng
-- @Date:   2020-11-12 22:26:20
-- @remark: 主场景

local MainScene = class("MainScene", G_Class.SceneBase)

local kType = {
	FIGHT = 1,
}

function MainScene:onCreate()
	MainScene.super.onCreate(self)

	self:loadUILua("scenes.UI_MainScene")

	changeParticleSystemPositionType(self.ui.root, 2)

    self.ui.ScrollView:jumpToPercentHorizontal(35)
    self.ui.ScrollView:setScrollBarEnabled(false)

    local children = self.ui.Panel_Touch:getChildren()
    for k, v in pairs(children) do
        UIUtils:addClickEventListener(v, function()
        	self:onClickUnit(v.UserData[1])
    	end)
    end
end

function MainScene:onClickUnit(sysId)
	print("onClickUnit", sysId)

	require("app.windows.home.MapWindow").new():show()
end

function MainScene:onClickEnter()
    -- _MyG.ScenesManager:enterScene(_MyG.SCENE_ID_SELECT)

    print("onClickEnter---------->>")
end

return MainScene
