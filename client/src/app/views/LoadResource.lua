local msgViewBase = require("app.common.msgViewBase")

local LoadResource = class("LoadResource", msgViewBase)

function LoadResource:onCreate()
	self.super.onCreate(self)

	self.ui = _MyG.loadStudioFile("LoadResource", self)
    self:addChild(self.ui.root)

    self.totalWidth = self.ui.Image_LoadBG:getContentSize().width
    self.panelheight = self.ui.Panel_Load:getContentSize().height
    self:loadUpdate(0.0)
end

function LoadResource:loadUpdate(percent)
	self.ui.ldrunning:setPositionX(percent * self.totalWidth)
	self.ui.Panel_Load:setContentSize({width = percent * self.totalWidth, height = self.panelheight})
end

function LoadResource:setNextSceneName(sceneName)
	self.nextSceneName = sceneName
end

function LoadResource:loadFinish()
end

return LoadResource