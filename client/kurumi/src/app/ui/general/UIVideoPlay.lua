-- @Author: fangcheng
-- @Date:   2022-1-16 20:29:09
-- @remark: 

local UIVideoPlay = class("UIVideoPlay", G_Class.UIMainFrame)

function UIVideoPlay:ctor()
	UIVideoPlay.super.ctor(self)

	self:loadUILua("ccs.ui.general.UI_VideoPlay")

    self:eventOnce(SysEvent.UI_AFTER_OPENED, handler(self, self.initUI), self)
end

function UIVideoPlay:initUI()
    local videoName = "plot.mp4"


    local fileUtils = cc.FileUtils:getInstance()
    local writableDir = fileUtils:getWritablePath() .. "hot_up/res/video/"
    print("writableDir", writableDir)
    if not fileUtils:isDirectoryExist(writableDir) then
        if not fileUtils:createDirectory(writableDir) then
            print("createDirectory fail:", writableDir)
            return
        end
    end

    local writablePath = writableDir .. videoName

    if not fileUtils:isFileExist(writablePath) then
        local internalPath = fileUtils:fullPathForFilename("video/" .. videoName)
        if not GTools:copyFile(internalPath, writablePath) then
            print("copyFile fail:", internalPath, writablePath)
            return
        end
    end

    local player = video.Player:create(writablePath)
    player:vplay()
    player:addTo(self.ui.Panel_Video)

    local size = player:getContentSize()
    local winSize = display.size

    local scalex = winSize.width / size.width
    local scaley = winSize.height / size.height

    player:setPosition(winSize.width * 0.5, winSize.height * 0.5)
    player:setScale(math.max(scalex, scaley))
end

function UIVideoPlay:onClickBack(sender)
	self:dismiss()
end

return UIVideoPlay