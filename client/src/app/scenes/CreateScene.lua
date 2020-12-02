local msgViewBase = require("app.common.msgViewBase")

local CreateScene = class("CreateScene", msgViewBase)

function CreateScene:onCreate(name, args)
	CreateScene.super.onCreate(self)
	self.ui = _MyG.loadStudioFile("CreateScene", self)
	self:addChild(self.ui.root)
	
	self:initSecne()
end

function CreateScene:initSecne()
	self.selectIndex = 1
	self.ui.Button_6:setTouchEnabled(true)
	self.ui.Button_6:setEnabled(true)

	local chilrend = self.ui.root:getChildren()

	self.selectRoleConfig = {}
	self.selectRoleConfig[1] = 
	{
		file = "uianimation/baijixiuluo.ExportJson",
		armatureName = "baijixiuluo",
	}
	self.selectRoleConfig[2] = 
	{
		file = "uianimation/baijiluocha.ExportJson",
		armatureName = "baijiluocha",
	}
end

function CreateScene:loadFinish(percent)
	if percent >= 1.0 then
		self.ui.baijixiuluo:init(self.selectRoleConfig[self.selectIndex].armatureName)
		self.ui.baijixiuluo:getAnimation():playWithIndex(0)

		if not self.isShowBox then
			_MyG.MessageBox:showBox("该职业尚未开放")
			self.isShowBox = true
		end
	end
end

function CreateScene:onClickSelect(sender)
	local index = tonumber(sender.UserData[1])
	if self.selectIndex == index then
		return
	end

	if index == 1 then
		self.ui.Button_6:setTouchEnabled(true)
		self.ui.Button_6:setEnabled(true)
	elseif index == 2 then
		self.ui.Button_6:setTouchEnabled(false)
		self.ui.Button_6:setEnabled(false)
	else
		return
	end
	self.selectIndex = index
	ccs.ArmatureDataManager:getInstance():addArmatureFileInfoAsync(self.selectRoleConfig[index].file, function(...) self:loadFinish(...) end)
end

function CreateScene:onClickCreate(sender)
	local nickName = self.ui.TextField_NickName:getString()
	_MyG.ScenesManager:enterScene(_MyG.SCENE_ID_MAIN)
end 

return CreateScene