
local helper = require("helper")

-- 修订号最大值
local REVISION_MAX = 100


assets = {}
config = {}


local tmpLuaFile = lfs.currentdir() .. "/tmp.lua"

-- @param major 主版本
-- @param minor 次版本号
-- @param revision 修订号
local function getOutDir(root, major, minor, revision)
    return string.format("%s/v%d/%d_%d_%d/", root, major, major, minor, revision)
end

-- @brief 获取差异资源列表
local function getDifferenceAssets(oldAssets, newAssets)
    local files = {}
    for k, v in pairs(newAssets) do
        local asset = oldAssets[k]
        if asset and asset.fileSize == v.fileSize and asset.md5 == v.md5 then
            -- 文件相同
        else
            table.insert(files, k)
        end
    end
    return files
end

-- @brief 获取差异文件夹名称
local function getDifferenceDirName(oldVersion, newVersion)
    oldVersion = string.gsub(oldVersion, "%.", "_")
    newVersion = string.gsub(newVersion, "%.", "_")

    return string.format("%s_to_%s", oldVersion, newVersion)
end 


-- @brief 是否忽略文件
local function igore(igoreList, fileName)
    for k, v in pairs(igoreList) do
        local len = string.len(v)

        -- 以*结尾
        if string.byte(v, string.len(v)) == 42 then
            local prefix_1 = string.sub(v, 1, -2)
            local prefix_2 = string.sub(fileName, 1, len - 1)
            if prefix_1 == prefix_2 then return true end
        else
            if fileName == v then return true end
        end
    end

    return false
end

-- @brief 文件处理
local function fileHandling(inFile, outPath, fileName)
    local removeInFile = false

    if config["usePngquant"] and helper.file_extension(inFile) == "png" then
        local newFile = helper.pngquant(inFile)
        removeInFile = newFile ~= inFile
        inFile = newFile
    end

    -- 加密用到的sign
    local encryptsign = config["encryptsign"]
    -- 加密用到的key
    local encryptkey = config["encryptkey"]
    
    -- 文件内容
    local content = helper.file_read(inFile)
    local fileSize  = string.len(content)

    -- 启用xxtea加密
    if config["enableXXTea"] then
        local extension = helper.file_extension(inFile)
        if extension == "lua" then
            local data, len = xxtea.encode(content, encryptkey)
            data = encryptsign .. data

            content = data
            fileSize = len + string.len(encryptsign)
        end
    end

    local t = {}
    t["md5"]       = helper.md5(content)
    t["fileSize"]  = fileSize
    assets[fileName] = t

    -- 写入文件
    helper.file_write(outPath .. fileName, content)

    if removeInFile then
        helper.file_remove(inFile)
    end
end

-- @brief 存档目录清理
local function clearArchiveDirectory(directory)
    local list = {}
    helper.lookup(directory, list, true)

    for k, v in pairs(list) do
        if v.directory then
            helper.rmdir(v.name)
        else
            if helper.file_extension(v.name) ~= "manifest" then
                helper.file_remove(v.name)
            end
        end
    end
end


function doit()
	if not helper.file_exist("config.lua") then
		print("Error:the 'config.lua' does not exist")
        return
	end

    config = require("config")

    -- 主版本号
    config["majorVersion"] = tonumber(config["majorVersion"])
    -- 次版本号
    config["minorVersion"] = tonumber(config["minorVersion"])
    -- 修订号
    config["revisionNumber"] = tonumber(config["revisionNumber"])
    

    if config["revisionNumber"] > REVISION_MAX then
        print(string.format("Configuration error: the revision number exceeds the maximum value of %d", REVISION_MAX))
        return
    end

    -- 输出目录
    local outDir = getOutDir(config["outputDir"], config["majorVersion"], config["minorVersion"], config["revisionNumber"])
    local outAssetsDir = outDir .. "assets/"

    local suc, err = helper.rmdir(outDir)
    if not suc then
        print(string.format("Error:%q", tostring(err)))
        return
    end

    if helper.exists(outDir) then
        print(string.format("Error:Unable to delete directory %q", outDir))
        return
    end
    helper.mkdir(outDir)


    -- 获取目录所有文件列表
    local rootDir  = config["resourceDir"]
    local files    = {}
    helper.lookup_files(rootDir .. "/res/", files, true)
    helper.lookup_files(rootDir .. "/src/", files, true)

    
    local progressBar = helper.Bar.new("")

    -- 加密/处理文件,并将处理好的文件写入 assets 文件夹中缓存
    assets = {}
    for k, v in pairs(files) do
        local fileName = string.sub(v, #rootDir + 2, -1)
        fileName = string.gsub(fileName, "//", "/")

        local extension = helper.file_extension(fileName)
        if extension ~= "manifest" and not igore(config.ignoreFileList, fileName) then
            -- 编译Jit
            if config["useLuaJit"] and extension == "lua" and helper.startWith(fileName, "src/") then
                -- 32位
                helper.compileLua(v, tmpLuaFile, true)
                fileHandling(tmpLuaFile, outAssetsDir, string.gsub(fileName, "^src/", "src32/") .. "c")

                -- 64位
                helper.compileLua(v, tmpLuaFile, false)
                fileHandling(tmpLuaFile, outAssetsDir, string.gsub(fileName, "^src/", "src64/") .. "c")
            else
                fileHandling(v, outAssetsDir, fileName)
            end
        end

        progressBar:updatePercent(k / #files)
    end


    -- 不是散文件模式
    if not config["looseFileMode"] then
        local t = {}
        t.version = config["version"]
        t.assets = assets
        helper.file_write(outDir .. "assets.manifest", helper.toJson(t))

        assets = {}

        -- 遍历当前主版本下的所有子版本清单文件
        local difference = {}
        local minor = 0
        local revision = 0
        repeat
            if minor > config["minorVersion"] then break end

            revision = 0
            repeat
                if minor == config["minorVersion"] and revision == config["revisionNumber"] then break end

                local curDirName = getOutDir(config["outputDir"], config["majorVersion"], minor, revision)
                clearArchiveDirectory(curDirName)

                local assetsFile = curDirName .. "assets.manifest"
                if helper.file_exist(assetsFile) then
                    table.insert(difference, helper.decodeJsonFile(assetsFile))
                else
                    -- break
                    if revision >= REVISION_MAX then break end
                end
                revision = revision + 1
            until(false)

            minor = minor + 1
        until(false)

        -- 生成差异包
        if #difference > 0 then
            print("\n")
            for k, v in pairs(difference) do
                local diffFiles = getDifferenceAssets(v.assets, t.assets)

                if #diffFiles == 0 then
                    -- 这两个版本之间没有任何文件差异,仅仅是版本号不同
                    print(string.format("There is no difference between version %q and version %q, skipping [%d/%d]", v.version, t.version, k, #difference))
                else
                    local diffDirName = outDir .. getDifferenceDirName(v.version, t.version)

                    for _, file in pairs(diffFiles) do
                        local oldFile = outAssetsDir .. file
                        local newFile = diffDirName .. "/" .. file

                        if not helper.file_copy(oldFile, newFile) then
                            error(string.format("Failed to copy file %q to %q", oldFile, newFile))
                        end
                    end

                    -- 压缩文件夹
                    local zipfile = diffDirName .. ".zip"
                    helper.zipDir(diffDirName .. "/*", zipfile)

                    -- 删除源文件夹
                    local ok, err = helper.rmdir(diffDirName)
                    if not ok then print("error", err) end


                    local content  = helper.file_read(zipfile)
                    local fileSize = string.len(content)
                    local key      = getDifferenceDirName(v.version, t.version) .. ".zip"

                    assets[key] = {
                        md5 = helper.md5(content),
                        fileSize = fileSize,
                        compressed = true
                    }

                    print(string.format("Generate variance package: %s [%d/%d]", zipfile, k, #difference))
                end
            end
        end
    end


    -- config 文件需要拷贝到Manifest文件中的key
    local keys = {
        "packageUrl",
        "remoteManifestUrl",
        "strongUpdateVer",
        "strongUpdateURL",
        "strongUpdateDes",
        "updateDescription",
        "restartLevel",
        "looseFileMode",
        "version",
    }
    -- 信息组装
    local projectManifest = {}
    for k,v in pairs(keys) do
        projectManifest[v] = config[v]
    end
    projectManifest["assets"] = assets

    local projectJson = helper.toJson(projectManifest)

    -- 清单文件写入
    helper.file_write(outDir .. "project_dev.manifest", projectJson)
    helper.file_write(rootDir .. "/res/version/project_dev.manifest", projectJson)
    helper.file_write(outAssetsDir .. "/res/version/project_dev.manifest", projectJson)


    -- -- 不是散文件模式,删除 assets 文件夹
    -- if not config["looseFileMode"] then
    --     helper.rmdir(outAssetsDir)
    -- end

    return true
end


if doit() then
    helper.file_remove(tmpLuaFile)
else
    print("Packaging failed")
end

