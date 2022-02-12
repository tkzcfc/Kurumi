-- Auto Generate by Excel 'Emoji.xlsx', Don't try to modify!

local keyMap = { "Color", "Emoji", "First", "Last", "Time" }

local keyMapIndex = {}
for k, v in pairs(keyMap) do keyMapIndex[v] = k end

local D = {}
D[1] = {{255,255,0,100},"bang test\'hahaha\'\n\n",1,4,0.32}
D[2] = {{255,255,0,100},"cry",1,16,1.28}
D[3] = {{255,255,0,100},"nu",1,2,0.16}
D[4] = {{255,255,0,100},"xiao",1,4,0.32}
D[5] = {{255,255,0,100},"xihuan",1,4,0.32}
D[6] = {{255,255,0,100},"han",1,9,0.72}
D[7] = {{255,255,0,100},"yun",1,6,0.48}
D[8] = {{255,255,0,100},"zzz",1,10,0.8}

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