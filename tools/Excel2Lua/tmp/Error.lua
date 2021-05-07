-- Auto Generate by Excel 'Error.xlsx', Don't try to modify!

local M = {}

M.Data = {}
M.Data[1] = {Lang = 20001}
M.Data[2] = {Lang = 20002}
M.Data[100] = {Lang = 20100}
M.Data[101] = {Lang = 20101}
M.Data[102] = {Lang = 20102}
M.Data[103] = {Lang = 20103}
M.Data[104] = {Lang = 20104}
M.Data[105] = {Lang = 20105}
M.Data[106] = {Lang = 20106}
M.Data[107] = {Lang = 20107}
M.Data[108] = {Lang = 20108}
M.Data[109] = {Lang = 20109}
M.Data[110] = {Lang = 20110}
M.Data[111] = {Lang = 20111}
M.Data[112] = {Lang = 20112}
M.Data[113] = {Lang = 20113}
M.Data[114] = {Lang = 20114}
M.Data[115] = {Lang = 20115}
M.Data[116] = {Lang = 20116}
M.Data[117] = {Lang = 20117}
M.Data[118] = {Lang = 20118}
M.Data[119] = {Lang = 20119}
M.length = 22

function M.getData(key)
    return M.Data[key]
end

function M.getItem(key1, key2)
    if M.Data[key1] == nil then
        print(string.format("错误: 文件'Error.lua'中配置'%s'不存在!!!!!!!!!!!!!!!!!!!!!!!", tostring(key1)))
        return
    end
    return M.Data[key1][key2]
end

function M.getAllData()
    return M.Data
end

return M
