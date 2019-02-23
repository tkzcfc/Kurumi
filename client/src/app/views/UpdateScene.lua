local msgViewBase = require("app.common.msgViewBase")

local UpdateScene = class("UpdateScene", msgViewBase)

function UpdateScene:onCreate()
	UpdateScene.super.onCreate(self)

    self.ui = _MyG.loadStudioFile("UpdateScene", self)
    self:addChild(self.ui.root)

    self.totalWidth = self.ui.Image_LoadBG:getContentSize().width
    self.panelheight = self.ui.Panel_Load:getContentSize().height
    self:setPercent(0)

    self:setUpdateTip("更新检查中...")
    self:doUpdate()
end

function UpdateScene:doUpdate()
    local writablePath = cc.FileUtils:getInstance():getWritablePath()
    local storagePath = writablePath .. "new_version"

    -- 获取平台信息
    local targetPlatform = cc.Application:getInstance():getTargetPlatform()
    
    local platformName = "android"
    if targetPlatform == cc.PLATFORM_OS_WINDOWS then
        platformName = "windows"
    elseif targetPlatform == cc.PLATFORM_IOS then
        platformName = "ios"
    end

    -- 创建assetsManager对象
    local assetsManager = GameAssetsManager:create("res/version/project_dev.manifest", storagePath, platformName)
    assetsManager:retain()

    -- 设置下载消息listener
    local function handleassetsManager(event)
        if (GameAssetsManagerEvent.ALREADY_UP_TO_DATE == event:getEventCode()) then
            print("已经是最新版本了，进入游戏主界面")
            self:setPercent(100)
            self:setUpdateTip("无需更新")
            self:noUpdateAndEnterNextScene()
        end

        if (GameAssetsManagerEvent.NEW_VERSION_FOUND == event:getEventCode()) then
            print("发现新版本")
            
            local remoteManifest = event:getGameAssetsManager():getRemoteManifest()

            self.newVersionFoundTag = true
            self.updateDescription = remoteManifest:getUpdateDescription()
            self.restartLevel = remoteManifest:getRestartLevel()
            print("更新描述:", self.updateDescription)
            print("重启等级:", self.restartLevel)

            self:setUpdateTip("获取更新列表...")            
            self:tryShowBox()
        end

        -- if (GameAssetsManagerEvent.UPDATE_PROGRESSION == event:getEventCode()) then
        --     print(event:getAssetId(), "进度", event:getPercent())
        --     print("更新进度=" .. assetsManager:getUpdatePercent())
        -- end

        if (GameAssetsManagerEvent.UPDATE_FINISHED == event:getEventCode()) then
            print("更新完毕")
            self:setPercent(100)
            self:setUpdateTip("更新完毕")

            local box = require("app.ui.MessageBoxUI"):new()

            -- 重启等级
            -- 说明：0->不需要重启 1->程序自动重启 2->用户手动重启
            if self.restartLevel == 2 then
                box:showBox("更新完毕，请手动重启APP", function()
                    os.exit(0)
                end, nil, self)
            elseif self.restartLevel == 0 then
                box:showBox("更新完毕", function()
                    self:noUpdateAndEnterNextScene()
                end, nil, self)
            else
                box:showBox("更新完毕，即将重启", function()
                    restartApp()
                end, nil, self)
            end
        end

        if (GameAssetsManagerEvent.ERROR_NO_LOCAL_MANIFEST == event:getEventCode()) then
            print("发生错误:本地找不到manifest文件")
            self:setUpdateTip("错误:本地找不到manifest文件")
        end

        if (GameAssetsManagerEvent.ERROR_DOWNLOAD_MANIFEST == event:getEventCode()) then
            print("发生错误:下载manifest文件失败")
            self:setUpdateTip("错误:下载manifest文件失败")
        end

        if (GameAssetsManagerEvent.ERROR_PARSE_MANIFEST == event:getEventCode()) then
            print("发生错误:解析manifest文件失败")
            self:setUpdateTip("错误:解析manifest文件失败")
        end

        if (GameAssetsManagerEvent.ERROR_UPDATING == event:getEventCode()) then
            print("发生错误:更新失败")
            self:setUpdateTip("错误:更新失败")
        end

        if (GameAssetsManagerEvent.NEED_STRONG_UPDATE == event:getEventCode()) then
            self:showStrongUpdateBox(event)
        end

        if (GameAssetsManagerEvent.UPDATE_FILE_SIZE == event:getEventCode()) then
            print("更新文件大小:", event:getMessage())
            self.updateFileSize = event:getMessage()
            self:tryShowBox()
        end
    end

    assetsManager:setUpdateDownloadFilePercentLuaCallback(function(percent)
        print(percent)
        self:setPercent(percent)
        self:setUpdateTip(string.format("资源更新中(%0.1f%%)...", percent))
    end)


    local dispatcher = cc.Director:getInstance():getEventDispatcher()
    local eventListenerassetsManager = GameAssetsManagerEventListener:create(assetsManager, handleassetsManager)
    dispatcher:addEventListenerWithFixedPriority(eventListenerassetsManager, 1)


    -- 检查版本并升级
    assetsManager:update()

    self.assetsManager = assetsManager
end

function UpdateScene:onExit()
    print("exit")
    if self.assetsManager then
        self.assetsManager:release()
    end
end

function UpdateScene:tryShowBox()
    if self.newVersionFoundTag == nil or self.updateFileSize == nil then
        return
    end

    local winSize = cc.Director:getInstance():getVisibleSize()

    local size = tonumber(self.updateFileSize)
    if size == nil then
        size = self.updateFileSize
    else
        local kb = 1024
        local mb = 1024 * 1024
        if size > mb then
            size = size / mb
            size = string.format("%.02fMB", size)
        elseif size > kb then
            size = size / kb
            size = string.format("%dKB", size)
        end
    end

    -- 描述内容
    local description = "更新大小: "
    description = description..tostring(size).."\n"
    description = description .. "更新内容: "
    description = description .. self.updateDescription

    local function okCallfunc()
        --开始更新
        self.assetsManager:continueUpdate()
    end

    local function cancelCallfunc()
        os.exit(0)
    end

    local msgbox = require("app.ui.ScrollMsgBoxUI"):new()
    msgbox:setPosition(winSize.width * 0.5, winSize.height * 0.5)
    msgbox:setTitle("更新提示")
    msgbox:setButtonOKTitle("开始更新")
    msgbox:setButtonCancelTitle("取消更新")
    msgbox:showBox(description, okCallfunc, cancelCallfunc)
    self:addChild(msgbox)
end

function UpdateScene:showStrongUpdateBox(event)
    local url = event:getGameAssetsManager():getRemoteManifest():getStrongUpdateURL()
    local description = event:getGameAssetsManager():getRemoteManifest():getStrongUpdateDescription()
    print("需要强更新,强更新地址:", url)
    print("强更新描述:", description)
    self:setPercent(100)
    self:setUpdateTip("")

    -- 提示框显示
    local winSize = cc.Director:getInstance():getVisibleSize()
    
    local function okCallfunc()
        --跳转至更新链接
        cc.Application:getInstance():openURL(url); 
    end

    local function cancelCallfunc()
        os.exit(0)
    end

    local msgbox = require("app.ui.ScrollMsgBoxUI"):new()
    msgbox:setPosition(winSize.width * 0.5, winSize.height * 0.5)
    msgbox:setTitle("更新提示")
    msgbox:setButtonOKTitle("前往更新")
    msgbox:setButtonCancelTitle("取消更新")
    msgbox:showBox(description, okCallfunc, cancelCallfunc)
    self:addChild(msgbox)
end

function UpdateScene:setPercent(percent)
    percent = percent / 100
    percent = math.max(percent, 0.0)
    percent = math.min(percent, 1.0)
    self.ui.ldrunning:setPositionX(percent * self.totalWidth)
    self.ui.Panel_Load:setContentSize({width = percent * self.totalWidth, height = self.panelheight})
end

function UpdateScene:setUpdateTip(tip)
    self.ui.Text_Tip:setString(tip)
end

function UpdateScene:noUpdateAndEnterNextScene()
    require("app.init.init")
    self:delayCall(self, 0.2, function()
        _MyG.APP:run(_MyG.StartScene)
    end)
end

function UpdateScene:delayCall( node, delay, callback )
    local delay = cc.DelayTime:create( delay )
    local sequence = cc.Sequence:create( delay, cc.CallFunc:create( callback ) )
    node:runAction( sequence )
end

return UpdateScene

