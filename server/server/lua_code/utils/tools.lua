local print = print
local tconcat = table.concat
local tinsert = table.insert
local srep = string.rep
local type = type
local pairs = pairs
local tostring = tostring
local next = next
 
local function print_r(root)
    local cache = {  [root] = "." }
    local function _dump(t,space,name)
        local temp = {}
        for k,v in pairs(t) do
            local key = tostring(k)
            if cache[v] then
                tinsert(temp,"+" .. key .. " {" .. cache[v].."}")
            elseif type(v) == "table" then
                local new_key = name .. "." .. key
                cache[v] = new_key
                tinsert(temp,"+" .. key .. _dump(v,space .. (next(t,k) and "|" or " " ).. srep(" ",#key),new_key))
            else
                tinsert(temp,"+" .. key .. " [" .. tostring(v).."]")
            end
        end
        return tconcat(temp,"\n"..space)
    end
    print(_dump(root, "",""))
end
table.print = print_r

-- 序列化tablle表--將表轉化成string
local function serialize(obj)
    local lua = ""
    local t = type(obj)
    if t == "number" then
        lua = lua .. obj
    elseif t == "boolean" then
        lua = lua .. tostring(obj)
    elseif t == "string" then
        lua = lua .. string.format("%q", obj)
    elseif t == "table" then
        lua = lua .. "{\n"
    for k, v in pairs(obj) do
        lua = lua .. "[" .. serialize(k) .. "]=" .. serialize(v) .. ",\n"
    end
    local metatable = getmetatable(obj)
        if metatable ~= nil and type(metatable.__index) == "table" then
        for k, v in pairs(metatable.__index) do
            lua = lua .. "[" .. serialize(k) .. "]=" .. serialize(v) .. ",\n"
        end
    end
        lua = lua .. "}"
    elseif t == "nil" then
        return nil
    else
        return "-nil-" 
        --error("can not serialize a " .. t .. " type.")
    end
    return lua
end

table.serialize = serialize

-- 反序列化tablle表--將string轉化成table
local function unserialize(lua)
    local t = type(lua)
    if t == "nil" or lua == "" then
        return nil
    elseif t == "number" or t == "string" or t == "boolean" then
        lua = tostring(lua)
    else
        error("can not unserialize a " .. t .. " type.")
    end
    lua = "return " .. lua
    local func = loadstring(lua)
    if func == nil then
        return nil
    end
    return func()
end

table.unserialize = unserialize


----------------------------------------------------NET----------------------------------------------------

function sendMsgToGame(client, msgKey, msg)
	local baseMsg = { msgName = msgKey }
    baseMsg.msgData = protobuf.encode(msgKey, msg)
    local data = protobuf.encode("__msg_base_", baseMsg)
    client:send(data, string.len(data))

    if OPEN_DEBUG then
        print("send msg", msgKey)
        print(json.encode(msg).."\n")
    end
end

function recvMsg(msgdata)
    --print("msgdata len", string.len(msgdata))
    local baseMsg = protobuf.decode("__msg_base_" , msgdata)

    if type(baseMsg) ~= "table" 
    or baseMsg.msgName == nil 
    or baseMsg.msgData == nil then
        print("net : data is wrongful!!!")
        return "data is wrongful!!!"
    end 
    local msg = protobuf.decode(baseMsg.msgName, baseMsg.msgData)

    if OPEN_DEBUG then
        print("recv msg", baseMsg.msgName)
        print(json.encode(msg).."\n")
    end

    return baseMsg.msgName, msg
end

