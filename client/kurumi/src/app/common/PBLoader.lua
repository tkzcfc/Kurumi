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
    end

    self:test()
end

-- @brief 通过消息名称获取消息ID
function PBLoader:getMsgName(id)
	return self.idMsgMap[id]
end

-- @brief 通过id获取消息名称
function PBLoader:getMsgId(name)
	return self.msgIdMap[name]
end


function PBLoader:test()

    -- 消息编码
    local binary = pb.encode("PB.Other_Support.LobbyConn", {
        serviceId = 123456789,
    })
    print(pb.tohex(binary))


    -- 消息解码
    local msg, err = pb.decode("PB.Other_Support.LobbyConn", binary)

    if not msg then
        logE("decode msg error:", err)
        return
    end

    dump(msg)


    local msgName = self:getMsgName(2000000)
    print("msg name:", msgName)
    print("msg id:", self:getMsgId(msgName))
end

return PBLoader
