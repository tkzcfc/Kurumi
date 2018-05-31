local CreateScene = class("CreateScene", cc.load("mvc").ViewBase)

function CreateScene:onCreate()
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