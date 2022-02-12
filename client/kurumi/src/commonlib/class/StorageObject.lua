-- @Author : fc
-- @Date   : 2021-11-10 16:34:03
-- @remark : 自动存储对象

local type = type
local fileUtils = cc.FileUtils:getInstance()
local scheduler = cc.Director:getInstance():getScheduler()
local scriptEntryID = nil
local task = {}

--------------------------------------------------- functions ---------------------------------------------------

local function writeEx(filePath, data)
    local content = json.encode(data)
    fileUtils:writeStringToFile(content, filePath)
end

local function doWrite()
    if scriptEntryID == nil then return end
    scheduler:unscheduleScriptEntry(scriptEntryID)
    scriptEntryID = nil

    for k, v in pairs(task) do
        writeEx(k, v)
    end
    task = {}
end

-- @brief 文件写入
local function write(filePath, data)
    task[filePath] = data

    if scriptEntryID == nil then
        scriptEntryID = scheduler:scheduleScriptFunc(doWrite, 1, false)
    end
end

-- @brief 文件读取
local function read(filePath)
    if fileUtils:isFileExist(filePath) then
        local data = fileUtils:getStringFromFile(filePath)
        return json.decode(data) or {}
    end
    return {}
end


--------------------------------------------------- StorageObject ---------------------------------------------------

-- @brief 
local StorageObject = {}


StorageObject.__index = function(this, key)
    return this.map_key_value[key]
end

StorageObject.__newindex = function(this, key, value)
    if this.map_key_value[key] == value then return end
    this.map_key_value[key] = value
    write(this.filePath, this.map_key_value)
end

StorageObject.new = function(filePath)
    if not fileUtils:isAbsolutePath(filePath) then        
        local writablePath = fileUtils:getWritablePath() .. "storage/"
        if not fileUtils:isDirectoryExist(writablePath) then
            fileUtils:createDirectory(writablePath)
        end
        filePath = writablePath .. filePath
    end

    local t = {}
    t.map_key_value = read(filePath)
    t.filePath = filePath
    t.setDefault = StorageObject.setDefault
    t.flush = StorageObject.flush
    setmetatable(t, StorageObject)
    return t
end

StorageObject.setDefault = function(this, key, value)
    assert(key ~= nil)

    local cur = this[key]
    if cur == nil then
        this[key] = value
    else
        if type(cur) ~= type(value) then
            this[key] = value
        end
    end
end

StorageObject.flush = function()
    doWrite()
end

return StorageObject