-- @Author : fc
-- @Date   : 2021-10-20 14:17:58
-- @remark : 

require "lfs"

-- cjson
local json = require('cjson')
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




local helper = {}


-- @brief 获取文件后缀
function helper.file_extension(str)  
    return str:match(".+%.(%w+)$")  
end

-- @brief 读取文件
function helper.file_read(fileName)
    local f = assert(io.open(fileName,'rb'))
    local content = f:read("*all")f:close()
    return content
end 

-- @brief 写入文件
function helper.file_write(fileName, content)
    helper.mkdir_path(fileName)

    local  f = assert(io.open(fileName,'wb'))
    f:write(content)
    f:close()
end

-- @brief 获取文件长度
function helper.file_length(fileName)
    local fh = assert(io.open(fileName, "rb"))
    local len = assert(fh:seek("end"))
    fh:close()
    return len
end

-- @brief 拷贝文件
function helper.file_copy(fileName, newFileName)
    if helper.file_exist(fileName) then
        local content = helper.file_read(fileName)
        helper.file_write(newFileName, content)
        return true
    end
    return false
end

-- @brief 判断文件是否存在
function helper.file_exist(fileName)
    local f = io.open(fileName,"rb")
    if f == nil then
        return false
    end
    f:close()
    return true
end

function helper.file_remove(fileName)
    if helper.file_exist(fileName) then
        os.remove(fileName)
    end
end

-- @brief 获取文件md5值
function helper.file_md5(fileName)
    local content = file_read(fileName)
    return md5.sumhexa(content)
end

-- @brief 获取内容md5值
helper.md5 = md5.sumhexa

-- @brief 递归删除目录
function helper.rmdir(rootpath)
    if helper.exists(rootpath) then
        local iters = {}
        helper.lookup(rootpath, iters)

        for i = #iters, 1, -1 do
            local it = iters[i]
            local ok, err

            if it.directory then
                ok, err = lfs.rmdir(it.name)
            else
                ok, err = os.remove(it.name)
            end

            if not ok then
                return ok, ok
            end
        end

        return lfs.rmdir(rootpath)
    end
    return true
end

-- @brief 目录创建
function helper.mkdir(path)
    if not helper.exists(path) then
        return lfs.mkdir(path)
    end
    return true
end

-- @brief 判断目录是否存在
function helper.exists(path)
    local mode = lfs.attributes(path, "mode")
    return mode == 'directory'
end

-- @brief 通过文件路径创建对应的文件夹
function helper.mkdir_path(path)
    path = string.gsub(path, "\\", "/")
    path = string.gsub(path, "//", "/")
    local root = ''
    local count = 0
    repeat
        local cur = string.match(path, "(.-/)")
        if cur == nil then break end

        root = root .. cur
        path = string.sub(path, #cur + 1)
        helper.mkdir(root)
    until(false)
end

-- @brief 
function helper.lookup(rootpath, list)
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
                helper.lookup(path, list)
            end
        end
    end
end

-- @brief 递归获取路径下的所有文件
function helper.lookup_files(rootpath, files)
    local list = {}
    helper.lookup(rootpath, list)

    for k, v in pairs(list) do
        if not v.directory then
            table.insert(files, v.name)
        end
    end
end

function helper.contain(t, value)
    for k, v in pairs(t or {}) do
        if v == value then return true end
    end
    return false
end

function helper.toJson(t)
    -- json serializer
    local prettyJson  = require("pretty.json")

    local content = prettyJson.stringify(t, nil, 4)
    content = string.gsub(content, "\\/", "/")

    return content
end

function helper.decodeJsonFile(file)
    return helper.decodeJson(helper.file_read(file))
end

function helper.decodeJson(content)
    return json.decode(content)
end

function helper.zipDir(dir, zipName)
    -- E:\fc_test\git_pro\7z.exe a -tzip test.zip -r sw E:\fc_test\git_pro\misc\C++
    local exe = lfs.currentdir() .. "/tools/7z.exe"

      -- -bs{o|e|p}{0|1|2} : set output stream for output/error/progress line

    -- 压缩
    -- local cmd = string.format("%s a -tzip %s -r sw %s", exe, zipName, dir)

    -- 压缩后删除相关源文件
    local cmd = string.format("%s a -tzip %s -bso0 -sdel %s", exe, zipName, dir)

    os.execute(cmd)
end

function helper.startWith(str, start)
    return string.sub(str, 1, string.len(start)) == start
end

function helper.getExeDirPath(exe)
    return string.match(exe, "(.*)[/\\].*$")
end

function helper.compileLua(inFile, outFile, isBit32)
    local curdir = lfs.currentdir()

    local exe = curdir .. "/tools/luajit/64bit/luajit-win.exe"
    if isBit32 then
        exe = curdir .. "/tools/luajit/32bit/luajit-win.exe"
    end

    local cmd = string.format("%s -b -g %s %s", exe, inFile, outFile)

    lfs.chdir(helper.getExeDirPath(exe))
    os.execute(cmd)
    lfs.chdir(curdir)
end

---------------------------------------------------------------------------------------------------------------

-- 进度显示
local Bar = {}
Bar.__index = Bar

function Bar.new(...)
    local t = setmetatable({}, Bar)
    t:ctor(...)
    return t
end

function Bar:ctor(suffix)
    self.suffix = suffix or ""
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
    str = str .. timestr .. self.suffix

    io.stdout:write(str)
end

helper.Bar = Bar

return helper
