-- Auto Generate by Excel 'Error.xlsx', Don't try to modify!

local keyMap = { "Lang" }

local keyMapIndex = {}
for k, v in pairs(keyMap) do keyMapIndex[v] = k end

local D = {}
D[1] = {20001}
D[2] = {20002}
D[100] = {20100}
D[101] = {20101}
D[102] = {20102}
D[103] = {20103}
D[104] = {20104}
D[105] = {20105}
D[106] = {20106}
D[107] = {20107}
D[108] = {20108}
D[109] = {20109}
D[110] = {20110}
D[111] = {20111}
D[112] = {20112}
D[113] = {20113}
D[114] = {20114}
D[115] = {20115}
D[116] = {20116}
D[117] = {20117}
D[118] = {20118}
D[119] = {20119}

local M = {}
M.Data = D
M.length = 22
M.keyMapIndex = keyMapIndex
M.keyMap = keyMap

local meta = {
    __index = function(tab, key) return rawget(tab, keyMapIndex[key]) end
}
for k, v in pairs(M.Data) do setmetatable(v, meta) end

function M.getData(Id)
    local data = M.Data[Id]
    if not data then return end
    local t = {}
    for k, v in pairs(keyMapIndex) do t[k] = data[v] end
    return t
end

function M.getItem(Id, Key)
    local data = M.Data[Id]
    if data then return data[Key] end
    return nil
end

function M.getAllData()
    local dataList = {}
    for id, data in pairs(M.Data) do
        local t = {}
        for k, v in pairs(keyMapIndex) do t[k] = data[v] end
        dataList[k] = t
    end
    return dataList
end

return M