-- @Author: fangcheng
-- @Date:   2020-11-22 19:18:29
-- @remark: 角色创建界面

local CreateWindow = class("CreateWindow", G_Class.UIWindow)

local RoleConfig = {
	-- 刀
	[1] = 
	{
		file = "plist/uianimation/baijixiuluo.ExportJson",
		armatureName = "baijixiuluo",
		isopen = true,
		roleId = Const.Role.DAO
	},
	-- 弓
	[2] = 
	{
		file = "plist/uianimation/baijiluocha.ExportJson",
		armatureName = "baijiluocha",
		isopen = false,
		roleId = Const.Role.GONG
	},
}

function CreateWindow:ctor()
	CreateWindow.super.ctor(self)

	self:loadUILua("windows.home.UI_CreateWindow")

	self.selectIndex = 1
	self.ui.Button_Create:setTouchEnabled(true)
	self.ui.Button_Create:setEnabled(true)
end


function CreateWindow:initNetEvent()
	self:onNetMsg(MessageID.MSG_CREATE_ROLE_ACK, handler(self, self.onCreateRoleAck))
end

function CreateWindow:onCreateRoleAck(msg)
	if msg.code == errCode.SUCCESS then
		self:dismiss()
		self:on("onAfterClosedWindow", function()
			_MyG.LoginManager:requestEnterGame(msg.roleID)
		end, self)
	else
		UIUtils:showError(msg.code)
	end
end

function CreateWindow:loadFinish(percent)
	if percent >= 1.0 then
		if self.armatureRender == nil then
			local child = self.ui.Panel_Content:getChildren()

			for k,v in pairs(child) do
				if tolua.type(v) == "ccs.Armature" then
					self.armatureRender = v
					break
				end
			end
		end

		self.armatureRender:init(RoleConfig[self.selectIndex].armatureName)
		self.armatureRender:getAnimation():playWithIndex(0)

		-- 职业未开放
		if not RoleConfig[self.selectIndex].isopen then
			UIUtils:showError(113)
		end
	end
end

function CreateWindow:onClickSelect(sender)
	local index = tonumber(sender.UserData[1])
	if self.selectIndex == index then
		return
	end
	self.selectIndex = index

	self.ui.Button_Create:setTouchEnabled(RoleConfig[self.selectIndex].isopen)
	self.ui.Button_Create:setEnabled(RoleConfig[self.selectIndex].isopen)

	ccs.ArmatureDataManager:getInstance():addArmatureFileInfoAsync(RoleConfig[index].file, handler(self, self.loadFinish))
end

function CreateWindow:onClickCreate(sender)
	local nickName = self.ui.TextField_NickName:getString()
	if nickName == "" then
		UIUtils:showError(114)
		return
	end

	_MyG.NetManager:sendToGame(MessageID.MSG_CREATE_ROLE_REQ, {
		occupation = RoleConfig[self.selectIndex].roleId,
		name = nickName,
	})
end 


return CreateWindow