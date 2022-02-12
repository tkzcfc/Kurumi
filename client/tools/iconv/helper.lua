-- @Author : fc
-- @Date   : 2021-10-20 14:17:58
-- @remark : 

require "lfs"


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

-- @brief 删除文件
function helper.remove_file(fileName)
    if helper.file_exist(fileName) then
        return os.remove(fileName)
    end
    return true
end

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

return helper