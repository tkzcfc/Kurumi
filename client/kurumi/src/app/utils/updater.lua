-- @Author : fc
-- @Date   : 2021-11-03 17:19:54
-- @remark : 接口还是仿以前的C++接口,去掉散文件更新,只支持整包差异热更

local http = require('app.utils.http')
local updater = class("updater")
local lfs = require("lfs")

local CacheManifestName = "cache.manifest"
local fileUtils = cc.FileUtils:getInstance()


-- @brief 状态定义
local status = {
    NONE            = 0,  -- 无

    -- checkUpdate 函数调用会跳转的状态
    CHECKING        = 1,  -- 更新检查中...
    CHECK_FINISH    = 2,  -- 更新检查完成

    -- startUpdate 函数调用会跳转的状态
    DOWNLOADING     = 3,  -- 资源下载中...
    DECOMPRESSING   = 4,  -- 资源解压中...
    UPDATE_COMPLETE = 5,  -- 更新完成
}

local code = {
    -- checkUpdate 函数错误码
    ERROR_NO_LOCAL_MANIFEST = 0,  -- 找不到本地的清单文件
    ERROR_DOWNLOAD_MANIFEST = 1,  -- 远程清单文件下载失败
    ERROR_PARSE_MANIFEST    = 2,  -- 清单文件解析失败
    NEED_STRONG_UPDATE      = 3,  -- 需要强更新
    NEW_VERSION_FOUND       = 4,  -- 发现新版本
    ALREADY_UP_TO_DATE      = 5,  -- 已经是最新版本了

    -- startUpdate 函数错误码
    ERROR_DECOMPRESS        = 6,  -- 资源解压失败
    ERROR_DOWNLOAD          = 7,  -- 资源下载失败
    ERROR_VERIF             = 8,  -- 资源校验失败
    SUCCESS                 = 9,  -- 更新成功
}


updater.status = status
updater.code = code

-- @brief 
-- @param manifestFile 清单文件
-- @param storageDirName 更新本地存储目录名称
function updater:ctor(manifestFile, storageDirName)
    self.localManifestFile = manifestFile
    self.curStatus = status.NONE

    self:setStorageDirName(storageDirName)
end

-- @brief 检查更新
function updater:checkUpdate(resultCall, percentCall)
    assert(self.curStatus == status.NONE)

    if not fileUtils:isFileExist(self.localManifestFile) then
        resultCall(false, code.ERROR_NO_LOCAL_MANIFEST)
        return
    end

    -- 本地清单数据
    local data = fileUtils:getDataFromFile(self.localManifestFile)
    self.localData = json.decode(data)
    if self.localData == nil then
        resultCall(false, code.ERROR_PARSE_MANIFEST)
        return
    end

    -- 缓存的清单数据
    if fileUtils:isFileExist(self.cacheManifestFile) then
        local data = fileUtils:getDataFromFile(self.cacheManifestFile)
        self.cacheData = json.decode(data)
        if self.cacheData == nil then
            fileUtils:removeFile(self.cacheManifestFile)
        end
    end

    -- 如果有缓存的清单数据
    if self.cacheData then
        -- 缓存的强更版本与包内的版本不同
        local v1 = self.cacheData.strongUpdateVer
        local v2 = self.localData.strongUpdateVer

        if v1 == v2 then
            -- 使用缓存的清单数据
            self.localData = self.cacheData
        else
            -- 清空所有的更新数据
            self:repair()
            self.cacheData = nil
        end
    end

    self.curStatus = status.CHECKING
    -- 获取远程清单数据
    http.read(self.localData.remoteManifestUrl, function(ok, content)
        if ok then
            self.remoteContent = content
            self.remoteData = json.decode(content)

            -- 远程清单数据解析失败
            if self.remoteData == nil then
                resultCall(false, code.ERROR_PARSE_MANIFEST)
                self.curStatus = status.NONE
                return
            end

            assert(not self.remoteData.looseFileMode, "不支持散文件模式")

            self.curStatus = status.CHECK_FINISH

            -- 需要强更新
            if self:isNeedStrongUpdate() then
                resultCall(true, code.NEED_STRONG_UPDATE)
            else
                -- 不需要更新
                if self:versionGreater() then
                    resultCall(true, code.ALREADY_UP_TO_DATE)
                else
                    -- 版本号不一样
                    local zipfile = self:getUpdateZipFile()
                    if zipfile == nil then
                        -- 将远程清单文件写入到本地
                        fileUtils:writeStringToFile(self.remoteContent, self.cacheManifestFile)
                        -- 无需下载,此版本升级到最新版没有新增任何文件
                        resultCall(true, code.ALREADY_UP_TO_DATE)
                    else
                        self.needDownloadInfo = zipfile 
                        -- 发现新版本,需要更新
                        resultCall(true, code.NEW_VERSION_FOUND)
                    end
                end
            end
        else
            resultCall(false, code.ERROR_DOWNLOAD_MANIFEST)
            self.curStatus = status.NONE
        end
    end, percentCall)
end

-- @brief 开始更新
function updater:startUpdate(resultCall, percentCall)
    assert(self.curStatus == status.CHECK_FINISH)
    assert(self.needDownloadInfo)

    self.curStatus = status.DOWNLOADING

    local url = self.remoteData.packageUrl .. "/" .. self.needDownloadInfo.file
    local saveto = self.tempStoragePath .. "/" .. self.needDownloadInfo.file

    -- 进度更新
    local function percent(now, total)
        if total <= 0 then
            total = self.needDownloadInfo.fileSize
        end
        percentCall(now, total)
    end

    http.fetch(url, saveto, function(ok, file)
        if ok then
            -- 文件校验
            if self.needDownloadInfo.md5 == crypto.md5file(file) then
                -- 解压资源
                self:decompressResources(file, resultCall, percentCall)
            else
                -- 资源校验失败,删除对应资源
                self.curStatus = status.CHECK_FINISH
                fileUtils:removeFile(file)
                resultCall(code.ERROR_VERIF)
            end
        else
            -- 文件下载失败
            self.curStatus = status.CHECK_FINISH
            resultCall(code.ERROR_DOWNLOAD)
        end
    end, percent)
end

-- @brief 获取当前状态
function updater:getCurStatus()
    return self.curStatus
end

-- @brief 此次更新总共需要下载多少字节
function updater:getTotalSize()
    if self.needDownloadInfo == nil then return 0 end
    return self.needDownloadInfo.fileSize or 0
end

-- @brief 获取此次更新的描述
function updater:updateDescription()
    return self.remoteData.updateDescription
end

-- @brief 获取强更新地址
function updater:getStrongUpdateURL()
    return self.remoteData.remoteManifestUrl
end

-- @brief 获取强更新描述
function updater:getStrongUpdateDes()
    return self.remoteData.strongUpdateDes
end

-- @brief 获取重启等级
-- 0 : 不需要重启 
-- 1 : 程序自动重启(修改到了基础框架脚本，脚本层重启) 
-- 2 : 用户手动重启
function updater:getRestartLevel()
    return self.remoteData.restartLevel
end

-- @brief 清理更新的所有文件
function updater:repair()
    fileUtils:removeFile(self.cacheManifestFile)
    fileUtils:removeDirectory(self.storagePath)
    fileUtils:removeDirectory(self.tempStoragePath)

    fileUtils:createDirectory(self.storagePath)
    fileUtils:createDirectory(self.tempStoragePath)
end

------------------------------------------------------- private  -------------------------------------------------------
function updater:setStorageDirName(storageDirName)
    local writablePath = fileUtils:getWritablePath()

    self.storagePath = writablePath .. storageDirName
    fileUtils:createDirectory(self.storagePath)

    self.tempStoragePath = writablePath .. storageDirName .. "_tmp"
    fileUtils:createDirectory(self.tempStoragePath)

    self.cacheManifestFile = writablePath .. CacheManifestName
end

function updater:isNeedStrongUpdate()
    local v1 = tonumber(self.localData.strongUpdateVer) or 0
    local v2 = tonumber(self.remoteData.strongUpdateVer) or 0
    return v1 < v2
end

-- @brief 
-- @return true 不需要更新
-- @return false 需要更新
function updater:versionGreater()
    local la, lb, lc = string.match(self.localData.version, "(%d+)%.(%d+)%.(%d+)")
    local ra, rb, rc = string.match(self.remoteData.version, "(%d+)%.(%d+)%.(%d+)")

    la = tonumber(la)
    lb = tonumber(lb)
    lc = tonumber(lc)
    ra = tonumber(ra)
    rb = tonumber(rb)
    rc = tonumber(rc)

    if la < ra then 
        return false
    elseif la > ra then
        return true
    end

    if lb < rb then 
        return false
    elseif lb > rb then
        return true
    end

    if lc < rc then 
        return false
    elseif lc > rc then
        return true
    end

    return true
end

-- @brief 获取从当前版本到最新版需要更新的文件
function updater:getUpdateZipFile()
    local from = string.gsub(self.localData.version, "%.", "_")
    local to   = string.gsub(self.remoteData.version, "%.", "_")
    local file = string.format("%s_to_%s.zip", from, to)

    for k, v in pairs(self.remoteData.assets or {}) do
        if k == file then
            v.file = k
            return v
        end
    end
end

-- @brief 资源解压
function updater:decompressResources(zipFile, resultCall, percentCall)
    self.curStatus = status.DECOMPRESSING

    cc.decompressZipAsync(zipFile, "", true, function(ok, err)
        if ok then
            -- 解压成功,将临时目录的资源拷贝到更新目录中去
            self:copyResource()
            self.curStatus = status.UPDATE_COMPLETE
            resultCall(code.SUCCESS)
        else
            -- 资源解压失败,删除对应资源
            self.curStatus = status.CHECK_FINISH
            fileUtils:removeFile(zipFile)
            resultCall(code.ERROR_DECOMPRESS)
        end
    end, percentCall)
end

-- @brief 资源拷贝
-- 将 self.tempStoragePath 目录的资源拷贝到 self.storagePath 中去
function updater:copyResource()
    local list = {}
    updater.lookup(self.tempStoragePath, list)

    local function getNewName(name)
        name = string.sub(name, #self.tempStoragePath + 1)
        return self.storagePath .. name
    end

    for k, v in pairs(list) do
        local name = getNewName(v.name)

        if v.directory then
            -- 创建对应目录结构
            fileUtils:createDirectory(name);
        else
            fileUtils:renameFile(v.name, name)
        end
    end

    fileUtils:removeDirectory(self.tempStoragePath)
    fileUtils:createDirectory(self.tempStoragePath)
    
    -- 将远程清单文件写入到本地
    fileUtils:writeStringToFile(self.remoteContent, self.cacheManifestFile)
end

-- @brief 文件夹递归遍历
function updater.lookup(rootpath, list)
    for entry in lfs.dir(rootpath) do
        if entry ~= '.' and entry ~= '..' then  
            local path = rootpath .. '/' .. entry
            local attr = lfs.attributes(path)
            if attr.mode == "file" then
                table.insert(list, {
                    name = path
                })
            elseif attr.mode == 'directory' then
                table.insert(list, {
                    directory = true,
                    name = path
                })
                updater.lookup(path, list)
            end
        end
    end
end

return updater
