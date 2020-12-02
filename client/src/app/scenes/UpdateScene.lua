-- @Author : fangcheng
-- @Date   : 2020-02-28 21:26:16
-- @remark : 热更新场景

local UpdateScene = class("UpdateScene", cc.load("mvc").ViewBase)

function UpdateScene:onCreate()
    self.uiPage = require("scenes.UI_UpdateScene").create(function (path, node, funcName)
        return function(...) 
            if self[funcName] and type(self[funcName]) == "function" then
                self[funcName](self, ...)
            else
                print(string.format("[%s -> %s]: %s方法未实现", path, node:getName(), funcName))
            end
         end
    end)
    self:addChild(self.uiPage.root)

    self.uiPage.root:setContentSize(cc.Director:getInstance():getVisibleSize())
    ccui.Helper:doLayout(self.uiPage.root)

    self.loadingBarWidth = self.uiPage.LoadingBar_Percent:getContentSize().width

    self.uiPage.Text_Status:setString("")

    self:setPercent(0)

    print("------------------------------------")
    print("------------------------------------")
    print("------------------------------------")
    print("------------------------------------")

    self:startCheckUpdate()
    -- self:beginGame()
end

function UpdateScene:startCheckUpdate()

    if self.isUpdate then
        return
    end
    self.isUpdate = true

    local writablePath = cc.FileUtils:getInstance():getWritablePath()
    local storagePath = writablePath .. "new_version"

    -- 创建assetsManager对象
    local assetsManager = GameAssetsManager:create("res/version/project_dev.manifest", storagePath, "android")
    assetsManager:retain()

    -- 设置下载消息listener
    local function handleassetsManager(event)
        print("event------>>", event, event:getEventCode())
        if (GameAssetsManagerEvent.ALREADY_UP_TO_DATE == event:getEventCode()) then
            print("已经是最新版本了，进入游戏主界面")
            self:setPercent(100)
            self.uiPage.Text_Status:setString("最新版本")
            self:beginGame()
        end

        if (GameAssetsManagerEvent.NEW_VERSION_FOUND == event:getEventCode()) then
            print("发现新版本")

            local remoteManifest = event:getGameAssetsManager():getRemoteManifest()
            print("更新描述:", remoteManifest:getUpdateDescription())
            print("重启等级:", remoteManifest:getRestartLevel())
        end

        -- if (GameAssetsManagerEvent.UPDATE_PROGRESSION == event:getEventCode()) then
        --     print(event:getAssetId(), "进度", event:getPercent())
        --     print("更新进度=" .. assetsManager:getUpdatePercent())
        --     self:setPercent(assetsManager:getUpdatePercent())
        --     self.uiPage.Text_Status:setString("正在升级")
        -- end

        if (GameAssetsManagerEvent.UPDATE_FINISHED == event:getEventCode()) then
            print("更新完毕")
            self:setPercent(100)
            self.uiPage.Text_Status:setString("更新完毕")
            restartApp("UpdateScene")
        end

        if (GameAssetsManagerEvent.ERROR_NO_LOCAL_MANIFEST == event:getEventCode()) then
            print("发生错误:本地找不到manifest文件")
            self.uiPage.Text_Status:setString("错误:本地找不到manifest文件")
        end

        if (GameAssetsManagerEvent.ERROR_DOWNLOAD_MANIFEST == event:getEventCode()) then
            print("发生错误:下载manifest文件失败")
            self.uiPage.Text_Status:setString("错误:下载manifest文件失败")
        end

        if (GameAssetsManagerEvent.ERROR_PARSE_MANIFEST == event:getEventCode()) then
            print("发生错误:解析manifest文件失败")
            self.uiPage.Text_Status:setString("错误:解析manifest文件失败")
        end

        if (GameAssetsManagerEvent.ERROR_UPDATING == event:getEventCode()) then
            print("发生错误:更新失败")
            self.uiPage.Text_Status:setString("错误:更新失败")
        end

        if (GameAssetsManagerEvent.NEED_STRONG_UPDATE == event:getEventCode()) then
            local url = event:getGameAssetsManager():getRemoteManifest():getStrongUpdateURL()
            local description = event:getGameAssetsManager():getRemoteManifest():getStrongUpdateDescription()
            print("需要强更新,强更新地址:", url)
            print("强更新描述:", description)
            self.uiPage.Text_Status:setString("需要强更新,强更新地址:" .. url)
        end

        if (GameAssetsManagerEvent.UPDATE_FILE_SIZE == event:getEventCode()) then
            print("更新文件大小:", event:getMessage())
            -- 开始更新
            assetsManager:continueUpdate()
        end
    end

    assetsManager:setUpdateDownloadFilePercentLuaCallback(function(percent)
        print(percent)
        self:setPercent(percent)
        self.uiPage.Text_Status:setString("正在升级")
    end)


    local dispatcher = cc.Director:getInstance():getEventDispatcher()
    local eventListenerassetsManager = GameAssetsManagerEventListener:create(assetsManager, handleassetsManager)
    dispatcher:addEventListenerWithFixedPriority(eventListenerassetsManager, 1)


    -- 检查版本并升级
    assetsManager:update()
    -- assetsManager:checkUpdate()

    self.assetsManager = assetsManager
end

function UpdateScene:onExit()
    print("exit")
    if self.assetsManager then
        self.assetsManager:release()
    end
end

function UpdateScene:setPercent(percent)
    local x = self.loadingBarWidth * (percent / 100)
    self.uiPage.Panel_Load:setPositionX(x)
    self.uiPage.Node_Animation:setPositionX(x)
end

-- 已经是最新版本，直接进入游戏
function UpdateScene:beginGame()
    local function callback()
        require("app.init"):load(function()
            _MyG.ScenesManager:switchScene(_MyG.StartSceneID)
        end)
    end
    self:runAction(cc.CallFunc:create(callback))
    -- self:runAction(cc.Sequence:create(cc.DelayTime:create(5), cc.CallFunc:create(callback)))
end

return UpdateScene