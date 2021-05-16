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
D[100001] = {100001}
D[100002] = {100002}
D[100003] = {100003}
D[100004] = {100004}
D[100005] = {100005}
D[100006] = {100006}
D[100007] = {100007}
D[100100] = {100100}
D[100101] = {100101}
D[100102] = {100102}
D[100200] = {100200}
D[100201] = {100201}
D[100202] = {100202}
D[100203] = {100203}
D[200000] = {200000}
D[200001] = {200001}
D[200002] = {200002}
D[200100] = {200100}
D[210000] = {210000}
D[210001] = {210001}
D[210002] = {210002}
D[210003] = {210003}
D[210004] = {210004}
D[210005] = {210005}
D[210006] = {210006}
D[210007] = {210007}
D[210008] = {210008}
D[210100] = {210100}
D[210101] = {210101}
D[210102] = {210102}
D[220001] = {220001}
D[220002] = {220002}
D[220003] = {220003}
D[220010] = {220010}
D[220011] = {220011}
D[220012] = {220012}
D[220030] = {220030}
D[220031] = {220031}
D[220032] = {220032}
D[220033] = {220033}
D[220034] = {220034}

local M = {}
M.Data = D
M.length = 63
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