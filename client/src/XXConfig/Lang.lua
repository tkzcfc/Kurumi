-- Auto Generate by Excel 'language.xlsx', Don't try to modify!

local keyMap = { "cn", "en" }

local keyMapIndex = {}
for k, v in pairs(keyMap) do keyMapIndex[v] = k end

local D = {}
D[11001] = {"bang test\'hahaha\'\n\n","1.0"}
D[11002] = {"cry","1.0"}
D[11003] = {"nu","1.0"}
D[11004] = {"xiao","1.0"}
D[11005] = {"xihuan","1.0"}
D[11006] = {"han","1.0"}
D[11007] = {"yun","1.0"}
D[11008] = {"zzz","1.0"}

local M = {}
M.Data = D
M.length = 8
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