-- @Author : fc
-- @Date   : 2022-06-15 20:47:51
-- @remark : 
-- @URL    : https://github.com/starwing/lua-protobuf

local pb = require "luapb"

local PBLoader = class("PBLoader")

-- @brief pb初始化
function PBLoader:initialize()
    local pblist = require("pb.pblist")

    -- pb文件加载
    for _, filename in pairs(pblist) do
        local data = cc.FileUtils:getInstance():getDataFromFile("pb/" .. filename)
        local ok, err = pb.load(data)
        if not ok then
            print(string.format("load pb(%s), error: %s\n", filename, tostring(err)))
        end
    end

    self.msgIdMap = {}
    self.idMsgMap = {}

    -- 消息ID和消息名称映射
    for name, basename, type in pb.types() do
        if type == "enum" and basename == "MsgId" then
            local id = pb.enum(name, "Id")
            if id then
            	local msgName = string.sub(name, 2, -7)
            	self.msgIdMap[msgName] = id
            	self.idMsgMap[id] = msgName
            end
        end

        -- if name == ".err.Code" then
        --     print(name, basename, type)
        -- end
    end


    local meta = {
        __index = function(_, key)
            return pb.enum(".err.Code", key)
        end
    }
    global.errCode = setmetatable({}, meta)
end

-- @brief 通过消息名称获取消息ID
function PBLoader:getMsgName(id)
	return self.idMsgMap[id]
end

-- @brief 通过id获取消息名称
function PBLoader:getMsgId(name)
	return self.msgIdMap[name]
end

return PBLoader
