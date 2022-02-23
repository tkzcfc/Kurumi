-- Auto Generate by Excel 'RoleSkin.xlsx', Don't try to modify!

local keyMap = { "HeadImg", "Occupation", "PvpImg", "SpineFile" }

local keyMapIndex = {}
for k, v in pairs(keyMap) do keyMapIndex[v] = k end

local D = {}
D[1] = {"",1,"","role/baiji/hero_shizxianzi_dao.ExportJson"}
D[2] = {"",2,"","role/baiji/hero_shizmaonv_dao.ExportJson"}
D[3] = {"",1,"","role/baiji/hero_shizshenyin_gj.ExportJson"}
D[4] = {"",2,"","role/baiji/hero_shizmaonv_gj.ExportJson"}
D[5] = {"",1,"","role/baiji/hero_shizwushikaijia_gj.ExportJson"}
D[6] = {"",2,"","role/baiji/hero_shiznvpu_gj.ExportJson"}
D[7] = {"",1,"","role/baiji/hero_lanse_gj.ExportJson"}
D[8] = {"",2,"","role/baiji/hero_luocha_dao.ExportJson"}
D[9] = {"",1,"","role/baiji/hero_shizhuak_dao.ExportJson"}
D[10] = {"",2,"","role/baiji/hero_xiuluo_dao.ExportJson"}
D[11] = {"",1,"","role/baiji/hero_shizconglin_gj.ExportJson"}
D[12] = {"",2,"","role/baiji/hero_shizconglin_dao.ExportJson"}
D[13] = {"",1,"","role/baiji/hero_shizhuak_gj.ExportJson"}
D[14] = {"",2,"","role/baiji/hero_baiji_dao.ExportJson"}
D[15] = {"",1,"","role/baiji/hero_shiznvpu_dao.ExportJson"}
D[16] = {"",2,"","role/baiji/hero_luocha_gj.ExportJson"}
D[17] = {"",1,"","role/baiji/hero_shizwushikaijia_dao.ExportJson"}
D[18] = {"",2,"","role/baiji/hero_baiji_gj.ExportJson"}
D[19] = {"",1,"","role/baiji/hero_xiuluo_gj.ExportJson"}
D[20] = {"",2,"","role/baiji/hero_shizxianzi_gj.ExportJson"}
D[21] = {"",1,"","role/baiji/hero_lanse_dao.ExportJson"}
D[22] = {"",2,"","role/baiji/hero_shizshenyin_dao.ExportJson"}
D[23] = {"",1,"","role/baiji/hero_shizshuishoufu_dao.ExportJson"}
D[24] = {"",2,"","role/baiji/hero_shizshuishoufu_gj.ExportJson"}

local M = {}
M.Data = D
M.length = 24
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