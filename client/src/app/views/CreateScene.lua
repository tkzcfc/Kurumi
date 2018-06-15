local msgViewBase = require("app.common.msgViewBase")

local CreateScene = class("CreateScene", msgViewBase)

function CreateScene:onCreate()
	self.super.onCreate(self)
	self.ui = _MyG.loadStudioFile("CreateScene", self)
    self:addChild(self.ui.root)
end

function CreateScene:onClickSelect(sender)
end

function CreateScene:onClickCreate(sender)
	local nickName = self.ui.TextField_NickName:getString()
	print(nickName)
	_MyG.APP:run("GameMain")
end 

return CreateScene