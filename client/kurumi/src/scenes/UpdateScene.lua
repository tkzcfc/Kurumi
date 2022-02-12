-- @Author : fangcheng
-- @Date   : 2020-02-28 21:26:16
-- @remark : 热更新场景

local UpdateScene = class("UpdateScene", function()
    return display.newScene("UpdateScene")
end)

local updater = require("app.utils.updater")
local update_status = updater.status
local update_code = updater.code

-- 禁用热更新
local disableHotUpdate = false

-- 格式化大小
local function fmt(size)
    if size < 1024 then
        return string.format("%dbytes", size)
    elseif size < 1024 * 1024 then
        return string.format("%.2fkb", size / 1024)
    elseif size < 1024 * 1024 * 1024 then
        return string.format("%.2fmb", size / 1024 / 1024)
    end
    return string.format("%.2fgb", size / 1024 / 1024 / 1024)
end

function UpdateScene:ctor()
    self:initUI()

    if disableHotUpdate then
        self:updateFinish()
    else
        self:checkUpdate()
    end
end

-- @brief 
function UpdateScene:initUI()
    self.uiPage = require("ccs.scenes.UI_UpdateScene").create(function (path, node, funcName)
        return function(...) 
            if self[funcName] and type(self[funcName]) == "function" then
                self[funcName](self, ...)
            else
                print(string.format("[%s -> %s]: %s方法未实现", path, node:getName(), funcName))
            end
         end
    end)
    self:addChild(self.uiPage.root)

    self.uiPage.root:setContentSize(display.size)
    ccui.Helper:doLayout(self.uiPage.root)

    -- 进度条宽度
    self.loadingBarWidth = self.uiPage.LoadingBar_Percent:getContentSize().width
    -- 当前状态
    self.uiPage.Text_Status:setString("")
    -- 更新进度文字
    self.uiPage.Text_Percent:setString("")
    -- 设置默认进度为0
    self:setPercent(0)
end

-- @brief 检测更新
function UpdateScene:checkUpdate()
    self:setTip("检查更新...")

    self.updater = updater.new("res/version/project_dev.manifest", "hot_up")

    local function result(success, code)
        local str = "检查更新失败:"
        if success then
            str = "检查更新成功:"
        end

        if code == update_code.ERROR_NO_LOCAL_MANIFEST then
            str = str .. "错误:找不到本地的清单文件"
        elseif code == update_code.ERROR_DOWNLOAD_MANIFEST then
            str = str .. "错误:远程清单文件下载失败"
        elseif code == update_code.ERROR_PARSE_MANIFEST then
            str = str .. "错误:清单文件解析失败"
        elseif code == update_code.NEED_STRONG_UPDATE then
            str = str .. "需要强更新"

            print("强更新的描述:", self.updater:getStrongUpdateDes())
            print("强更新的地址:", self.updater:getStrongUpdateURL())

        elseif code == update_code.NEW_VERSION_FOUND then
            str = str .. "发现新版本"
            self.uiPage.Text_Percent:setString("")

            print("需要更新大小:", fmt(self.updater:getTotalSize()))
            print("此次更新的描述:", self.updater:updateDescription())
            self:doUpdate()
        elseif code == update_code.ALREADY_UP_TO_DATE then
            str = str .. "已经是最新版本了"
            self:updateFinish()
        end

        self:setTip(str)
        print(str)
    end

    local function percent(now, total)
        if total == 0 then
            self:setPercent(0)
        else
            self:setPercent(now / total * 100)
        end
        self:setTextPercent(fmt(now), fmt(total), "检查更新")
    end

    self.updater:checkUpdate(result, percent)
end

-- @brief 开始更新
function UpdateScene:doUpdate()
    local function result(code)
        local str = ""
        if code == update_code.ERROR_DECOMPRESS then
            str = "错误:资源解压失败"
        elseif code == update_code.ERROR_DOWNLOAD then
            str = "错误:资源下载失败"
        elseif code == update_code.ERROR_VERIF then
            str = "错误:资源校验失败"
        elseif code == update_code.SUCCESS then
            str = "更新成功"

            -- 重启等级
            local level = self.updater:getRestartLevel()
            print("level:", level)
            if level == 0 then
                -- 直接进入游戏
                self:updateFinish()
            elseif level == 1 then
                -- 修改到了基础框架脚本
                restartGame()
            else
                -- 需要提示用户手动重启
            end
        end

        self:setTip(str)
        print(str)
    end

    local function percent(now, total)
        if total == 0 then
            self:setPercent(0)
        else
            self:setPercent(now / total * 100)
        end

        if self.updater:getCurStatus() == update_status.DOWNLOADING then
            self:setTextPercent(fmt(now), fmt(total), "资源下载中")
        elseif self.updater:getCurStatus() == update_status.DECOMPRESSING then
            self:setTextPercent(now, total, "资源解压中")
        end
    end
    self.updater:startUpdate(result, percent)
end

-- @brief 设置当前进度条进度
-- @param percent [0,100]
function UpdateScene:setPercent(percent)
    local size = self.uiPage.Panel_Load:getContentSize()
    size.width = self.loadingBarWidth * (percent / 100)

    self.uiPage.Panel_Load:setContentSize(size)
    self.uiPage.Node_Animation:setPositionX(size.width)
end

-- @brief 设置进度条下方的文本提示
function UpdateScene:setTip(str)
    self.uiPage.Text_Status:setString(str)
end

-- @brief 设置进度条上方的文本进度
function UpdateScene:setTextPercent(now, total, head)
    now = tostring(now)
    total = tostring(total)

    if head == nil then
        head = ""
    else
        head = head .. ":"
    end

    local str = string.format("%s%s/%s", head, now, total)
    self.uiPage.Text_Percent:setString(str)
end

---------------------------------------------------------- util ----------------------------------------------------------

-- 已经是最新版本，直接进入游戏
function UpdateScene:updateFinish()
    local loadGame = handler(self, self.loadGame)
    self:runAction(cc.CallFunc:create(loadGame))
    -- self:runAction(cc.Sequence:create(cc.DelayTime:create(5), cc.CallFunc:create(loadGame)))
end

-- @brief 载入游戏
function UpdateScene:loadGame()
    self:setTip("进入游戏...")
    self.uiPage.Text_Percent:setString("")

    local progress = function(percent)
        self:setPercent(percent * 100)
    end

    local function finish()
        display.replaceScene(require("scenes.GameScene").new())
    end

    local loader = require("app.loader").new()
    loader:load(progress, function()
        self:runAction(cc.CallFunc:create(finish))
    end)
    
        -- display.replaceScene(require("scenes.TestScene").new())
end

return UpdateScene