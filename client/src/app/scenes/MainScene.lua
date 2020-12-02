-- @Author: fangcheng
-- @Date:   2020-11-12 22:26:20
-- @remark: 

local MainScene = class("MainScene", G_Class.SceneBase)

function MainScene:onCreate()
	MainScene.super.onCreate(self)

	self.ui = G_Helper.loadStudioFile("scenes.UI_MainScene", self)
    self:addChild(self.ui.root)
end

function MainScene:onClickTest1(sender)
	G_UIUtils:showRemind("QwQ")
end

function MainScene:onClickTest2(sender)
	G_UIUtils:showOneBtnMsgBox("Test", function()
		print("click ok")
	end)
end

function MainScene:onClickTest3(sender)
	_MyG.ScenesManager:pushUIScene("app.windows.login.LoginWindow", { 
		onKeyBackReleasedCall = function()
			_MyG.ScenesManager:popScene()
			return true
		end
	})
end

return MainScene
