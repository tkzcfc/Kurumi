require "lfs"

-- xxtea
local xxtea = require("xxtea")
-- md5
local md5 = require("md5.core")
function md5.sumhexa (k)
  k = md5.sum(k)
  return (string.gsub(k, ".", function (c)
           return string.format("%02x", string.byte(c))
         end))
end

-- @brief 获取文件后缀
local function file_extension(str)  
    return str:match(".+%.(%w+)$")  
end

-- @brief 读取文件
local function file_read(fileName)
    local f = assert(io.open(fileName,'rb'))
    local content = f:read("*all")f:close()
    return content
end 

-- @brief 写入文件
local function file_write(fileName, content)
    local  f = assert(io.open(fileName,'wb'))
    f:write(content)
    f:close()
end

-- @brief 获取文件长度
local function file_length(filename)
  local fh = assert(io.open(filename, "rb"))
  local len = assert(fh:seek("end"))
  fh:close()
  return len
end

-- @brief 判断文件是否存在
local function file_exist(filename)
	local f = io.open(filename,"rb")
	if f == nil then
		return false
	end
	f:close()
	return true
end

-- @brief 获取文件md5值
local function file_md5(filename)
    local fileContent = file_read(filename)
    return md5.sumhexa(fileContent)
end

-- @brief 删除目录
function os.rmdir(path)
    if os.exists(path) then
        local function _rmdir(path)
            local iter, dir_obj = lfs.dir(path)
            while true do
                local dir = iter(dir_obj)
                if dir == nil then break end
                if dir ~= "." and dir ~= ".." then
                    local curDir = path..dir
                    local mode = lfs.attributes(curDir, "mode") 
                    if mode == "directory" then
                        local suc, err = _rmdir(curDir.."/")
                        if not suc then return false, err end
                    elseif mode == "file" then
                        local suc, err = os.remove(curDir)
                        if not suc then return false, err end
                    end
                end
            end
            return lfs.rmdir(path)
        end
        return _rmdir(path)
    end
    return true
end

-- @brief 目录创建
function os.mkdir(path)
    if not os.exists(path) then
        return lfs.mkdir(path)
    end
    return true
end

-- @brief 判断目录是否存在
function os.exists(path)
    local mode = lfs.attributes(path, "mode")
    return mode == 'directory'
end

-- @brief 通过文件路径创建对应的文件夹
local function mkdir_path(path)
    path = string.gsub(path, "\\", "/")
    path = string.gsub(path, "//", "/")
    local root = ''
    local count = 0
    repeat
        local cur = string.match(path, "(.-/)")
        if cur == nil then break end

        root = root .. cur
        path = string.sub(path, #cur + 1)
        os.mkdir(root)
    until(false)
end


--------------------------------------------------------------------------
-- 进度显示
local Bar = {}
Bar.__index = Bar

function Bar.new()
    local t = setmetatable({}, Bar)
    t:ctor()
    return t
end

function Bar:ctor()
    self.totalCount = 20
    self.startTime = os.time()
    self:updatePercent(0)
end

-- @brief 更新进度
function Bar:updatePercent(percent)
    if percent > 1 then percent = 1 end

    local count = math.floor(percent * self.totalCount)
    local fmt = "\r%.f%%[%s%s]"
    local str = string.format(fmt, percent * 100, string.rep("#", count), string.rep(" ", self.totalCount - count))

    local diff = (24-8)*60*60
    local timestr = os.date("  %H:%M:%S", os.difftime(os.time(), self.startTime) + diff )
    str = str .. timestr

    io.stdout:write(str)
end


--------------------------------------------------------------------------

local filesTab = {}
function lookup(rootpath)  
    for entry in lfs.dir(rootpath) do  
        if entry ~= '.' and entry ~= '..' then  
            local path = rootpath .. '/' .. entry  
            local attr = lfs.attributes(path)
            if attr.mode ~= 'directory' then
                if attr.mode == "file" then
                    table.insert(filesTab, path)
                end
            else
                lookup(path)  
            end  
        end  
    end  
end

function doit()
	if not file_exist("config.lua") then
		print("Error：the 'config.lua' does not exist")
        return
	end

    local config = require("config")

    -- 加密用到的sign
    local encryptsign = config["encryptsign"]

    -- 加密用到的key
    local encryptkey = config["encryptkey"]

    -- 输出目录
    local version = config["version"]
    local outDir = "v_" .. string.gsub(version, "%.", "_") .. "/"
    
    local suc, err = os.rmdir(outDir)
    if not suc then
        print(string.format("Error：%q", tostring(err)))
        return
    end

    if os.exists(outDir) then
        print(string.format("Error：Unable to delete directory %q", outDir))
        return
    end
    os.mkdir(outDir)
    
    -- 需要解压的压缩文件列表
    local compressedFileList = config["compressedFileList"] or {}
    local function isCompressedFileList(filename)
        for k,v in pairs(compressedFileList) do
            if v == filename then
                return true
            end
        end
        return false
    end
    
    -- 忽略文件列表
    local ignoreFileList = config["ignoreFileList"] or {}
    local function isIgnoreFileList(filename)
        for k,v in pairs(ignoreFileList) do
            if v == filename then
                return true
            end
        end
        return false
    end

    -- 获取目录所有文件列表
    local rootDir = config["resourceDir"]
    -- print("lookup:", rootDir .. "/res/")
    lookup(rootDir .. "/res/")
    -- print("lookup:", rootDir .. "/src/")
    lookup(rootDir .. "/src/")
    
    local progressBar = Bar.new()
    
    -- 加密并计算文件MD5值
    local assetsTab = {}
    for k,v in pairs(filesTab) do
        local filename = string.sub(v, #rootDir + 2, -1)
		filename = string.gsub(filename, "//", "/")

        local extension = file_extension(filename)
        if extension ~= "manifest" and not isIgnoreFileList(filename) then
            local info = {}
            if extension == "lua" then
                local fcontent = file_read(v)
                -- 加密
                local data, len = xxtea.encode(fcontent, encryptkey)
                data = encryptsign .. data
                len = len + string.len(encryptsign)
    
                -- 计算md5值
                info["md5"] = md5.sumhexa(data)
                info["fileSize"] = len
    
                -- 写入文件
                mkdir_path(outDir .. filename)
                file_write(outDir .. filename, data)
            else
                local fcontent = file_read(v)

                -- 计算md5值
                info["md5"] = md5.sumhexa(fcontent)
                info["fileSize"] = string.len(fcontent)
    
                -- 写入文件
                mkdir_path(outDir .. filename)
                file_write(outDir .. filename, fcontent)
            end

			if extension == "zip" and isCompressedFileList(filename) then
				info["compressed"] = true
			end
            assetsTab[filename] = info
        end
        progressBar:updatePercent(k / #filesTab)
    end
    
    -- config 文件需要拷贝到Manifest文件中的key
    local keys = {
        "packageUrl",
        "remoteManifestUrl",
        "remoteVersionUrl",
        "version",
        "engineVersion",
        "searchPaths",
        "strongUpdateVer",
        "strongUpdateURL",
        "strongUpdateDes",
        "updateDescription",
        "restartLevel",
    }
    -- 信息组装
    local projectManifest = {}
    local versionManifest = {}
    for k,v in pairs(keys) do
        projectManifest[v] = config[v]
        versionManifest[v] = config[v]
    end
    projectManifest["assets"] = assetsTab
    
    -- json serializer
    local prettyJson  = require("pretty.json")

    local projectJson = prettyJson.stringify(projectManifest, nil, 4)
    local versionJson = prettyJson.stringify(versionManifest, nil, 4)

    projectJson = string.gsub(projectJson, "\\/", "/")
    versionJson = string.gsub(versionJson, "\\/", "/")

    -- 清单文件写入
    file_write(outDir .. "project_dev.manifest", projectJson)
    file_write(outDir .. "version_dev.manifest", versionJson)

    local manifestpath = rootDir .. "/res/version/project_dev.manifest"
    mkdir_path(manifestpath)
    file_write(manifestpath, projectJson)

    manifestpath = rootDir .. "/res/version/version_dev.manifest"
    mkdir_path(manifestpath)
    file_write(manifestpath, versionJson)
end

doit()
